<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/dma-mapping.h>
#समावेश "ahb.h"
#समावेश "debug.h"
#समावेश "hif.h"
#समावेश <linux/remoteproc.h>

अटल स्थिर काष्ठा of_device_id ath11k_ahb_of_match[] = अणु
	/* TODO: Should we change the compatible string to something similar
	 * to one that ath10k uses?
	 */
	अणु .compatible = "qcom,ipq8074-wifi",
	  .data = (व्योम *)ATH11K_HW_IPQ8074,
	पूर्ण,
	अणु .compatible = "qcom,ipq6018-wifi",
	  .data = (व्योम *)ATH11K_HW_IPQ6018_HW10,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ath11k_ahb_of_match);

अटल स्थिर काष्ठा ath11k_bus_params ath11k_ahb_bus_params = अणु
	.mhi_support = false,
	.m3_fw_support = false,
	.fixed_bdf_addr = true,
	.fixed_mem_region = true,
पूर्ण;

#घोषणा ATH11K_IRQ_CE0_OFFSET 4

अटल स्थिर अक्षर *irq_name[ATH11K_IRQ_NUM_MAX] = अणु
	"misc-pulse1",
	"misc-latch",
	"sw-exception",
	"watchdog",
	"ce0",
	"ce1",
	"ce2",
	"ce3",
	"ce4",
	"ce5",
	"ce6",
	"ce7",
	"ce8",
	"ce9",
	"ce10",
	"ce11",
	"host2wbm-desc-feed",
	"host2reo-re-injection",
	"host2reo-command",
	"host2rxdma-monitor-ring3",
	"host2rxdma-monitor-ring2",
	"host2rxdma-monitor-ring1",
	"reo2ost-exception",
	"wbm2host-rx-release",
	"reo2host-status",
	"reo2host-destination-ring4",
	"reo2host-destination-ring3",
	"reo2host-destination-ring2",
	"reo2host-destination-ring1",
	"rxdma2host-monitor-destination-mac3",
	"rxdma2host-monitor-destination-mac2",
	"rxdma2host-monitor-destination-mac1",
	"ppdu-end-interrupts-mac3",
	"ppdu-end-interrupts-mac2",
	"ppdu-end-interrupts-mac1",
	"rxdma2host-monitor-status-ring-mac3",
	"rxdma2host-monitor-status-ring-mac2",
	"rxdma2host-monitor-status-ring-mac1",
	"host2rxdma-host-buf-ring-mac3",
	"host2rxdma-host-buf-ring-mac2",
	"host2rxdma-host-buf-ring-mac1",
	"rxdma2host-destination-ring-mac3",
	"rxdma2host-destination-ring-mac2",
	"rxdma2host-destination-ring-mac1",
	"host2tcl-input-ring4",
	"host2tcl-input-ring3",
	"host2tcl-input-ring2",
	"host2tcl-input-ring1",
	"wbm2host-tx-completions-ring3",
	"wbm2host-tx-completions-ring2",
	"wbm2host-tx-completions-ring1",
	"tcl2host-status-ring",
पूर्ण;

/* क्रमागत ext_irq_num - irq numbers that can be used by बाह्यal modules
 * like datapath
 */
क्रमागत ext_irq_num अणु
	host2wbm_desc_feed = 16,
	host2reo_re_injection,
	host2reo_command,
	host2rxdma_monitor_ring3,
	host2rxdma_monitor_ring2,
	host2rxdma_monitor_ring1,
	reo2host_exception,
	wbm2host_rx_release,
	reo2host_status,
	reo2host_destination_ring4,
	reo2host_destination_ring3,
	reo2host_destination_ring2,
	reo2host_destination_ring1,
	rxdma2host_monitor_destination_mac3,
	rxdma2host_monitor_destination_mac2,
	rxdma2host_monitor_destination_mac1,
	ppdu_end_पूर्णांकerrupts_mac3,
	ppdu_end_पूर्णांकerrupts_mac2,
	ppdu_end_पूर्णांकerrupts_mac1,
	rxdma2host_monitor_status_ring_mac3,
	rxdma2host_monitor_status_ring_mac2,
	rxdma2host_monitor_status_ring_mac1,
	host2rxdma_host_buf_ring_mac3,
	host2rxdma_host_buf_ring_mac2,
	host2rxdma_host_buf_ring_mac1,
	rxdma2host_destination_ring_mac3,
	rxdma2host_destination_ring_mac2,
	rxdma2host_destination_ring_mac1,
	host2tcl_input_ring4,
	host2tcl_input_ring3,
	host2tcl_input_ring2,
	host2tcl_input_ring1,
	wbm2host_tx_completions_ring3,
	wbm2host_tx_completions_ring2,
	wbm2host_tx_completions_ring1,
	tcl2host_status_ring,
पूर्ण;

अटल अंतरभूत u32 ath11k_ahb_पढ़ो32(काष्ठा ath11k_base *ab, u32 offset)
अणु
	वापस ioपढ़ो32(ab->mem + offset);
पूर्ण

अटल अंतरभूत व्योम ath11k_ahb_ग_लिखो32(काष्ठा ath11k_base *ab, u32 offset, u32 value)
अणु
	ioग_लिखो32(value, ab->mem + offset);
पूर्ण

अटल व्योम ath11k_ahb_समाप्त_tasklets(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		काष्ठा ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		tasklet_समाप्त(&ce_pipe->पूर्णांकr_tq);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ext_grp_disable(काष्ठा ath11k_ext_irq_grp *irq_grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < irq_grp->num_irq; i++)
		disable_irq_nosync(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
पूर्ण

अटल व्योम __ath11k_ahb_ext_irq_disable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		ath11k_ahb_ext_grp_disable(irq_grp);

		napi_synchronize(&irq_grp->napi);
		napi_disable(&irq_grp->napi);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ext_grp_enable(काष्ठा ath11k_ext_irq_grp *irq_grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < irq_grp->num_irq; i++)
		enable_irq(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
पूर्ण

अटल व्योम ath11k_ahb_setbit32(काष्ठा ath11k_base *ab, u8 bit, u32 offset)
अणु
	u32 val;

	val = ath11k_ahb_पढ़ो32(ab, offset);
	ath11k_ahb_ग_लिखो32(ab, offset, val | BIT(bit));
पूर्ण

अटल व्योम ath11k_ahb_clearbit32(काष्ठा ath11k_base *ab, u8 bit, u32 offset)
अणु
	u32 val;

	val = ath11k_ahb_पढ़ो32(ab, offset);
	ath11k_ahb_ग_लिखो32(ab, offset, val & ~BIT(bit));
पूर्ण

अटल व्योम ath11k_ahb_ce_irq_enable(काष्ठा ath11k_base *ab, u16 ce_id)
अणु
	स्थिर काष्ठा ce_pipe_config *ce_config;

	ce_config = &ab->hw_params.target_ce_config[ce_id];
	अगर (__le32_to_cpu(ce_config->pipedir) & PIPEसूची_OUT)
		ath11k_ahb_setbit32(ab, ce_id, CE_HOST_IE_ADDRESS);

	अगर (__le32_to_cpu(ce_config->pipedir) & PIPEसूची_IN) अणु
		ath11k_ahb_setbit32(ab, ce_id, CE_HOST_IE_2_ADDRESS);
		ath11k_ahb_setbit32(ab, ce_id + CE_HOST_IE_3_SHIFT,
				    CE_HOST_IE_3_ADDRESS);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ce_irq_disable(काष्ठा ath11k_base *ab, u16 ce_id)
अणु
	स्थिर काष्ठा ce_pipe_config *ce_config;

	ce_config = &ab->hw_params.target_ce_config[ce_id];
	अगर (__le32_to_cpu(ce_config->pipedir) & PIPEसूची_OUT)
		ath11k_ahb_clearbit32(ab, ce_id, CE_HOST_IE_ADDRESS);

	अगर (__le32_to_cpu(ce_config->pipedir) & PIPEसूची_IN) अणु
		ath11k_ahb_clearbit32(ab, ce_id, CE_HOST_IE_2_ADDRESS);
		ath11k_ahb_clearbit32(ab, ce_id + CE_HOST_IE_3_SHIFT,
				      CE_HOST_IE_3_ADDRESS);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_sync_ce_irqs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;
	पूर्णांक irq_idx;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;
		synchronize_irq(ab->irq_num[irq_idx]);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_sync_ext_irqs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, j;
	पूर्णांक irq_idx;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		क्रम (j = 0; j < irq_grp->num_irq; j++) अणु
			irq_idx = irq_grp->irqs[j];
			synchronize_irq(ab->irq_num[irq_idx]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ce_irqs_enable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		ath11k_ahb_ce_irq_enable(ab, i);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ce_irqs_disable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		ath11k_ahb_ce_irq_disable(ab, i);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_ahb_start(काष्ठा ath11k_base *ab)
अणु
	ath11k_ahb_ce_irqs_enable(ab);
	ath11k_ce_rx_post_buf(ab);

	वापस 0;
पूर्ण

अटल व्योम ath11k_ahb_ext_irq_enable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		napi_enable(&irq_grp->napi);
		ath11k_ahb_ext_grp_enable(irq_grp);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_ext_irq_disable(काष्ठा ath11k_base *ab)
अणु
	__ath11k_ahb_ext_irq_disable(ab);
	ath11k_ahb_sync_ext_irqs(ab);
पूर्ण

अटल व्योम ath11k_ahb_stop(काष्ठा ath11k_base *ab)
अणु
	अगर (!test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags))
		ath11k_ahb_ce_irqs_disable(ab);
	ath11k_ahb_sync_ce_irqs(ab);
	ath11k_ahb_समाप्त_tasklets(ab);
	del_समयr_sync(&ab->rx_replenish_retry);
	ath11k_ce_cleanup_pipes(ab);
पूर्ण

अटल पूर्णांक ath11k_ahb_घातer_up(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ahb *ab_ahb = ath11k_ahb_priv(ab);
	पूर्णांक ret;

	ret = rproc_boot(ab_ahb->tgt_rproc);
	अगर (ret)
		ath11k_err(ab, "failed to boot the remote processor Q6\n");

	वापस ret;
पूर्ण

अटल व्योम ath11k_ahb_घातer_करोwn(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ahb *ab_ahb = ath11k_ahb_priv(ab);

	rproc_shutकरोwn(ab_ahb->tgt_rproc);
पूर्ण

अटल पूर्णांक ath11k_ahb_fwreset_from_cold_boot(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक समयout;

	अगर (ath11k_cold_boot_cal == 0 || ab->qmi.cal_करोne ||
	    ab->hw_params.cold_boot_calib == 0)
		वापस 0;

	ath11k_dbg(ab, ATH11K_DBG_AHB, "wait for cold boot done\n");
	समयout = रुको_event_समयout(ab->qmi.cold_boot_रुकोq,
				     (ab->qmi.cal_करोne  == 1),
				     ATH11K_COLD_BOOT_FW_RESET_DELAY);
	अगर (समयout <= 0) अणु
		ath11k_cold_boot_cal = 0;
		ath11k_warn(ab, "Coldboot Calibration failed timed out\n");
	पूर्ण

	/* reset the firmware */
	ath11k_ahb_घातer_करोwn(ab);
	ath11k_ahb_घातer_up(ab);

	ath11k_dbg(ab, ATH11K_DBG_AHB, "exited from cold boot mode\n");
	वापस 0;
पूर्ण

अटल व्योम ath11k_ahb_init_qmi_ce_config(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce_len = ab->hw_params.target_ce_count;
	cfg->tgt_ce = ab->hw_params.target_ce_config;
	cfg->svc_to_ce_map_len = ab->hw_params.svc_to_ce_map_len;
	cfg->svc_to_ce_map = ab->hw_params.svc_to_ce_map;
	ab->qmi.service_ins_id = ab->hw_params.qmi_service_ins_id;
पूर्ण

अटल व्योम ath11k_ahb_मुक्त_ext_irq(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		क्रम (j = 0; j < irq_grp->num_irq; j++)
			मुक्त_irq(ab->irq_num[irq_grp->irqs[j]], irq_grp);
	पूर्ण
पूर्ण

अटल व्योम ath11k_ahb_मुक्त_irq(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक irq_idx;
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;
		मुक्त_irq(ab->irq_num[irq_idx], &ab->ce.ce_pipe[i]);
	पूर्ण

	ath11k_ahb_मुक्त_ext_irq(ab);
पूर्ण

अटल व्योम ath11k_ahb_ce_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath11k_ce_pipe *ce_pipe = from_tasklet(ce_pipe, t, पूर्णांकr_tq);

	ath11k_ce_per_engine_service(ce_pipe->ab, ce_pipe->pipe_num);

	ath11k_ahb_ce_irq_enable(ce_pipe->ab, ce_pipe->pipe_num);
पूर्ण

अटल irqवापस_t ath11k_ahb_ce_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath11k_ce_pipe *ce_pipe = arg;

	/* last पूर्णांकerrupt received क्रम this CE */
	ce_pipe->बारtamp = jअगरfies;

	ath11k_ahb_ce_irq_disable(ce_pipe->ab, ce_pipe->pipe_num);

	tasklet_schedule(&ce_pipe->पूर्णांकr_tq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath11k_ahb_ext_grp_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k_ext_irq_grp *irq_grp = container_of(napi,
						काष्ठा ath11k_ext_irq_grp,
						napi);
	काष्ठा ath11k_base *ab = irq_grp->ab;
	पूर्णांक work_करोne;

	work_करोne = ath11k_dp_service_srng(ab, irq_grp, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		ath11k_ahb_ext_grp_enable(irq_grp);
	पूर्ण

	अगर (work_करोne > budget)
		work_करोne = budget;

	वापस work_करोne;
पूर्ण

अटल irqवापस_t ath11k_ahb_ext_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath11k_ext_irq_grp *irq_grp = arg;

	/* last पूर्णांकerrupt received क्रम this group */
	irq_grp->बारtamp = jअगरfies;

	ath11k_ahb_ext_grp_disable(irq_grp);

	napi_schedule(&irq_grp->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath11k_ahb_ext_irq_config(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_hw_params *hw = &ab->hw_params;
	पूर्णांक i, j;
	पूर्णांक irq;
	पूर्णांक ret;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];
		u32 num_irq = 0;

		irq_grp->ab = ab;
		irq_grp->grp_id = i;
		init_dummy_netdev(&irq_grp->napi_ndev);
		netअगर_napi_add(&irq_grp->napi_ndev, &irq_grp->napi,
			       ath11k_ahb_ext_grp_napi_poll, NAPI_POLL_WEIGHT);

		क्रम (j = 0; j < ATH11K_EXT_IRQ_NUM_MAX; j++) अणु
			अगर (ab->hw_params.ring_mask->tx[i] & BIT(j)) अणु
				irq_grp->irqs[num_irq++] =
					wbm2host_tx_completions_ring1 - j;
			पूर्ण

			अगर (ab->hw_params.ring_mask->rx[i] & BIT(j)) अणु
				irq_grp->irqs[num_irq++] =
					reo2host_destination_ring1 - j;
			पूर्ण

			अगर (ab->hw_params.ring_mask->rx_err[i] & BIT(j))
				irq_grp->irqs[num_irq++] = reo2host_exception;

			अगर (ab->hw_params.ring_mask->rx_wbm_rel[i] & BIT(j))
				irq_grp->irqs[num_irq++] = wbm2host_rx_release;

			अगर (ab->hw_params.ring_mask->reo_status[i] & BIT(j))
				irq_grp->irqs[num_irq++] = reo2host_status;

			अगर (j < ab->hw_params.max_radios) अणु
				अगर (ab->hw_params.ring_mask->rxdma2host[i] & BIT(j)) अणु
					irq_grp->irqs[num_irq++] =
						rxdma2host_destination_ring_mac1 -
						ath11k_hw_get_mac_from_pdev_id(hw, j);
				पूर्ण

				अगर (ab->hw_params.ring_mask->host2rxdma[i] & BIT(j)) अणु
					irq_grp->irqs[num_irq++] =
						host2rxdma_host_buf_ring_mac1 -
						ath11k_hw_get_mac_from_pdev_id(hw, j);
				पूर्ण

				अगर (ab->hw_params.ring_mask->rx_mon_status[i] & BIT(j)) अणु
					irq_grp->irqs[num_irq++] =
						ppdu_end_पूर्णांकerrupts_mac1 -
						ath11k_hw_get_mac_from_pdev_id(hw, j);
					irq_grp->irqs[num_irq++] =
						rxdma2host_monitor_status_ring_mac1 -
						ath11k_hw_get_mac_from_pdev_id(hw, j);
				पूर्ण
			पूर्ण
		पूर्ण
		irq_grp->num_irq = num_irq;

		क्रम (j = 0; j < irq_grp->num_irq; j++) अणु
			पूर्णांक irq_idx = irq_grp->irqs[j];

			irq = platक्रमm_get_irq_byname(ab->pdev,
						      irq_name[irq_idx]);
			ab->irq_num[irq_idx] = irq;
			irq_set_status_flags(irq, IRQ_NOAUTOEN | IRQ_DISABLE_UNLAZY);
			ret = request_irq(irq, ath11k_ahb_ext_पूर्णांकerrupt_handler,
					  IRQF_TRIGGER_RISING,
					  irq_name[irq_idx], irq_grp);
			अगर (ret) अणु
				ath11k_err(ab, "failed request_irq for %d\n",
					   irq);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_ahb_config_irq(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक irq, irq_idx, i;
	पूर्णांक ret;

	/* Configure CE irqs */
	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		काष्ठा ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;

		tasklet_setup(&ce_pipe->पूर्णांकr_tq, ath11k_ahb_ce_tasklet);
		irq = platक्रमm_get_irq_byname(ab->pdev, irq_name[irq_idx]);
		ret = request_irq(irq, ath11k_ahb_ce_पूर्णांकerrupt_handler,
				  IRQF_TRIGGER_RISING, irq_name[irq_idx],
				  ce_pipe);
		अगर (ret)
			वापस ret;

		ab->irq_num[irq_idx] = irq;
	पूर्ण

	/* Configure बाह्यal पूर्णांकerrupts */
	ret = ath11k_ahb_ext_irq_config(ab);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_ahb_map_service_to_pipe(काष्ठा ath11k_base *ab, u16 service_id,
					  u8 *ul_pipe, u8 *dl_pipe)
अणु
	स्थिर काष्ठा service_to_pipe *entry;
	bool ul_set = false, dl_set = false;
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.svc_to_ce_map_len; i++) अणु
		entry = &ab->hw_params.svc_to_ce_map[i];

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

	अगर (WARN_ON(!ul_set || !dl_set))
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ath11k_hअगर_ops ath11k_ahb_hअगर_ops = अणु
	.start = ath11k_ahb_start,
	.stop = ath11k_ahb_stop,
	.पढ़ो32 = ath11k_ahb_पढ़ो32,
	.ग_लिखो32 = ath11k_ahb_ग_लिखो32,
	.irq_enable = ath11k_ahb_ext_irq_enable,
	.irq_disable = ath11k_ahb_ext_irq_disable,
	.map_service_to_pipe = ath11k_ahb_map_service_to_pipe,
	.घातer_करोwn = ath11k_ahb_घातer_करोwn,
	.घातer_up = ath11k_ahb_घातer_up,
पूर्ण;

अटल पूर्णांक ath11k_core_get_rproc(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ahb *ab_ahb = ath11k_ahb_priv(ab);
	काष्ठा device *dev = ab->dev;
	काष्ठा rproc *prproc;
	phandle rproc_phandle;

	अगर (of_property_पढ़ो_u32(dev->of_node, "qcom,rproc", &rproc_phandle)) अणु
		ath11k_err(ab, "failed to get q6_rproc handle\n");
		वापस -ENOENT;
	पूर्ण

	prproc = rproc_get_by_phandle(rproc_phandle);
	अगर (!prproc) अणु
		ath11k_err(ab, "failed to get rproc\n");
		वापस -EINVAL;
	पूर्ण
	ab_ahb->tgt_rproc = prproc;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_ahb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath11k_base *ab;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा resource *mem_res;
	व्योम __iomem *mem;
	पूर्णांक ret;

	of_id = of_match_device(ath11k_ahb_of_match, &pdev->dev);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "failed to find matching device tree id\n");
		वापस -EINVAL;
	पूर्ण

	mem = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &mem_res);
	अगर (IS_ERR(mem)) अणु
		dev_err(&pdev->dev, "ioremap error\n");
		वापस PTR_ERR(mem);
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to set 32-bit consistent dma\n");
		वापस ret;
	पूर्ण

	ab = ath11k_core_alloc(&pdev->dev, माप(काष्ठा ath11k_ahb),
			       ATH11K_BUS_AHB,
			       &ath11k_ahb_bus_params);
	अगर (!ab) अणु
		dev_err(&pdev->dev, "failed to allocate ath11k base\n");
		वापस -ENOMEM;
	पूर्ण

	ab->hअगर.ops = &ath11k_ahb_hअगर_ops;
	ab->pdev = pdev;
	ab->hw_rev = (क्रमागत ath11k_hw_rev)of_id->data;
	ab->mem = mem;
	ab->mem_len = resource_size(mem_res);
	platक्रमm_set_drvdata(pdev, ab);

	ret = ath11k_core_pre_init(ab);
	अगर (ret)
		जाओ err_core_मुक्त;

	ret = ath11k_hal_srng_init(ab);
	अगर (ret)
		जाओ err_core_मुक्त;

	ret = ath11k_ce_alloc_pipes(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to allocate ce pipes: %d\n", ret);
		जाओ err_hal_srng_deinit;
	पूर्ण

	ath11k_ahb_init_qmi_ce_config(ab);

	ret = ath11k_core_get_rproc(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to get rproc: %d\n", ret);
		जाओ err_ce_मुक्त;
	पूर्ण

	ret = ath11k_core_init(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to init core: %d\n", ret);
		जाओ err_ce_मुक्त;
	पूर्ण

	ret = ath11k_ahb_config_irq(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to configure irq: %d\n", ret);
		जाओ err_ce_मुक्त;
	पूर्ण

	ath11k_ahb_fwreset_from_cold_boot(ab);

	वापस 0;

err_ce_मुक्त:
	ath11k_ce_मुक्त_pipes(ab);

err_hal_srng_deinit:
	ath11k_hal_srng_deinit(ab);

err_core_मुक्त:
	ath11k_core_मुक्त(ab);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_ahb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath11k_base *ab = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ left;

	अगर (test_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags)) अणु
		ath11k_ahb_घातer_करोwn(ab);
		ath11k_debugfs_soc_destroy(ab);
		ath11k_qmi_deinit_service(ab);
		जाओ qmi_fail;
	पूर्ण

	reinit_completion(&ab->driver_recovery);

	अगर (test_bit(ATH11K_FLAG_RECOVERY, &ab->dev_flags)) अणु
		left = रुको_क्रम_completion_समयout(&ab->driver_recovery,
						   ATH11K_AHB_RECOVERY_TIMEOUT);
		अगर (!left)
			ath11k_warn(ab, "failed to receive recovery response completion\n");
	पूर्ण

	set_bit(ATH11K_FLAG_UNREGISTERING, &ab->dev_flags);
	cancel_work_sync(&ab->restart_work);

	ath11k_core_deinit(ab);
qmi_fail:
	ath11k_ahb_मुक्त_irq(ab);
	ath11k_hal_srng_deinit(ab);
	ath11k_ce_मुक्त_pipes(ab);
	ath11k_core_मुक्त(ab);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ath11k_ahb_driver = अणु
	.driver         = अणु
		.name   = "ath11k",
		.of_match_table = ath11k_ahb_of_match,
	पूर्ण,
	.probe  = ath11k_ahb_probe,
	.हटाओ = ath11k_ahb_हटाओ,
पूर्ण;

अटल पूर्णांक ath11k_ahb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ath11k_ahb_driver);
पूर्ण
module_init(ath11k_ahb_init);

अटल व्योम ath11k_ahb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ath11k_ahb_driver);
पूर्ण
module_निकास(ath11k_ahb_निकास);

MODULE_DESCRIPTION("Driver support for Qualcomm Technologies 802.11ax WLAN AHB devices");
MODULE_LICENSE("Dual BSD/GPL");
