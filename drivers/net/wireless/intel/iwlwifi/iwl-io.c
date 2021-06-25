<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2003-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2015-2016 Intel Deutschland GmbH
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-io.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-fh.h"

व्योम iwl_ग_लिखो8(काष्ठा iwl_trans *trans, u32 ofs, u8 val)
अणु
	trace_iwlwअगरi_dev_ioग_लिखो8(trans->dev, ofs, val);
	iwl_trans_ग_लिखो8(trans, ofs, val);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो8);

व्योम iwl_ग_लिखो32(काष्ठा iwl_trans *trans, u32 ofs, u32 val)
अणु
	trace_iwlwअगरi_dev_ioग_लिखो32(trans->dev, ofs, val);
	iwl_trans_ग_लिखो32(trans, ofs, val);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो32);

व्योम iwl_ग_लिखो64(काष्ठा iwl_trans *trans, u64 ofs, u64 val)
अणु
	trace_iwlwअगरi_dev_ioग_लिखो64(trans->dev, ofs, val);
	iwl_trans_ग_लिखो32(trans, ofs, lower_32_bits(val));
	iwl_trans_ग_लिखो32(trans, ofs + 4, upper_32_bits(val));
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो64);

u32 iwl_पढ़ो32(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	u32 val = iwl_trans_पढ़ो32(trans, ofs);

	trace_iwlwअगरi_dev_ioपढ़ो32(trans->dev, ofs, val);
	वापस val;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो32);

#घोषणा IWL_POLL_INTERVAL 10	/* microseconds */

पूर्णांक iwl_poll_bit(काष्ठा iwl_trans *trans, u32 addr,
		 u32 bits, u32 mask, पूर्णांक समयout)
अणु
	पूर्णांक t = 0;

	करो अणु
		अगर ((iwl_पढ़ो32(trans, addr) & mask) == (bits & mask))
			वापस t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	पूर्ण जबतक (t < समयout);

	वापस -ETIMEDOUT;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_poll_bit);

u32 iwl_पढ़ो_direct32(काष्ठा iwl_trans *trans, u32 reg)
अणु
	u32 value = 0x5a5a5a5a;

	अगर (iwl_trans_grab_nic_access(trans)) अणु
		value = iwl_पढ़ो32(trans, reg);
		iwl_trans_release_nic_access(trans);
	पूर्ण

	वापस value;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो_direct32);

व्योम iwl_ग_लिखो_direct32(काष्ठा iwl_trans *trans, u32 reg, u32 value)
अणु
	अगर (iwl_trans_grab_nic_access(trans)) अणु
		iwl_ग_लिखो32(trans, reg, value);
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो_direct32);

व्योम iwl_ग_लिखो_direct64(काष्ठा iwl_trans *trans, u64 reg, u64 value)
अणु
	अगर (iwl_trans_grab_nic_access(trans)) अणु
		iwl_ग_लिखो64(trans, reg, value);
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो_direct64);

पूर्णांक iwl_poll_direct_bit(काष्ठा iwl_trans *trans, u32 addr, u32 mask,
			पूर्णांक समयout)
अणु
	पूर्णांक t = 0;

	करो अणु
		अगर ((iwl_पढ़ो_direct32(trans, addr) & mask) == mask)
			वापस t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	पूर्ण जबतक (t < समयout);

	वापस -ETIMEDOUT;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_poll_direct_bit);

u32 iwl_पढ़ो_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	u32 val = iwl_trans_पढ़ो_prph(trans, ofs);
	trace_iwlwअगरi_dev_ioपढ़ो_prph32(trans->dev, ofs, val);
	वापस val;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो_prph_no_grab);

व्योम iwl_ग_लिखो_prph_no_grab(काष्ठा iwl_trans *trans, u32 ofs, u32 val)
अणु
	trace_iwlwअगरi_dev_ioग_लिखो_prph32(trans->dev, ofs, val);
	iwl_trans_ग_लिखो_prph(trans, ofs, val);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो_prph_no_grab);

व्योम iwl_ग_लिखो_prph64_no_grab(काष्ठा iwl_trans *trans, u64 ofs, u64 val)
अणु
	trace_iwlwअगरi_dev_ioग_लिखो_prph64(trans->dev, ofs, val);
	iwl_ग_लिखो_prph_no_grab(trans, ofs, val & 0xffffffff);
	iwl_ग_लिखो_prph_no_grab(trans, ofs + 4, val >> 32);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो_prph64_no_grab);

u32 iwl_पढ़ो_prph(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	u32 val = 0x5a5a5a5a;

	अगर (iwl_trans_grab_nic_access(trans)) अणु
		val = iwl_पढ़ो_prph_no_grab(trans, ofs);
		iwl_trans_release_nic_access(trans);
	पूर्ण
	वापस val;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो_prph);

व्योम iwl_ग_लिखो_prph_delay(काष्ठा iwl_trans *trans, u32 ofs, u32 val, u32 delay_ms)
अणु
	अगर (iwl_trans_grab_nic_access(trans)) अणु
		mdelay(delay_ms);
		iwl_ग_लिखो_prph_no_grab(trans, ofs, val);
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_ग_लिखो_prph_delay);

पूर्णांक iwl_poll_prph_bit(काष्ठा iwl_trans *trans, u32 addr,
		      u32 bits, u32 mask, पूर्णांक समयout)
अणु
	पूर्णांक t = 0;

	करो अणु
		अगर ((iwl_पढ़ो_prph(trans, addr) & mask) == (bits & mask))
			वापस t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	पूर्ण जबतक (t < समयout);

	वापस -ETIMEDOUT;
पूर्ण

व्योम iwl_set_bits_prph(काष्ठा iwl_trans *trans, u32 ofs, u32 mask)
अणु
	अगर (iwl_trans_grab_nic_access(trans)) अणु
		iwl_ग_लिखो_prph_no_grab(trans, ofs,
				       iwl_पढ़ो_prph_no_grab(trans, ofs) |
				       mask);
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_set_bits_prph);

व्योम iwl_set_bits_mask_prph(काष्ठा iwl_trans *trans, u32 ofs,
			    u32 bits, u32 mask)
अणु
	अगर (iwl_trans_grab_nic_access(trans)) अणु
		iwl_ग_लिखो_prph_no_grab(trans, ofs,
				       (iwl_पढ़ो_prph_no_grab(trans, ofs) &
					mask) | bits);
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_set_bits_mask_prph);

व्योम iwl_clear_bits_prph(काष्ठा iwl_trans *trans, u32 ofs, u32 mask)
अणु
	u32 val;

	अगर (iwl_trans_grab_nic_access(trans)) अणु
		val = iwl_पढ़ो_prph_no_grab(trans, ofs);
		iwl_ग_लिखो_prph_no_grab(trans, ofs, (val & ~mask));
		iwl_trans_release_nic_access(trans);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_clear_bits_prph);

व्योम iwl_क्रमce_nmi(काष्ठा iwl_trans *trans)
अणु
	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_9000)
		iwl_ग_लिखो_prph_delay(trans, DEVICE_SET_NMI_REG,
				     DEVICE_SET_NMI_VAL_DRV, 1);
	अन्यथा अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		iwl_ग_लिखो_umac_prph(trans, UREG_NIC_SET_NMI_DRIVER,
				UREG_NIC_SET_NMI_DRIVER_NMI_FROM_DRIVER);
	अन्यथा
		iwl_ग_लिखो_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_NMI_BIT);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_क्रमce_nmi);

अटल स्थिर अक्षर *get_rfh_string(पूर्णांक cmd)
अणु
#घोषणा IWL_CMD(x) हाल x: वापस #x
#घोषणा IWL_CMD_MQ(arg, reg, q) अणु अगर (arg == reg(q)) वापस #reg; पूर्ण

	पूर्णांक i;

	क्रम (i = 0; i < IWL_MAX_RX_HW_QUEUES; i++) अणु
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_BA_LSB, i);
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_WIDX, i);
		IWL_CMD_MQ(cmd, RFH_Q_FRBDCB_RIDX, i);
		IWL_CMD_MQ(cmd, RFH_Q_URBD_STTS_WPTR_LSB, i);
	पूर्ण

	चयन (cmd) अणु
	IWL_CMD(RFH_RXF_DMA_CFG);
	IWL_CMD(RFH_GEN_CFG);
	IWL_CMD(RFH_GEN_STATUS);
	IWL_CMD(FH_TSSR_TX_STATUS_REG);
	IWL_CMD(FH_TSSR_TX_ERROR_REG);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
#अघोषित IWL_CMD_MQ
पूर्ण

काष्ठा reg अणु
	u32 addr;
	bool is64;
पूर्ण;

अटल पूर्णांक iwl_dump_rfh(काष्ठा iwl_trans *trans, अक्षर **buf)
अणु
	पूर्णांक i, q;
	पूर्णांक num_q = trans->num_rx_queues;
	अटल स्थिर u32 rfh_tbl[] = अणु
		RFH_RXF_DMA_CFG,
		RFH_GEN_CFG,
		RFH_GEN_STATUS,
		FH_TSSR_TX_STATUS_REG,
		FH_TSSR_TX_ERROR_REG,
	पूर्ण;
	अटल स्थिर काष्ठा reg rfh_mq_tbl[] = अणु
		अणु RFH_Q0_FRBDCB_BA_LSB, true पूर्ण,
		अणु RFH_Q0_FRBDCB_WIDX, false पूर्ण,
		अणु RFH_Q0_FRBDCB_RIDX, false पूर्ण,
		अणु RFH_Q0_URBD_STTS_WPTR_LSB, true पूर्ण,
	पूर्ण;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (buf) अणु
		पूर्णांक pos = 0;
		/*
		 * Register (up to 34 क्रम name + 8 blank/q क्रम MQ): 40 अक्षरs
		 * Colon + space: 2 अक्षरacters
		 * 0X%08x: 10 अक्षरacters
		 * New line: 1 अक्षरacter
		 * Total of 53 अक्षरacters
		 */
		माप_प्रकार bufsz = ARRAY_SIZE(rfh_tbl) * 53 +
			       ARRAY_SIZE(rfh_mq_tbl) * 53 * num_q + 40;

		*buf = kदो_स्मृति(bufsz, GFP_KERNEL);
		अगर (!*buf)
			वापस -ENOMEM;

		pos += scnम_लिखो(*buf + pos, bufsz - pos,
				"RFH register values:\n");

		क्रम (i = 0; i < ARRAY_SIZE(rfh_tbl); i++)
			pos += scnम_लिखो(*buf + pos, bufsz - pos,
				"%40s: 0X%08x\n",
				get_rfh_string(rfh_tbl[i]),
				iwl_पढ़ो_prph(trans, rfh_tbl[i]));

		क्रम (i = 0; i < ARRAY_SIZE(rfh_mq_tbl); i++)
			क्रम (q = 0; q < num_q; q++) अणु
				u32 addr = rfh_mq_tbl[i].addr;

				addr += q * (rfh_mq_tbl[i].is64 ? 8 : 4);
				pos += scnम_लिखो(*buf + pos, bufsz - pos,
					"%34s(q %2d): 0X%08x\n",
					get_rfh_string(addr), q,
					iwl_पढ़ो_prph(trans, addr));
			पूर्ण

		वापस pos;
	पूर्ण
#पूर्ण_अगर

	IWL_ERR(trans, "RFH register values:\n");
	क्रम (i = 0; i < ARRAY_SIZE(rfh_tbl); i++)
		IWL_ERR(trans, "  %34s: 0X%08x\n",
			get_rfh_string(rfh_tbl[i]),
			iwl_पढ़ो_prph(trans, rfh_tbl[i]));

	क्रम (i = 0; i < ARRAY_SIZE(rfh_mq_tbl); i++)
		क्रम (q = 0; q < num_q; q++) अणु
			u32 addr = rfh_mq_tbl[i].addr;

			addr += q * (rfh_mq_tbl[i].is64 ? 8 : 4);
			IWL_ERR(trans, "  %34s(q %d): 0X%08x\n",
				get_rfh_string(addr), q,
				iwl_पढ़ो_prph(trans, addr));
		पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *get_fh_string(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	IWL_CMD(FH_RSCSR_CHNL0_STTS_WPTR_REG);
	IWL_CMD(FH_RSCSR_CHNL0_RBDCB_BASE_REG);
	IWL_CMD(FH_RSCSR_CHNL0_WPTR);
	IWL_CMD(FH_MEM_RCSR_CHNL0_CONFIG_REG);
	IWL_CMD(FH_MEM_RSSR_SHARED_CTRL_REG);
	IWL_CMD(FH_MEM_RSSR_RX_STATUS_REG);
	IWL_CMD(FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV);
	IWL_CMD(FH_TSSR_TX_STATUS_REG);
	IWL_CMD(FH_TSSR_TX_ERROR_REG);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
#अघोषित IWL_CMD
पूर्ण

पूर्णांक iwl_dump_fh(काष्ठा iwl_trans *trans, अक्षर **buf)
अणु
	पूर्णांक i;
	अटल स्थिर u32 fh_tbl[] = अणु
		FH_RSCSR_CHNL0_STTS_WPTR_REG,
		FH_RSCSR_CHNL0_RBDCB_BASE_REG,
		FH_RSCSR_CHNL0_WPTR,
		FH_MEM_RCSR_CHNL0_CONFIG_REG,
		FH_MEM_RSSR_SHARED_CTRL_REG,
		FH_MEM_RSSR_RX_STATUS_REG,
		FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV,
		FH_TSSR_TX_STATUS_REG,
		FH_TSSR_TX_ERROR_REG
	पूर्ण;

	अगर (trans->trans_cfg->mq_rx_supported)
		वापस iwl_dump_rfh(trans, buf);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (buf) अणु
		पूर्णांक pos = 0;
		माप_प्रकार bufsz = ARRAY_SIZE(fh_tbl) * 48 + 40;

		*buf = kदो_स्मृति(bufsz, GFP_KERNEL);
		अगर (!*buf)
			वापस -ENOMEM;

		pos += scnम_लिखो(*buf + pos, bufsz - pos,
				"FH register values:\n");

		क्रम (i = 0; i < ARRAY_SIZE(fh_tbl); i++)
			pos += scnम_लिखो(*buf + pos, bufsz - pos,
				"  %34s: 0X%08x\n",
				get_fh_string(fh_tbl[i]),
				iwl_पढ़ो_direct32(trans, fh_tbl[i]));

		वापस pos;
	पूर्ण
#पूर्ण_अगर

	IWL_ERR(trans, "FH register values:\n");
	क्रम (i = 0; i <  ARRAY_SIZE(fh_tbl); i++)
		IWL_ERR(trans, "  %34s: 0X%08x\n",
			get_fh_string(fh_tbl[i]),
			iwl_पढ़ो_direct32(trans, fh_tbl[i]));

	वापस 0;
पूर्ण

पूर्णांक iwl_finish_nic_init(काष्ठा iwl_trans *trans,
			स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans)
अणु
	पूर्णांक err;

	अगर (cfg_trans->bisr_workaround) अणु
		/* ensure the TOP FSM isn't still in previous reset */
		mdelay(2);
	पूर्ण

	/*
	 * Set "initialization complete" bit to move adapter from
	 * D0U* --> D0A* (घातered-up active) state.
	 */
	iwl_set_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	अगर (cfg_trans->device_family == IWL_DEVICE_FAMILY_8000)
		udelay(2);

	/*
	 * Wait क्रम घड़ी stabilization; once stabilized, access to
	 * device-पूर्णांकernal resources is supported, e.g. iwl_ग_लिखो_prph()
	 * and accesses to uCode SRAM.
	 */
	err = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			   CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			   25000);
	अगर (err < 0)
		IWL_DEBUG_INFO(trans, "Failed to wake NIC\n");

	अगर (cfg_trans->bisr_workaround) अणु
		/* ensure BISR shअगरt has finished */
		udelay(200);
	पूर्ण

	वापस err < 0 ? err : 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_finish_nic_init);

व्योम iwl_trans_sync_nmi_with_addr(काष्ठा iwl_trans *trans, u32 पूर्णांकa_addr,
				  u32 sw_err_bit)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + IWL_TRANS_NMI_TIMEOUT;
	bool पूर्णांकerrupts_enabled = test_bit(STATUS_INT_ENABLED, &trans->status);

	/* अगर the पूर्णांकerrupts were alपढ़ोy disabled, there is no poपूर्णांक in
	 * calling iwl_disable_पूर्णांकerrupts
	 */
	अगर (पूर्णांकerrupts_enabled)
		iwl_trans_पूर्णांकerrupts(trans, false);

	iwl_क्रमce_nmi(trans);
	जबतक (समय_after(समयout, jअगरfies)) अणु
		u32 पूर्णांकa_hw = iwl_पढ़ो32(trans, पूर्णांकa_addr);

		/* Error detected by uCode */
		अगर (पूर्णांकa_hw & sw_err_bit) अणु
			/* Clear causes रेजिस्टर */
			iwl_ग_लिखो32(trans, पूर्णांकa_addr, पूर्णांकa_hw & sw_err_bit);
			अवरोध;
		पूर्ण

		mdelay(1);
	पूर्ण

	/* enable पूर्णांकerrupts only अगर there were alपढ़ोy enabled beक्रमe this
	 * function to aव्योम a हाल were the driver enable पूर्णांकerrupts beक्रमe
	 * proper configurations were made
	 */
	अगर (पूर्णांकerrupts_enabled)
		iwl_trans_पूर्णांकerrupts(trans, true);

	iwl_trans_fw_error(trans);
पूर्ण
