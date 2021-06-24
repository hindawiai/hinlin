<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/delay.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_csr.h"
#समावेश "nitrox_hal.h"

#घोषणा PLL_REF_CLK 50
#घोषणा MAX_CSR_RETRIES 10

/**
 * emu_enable_cores - Enable EMU cluster cores.
 * @ndev: NITROX device
 */
अटल व्योम emu_enable_cores(काष्ठा nitrox_device *ndev)
अणु
	जोड़ emu_se_enable emu_se;
	जोड़ emu_ae_enable emu_ae;
	पूर्णांक i;

	/* AE cores 20 per cluster */
	emu_ae.value = 0;
	emu_ae.s.enable = 0xfffff;

	/* SE cores 16 per cluster */
	emu_se.value = 0;
	emu_se.s.enable = 0xffff;

	/* enable per cluster cores */
	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		nitrox_ग_लिखो_csr(ndev, EMU_AE_ENABLEX(i), emu_ae.value);
		nitrox_ग_लिखो_csr(ndev, EMU_SE_ENABLEX(i), emu_se.value);
	पूर्ण
पूर्ण

/**
 * nitrox_config_emu_unit - configure EMU unit.
 * @ndev: NITROX device
 */
व्योम nitrox_config_emu_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ emu_wd_पूर्णांक_ena_w1s emu_wd_पूर्णांक;
	जोड़ emu_ge_पूर्णांक_ena_w1s emu_ge_पूर्णांक;
	u64 offset;
	पूर्णांक i;

	/* enable cores */
	emu_enable_cores(ndev);

	/* enable general error and watch करोg पूर्णांकerrupts */
	emu_ge_पूर्णांक.value = 0;
	emu_ge_पूर्णांक.s.se_ge = 0xffff;
	emu_ge_पूर्णांक.s.ae_ge = 0xfffff;
	emu_wd_पूर्णांक.value = 0;
	emu_wd_पूर्णांक.s.se_wd = 1;

	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		offset = EMU_WD_INT_ENA_W1SX(i);
		nitrox_ग_लिखो_csr(ndev, offset, emu_wd_पूर्णांक.value);
		offset = EMU_GE_INT_ENA_W1SX(i);
		nitrox_ग_लिखो_csr(ndev, offset, emu_ge_पूर्णांक.value);
	पूर्ण
पूर्ण

अटल व्योम reset_pkt_input_ring(काष्ठा nitrox_device *ndev, पूर्णांक ring)
अणु
	जोड़ nps_pkt_in_instr_ctl pkt_in_ctl;
	जोड़ nps_pkt_in_करोne_cnts pkt_in_cnts;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* step 1: disable the ring, clear enable bit */
	offset = NPS_PKT_IN_INSTR_CTLX(ring);
	pkt_in_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	pkt_in_ctl.s.enb = 0;
	nitrox_ग_लिखो_csr(ndev, offset, pkt_in_ctl.value);

	/* step 2: रुको to clear [ENB] */
	usleep_range(100, 150);
	करो अणु
		pkt_in_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (!pkt_in_ctl.s.enb)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);

	/* step 3: clear करोne counts */
	offset = NPS_PKT_IN_DONE_CNTSX(ring);
	pkt_in_cnts.value = nitrox_पढ़ो_csr(ndev, offset);
	nitrox_ग_लिखो_csr(ndev, offset, pkt_in_cnts.value);
	usleep_range(50, 100);
पूर्ण

व्योम enable_pkt_input_ring(काष्ठा nitrox_device *ndev, पूर्णांक ring)
अणु
	जोड़ nps_pkt_in_instr_ctl pkt_in_ctl;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* 64-byte inकाष्ठाion size */
	offset = NPS_PKT_IN_INSTR_CTLX(ring);
	pkt_in_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	pkt_in_ctl.s.is64b = 1;
	pkt_in_ctl.s.enb = 1;
	nitrox_ग_लिखो_csr(ndev, offset, pkt_in_ctl.value);

	/* रुको क्रम set [ENB] */
	करो अणु
		pkt_in_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (pkt_in_ctl.s.enb)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);
पूर्ण

/**
 * nitrox_config_pkt_input_rings - configure Packet Input Rings
 * @ndev: NITROX device
 */
व्योम nitrox_config_pkt_input_rings(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->nr_queues; i++) अणु
		काष्ठा nitrox_cmdq *cmdq = &ndev->pkt_inq[i];
		जोड़ nps_pkt_in_instr_rsize pkt_in_rsize;
		जोड़ nps_pkt_in_instr_baoff_dbell pkt_in_dbell;
		u64 offset;

		reset_pkt_input_ring(ndev, i);

		/**
		 * step 4:
		 * configure ring base address 16-byte aligned,
		 * size and पूर्णांकerrupt threshold.
		 */
		offset = NPS_PKT_IN_INSTR_BADDRX(i);
		nitrox_ग_लिखो_csr(ndev, offset, cmdq->dma);

		/* configure ring size */
		offset = NPS_PKT_IN_INSTR_RSIZEX(i);
		pkt_in_rsize.value = 0;
		pkt_in_rsize.s.rsize = ndev->qlen;
		nitrox_ग_लिखो_csr(ndev, offset, pkt_in_rsize.value);

		/* set high threshold क्रम pkt input ring पूर्णांकerrupts */
		offset = NPS_PKT_IN_INT_LEVELSX(i);
		nitrox_ग_लिखो_csr(ndev, offset, 0xffffffff);

		/* step 5: clear off करोor bell counts */
		offset = NPS_PKT_IN_INSTR_BAOFF_DBELLX(i);
		pkt_in_dbell.value = 0;
		pkt_in_dbell.s.dbell = 0xffffffff;
		nitrox_ग_लिखो_csr(ndev, offset, pkt_in_dbell.value);

		/* enable the ring */
		enable_pkt_input_ring(ndev, i);
	पूर्ण
पूर्ण

अटल व्योम reset_pkt_solicit_port(काष्ठा nitrox_device *ndev, पूर्णांक port)
अणु
	जोड़ nps_pkt_slc_ctl pkt_slc_ctl;
	जोड़ nps_pkt_slc_cnts pkt_slc_cnts;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* step 1: disable slc port */
	offset = NPS_PKT_SLC_CTLX(port);
	pkt_slc_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	pkt_slc_ctl.s.enb = 0;
	nitrox_ग_लिखो_csr(ndev, offset, pkt_slc_ctl.value);

	/* step 2 */
	usleep_range(100, 150);
	/* रुको to clear [ENB] */
	करो अणु
		pkt_slc_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (!pkt_slc_ctl.s.enb)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);

	/* step 3: clear slc counters */
	offset = NPS_PKT_SLC_CNTSX(port);
	pkt_slc_cnts.value = nitrox_पढ़ो_csr(ndev, offset);
	nitrox_ग_लिखो_csr(ndev, offset, pkt_slc_cnts.value);
	usleep_range(50, 100);
पूर्ण

व्योम enable_pkt_solicit_port(काष्ठा nitrox_device *ndev, पूर्णांक port)
अणु
	जोड़ nps_pkt_slc_ctl pkt_slc_ctl;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	offset = NPS_PKT_SLC_CTLX(port);
	pkt_slc_ctl.value = 0;
	pkt_slc_ctl.s.enb = 1;
	/*
	 * 8 trailing 0x00 bytes will be added
	 * to the end of the outgoing packet.
	 */
	pkt_slc_ctl.s.z = 1;
	/* enable response header */
	pkt_slc_ctl.s.rh = 1;
	nitrox_ग_लिखो_csr(ndev, offset, pkt_slc_ctl.value);

	/* रुको to set [ENB] */
	करो अणु
		pkt_slc_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (pkt_slc_ctl.s.enb)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);
पूर्ण

अटल व्योम config_pkt_solicit_port(काष्ठा nitrox_device *ndev, पूर्णांक port)
अणु
	जोड़ nps_pkt_slc_पूर्णांक_levels pkt_slc_पूर्णांक;
	u64 offset;

	reset_pkt_solicit_port(ndev, port);

	/* step 4: configure पूर्णांकerrupt levels */
	offset = NPS_PKT_SLC_INT_LEVELSX(port);
	pkt_slc_पूर्णांक.value = 0;
	/* समय पूर्णांकerrupt threshold */
	pkt_slc_पूर्णांक.s.समयt = 0x3fffff;
	nitrox_ग_लिखो_csr(ndev, offset, pkt_slc_पूर्णांक.value);

	/* enable the solicit port */
	enable_pkt_solicit_port(ndev, port);
पूर्ण

व्योम nitrox_config_pkt_solicit_ports(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->nr_queues; i++)
		config_pkt_solicit_port(ndev, i);
पूर्ण

/**
 * enable_nps_core_पूर्णांकerrupts - enable NPS core पूर्णांकerrutps
 * @ndev: NITROX device.
 *
 * This includes NPS core पूर्णांकerrupts.
 */
अटल व्योम enable_nps_core_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	जोड़ nps_core_पूर्णांक_ena_w1s core_पूर्णांक;

	/* NPS core पूर्णांकerrutps */
	core_पूर्णांक.value = 0;
	core_पूर्णांक.s.host_wr_err = 1;
	core_पूर्णांक.s.host_wr_समयout = 1;
	core_पूर्णांक.s.exec_wr_समयout = 1;
	core_पूर्णांक.s.npco_dma_malक्रमm = 1;
	core_पूर्णांक.s.host_nps_wr_err = 1;
	nitrox_ग_लिखो_csr(ndev, NPS_CORE_INT_ENA_W1S, core_पूर्णांक.value);
पूर्ण

व्योम nitrox_config_nps_core_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ nps_core_gbl_vfcfg core_gbl_vfcfg;

	/* endian control inक्रमmation */
	nitrox_ग_लिखो_csr(ndev, NPS_CORE_CONTROL, 1ULL);

	/* disable ILK पूर्णांकerface */
	core_gbl_vfcfg.value = 0;
	core_gbl_vfcfg.s.ilk_disable = 1;
	core_gbl_vfcfg.s.cfg = __NDEV_MODE_PF;
	nitrox_ग_लिखो_csr(ndev, NPS_CORE_GBL_VFCFG, core_gbl_vfcfg.value);

	/* enable nps core पूर्णांकerrupts */
	enable_nps_core_पूर्णांकerrupts(ndev);
पूर्ण

/**
 * enable_nps_pkt_पूर्णांकerrupts - enable NPS packet पूर्णांकerrutps
 * @ndev: NITROX device.
 *
 * This includes NPS packet in and slc पूर्णांकerrupts.
 */
अटल व्योम enable_nps_pkt_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	/* NPS packet in ring पूर्णांकerrupts */
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_IN_RERR_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_IN_RERR_HI_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_IN_ERR_TYPE_ENA_W1S, (~0ULL));
	/* NPS packet slc port पूर्णांकerrupts */
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_SLC_RERR_HI_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_SLC_RERR_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, NPS_PKT_SLC_ERR_TYPE_ENA_W1S, (~0uLL));
पूर्ण

व्योम nitrox_config_nps_pkt_unit(काष्ठा nitrox_device *ndev)
अणु
	/* config input and solicit ports */
	nitrox_config_pkt_input_rings(ndev);
	nitrox_config_pkt_solicit_ports(ndev);

	/* enable nps packet पूर्णांकerrupts */
	enable_nps_pkt_पूर्णांकerrupts(ndev);
पूर्ण

अटल व्योम reset_aqm_ring(काष्ठा nitrox_device *ndev, पूर्णांक ring)
अणु
	जोड़ aqmq_en aqmq_en_reg;
	जोड़ aqmq_activity_stat activity_stat;
	जोड़ aqmq_cmp_cnt cmp_cnt;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* step 1: disable the queue */
	offset = AQMQ_ENX(ring);
	aqmq_en_reg.value = 0;
	aqmq_en_reg.queue_enable = 0;
	nitrox_ग_लिखो_csr(ndev, offset, aqmq_en_reg.value);

	/* step 2: रुको क्रम AQMQ_ACTIVITY_STATX[QUEUE_ACTIVE] to clear */
	usleep_range(100, 150);
	offset = AQMQ_ACTIVITY_STATX(ring);
	करो अणु
		activity_stat.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (!activity_stat.queue_active)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);

	/* step 3: clear commands completed count */
	offset = AQMQ_CMP_CNTX(ring);
	cmp_cnt.value = nitrox_पढ़ो_csr(ndev, offset);
	nitrox_ग_लिखो_csr(ndev, offset, cmp_cnt.value);
	usleep_range(50, 100);
पूर्ण

व्योम enable_aqm_ring(काष्ठा nitrox_device *ndev, पूर्णांक ring)
अणु
	जोड़ aqmq_en aqmq_en_reg;
	u64 offset;

	offset = AQMQ_ENX(ring);
	aqmq_en_reg.value = 0;
	aqmq_en_reg.queue_enable = 1;
	nitrox_ग_लिखो_csr(ndev, offset, aqmq_en_reg.value);
	usleep_range(50, 100);
पूर्ण

व्योम nitrox_config_aqm_rings(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक ring;

	क्रम (ring = 0; ring < ndev->nr_queues; ring++) अणु
		काष्ठा nitrox_cmdq *cmdq = ndev->aqmq[ring];
		जोड़ aqmq_drbl drbl;
		जोड़ aqmq_qsz qsize;
		जोड़ aqmq_cmp_thr cmp_thr;
		u64 offset;

		/* steps 1 - 3 */
		reset_aqm_ring(ndev, ring);

		/* step 4: clear करोorbell count of ring */
		offset = AQMQ_DRBLX(ring);
		drbl.value = 0;
		drbl.dbell_count = 0xFFFFFFFF;
		nitrox_ग_लिखो_csr(ndev, offset, drbl.value);

		/* step 5: configure host ring details */

		/* set host address क्रम next command of ring */
		offset = AQMQ_NXT_CMDX(ring);
		nitrox_ग_लिखो_csr(ndev, offset, 0ULL);

		/* set host address of ring base */
		offset = AQMQ_BADRX(ring);
		nitrox_ग_लिखो_csr(ndev, offset, cmdq->dma);

		/* set ring size */
		offset = AQMQ_QSZX(ring);
		qsize.value = 0;
		qsize.host_queue_size = ndev->qlen;
		nitrox_ग_लिखो_csr(ndev, offset, qsize.value);

		/* set command completion threshold */
		offset = AQMQ_CMP_THRX(ring);
		cmp_thr.value = 0;
		cmp_thr.commands_completed_threshold = 1;
		nitrox_ग_लिखो_csr(ndev, offset, cmp_thr.value);

		/* step 6: enable the queue */
		enable_aqm_ring(ndev, ring);
	पूर्ण
पूर्ण

अटल व्योम enable_aqm_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	/* clear पूर्णांकerrupt enable bits */
	nitrox_ग_लिखो_csr(ndev, AQM_DBELL_OVF_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_DBELL_OVF_HI_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_DMA_RD_ERR_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_DMA_RD_ERR_HI_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_EXEC_NA_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_EXEC_NA_HI_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_EXEC_ERR_LO_ENA_W1S, (~0ULL));
	nitrox_ग_लिखो_csr(ndev, AQM_EXEC_ERR_HI_ENA_W1S, (~0ULL));
पूर्ण

व्योम nitrox_config_aqm_unit(काष्ठा nitrox_device *ndev)
अणु
	/* config aqm command queues */
	nitrox_config_aqm_rings(ndev);

	/* enable aqm पूर्णांकerrupts */
	enable_aqm_पूर्णांकerrupts(ndev);
पूर्ण

व्योम nitrox_config_pom_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ pom_पूर्णांक_ena_w1s pom_पूर्णांक;
	पूर्णांक i;

	/* enable pom पूर्णांकerrupts */
	pom_पूर्णांक.value = 0;
	pom_पूर्णांक.s.illegal_dport = 1;
	nitrox_ग_लिखो_csr(ndev, POM_INT_ENA_W1S, pom_पूर्णांक.value);

	/* enable perf counters */
	क्रम (i = 0; i < ndev->hw.se_cores; i++)
		nitrox_ग_लिखो_csr(ndev, POM_PERF_CTL, BIT_ULL(i));
पूर्ण

/**
 * nitrox_config_अक्रम_unit - enable NITROX अक्रमom number unit
 * @ndev: NITROX device
 */
व्योम nitrox_config_अक्रम_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ efl_rnm_ctl_status efl_rnm_ctl;
	u64 offset;

	offset = EFL_RNM_CTL_STATUS;
	efl_rnm_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	efl_rnm_ctl.s.ent_en = 1;
	efl_rnm_ctl.s.rng_en = 1;
	nitrox_ग_लिखो_csr(ndev, offset, efl_rnm_ctl.value);
पूर्ण

व्योम nitrox_config_efl_unit(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		जोड़ efl_core_पूर्णांक_ena_w1s efl_core_पूर्णांक;
		u64 offset;

		/* EFL core पूर्णांकerrupts */
		offset = EFL_CORE_INT_ENA_W1SX(i);
		efl_core_पूर्णांक.value = 0;
		efl_core_पूर्णांक.s.len_ovr = 1;
		efl_core_पूर्णांक.s.d_left = 1;
		efl_core_पूर्णांक.s.epci_decode_err = 1;
		nitrox_ग_लिखो_csr(ndev, offset, efl_core_पूर्णांक.value);

		offset = EFL_CORE_VF_ERR_INT0_ENA_W1SX(i);
		nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));
		offset = EFL_CORE_VF_ERR_INT1_ENA_W1SX(i);
		nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));
	पूर्ण
पूर्ण

व्योम nitrox_config_bmi_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ bmi_ctl bmi_ctl;
	जोड़ bmi_पूर्णांक_ena_w1s bmi_पूर्णांक_ena;
	u64 offset;

	/* no threshold limits क्रम PCIe */
	offset = BMI_CTL;
	bmi_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	bmi_ctl.s.max_pkt_len = 0xff;
	bmi_ctl.s.nps_मुक्त_thrsh = 0xff;
	bmi_ctl.s.nps_hdrq_thrsh = 0x7a;
	nitrox_ग_लिखो_csr(ndev, offset, bmi_ctl.value);

	/* enable पूर्णांकerrupts */
	offset = BMI_INT_ENA_W1S;
	bmi_पूर्णांक_ena.value = 0;
	bmi_पूर्णांक_ena.s.max_len_err_nps = 1;
	bmi_पूर्णांक_ena.s.pkt_rcv_err_nps = 1;
	bmi_पूर्णांक_ena.s.fpf_undrrn = 1;
	nitrox_ग_लिखो_csr(ndev, offset, bmi_पूर्णांक_ena.value);
पूर्ण

व्योम nitrox_config_bmo_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ bmo_ctl2 bmo_ctl2;
	u64 offset;

	/* no threshold limits क्रम PCIe */
	offset = BMO_CTL2;
	bmo_ctl2.value = nitrox_पढ़ो_csr(ndev, offset);
	bmo_ctl2.s.nps_slc_buf_thrsh = 0xff;
	nitrox_ग_लिखो_csr(ndev, offset, bmo_ctl2.value);
पूर्ण

व्योम invalidate_lbc(काष्ठा nitrox_device *ndev)
अणु
	जोड़ lbc_inval_ctl lbc_ctl;
	जोड़ lbc_inval_status lbc_stat;
	पूर्णांक max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* invalidate LBC */
	offset = LBC_INVAL_CTL;
	lbc_ctl.value = nitrox_पढ़ो_csr(ndev, offset);
	lbc_ctl.s.cam_inval_start = 1;
	nitrox_ग_लिखो_csr(ndev, offset, lbc_ctl.value);

	offset = LBC_INVAL_STATUS;
	करो अणु
		lbc_stat.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (lbc_stat.s.करोne)
			अवरोध;
		udelay(50);
	पूर्ण जबतक (max_retries--);
पूर्ण

व्योम nitrox_config_lbc_unit(काष्ठा nitrox_device *ndev)
अणु
	जोड़ lbc_पूर्णांक_ena_w1s lbc_पूर्णांक_ena;
	u64 offset;

	invalidate_lbc(ndev);

	/* enable पूर्णांकerrupts */
	offset = LBC_INT_ENA_W1S;
	lbc_पूर्णांक_ena.value = 0;
	lbc_पूर्णांक_ena.s.dma_rd_err = 1;
	lbc_पूर्णांक_ena.s.over_fetch_err = 1;
	lbc_पूर्णांक_ena.s.cam_inval_पात = 1;
	lbc_पूर्णांक_ena.s.cam_hard_err = 1;
	nitrox_ग_लिखो_csr(ndev, offset, lbc_पूर्णांक_ena.value);

	offset = LBC_PLM_VF1_64_INT_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));
	offset = LBC_PLM_VF65_128_INT_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));

	offset = LBC_ELM_VF1_64_INT_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));
	offset = LBC_ELM_VF65_128_INT_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, offset, (~0ULL));
पूर्ण

व्योम config_nps_core_vfcfg_mode(काष्ठा nitrox_device *ndev, क्रमागत vf_mode mode)
अणु
	जोड़ nps_core_gbl_vfcfg vfcfg;

	vfcfg.value = nitrox_पढ़ो_csr(ndev, NPS_CORE_GBL_VFCFG);
	vfcfg.s.cfg = mode & 0x7;

	nitrox_ग_लिखो_csr(ndev, NPS_CORE_GBL_VFCFG, vfcfg.value);
पूर्ण

अटल स्थिर अक्षर *get_core_option(u8 se_cores, u8 ae_cores)
अणु
	स्थिर अक्षर *option = "";

	अगर (ae_cores == AE_MAX_CORES) अणु
		चयन (se_cores) अणु
		हाल SE_MAX_CORES:
			option = "60";
			अवरोध;
		हाल 40:
			option = "60s";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ae_cores == (AE_MAX_CORES / 2)) अणु
		option = "30";
	पूर्ण अन्यथा अणु
		option = "60i";
	पूर्ण

	वापस option;
पूर्ण

अटल स्थिर अक्षर *get_feature_option(u8 zip_cores, पूर्णांक core_freq)
अणु
	अगर (zip_cores == 0)
		वापस "";
	अन्यथा अगर (zip_cores < ZIP_MAX_CORES)
		वापस "-C15";

	अगर (core_freq >= 850)
		वापस "-C45";
	अन्यथा अगर (core_freq >= 750)
		वापस "-C35";
	अन्यथा अगर (core_freq >= 550)
		वापस "-C25";

	वापस "";
पूर्ण

व्योम nitrox_get_hwinfo(काष्ठा nitrox_device *ndev)
अणु
	जोड़ emu_fuse_map emu_fuse;
	जोड़ rst_boot rst_boot;
	जोड़ fus_dat1 fus_dat1;
	अचिन्हित अक्षर name[IFNAMSIZ * 2] = अणुपूर्ण;
	पूर्णांक i, dead_cores;
	u64 offset;

	/* get core frequency */
	offset = RST_BOOT;
	rst_boot.value = nitrox_पढ़ो_csr(ndev, offset);
	ndev->hw.freq = (rst_boot.pnr_mul + 3) * PLL_REF_CLK;

	क्रम (i = 0; i < NR_CLUSTERS; i++) अणु
		offset = EMU_FUSE_MAPX(i);
		emu_fuse.value = nitrox_पढ़ो_csr(ndev, offset);
		अगर (emu_fuse.s.valid) अणु
			dead_cores = hweight32(emu_fuse.s.ae_fuse);
			ndev->hw.ae_cores += AE_CORES_PER_CLUSTER - dead_cores;
			dead_cores = hweight16(emu_fuse.s.se_fuse);
			ndev->hw.se_cores += SE_CORES_PER_CLUSTER - dead_cores;
		पूर्ण
	पूर्ण
	/* find zip hardware availability */
	offset = FUS_DAT1;
	fus_dat1.value = nitrox_पढ़ो_csr(ndev, offset);
	अगर (!fus_dat1.nozip) अणु
		dead_cores = hweight8(fus_dat1.zip_info);
		ndev->hw.zip_cores = ZIP_MAX_CORES - dead_cores;
	पूर्ण

	/* determine the partname
	 * CNN55<core option>-<freq><pincount>-<feature option>-<rev>
	 */
	snम_लिखो(name, माप(name), "CNN55%s-%3dBG676%s-1.%u",
		 get_core_option(ndev->hw.se_cores, ndev->hw.ae_cores),
		 ndev->hw.freq,
		 get_feature_option(ndev->hw.zip_cores, ndev->hw.freq),
		 ndev->hw.revision_id);

	/* copy partname */
	म_नकलन(ndev->hw.partname, name, माप(ndev->hw.partname));
पूर्ण

व्योम enable_pf2vf_mbox_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	u64 value = ~0ULL;
	u64 reg_addr;

	/* Mailbox पूर्णांकerrupt low enable set रेजिस्टर */
	reg_addr = NPS_PKT_MBOX_INT_LO_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, reg_addr, value);

	/* Mailbox पूर्णांकerrupt high enable set रेजिस्टर */
	reg_addr = NPS_PKT_MBOX_INT_HI_ENA_W1S;
	nitrox_ग_लिखो_csr(ndev, reg_addr, value);
पूर्ण

व्योम disable_pf2vf_mbox_पूर्णांकerrupts(काष्ठा nitrox_device *ndev)
अणु
	u64 value = ~0ULL;
	u64 reg_addr;

	/* Mailbox पूर्णांकerrupt low enable clear रेजिस्टर */
	reg_addr = NPS_PKT_MBOX_INT_LO_ENA_W1C;
	nitrox_ग_लिखो_csr(ndev, reg_addr, value);

	/* Mailbox पूर्णांकerrupt high enable clear रेजिस्टर */
	reg_addr = NPS_PKT_MBOX_INT_HI_ENA_W1C;
	nitrox_ग_लिखो_csr(ndev, reg_addr, value);
पूर्ण
