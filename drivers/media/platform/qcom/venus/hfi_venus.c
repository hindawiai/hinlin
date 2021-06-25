<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "hfi_cmds.h"
#समावेश "hfi_msgs.h"
#समावेश "hfi_venus.h"
#समावेश "hfi_venus_io.h"
#समावेश "firmware.h"

#घोषणा HFI_MASK_QHDR_TX_TYPE		0xff000000
#घोषणा HFI_MASK_QHDR_RX_TYPE		0x00ff0000
#घोषणा HFI_MASK_QHDR_PRI_TYPE		0x0000ff00
#घोषणा HFI_MASK_QHDR_ID_TYPE		0x000000ff

#घोषणा HFI_HOST_TO_CTRL_CMD_Q		0
#घोषणा HFI_CTRL_TO_HOST_MSG_Q		1
#घोषणा HFI_CTRL_TO_HOST_DBG_Q		2
#घोषणा HFI_MASK_QHDR_STATUS		0x000000ff

#घोषणा IFACEQ_NUM			3
#घोषणा IFACEQ_CMD_IDX			0
#घोषणा IFACEQ_MSG_IDX			1
#घोषणा IFACEQ_DBG_IDX			2
#घोषणा IFACEQ_MAX_BUF_COUNT		50
#घोषणा IFACEQ_MAX_PARALLEL_CLNTS	16
#घोषणा IFACEQ_DFLT_QHDR		0x01010000

#घोषणा POLL_INTERVAL_US		50

#घोषणा IFACEQ_MAX_PKT_SIZE		1024
#घोषणा IFACEQ_MED_PKT_SIZE		768
#घोषणा IFACEQ_MIN_PKT_SIZE		8
#घोषणा IFACEQ_VAR_SMALL_PKT_SIZE	100
#घोषणा IFACEQ_VAR_LARGE_PKT_SIZE	512
#घोषणा IFACEQ_VAR_HUGE_PKT_SIZE	(1024 * 12)

काष्ठा hfi_queue_table_header अणु
	u32 version;
	u32 size;
	u32 qhdr0_offset;
	u32 qhdr_size;
	u32 num_q;
	u32 num_active_q;
पूर्ण;

काष्ठा hfi_queue_header अणु
	u32 status;
	u32 start_addr;
	u32 type;
	u32 q_size;
	u32 pkt_size;
	u32 pkt_drop_cnt;
	u32 rx_wm;
	u32 tx_wm;
	u32 rx_req;
	u32 tx_req;
	u32 rx_irq_status;
	u32 tx_irq_status;
	u32 पढ़ो_idx;
	u32 ग_लिखो_idx;
पूर्ण;

#घोषणा IFACEQ_TABLE_SIZE	\
	(माप(काष्ठा hfi_queue_table_header) +	\
	 माप(काष्ठा hfi_queue_header) * IFACEQ_NUM)

#घोषणा IFACEQ_QUEUE_SIZE	(IFACEQ_MAX_PKT_SIZE *	\
	IFACEQ_MAX_BUF_COUNT * IFACEQ_MAX_PARALLEL_CLNTS)

#घोषणा IFACEQ_GET_QHDR_START_ADDR(ptr, i)	\
	(व्योम *)(((ptr) + माप(काष्ठा hfi_queue_table_header)) +	\
		((i) * माप(काष्ठा hfi_queue_header)))

#घोषणा QDSS_SIZE		SZ_4K
#घोषणा SFR_SIZE		SZ_4K
#घोषणा QUEUE_SIZE		\
	(IFACEQ_TABLE_SIZE + (IFACEQ_QUEUE_SIZE * IFACEQ_NUM))

#घोषणा ALIGNED_QDSS_SIZE	ALIGN(QDSS_SIZE, SZ_4K)
#घोषणा ALIGNED_SFR_SIZE	ALIGN(SFR_SIZE, SZ_4K)
#घोषणा ALIGNED_QUEUE_SIZE	ALIGN(QUEUE_SIZE, SZ_4K)
#घोषणा SHARED_QSIZE		ALIGN(ALIGNED_SFR_SIZE + ALIGNED_QUEUE_SIZE + \
				      ALIGNED_QDSS_SIZE, SZ_1M)

काष्ठा mem_desc अणु
	dma_addr_t da;	/* device address */
	व्योम *kva;	/* kernel भव address */
	u32 size;
	अचिन्हित दीर्घ attrs;
पूर्ण;

काष्ठा अगरace_queue अणु
	काष्ठा hfi_queue_header *qhdr;
	काष्ठा mem_desc qmem;
पूर्ण;

क्रमागत venus_state अणु
	VENUS_STATE_DEINIT = 1,
	VENUS_STATE_INIT,
पूर्ण;

काष्ठा venus_hfi_device अणु
	काष्ठा venus_core *core;
	u32 irq_status;
	u32 last_packet_type;
	bool घातer_enabled;
	bool suspended;
	क्रमागत venus_state state;
	/* serialize पढ़ो / ग_लिखो to the shared memory */
	काष्ठा mutex lock;
	काष्ठा completion pwr_collapse_prep;
	काष्ठा completion release_resource;
	काष्ठा mem_desc अगरaceq_table;
	काष्ठा mem_desc sfr;
	काष्ठा अगरace_queue queues[IFACEQ_NUM];
	u8 pkt_buf[IFACEQ_VAR_HUGE_PKT_SIZE];
	u8 dbg_buf[IFACEQ_VAR_HUGE_PKT_SIZE];
पूर्ण;

अटल bool venus_pkt_debug;
पूर्णांक venus_fw_debug = HFI_DEBUG_MSG_ERROR | HFI_DEBUG_MSG_FATAL;
अटल bool venus_sys_idle_indicator;
अटल bool venus_fw_low_घातer_mode = true;
अटल पूर्णांक venus_hw_rsp_समयout = 1000;
अटल bool venus_fw_coverage;

अटल व्योम venus_set_state(काष्ठा venus_hfi_device *hdev,
			    क्रमागत venus_state state)
अणु
	mutex_lock(&hdev->lock);
	hdev->state = state;
	mutex_unlock(&hdev->lock);
पूर्ण

अटल bool venus_is_valid_state(काष्ठा venus_hfi_device *hdev)
अणु
	वापस hdev->state != VENUS_STATE_DEINIT;
पूर्ण

अटल व्योम venus_dump_packet(काष्ठा venus_hfi_device *hdev, स्थिर व्योम *packet)
अणु
	माप_प्रकार pkt_size = *(u32 *)packet;

	अगर (!venus_pkt_debug)
		वापस;

	prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 16, 1, packet,
		       pkt_size, true);
पूर्ण

अटल पूर्णांक venus_ग_लिखो_queue(काष्ठा venus_hfi_device *hdev,
			     काष्ठा अगरace_queue *queue,
			     व्योम *packet, u32 *rx_req)
अणु
	काष्ठा hfi_queue_header *qhdr;
	u32 dwords, new_wr_idx;
	u32 empty_space, rd_idx, wr_idx, qsize;
	u32 *wr_ptr;

	अगर (!queue->qmem.kva)
		वापस -EINVAL;

	qhdr = queue->qhdr;
	अगर (!qhdr)
		वापस -EINVAL;

	venus_dump_packet(hdev, packet);

	dwords = (*(u32 *)packet) >> 2;
	अगर (!dwords)
		वापस -EINVAL;

	rd_idx = qhdr->पढ़ो_idx;
	wr_idx = qhdr->ग_लिखो_idx;
	qsize = qhdr->q_size;
	/* ensure rd/wr indices's are पढ़ो from memory */
	rmb();

	अगर (wr_idx >= rd_idx)
		empty_space = qsize - (wr_idx - rd_idx);
	अन्यथा
		empty_space = rd_idx - wr_idx;

	अगर (empty_space <= dwords) अणु
		qhdr->tx_req = 1;
		/* ensure tx_req is updated in memory */
		wmb();
		वापस -ENOSPC;
	पूर्ण

	qhdr->tx_req = 0;
	/* ensure tx_req is updated in memory */
	wmb();

	new_wr_idx = wr_idx + dwords;
	wr_ptr = (u32 *)(queue->qmem.kva + (wr_idx << 2));
	अगर (new_wr_idx < qsize) अणु
		स_नकल(wr_ptr, packet, dwords << 2);
	पूर्ण अन्यथा अणु
		माप_प्रकार len;

		new_wr_idx -= qsize;
		len = (dwords - new_wr_idx) << 2;
		स_नकल(wr_ptr, packet, len);
		स_नकल(queue->qmem.kva, packet + len, new_wr_idx << 2);
	पूर्ण

	/* make sure packet is written beक्रमe updating the ग_लिखो index */
	wmb();

	qhdr->ग_लिखो_idx = new_wr_idx;
	*rx_req = qhdr->rx_req ? 1 : 0;

	/* make sure ग_लिखो index is updated beक्रमe an पूर्णांकerrupt is उठाओd */
	mb();

	वापस 0;
पूर्ण

अटल पूर्णांक venus_पढ़ो_queue(काष्ठा venus_hfi_device *hdev,
			    काष्ठा अगरace_queue *queue, व्योम *pkt, u32 *tx_req)
अणु
	काष्ठा hfi_queue_header *qhdr;
	u32 dwords, new_rd_idx;
	u32 rd_idx, wr_idx, type, qsize;
	u32 *rd_ptr;
	u32 recv_request = 0;
	पूर्णांक ret = 0;

	अगर (!queue->qmem.kva)
		वापस -EINVAL;

	qhdr = queue->qhdr;
	अगर (!qhdr)
		वापस -EINVAL;

	type = qhdr->type;
	rd_idx = qhdr->पढ़ो_idx;
	wr_idx = qhdr->ग_लिखो_idx;
	qsize = qhdr->q_size;

	/* make sure data is valid beक्रमe using it */
	rmb();

	/*
	 * Do not set receive request क्रम debug queue, अगर set, Venus generates
	 * पूर्णांकerrupt क्रम debug messages even when there is no response message
	 * available. In general debug queue will not become full as it is being
	 * emptied out क्रम every पूर्णांकerrupt from Venus. Venus will anyway
	 * generates पूर्णांकerrupt अगर it is full.
	 */
	अगर (type & HFI_CTRL_TO_HOST_MSG_Q)
		recv_request = 1;

	अगर (rd_idx == wr_idx) अणु
		qhdr->rx_req = recv_request;
		*tx_req = 0;
		/* update rx_req field in memory */
		wmb();
		वापस -ENODATA;
	पूर्ण

	rd_ptr = (u32 *)(queue->qmem.kva + (rd_idx << 2));
	dwords = *rd_ptr >> 2;
	अगर (!dwords)
		वापस -EINVAL;

	new_rd_idx = rd_idx + dwords;
	अगर (((dwords << 2) <= IFACEQ_VAR_HUGE_PKT_SIZE) && rd_idx <= qsize) अणु
		अगर (new_rd_idx < qsize) अणु
			स_नकल(pkt, rd_ptr, dwords << 2);
		पूर्ण अन्यथा अणु
			माप_प्रकार len;

			new_rd_idx -= qsize;
			len = (dwords - new_rd_idx) << 2;
			स_नकल(pkt, rd_ptr, len);
			स_नकल(pkt + len, queue->qmem.kva, new_rd_idx << 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* bad packet received, dropping */
		new_rd_idx = qhdr->ग_लिखो_idx;
		ret = -EBADMSG;
	पूर्ण

	/* ensure the packet is पढ़ो beक्रमe updating पढ़ो index */
	rmb();

	qhdr->पढ़ो_idx = new_rd_idx;
	/* ensure updating पढ़ो index */
	wmb();

	rd_idx = qhdr->पढ़ो_idx;
	wr_idx = qhdr->ग_लिखो_idx;
	/* ensure rd/wr indices are पढ़ो from memory */
	rmb();

	अगर (rd_idx != wr_idx)
		qhdr->rx_req = 0;
	अन्यथा
		qhdr->rx_req = recv_request;

	*tx_req = qhdr->tx_req ? 1 : 0;

	/* ensure rx_req is stored to memory and tx_req is loaded from memory */
	mb();

	venus_dump_packet(hdev, pkt);

	वापस ret;
पूर्ण

अटल पूर्णांक venus_alloc(काष्ठा venus_hfi_device *hdev, काष्ठा mem_desc *desc,
		       u32 size)
अणु
	काष्ठा device *dev = hdev->core->dev;

	desc->attrs = DMA_ATTR_WRITE_COMBINE;
	desc->size = ALIGN(size, SZ_4K);

	desc->kva = dma_alloc_attrs(dev, desc->size, &desc->da, GFP_KERNEL,
				    desc->attrs);
	अगर (!desc->kva)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम venus_मुक्त(काष्ठा venus_hfi_device *hdev, काष्ठा mem_desc *mem)
अणु
	काष्ठा device *dev = hdev->core->dev;

	dma_मुक्त_attrs(dev, mem->size, mem->kva, mem->da, mem->attrs);
पूर्ण

अटल व्योम venus_set_रेजिस्टरs(काष्ठा venus_hfi_device *hdev)
अणु
	स्थिर काष्ठा venus_resources *res = hdev->core->res;
	स्थिर काष्ठा reg_val *tbl = res->reg_tbl;
	अचिन्हित पूर्णांक count = res->reg_tbl_size;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		ग_लिखोl(tbl[i].value, hdev->core->base + tbl[i].reg);
पूर्ण

अटल व्योम venus_soft_पूर्णांक(काष्ठा venus_hfi_device *hdev)
अणु
	व्योम __iomem *cpu_ic_base = hdev->core->cpu_ic_base;
	u32 clear_bit;

	अगर (IS_V6(hdev->core))
		clear_bit = BIT(CPU_IC_SOFTINT_H2A_SHIFT_V6);
	अन्यथा
		clear_bit = BIT(CPU_IC_SOFTINT_H2A_SHIFT);

	ग_लिखोl(clear_bit, cpu_ic_base + CPU_IC_SOFTINT);
पूर्ण

अटल पूर्णांक venus_अगरace_cmdq_ग_लिखो_nolock(काष्ठा venus_hfi_device *hdev,
					 व्योम *pkt, bool sync)
अणु
	काष्ठा device *dev = hdev->core->dev;
	काष्ठा hfi_pkt_hdr *cmd_packet;
	काष्ठा अगरace_queue *queue;
	u32 rx_req;
	पूर्णांक ret;

	अगर (!venus_is_valid_state(hdev))
		वापस -EINVAL;

	cmd_packet = (काष्ठा hfi_pkt_hdr *)pkt;
	hdev->last_packet_type = cmd_packet->pkt_type;

	queue = &hdev->queues[IFACEQ_CMD_IDX];

	ret = venus_ग_लिखो_queue(hdev, queue, pkt, &rx_req);
	अगर (ret) अणु
		dev_err(dev, "write to iface cmd queue failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (sync) अणु
		/*
		 * Inक्रमm video hardware to उठाओ पूर्णांकerrupt क्रम synchronous
		 * commands
		 */
		queue = &hdev->queues[IFACEQ_MSG_IDX];
		queue->qhdr->rx_req = 1;
		/* ensure rx_req is updated in memory */
		wmb();
	पूर्ण

	अगर (rx_req)
		venus_soft_पूर्णांक(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_अगरace_cmdq_ग_लिखो(काष्ठा venus_hfi_device *hdev, व्योम *pkt, bool sync)
अणु
	पूर्णांक ret;

	mutex_lock(&hdev->lock);
	ret = venus_अगरace_cmdq_ग_लिखो_nolock(hdev, pkt, sync);
	mutex_unlock(&hdev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक venus_hfi_core_set_resource(काष्ठा venus_core *core, u32 id,
				       u32 size, u32 addr, व्योम *cookie)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा hfi_sys_set_resource_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	अगर (id == VIDC_RESOURCE_NONE)
		वापस 0;

	pkt = (काष्ठा hfi_sys_set_resource_pkt *)packet;

	ret = pkt_sys_set_resource(pkt, id, size, addr, cookie);
	अगर (ret)
		वापस ret;

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_boot_core(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	अटल स्थिर अचिन्हित पूर्णांक max_tries = 100;
	u32 ctrl_status = 0, mask_val;
	अचिन्हित पूर्णांक count = 0;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	व्योम __iomem *wrapper_base = hdev->core->wrapper_base;
	पूर्णांक ret = 0;

	ग_लिखोl(BIT(VIDC_CTRL_INIT_CTRL_SHIFT), cpu_cs_base + VIDC_CTRL_INIT);
	अगर (IS_V6(hdev->core)) अणु
		mask_val = पढ़ोl(wrapper_base + WRAPPER_INTR_MASK);
		mask_val &= ~(WRAPPER_INTR_MASK_A2HWD_BASK_V6 |
			      WRAPPER_INTR_MASK_A2HCPU_MASK);
	पूर्ण अन्यथा अणु
		mask_val = WRAPPER_INTR_MASK_A2HVCODEC_MASK;
	पूर्ण
	ग_लिखोl(mask_val, wrapper_base + WRAPPER_INTR_MASK);
	ग_लिखोl(1, cpu_cs_base + CPU_CS_SCIACMDARG3);

	जबतक (!ctrl_status && count < max_tries) अणु
		ctrl_status = पढ़ोl(cpu_cs_base + CPU_CS_SCIACMDARG0);
		अगर ((ctrl_status & CPU_CS_SCIACMDARG0_ERROR_STATUS_MASK) == 4) अणु
			dev_err(dev, "invalid setting for UC_REGION\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		usleep_range(500, 1000);
		count++;
	पूर्ण

	अगर (count >= max_tries)
		ret = -ETIMEDOUT;

	अगर (IS_V6(hdev->core)) अणु
		ग_लिखोl(0x1, cpu_cs_base + CPU_CS_H2XSOFTINTEN_V6);
		ग_लिखोl(0x0, cpu_cs_base + CPU_CS_X2RPMH_V6);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 venus_hwversion(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	व्योम __iomem *wrapper_base = hdev->core->wrapper_base;
	u32 ver;
	u32 major, minor, step;

	ver = पढ़ोl(wrapper_base + WRAPPER_HW_VERSION);
	major = ver & WRAPPER_HW_VERSION_MAJOR_VERSION_MASK;
	major = major >> WRAPPER_HW_VERSION_MAJOR_VERSION_SHIFT;
	minor = ver & WRAPPER_HW_VERSION_MINOR_VERSION_MASK;
	minor = minor >> WRAPPER_HW_VERSION_MINOR_VERSION_SHIFT;
	step = ver & WRAPPER_HW_VERSION_STEP_VERSION_MASK;

	dev_dbg(dev, VDBGL "venus hw version %x.%x.%x\n", major, minor, step);

	वापस major;
पूर्ण

अटल पूर्णांक venus_run(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	पूर्णांक ret;

	/*
	 * Re-program all of the रेजिस्टरs that get reset as a result of
	 * regulator_disable() and _enable()
	 */
	venus_set_रेजिस्टरs(hdev);

	ग_लिखोl(hdev->अगरaceq_table.da, cpu_cs_base + UC_REGION_ADDR);
	ग_लिखोl(SHARED_QSIZE, cpu_cs_base + UC_REGION_SIZE);
	ग_लिखोl(hdev->अगरaceq_table.da, cpu_cs_base + CPU_CS_SCIACMDARG2);
	ग_लिखोl(0x01, cpu_cs_base + CPU_CS_SCIACMDARG1);
	अगर (hdev->sfr.da)
		ग_लिखोl(hdev->sfr.da, cpu_cs_base + SFR_ADDR);

	ret = venus_boot_core(hdev);
	अगर (ret) अणु
		dev_err(dev, "failed to reset venus core\n");
		वापस ret;
	पूर्ण

	venus_hwversion(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_halt_axi(काष्ठा venus_hfi_device *hdev)
अणु
	व्योम __iomem *wrapper_base = hdev->core->wrapper_base;
	व्योम __iomem *vbअगर_base = hdev->core->vbअगर_base;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	व्योम __iomem *aon_base = hdev->core->aon_base;
	काष्ठा device *dev = hdev->core->dev;
	u32 val;
	u32 mask_val;
	पूर्णांक ret;

	अगर (IS_V6(hdev->core)) अणु
		ग_लिखोl(0x3, cpu_cs_base + CPU_CS_X2RPMH_V6);

		ग_लिखोl(0x1, aon_base + AON_WRAPPER_MVP_NOC_LPI_CONTROL);
		ret = पढ़ोl_poll_समयout(aon_base + AON_WRAPPER_MVP_NOC_LPI_STATUS,
					 val,
					 val & BIT(0),
					 POLL_INTERVAL_US,
					 VBIF_AXI_HALT_ACK_TIMEOUT_US);
		अगर (ret)
			वापस -ETIMEDOUT;

		mask_val = (BIT(2) | BIT(1) | BIT(0));
		ग_लिखोl(mask_val, wrapper_base + WRAPPER_DEBUG_BRIDGE_LPI_CONTROL_V6);

		ग_लिखोl(0x00, wrapper_base + WRAPPER_DEBUG_BRIDGE_LPI_CONTROL_V6);
		ret = पढ़ोl_poll_समयout(wrapper_base + WRAPPER_DEBUG_BRIDGE_LPI_STATUS_V6,
					 val,
					 val == 0,
					 POLL_INTERVAL_US,
					 VBIF_AXI_HALT_ACK_TIMEOUT_US);

		अगर (ret) अणु
			dev_err(dev, "DBLP Release: lpi_status %x\n", val);
			वापस -ETIMEDOUT;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (IS_V4(hdev->core)) अणु
		val = पढ़ोl(wrapper_base + WRAPPER_CPU_AXI_HALT);
		val |= WRAPPER_CPU_AXI_HALT_HALT;
		ग_लिखोl(val, wrapper_base + WRAPPER_CPU_AXI_HALT);

		ret = पढ़ोl_poll_समयout(wrapper_base + WRAPPER_CPU_AXI_HALT_STATUS,
					 val,
					 val & WRAPPER_CPU_AXI_HALT_STATUS_IDLE,
					 POLL_INTERVAL_US,
					 VBIF_AXI_HALT_ACK_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(dev, "AXI bus port halt timeout\n");
			वापस ret;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Halt AXI and AXI IMEM VBIF Access */
	val = पढ़ोl(vbअगर_base + VBIF_AXI_HALT_CTRL0);
	val |= VBIF_AXI_HALT_CTRL0_HALT_REQ;
	ग_लिखोl(val, vbअगर_base + VBIF_AXI_HALT_CTRL0);

	/* Request क्रम AXI bus port halt */
	ret = पढ़ोl_poll_समयout(vbअगर_base + VBIF_AXI_HALT_CTRL1, val,
				 val & VBIF_AXI_HALT_CTRL1_HALT_ACK,
				 POLL_INTERVAL_US,
				 VBIF_AXI_HALT_ACK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "AXI bus port halt timeout\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venus_घातer_off(काष्ठा venus_hfi_device *hdev)
अणु
	पूर्णांक ret;

	अगर (!hdev->घातer_enabled)
		वापस 0;

	ret = venus_set_hw_state_suspend(hdev->core);
	अगर (ret)
		वापस ret;

	ret = venus_halt_axi(hdev);
	अगर (ret)
		वापस ret;

	hdev->घातer_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_घातer_on(काष्ठा venus_hfi_device *hdev)
अणु
	पूर्णांक ret;

	अगर (hdev->घातer_enabled)
		वापस 0;

	ret = venus_set_hw_state_resume(hdev->core);
	अगर (ret)
		जाओ err;

	ret = venus_run(hdev);
	अगर (ret)
		जाओ err_suspend;

	hdev->घातer_enabled = true;

	वापस 0;

err_suspend:
	venus_set_hw_state_suspend(hdev->core);
err:
	hdev->घातer_enabled = false;
	वापस ret;
पूर्ण

अटल पूर्णांक venus_अगरace_msgq_पढ़ो_nolock(काष्ठा venus_hfi_device *hdev,
					व्योम *pkt)
अणु
	काष्ठा अगरace_queue *queue;
	u32 tx_req;
	पूर्णांक ret;

	अगर (!venus_is_valid_state(hdev))
		वापस -EINVAL;

	queue = &hdev->queues[IFACEQ_MSG_IDX];

	ret = venus_पढ़ो_queue(hdev, queue, pkt, &tx_req);
	अगर (ret)
		वापस ret;

	अगर (tx_req)
		venus_soft_पूर्णांक(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_अगरace_msgq_पढ़ो(काष्ठा venus_hfi_device *hdev, व्योम *pkt)
अणु
	पूर्णांक ret;

	mutex_lock(&hdev->lock);
	ret = venus_अगरace_msgq_पढ़ो_nolock(hdev, pkt);
	mutex_unlock(&hdev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक venus_अगरace_dbgq_पढ़ो_nolock(काष्ठा venus_hfi_device *hdev,
					व्योम *pkt)
अणु
	काष्ठा अगरace_queue *queue;
	u32 tx_req;
	पूर्णांक ret;

	ret = venus_is_valid_state(hdev);
	अगर (!ret)
		वापस -EINVAL;

	queue = &hdev->queues[IFACEQ_DBG_IDX];

	ret = venus_पढ़ो_queue(hdev, queue, pkt, &tx_req);
	अगर (ret)
		वापस ret;

	अगर (tx_req)
		venus_soft_पूर्णांक(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_अगरace_dbgq_पढ़ो(काष्ठा venus_hfi_device *hdev, व्योम *pkt)
अणु
	पूर्णांक ret;

	अगर (!pkt)
		वापस -EINVAL;

	mutex_lock(&hdev->lock);
	ret = venus_अगरace_dbgq_पढ़ो_nolock(hdev, pkt);
	mutex_unlock(&hdev->lock);

	वापस ret;
पूर्ण

अटल व्योम venus_set_qhdr_शेषs(काष्ठा hfi_queue_header *qhdr)
अणु
	qhdr->status = 1;
	qhdr->type = IFACEQ_DFLT_QHDR;
	qhdr->q_size = IFACEQ_QUEUE_SIZE / 4;
	qhdr->pkt_size = 0;
	qhdr->rx_wm = 1;
	qhdr->tx_wm = 1;
	qhdr->rx_req = 1;
	qhdr->tx_req = 0;
	qhdr->rx_irq_status = 0;
	qhdr->tx_irq_status = 0;
	qhdr->पढ़ो_idx = 0;
	qhdr->ग_लिखो_idx = 0;
पूर्ण

अटल व्योम venus_पूर्णांकerface_queues_release(काष्ठा venus_hfi_device *hdev)
अणु
	mutex_lock(&hdev->lock);

	venus_मुक्त(hdev, &hdev->अगरaceq_table);
	venus_मुक्त(hdev, &hdev->sfr);

	स_रखो(hdev->queues, 0, माप(hdev->queues));
	स_रखो(&hdev->अगरaceq_table, 0, माप(hdev->अगरaceq_table));
	स_रखो(&hdev->sfr, 0, माप(hdev->sfr));

	mutex_unlock(&hdev->lock);
पूर्ण

अटल पूर्णांक venus_पूर्णांकerface_queues_init(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा hfi_queue_table_header *tbl_hdr;
	काष्ठा अगरace_queue *queue;
	काष्ठा hfi_sfr *sfr;
	काष्ठा mem_desc desc = अणु0पूर्ण;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = venus_alloc(hdev, &desc, ALIGNED_QUEUE_SIZE);
	अगर (ret)
		वापस ret;

	hdev->अगरaceq_table = desc;
	offset = IFACEQ_TABLE_SIZE;

	क्रम (i = 0; i < IFACEQ_NUM; i++) अणु
		queue = &hdev->queues[i];
		queue->qmem.da = desc.da + offset;
		queue->qmem.kva = desc.kva + offset;
		queue->qmem.size = IFACEQ_QUEUE_SIZE;
		offset += queue->qmem.size;
		queue->qhdr =
			IFACEQ_GET_QHDR_START_ADDR(hdev->अगरaceq_table.kva, i);

		venus_set_qhdr_शेषs(queue->qhdr);

		queue->qhdr->start_addr = queue->qmem.da;

		अगर (i == IFACEQ_CMD_IDX)
			queue->qhdr->type |= HFI_HOST_TO_CTRL_CMD_Q;
		अन्यथा अगर (i == IFACEQ_MSG_IDX)
			queue->qhdr->type |= HFI_CTRL_TO_HOST_MSG_Q;
		अन्यथा अगर (i == IFACEQ_DBG_IDX)
			queue->qhdr->type |= HFI_CTRL_TO_HOST_DBG_Q;
	पूर्ण

	tbl_hdr = hdev->अगरaceq_table.kva;
	tbl_hdr->version = 0;
	tbl_hdr->size = IFACEQ_TABLE_SIZE;
	tbl_hdr->qhdr0_offset = माप(काष्ठा hfi_queue_table_header);
	tbl_hdr->qhdr_size = माप(काष्ठा hfi_queue_header);
	tbl_hdr->num_q = IFACEQ_NUM;
	tbl_hdr->num_active_q = IFACEQ_NUM;

	/*
	 * Set receive request to zero on debug queue as there is no
	 * need of पूर्णांकerrupt from video hardware क्रम debug messages
	 */
	queue = &hdev->queues[IFACEQ_DBG_IDX];
	queue->qhdr->rx_req = 0;

	ret = venus_alloc(hdev, &desc, ALIGNED_SFR_SIZE);
	अगर (ret) अणु
		hdev->sfr.da = 0;
	पूर्ण अन्यथा अणु
		hdev->sfr = desc;
		sfr = hdev->sfr.kva;
		sfr->buf_size = ALIGNED_SFR_SIZE;
	पूर्ण

	/* ensure table and queue header काष्ठाs are settled in memory */
	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक venus_sys_set_debug(काष्ठा venus_hfi_device *hdev, u32 debug)
अणु
	काष्ठा hfi_sys_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_sys_set_property_pkt *)packet;

	pkt_sys_debug_config(pkt, HFI_DEBUG_MODE_QUEUE, debug);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_sys_set_coverage(काष्ठा venus_hfi_device *hdev, u32 mode)
अणु
	काष्ठा hfi_sys_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_sys_set_property_pkt *)packet;

	pkt_sys_coverage_config(pkt, mode);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_sys_set_idle_message(काष्ठा venus_hfi_device *hdev,
				      bool enable)
अणु
	काष्ठा hfi_sys_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	अगर (!enable)
		वापस 0;

	pkt = (काष्ठा hfi_sys_set_property_pkt *)packet;

	pkt_sys_idle_indicator(pkt, enable);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_sys_set_घातer_control(काष्ठा venus_hfi_device *hdev,
				       bool enable)
अणु
	काष्ठा hfi_sys_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_sys_set_property_pkt *)packet;

	pkt_sys_घातer_control(pkt, enable);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_get_queue_size(काष्ठा venus_hfi_device *hdev,
				अचिन्हित पूर्णांक index)
अणु
	काष्ठा hfi_queue_header *qhdr;

	अगर (index >= IFACEQ_NUM)
		वापस -EINVAL;

	qhdr = hdev->queues[index].qhdr;
	अगर (!qhdr)
		वापस -EINVAL;

	वापस असल(qhdr->पढ़ो_idx - qhdr->ग_लिखो_idx);
पूर्ण

अटल पूर्णांक venus_sys_set_शेष_properties(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	पूर्णांक ret;

	ret = venus_sys_set_debug(hdev, venus_fw_debug);
	अगर (ret)
		dev_warn(dev, "setting fw debug msg ON failed (%d)\n", ret);

	/*
	 * Idle indicator is disabled by शेष on some 4xx firmware versions,
	 * enable it explicitly in order to make suspend functional by checking
	 * WFI (रुको-क्रम-पूर्णांकerrupt) bit.
	 */
	अगर (IS_V4(hdev->core) || IS_V6(hdev->core))
		venus_sys_idle_indicator = true;

	ret = venus_sys_set_idle_message(hdev, venus_sys_idle_indicator);
	अगर (ret)
		dev_warn(dev, "setting idle response ON failed (%d)\n", ret);

	ret = venus_sys_set_घातer_control(hdev, venus_fw_low_घातer_mode);
	अगर (ret)
		dev_warn(dev, "setting hw power collapse ON failed (%d)\n",
			 ret);

	वापस ret;
पूर्ण

अटल पूर्णांक venus_session_cmd(काष्ठा venus_inst *inst, u32 pkt_type, bool sync)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_pkt pkt;

	pkt_session_cmd(&pkt, pkt_type, inst);

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, sync);
पूर्ण

अटल व्योम venus_flush_debug_queue(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	व्योम *packet = hdev->dbg_buf;

	जबतक (!venus_अगरace_dbgq_पढ़ो(hdev, packet)) अणु
		काष्ठा hfi_msg_sys_coverage_pkt *pkt = packet;

		अगर (pkt->hdr.pkt_type != HFI_MSG_SYS_COV) अणु
			काष्ठा hfi_msg_sys_debug_pkt *pkt = packet;

			dev_dbg(dev, VDBGFW "%s", pkt->msg_data);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक venus_prepare_घातer_collapse(काष्ठा venus_hfi_device *hdev,
					bool रुको)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(venus_hw_rsp_समयout);
	काष्ठा hfi_sys_pc_prep_pkt pkt;
	पूर्णांक ret;

	init_completion(&hdev->pwr_collapse_prep);

	pkt_sys_pc_prep(&pkt);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
	अगर (ret)
		वापस ret;

	अगर (!रुको)
		वापस 0;

	ret = रुको_क्रम_completion_समयout(&hdev->pwr_collapse_prep, समयout);
	अगर (!ret) अणु
		venus_flush_debug_queue(hdev);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venus_are_queues_empty(काष्ठा venus_hfi_device *hdev)
अणु
	पूर्णांक ret1, ret2;

	ret1 = venus_get_queue_size(hdev, IFACEQ_MSG_IDX);
	अगर (ret1 < 0)
		वापस ret1;

	ret2 = venus_get_queue_size(hdev, IFACEQ_CMD_IDX);
	अगर (ret2 < 0)
		वापस ret2;

	अगर (!ret1 && !ret2)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम venus_sfr_prपूर्णांक(काष्ठा venus_hfi_device *hdev)
अणु
	काष्ठा device *dev = hdev->core->dev;
	काष्ठा hfi_sfr *sfr = hdev->sfr.kva;
	व्योम *p;

	अगर (!sfr)
		वापस;

	p = स_प्रथम(sfr->data, '\0', sfr->buf_size);
	/*
	 * SFR isn't guaranteed to be शून्य terminated since SYS_ERROR indicates
	 * that Venus is in the process of crashing.
	 */
	अगर (!p)
		sfr->data[sfr->buf_size - 1] = '\0';

	dev_err_ratelimited(dev, "SFR message from FW: %s\n", sfr->data);
पूर्ण

अटल व्योम venus_process_msg_sys_error(काष्ठा venus_hfi_device *hdev,
					व्योम *packet)
अणु
	काष्ठा hfi_msg_event_notअगरy_pkt *event_pkt = packet;

	अगर (event_pkt->event_id != HFI_EVENT_SYS_ERROR)
		वापस;

	venus_set_state(hdev, VENUS_STATE_DEINIT);

	venus_sfr_prपूर्णांक(hdev);
पूर्ण

अटल irqवापस_t venus_isr_thपढ़ो(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	स्थिर काष्ठा venus_resources *res;
	व्योम *pkt;
	u32 msg_ret;

	अगर (!hdev)
		वापस IRQ_NONE;

	res = hdev->core->res;
	pkt = hdev->pkt_buf;


	जबतक (!venus_अगरace_msgq_पढ़ो(hdev, pkt)) अणु
		msg_ret = hfi_process_msg_packet(core, pkt);
		चयन (msg_ret) अणु
		हाल HFI_MSG_EVENT_NOTIFY:
			venus_process_msg_sys_error(hdev, pkt);
			अवरोध;
		हाल HFI_MSG_SYS_INIT:
			venus_hfi_core_set_resource(core, res->vmem_id,
						    res->vmem_size,
						    res->vmem_addr,
						    hdev);
			अवरोध;
		हाल HFI_MSG_SYS_RELEASE_RESOURCE:
			complete(&hdev->release_resource);
			अवरोध;
		हाल HFI_MSG_SYS_PC_PREP:
			complete(&hdev->pwr_collapse_prep);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	venus_flush_debug_queue(hdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t venus_isr(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	u32 status;
	व्योम __iomem *cpu_cs_base;
	व्योम __iomem *wrapper_base;

	अगर (!hdev)
		वापस IRQ_NONE;

	cpu_cs_base = hdev->core->cpu_cs_base;
	wrapper_base = hdev->core->wrapper_base;

	status = पढ़ोl(wrapper_base + WRAPPER_INTR_STATUS);
	अगर (IS_V6(core)) अणु
		अगर (status & WRAPPER_INTR_STATUS_A2H_MASK ||
		    status & WRAPPER_INTR_STATUS_A2HWD_MASK_V6 ||
		    status & CPU_CS_SCIACMDARG0_INIT_IDLE_MSG_MASK)
			hdev->irq_status = status;
	पूर्ण अन्यथा अणु
		अगर (status & WRAPPER_INTR_STATUS_A2H_MASK ||
		    status & WRAPPER_INTR_STATUS_A2HWD_MASK ||
		    status & CPU_CS_SCIACMDARG0_INIT_IDLE_MSG_MASK)
			hdev->irq_status = status;
	पूर्ण
	ग_लिखोl(1, cpu_cs_base + CPU_CS_A2HSOFTINTCLR);
	अगर (!IS_V6(core))
		ग_लिखोl(status, wrapper_base + WRAPPER_INTR_CLEAR);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक venus_core_init(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा device *dev = core->dev;
	काष्ठा hfi_sys_get_property_pkt version_pkt;
	काष्ठा hfi_sys_init_pkt pkt;
	पूर्णांक ret;

	pkt_sys_init(&pkt, HFI_VIDEO_ARCH_OX);

	venus_set_state(hdev, VENUS_STATE_INIT);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
	अगर (ret)
		वापस ret;

	pkt_sys_image_version(&version_pkt);

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, &version_pkt, false);
	अगर (ret)
		dev_warn(dev, "failed to send image version pkt to fw\n");

	ret = venus_sys_set_शेष_properties(hdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_core_deinit(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);

	venus_set_state(hdev, VENUS_STATE_DEINIT);
	hdev->suspended = true;
	hdev->घातer_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_core_ping(काष्ठा venus_core *core, u32 cookie)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा hfi_sys_ping_pkt pkt;

	pkt_sys_ping(&pkt, cookie);

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
पूर्ण

अटल पूर्णांक venus_core_trigger_ssr(काष्ठा venus_core *core, u32 trigger_type)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा hfi_sys_test_ssr_pkt pkt;
	पूर्णांक ret;

	ret = pkt_sys_ssr_cmd(&pkt, trigger_type);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
पूर्ण

अटल पूर्णांक venus_session_init(काष्ठा venus_inst *inst, u32 session_type,
			      u32 codec)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_init_pkt pkt;
	पूर्णांक ret;

	ret = venus_sys_set_debug(hdev, venus_fw_debug);
	अगर (ret)
		जाओ err;

	ret = pkt_session_init(&pkt, inst, session_type, codec);
	अगर (ret)
		जाओ err;

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, true);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	venus_flush_debug_queue(hdev);
	वापस ret;
पूर्ण

अटल पूर्णांक venus_session_end(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा device *dev = hdev->core->dev;

	अगर (venus_fw_coverage) अणु
		अगर (venus_sys_set_coverage(hdev, venus_fw_coverage))
			dev_warn(dev, "fw coverage msg ON failed\n");
	पूर्ण

	वापस venus_session_cmd(inst, HFI_CMD_SYS_SESSION_END, true);
पूर्ण

अटल पूर्णांक venus_session_पात(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);

	venus_flush_debug_queue(hdev);

	वापस venus_session_cmd(inst, HFI_CMD_SYS_SESSION_ABORT, true);
पूर्ण

अटल पूर्णांक venus_session_flush(काष्ठा venus_inst *inst, u32 flush_mode)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_flush_pkt pkt;
	पूर्णांक ret;

	ret = pkt_session_flush(&pkt, inst, flush_mode);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, true);
पूर्ण

अटल पूर्णांक venus_session_start(काष्ठा venus_inst *inst)
अणु
	वापस venus_session_cmd(inst, HFI_CMD_SESSION_START, true);
पूर्ण

अटल पूर्णांक venus_session_stop(काष्ठा venus_inst *inst)
अणु
	वापस venus_session_cmd(inst, HFI_CMD_SESSION_STOP, true);
पूर्ण

अटल पूर्णांक venus_session_जारी(काष्ठा venus_inst *inst)
अणु
	वापस venus_session_cmd(inst, HFI_CMD_SESSION_CONTINUE, false);
पूर्ण

अटल पूर्णांक venus_session_etb(काष्ठा venus_inst *inst,
			     काष्ठा hfi_frame_data *in_frame)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	u32 session_type = inst->session_type;
	पूर्णांक ret;

	अगर (session_type == VIDC_SESSION_TYPE_DEC) अणु
		काष्ठा hfi_session_empty_buffer_compressed_pkt pkt;

		ret = pkt_session_etb_decoder(&pkt, inst, in_frame);
		अगर (ret)
			वापस ret;

		ret = venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
	पूर्ण अन्यथा अगर (session_type == VIDC_SESSION_TYPE_ENC) अणु
		काष्ठा hfi_session_empty_buffer_uncompressed_plane0_pkt pkt;

		ret = pkt_session_etb_encoder(&pkt, inst, in_frame);
		अगर (ret)
			वापस ret;

		ret = venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक venus_session_ftb(काष्ठा venus_inst *inst,
			     काष्ठा hfi_frame_data *out_frame)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_fill_buffer_pkt pkt;
	पूर्णांक ret;

	ret = pkt_session_ftb(&pkt, inst, out_frame);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, false);
पूर्ण

अटल पूर्णांक venus_session_set_buffers(काष्ठा venus_inst *inst,
				     काष्ठा hfi_buffer_desc *bd)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_set_buffers_pkt *pkt;
	u8 packet[IFACEQ_VAR_LARGE_PKT_SIZE];
	पूर्णांक ret;

	अगर (bd->buffer_type == HFI_BUFFER_INPUT)
		वापस 0;

	pkt = (काष्ठा hfi_session_set_buffers_pkt *)packet;

	ret = pkt_session_set_buffers(pkt, inst, bd);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
पूर्ण

अटल पूर्णांक venus_session_unset_buffers(काष्ठा venus_inst *inst,
				       काष्ठा hfi_buffer_desc *bd)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_release_buffer_pkt *pkt;
	u8 packet[IFACEQ_VAR_LARGE_PKT_SIZE];
	पूर्णांक ret;

	अगर (bd->buffer_type == HFI_BUFFER_INPUT)
		वापस 0;

	pkt = (काष्ठा hfi_session_release_buffer_pkt *)packet;

	ret = pkt_session_unset_buffers(pkt, inst, bd);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, pkt, true);
पूर्ण

अटल पूर्णांक venus_session_load_res(काष्ठा venus_inst *inst)
अणु
	वापस venus_session_cmd(inst, HFI_CMD_SESSION_LOAD_RESOURCES, true);
पूर्ण

अटल पूर्णांक venus_session_release_res(काष्ठा venus_inst *inst)
अणु
	वापस venus_session_cmd(inst, HFI_CMD_SESSION_RELEASE_RESOURCES, true);
पूर्ण

अटल पूर्णांक venus_session_parse_seq_hdr(काष्ठा venus_inst *inst, u32 seq_hdr,
				       u32 seq_hdr_len)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_parse_sequence_header_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_session_parse_sequence_header_pkt *)packet;

	ret = pkt_session_parse_seq_header(pkt, inst, seq_hdr, seq_hdr_len);
	अगर (ret)
		वापस ret;

	ret = venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक venus_session_get_seq_hdr(काष्ठा venus_inst *inst, u32 seq_hdr,
				     u32 seq_hdr_len)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_get_sequence_header_pkt *pkt;
	u8 packet[IFACEQ_VAR_SMALL_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_session_get_sequence_header_pkt *)packet;

	ret = pkt_session_get_seq_hdr(pkt, inst, seq_hdr, seq_hdr_len);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
पूर्ण

अटल पूर्णांक venus_session_set_property(काष्ठा venus_inst *inst, u32 ptype,
				      व्योम *pdata)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_LARGE_PKT_SIZE];
	पूर्णांक ret;

	pkt = (काष्ठा hfi_session_set_property_pkt *)packet;

	ret = pkt_session_set_property(pkt, inst, ptype, pdata);
	अगर (ret == -ENOTSUPP)
		वापस 0;
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, pkt, false);
पूर्ण

अटल पूर्णांक venus_session_get_property(काष्ठा venus_inst *inst, u32 ptype)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(inst->core);
	काष्ठा hfi_session_get_property_pkt pkt;
	पूर्णांक ret;

	ret = pkt_session_get_property(&pkt, inst, ptype);
	अगर (ret)
		वापस ret;

	वापस venus_अगरace_cmdq_ग_लिखो(hdev, &pkt, true);
पूर्ण

अटल पूर्णांक venus_resume(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	पूर्णांक ret = 0;

	mutex_lock(&hdev->lock);

	अगर (!hdev->suspended)
		जाओ unlock;

	ret = venus_घातer_on(hdev);

unlock:
	अगर (!ret)
		hdev->suspended = false;

	mutex_unlock(&hdev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक venus_suspend_1xx(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा device *dev = core->dev;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	u32 ctrl_status;
	पूर्णांक ret;

	अगर (!hdev->घातer_enabled || hdev->suspended)
		वापस 0;

	mutex_lock(&hdev->lock);
	ret = venus_is_valid_state(hdev);
	mutex_unlock(&hdev->lock);

	अगर (!ret) अणु
		dev_err(dev, "bad state, cannot suspend\n");
		वापस -EINVAL;
	पूर्ण

	ret = venus_prepare_घातer_collapse(hdev, true);
	अगर (ret) अणु
		dev_err(dev, "prepare for power collapse fail (%d)\n", ret);
		वापस ret;
	पूर्ण

	mutex_lock(&hdev->lock);

	अगर (hdev->last_packet_type != HFI_CMD_SYS_PC_PREP) अणु
		mutex_unlock(&hdev->lock);
		वापस -EINVAL;
	पूर्ण

	ret = venus_are_queues_empty(hdev);
	अगर (ret < 0 || !ret) अणु
		mutex_unlock(&hdev->lock);
		वापस -EINVAL;
	पूर्ण

	ctrl_status = पढ़ोl(cpu_cs_base + CPU_CS_SCIACMDARG0);
	अगर (!(ctrl_status & CPU_CS_SCIACMDARG0_PC_READY)) अणु
		mutex_unlock(&hdev->lock);
		वापस -EINVAL;
	पूर्ण

	ret = venus_घातer_off(hdev);
	अगर (ret) अणु
		mutex_unlock(&hdev->lock);
		वापस ret;
	पूर्ण

	hdev->suspended = true;

	mutex_unlock(&hdev->lock);

	वापस 0;
पूर्ण

अटल bool venus_cpu_and_video_core_idle(काष्ठा venus_hfi_device *hdev)
अणु
	व्योम __iomem *wrapper_base = hdev->core->wrapper_base;
	व्योम __iomem *wrapper_tz_base = hdev->core->wrapper_tz_base;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	u32 ctrl_status, cpu_status;

	अगर (IS_V6(hdev->core))
		cpu_status = पढ़ोl(wrapper_tz_base + WRAPPER_TZ_CPU_STATUS_V6);
	अन्यथा
		cpu_status = पढ़ोl(wrapper_base + WRAPPER_CPU_STATUS);
	ctrl_status = पढ़ोl(cpu_cs_base + CPU_CS_SCIACMDARG0);

	अगर (cpu_status & WRAPPER_CPU_STATUS_WFI &&
	    ctrl_status & CPU_CS_SCIACMDARG0_INIT_IDLE_MSG_MASK)
		वापस true;

	वापस false;
पूर्ण

अटल bool venus_cpu_idle_and_pc_पढ़ोy(काष्ठा venus_hfi_device *hdev)
अणु
	व्योम __iomem *wrapper_base = hdev->core->wrapper_base;
	व्योम __iomem *wrapper_tz_base = hdev->core->wrapper_tz_base;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	u32 ctrl_status, cpu_status;

	अगर (IS_V6(hdev->core))
		cpu_status = पढ़ोl(wrapper_tz_base + WRAPPER_TZ_CPU_STATUS_V6);
	अन्यथा
		cpu_status = पढ़ोl(wrapper_base + WRAPPER_CPU_STATUS);
	ctrl_status = पढ़ोl(cpu_cs_base + CPU_CS_SCIACMDARG0);

	अगर (cpu_status & WRAPPER_CPU_STATUS_WFI &&
	    ctrl_status & CPU_CS_SCIACMDARG0_PC_READY)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक venus_suspend_3xx(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा device *dev = core->dev;
	व्योम __iomem *cpu_cs_base = hdev->core->cpu_cs_base;
	u32 ctrl_status;
	bool val;
	पूर्णांक ret;

	अगर (!hdev->घातer_enabled || hdev->suspended)
		वापस 0;

	mutex_lock(&hdev->lock);
	ret = venus_is_valid_state(hdev);
	mutex_unlock(&hdev->lock);

	अगर (!ret) अणु
		dev_err(dev, "bad state, cannot suspend\n");
		वापस -EINVAL;
	पूर्ण

	ctrl_status = पढ़ोl(cpu_cs_base + CPU_CS_SCIACMDARG0);
	अगर (ctrl_status & CPU_CS_SCIACMDARG0_PC_READY)
		जाओ घातer_off;

	/*
	 * Power collapse sequence क्रम Venus 3xx and 4xx versions:
	 * 1. Check क्रम ARM9 and video core to be idle by checking WFI bit
	 *    (bit 0) in CPU status रेजिस्टर and by checking Idle (bit 30) in
	 *    Control status रेजिस्टर क्रम video core.
	 * 2. Send a command to prepare क्रम घातer collapse.
	 * 3. Check क्रम WFI and PC_READY bits.
	 */
	ret = पढ़ोx_poll_समयout(venus_cpu_and_video_core_idle, hdev, val, val,
				 1500, 100 * 1500);
	अगर (ret)
		वापस ret;

	ret = venus_prepare_घातer_collapse(hdev, false);
	अगर (ret) अणु
		dev_err(dev, "prepare for power collapse fail (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = पढ़ोx_poll_समयout(venus_cpu_idle_and_pc_पढ़ोy, hdev, val, val,
				 1500, 100 * 1500);
	अगर (ret)
		वापस ret;

घातer_off:
	mutex_lock(&hdev->lock);

	ret = venus_घातer_off(hdev);
	अगर (ret) अणु
		dev_err(dev, "venus_power_off (%d)\n", ret);
		mutex_unlock(&hdev->lock);
		वापस ret;
	पूर्ण

	hdev->suspended = true;

	mutex_unlock(&hdev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_suspend(काष्ठा venus_core *core)
अणु
	अगर (IS_V3(core) || IS_V4(core) || IS_V6(core))
		वापस venus_suspend_3xx(core);

	वापस venus_suspend_1xx(core);
पूर्ण

अटल स्थिर काष्ठा hfi_ops venus_hfi_ops = अणु
	.core_init			= venus_core_init,
	.core_deinit			= venus_core_deinit,
	.core_ping			= venus_core_ping,
	.core_trigger_ssr		= venus_core_trigger_ssr,

	.session_init			= venus_session_init,
	.session_end			= venus_session_end,
	.session_पात			= venus_session_पात,
	.session_flush			= venus_session_flush,
	.session_start			= venus_session_start,
	.session_stop			= venus_session_stop,
	.session_जारी		= venus_session_जारी,
	.session_etb			= venus_session_etb,
	.session_ftb			= venus_session_ftb,
	.session_set_buffers		= venus_session_set_buffers,
	.session_unset_buffers		= venus_session_unset_buffers,
	.session_load_res		= venus_session_load_res,
	.session_release_res		= venus_session_release_res,
	.session_parse_seq_hdr		= venus_session_parse_seq_hdr,
	.session_get_seq_hdr		= venus_session_get_seq_hdr,
	.session_set_property		= venus_session_set_property,
	.session_get_property		= venus_session_get_property,

	.resume				= venus_resume,
	.suspend			= venus_suspend,

	.isr				= venus_isr,
	.isr_thपढ़ो			= venus_isr_thपढ़ो,
पूर्ण;

व्योम venus_hfi_destroy(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);

	core->priv = शून्य;
	venus_पूर्णांकerface_queues_release(hdev);
	mutex_destroy(&hdev->lock);
	kमुक्त(hdev);
	core->ops = शून्य;
पूर्ण

पूर्णांक venus_hfi_create(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev;
	पूर्णांक ret;

	hdev = kzalloc(माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस -ENOMEM;

	mutex_init(&hdev->lock);

	hdev->core = core;
	hdev->suspended = true;
	core->priv = hdev;
	core->ops = &venus_hfi_ops;

	ret = venus_पूर्णांकerface_queues_init(hdev);
	अगर (ret)
		जाओ err_kमुक्त;

	वापस 0;

err_kमुक्त:
	kमुक्त(hdev);
	core->priv = शून्य;
	core->ops = शून्य;
	वापस ret;
पूर्ण

व्योम venus_hfi_queues_reinit(काष्ठा venus_core *core)
अणु
	काष्ठा venus_hfi_device *hdev = to_hfi_priv(core);
	काष्ठा hfi_queue_table_header *tbl_hdr;
	काष्ठा अगरace_queue *queue;
	काष्ठा hfi_sfr *sfr;
	अचिन्हित पूर्णांक i;

	mutex_lock(&hdev->lock);

	क्रम (i = 0; i < IFACEQ_NUM; i++) अणु
		queue = &hdev->queues[i];
		queue->qhdr =
			IFACEQ_GET_QHDR_START_ADDR(hdev->अगरaceq_table.kva, i);

		venus_set_qhdr_शेषs(queue->qhdr);

		queue->qhdr->start_addr = queue->qmem.da;

		अगर (i == IFACEQ_CMD_IDX)
			queue->qhdr->type |= HFI_HOST_TO_CTRL_CMD_Q;
		अन्यथा अगर (i == IFACEQ_MSG_IDX)
			queue->qhdr->type |= HFI_CTRL_TO_HOST_MSG_Q;
		अन्यथा अगर (i == IFACEQ_DBG_IDX)
			queue->qhdr->type |= HFI_CTRL_TO_HOST_DBG_Q;
	पूर्ण

	tbl_hdr = hdev->अगरaceq_table.kva;
	tbl_hdr->version = 0;
	tbl_hdr->size = IFACEQ_TABLE_SIZE;
	tbl_hdr->qhdr0_offset = माप(काष्ठा hfi_queue_table_header);
	tbl_hdr->qhdr_size = माप(काष्ठा hfi_queue_header);
	tbl_hdr->num_q = IFACEQ_NUM;
	tbl_hdr->num_active_q = IFACEQ_NUM;

	/*
	 * Set receive request to zero on debug queue as there is no
	 * need of पूर्णांकerrupt from video hardware क्रम debug messages
	 */
	queue = &hdev->queues[IFACEQ_DBG_IDX];
	queue->qhdr->rx_req = 0;

	sfr = hdev->sfr.kva;
	sfr->buf_size = ALIGNED_SFR_SIZE;

	/* ensure table and queue header काष्ठाs are settled in memory */
	wmb();

	mutex_unlock(&hdev->lock);
पूर्ण
