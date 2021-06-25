<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci_ids.h>

#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "icp_qat_hal.h"
#समावेश "icp_qat_uclo.h"

#घोषणा BAD_REGADDR	       0xffff
#घोषणा MAX_RETRY_TIMES	   10000
#घोषणा INIT_CTX_ARB_VALUE	0x0
#घोषणा INIT_CTX_ENABLE_VALUE     0x0
#घोषणा INIT_PC_VALUE	     0x0
#घोषणा INIT_WAKEUP_EVENTS_VALUE  0x1
#घोषणा INIT_SIG_EVENTS_VALUE     0x1
#घोषणा INIT_CCENABLE_VALUE       0x2000
#घोषणा RST_CSR_QAT_LSB	   20
#घोषणा RST_CSR_AE_LSB		  0
#घोषणा MC_TIMESTAMP_ENABLE       (0x1 << 7)

#घोषणा IGNORE_W1C_MASK ((~(1 << CE_BREAKPOINT_BITPOS)) & \
	(~(1 << CE_CNTL_STORE_PARITY_ERROR_BITPOS)) & \
	(~(1 << CE_REG_PAR_ERR_BITPOS)))
#घोषणा INSERT_IMMED_GPRA_CONST(inst, स्थिर_val) \
	(inst = ((inst & 0xFFFF00C03FFull) | \
		((((स्थिर_val) << 12) & 0x0FF00000ull) | \
		(((स्थिर_val) << 10) & 0x0003FC00ull))))
#घोषणा INSERT_IMMED_GPRB_CONST(inst, स्थिर_val) \
	(inst = ((inst & 0xFFFF00FFF00ull) | \
		((((स्थिर_val) << 12) & 0x0FF00000ull) | \
		(((स्थिर_val) <<  0) & 0x000000FFull))))

#घोषणा AE(handle, ae) ((handle)->hal_handle->aes[ae])

अटल स्थिर u64 inst_4b[] = अणु
	0x0F0400C0000ull, 0x0F4400C0000ull, 0x0F040000300ull, 0x0F440000300ull,
	0x0FC066C0000ull, 0x0F0000C0300ull, 0x0F0000C0300ull, 0x0F0000C0300ull,
	0x0A021000000ull
पूर्ण;

अटल स्थिर u64 inst[] = अणु
	0x0F0000C0000ull, 0x0F000000380ull, 0x0D805000011ull, 0x0FC082C0300ull,
	0x0F0000C0300ull, 0x0F0000C0300ull, 0x0F0000C0300ull, 0x0F0000C0300ull,
	0x0A0643C0000ull, 0x0BAC0000301ull, 0x0D802000101ull, 0x0F0000C0001ull,
	0x0FC066C0001ull, 0x0F0000C0300ull, 0x0F0000C0300ull, 0x0F0000C0300ull,
	0x0F000400300ull, 0x0A0610C0000ull, 0x0BAC0000301ull, 0x0D804400101ull,
	0x0A0580C0000ull, 0x0A0581C0000ull, 0x0A0582C0000ull, 0x0A0583C0000ull,
	0x0A0584C0000ull, 0x0A0585C0000ull, 0x0A0586C0000ull, 0x0A0587C0000ull,
	0x0A0588C0000ull, 0x0A0589C0000ull, 0x0A058AC0000ull, 0x0A058BC0000ull,
	0x0A058CC0000ull, 0x0A058DC0000ull, 0x0A058EC0000ull, 0x0A058FC0000ull,
	0x0A05C0C0000ull, 0x0A05C1C0000ull, 0x0A05C2C0000ull, 0x0A05C3C0000ull,
	0x0A05C4C0000ull, 0x0A05C5C0000ull, 0x0A05C6C0000ull, 0x0A05C7C0000ull,
	0x0A05C8C0000ull, 0x0A05C9C0000ull, 0x0A05CAC0000ull, 0x0A05CBC0000ull,
	0x0A05CCC0000ull, 0x0A05CDC0000ull, 0x0A05CEC0000ull, 0x0A05CFC0000ull,
	0x0A0400C0000ull, 0x0B0400C0000ull, 0x0A0401C0000ull, 0x0B0401C0000ull,
	0x0A0402C0000ull, 0x0B0402C0000ull, 0x0A0403C0000ull, 0x0B0403C0000ull,
	0x0A0404C0000ull, 0x0B0404C0000ull, 0x0A0405C0000ull, 0x0B0405C0000ull,
	0x0A0406C0000ull, 0x0B0406C0000ull, 0x0A0407C0000ull, 0x0B0407C0000ull,
	0x0A0408C0000ull, 0x0B0408C0000ull, 0x0A0409C0000ull, 0x0B0409C0000ull,
	0x0A040AC0000ull, 0x0B040AC0000ull, 0x0A040BC0000ull, 0x0B040BC0000ull,
	0x0A040CC0000ull, 0x0B040CC0000ull, 0x0A040DC0000ull, 0x0B040DC0000ull,
	0x0A040EC0000ull, 0x0B040EC0000ull, 0x0A040FC0000ull, 0x0B040FC0000ull,
	0x0D81581C010ull, 0x0E000010000ull, 0x0E000010000ull,
पूर्ण;

व्योम qat_hal_set_live_ctx(काष्ठा icp_qat_fw_loader_handle *handle,
			  अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask)
अणु
	AE(handle, ae).live_ctx_mask = ctx_mask;
पूर्ण

#घोषणा CSR_RETRY_TIMES 500
अटल पूर्णांक qat_hal_rd_ae_csr(काष्ठा icp_qat_fw_loader_handle *handle,
			     अचिन्हित अक्षर ae, अचिन्हित पूर्णांक csr)
अणु
	अचिन्हित पूर्णांक iterations = CSR_RETRY_TIMES;
	पूर्णांक value;

	करो अणु
		value = GET_AE_CSR(handle, ae, csr);
		अगर (!(GET_AE_CSR(handle, ae, LOCAL_CSR_STATUS) & LCS_STATUS))
			वापस value;
	पूर्ण जबतक (iterations--);

	pr_err("QAT: Read CSR timeout\n");
	वापस 0;
पूर्ण

अटल पूर्णांक qat_hal_wr_ae_csr(काष्ठा icp_qat_fw_loader_handle *handle,
			     अचिन्हित अक्षर ae, अचिन्हित पूर्णांक csr,
			     अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक iterations = CSR_RETRY_TIMES;

	करो अणु
		SET_AE_CSR(handle, ae, csr, value);
		अगर (!(GET_AE_CSR(handle, ae, LOCAL_CSR_STATUS) & LCS_STATUS))
			वापस 0;
	पूर्ण जबतक (iterations--);

	pr_err("QAT: Write CSR Timeout\n");
	वापस -EFAULT;
पूर्ण

अटल व्योम qat_hal_get_wakeup_event(काष्ठा icp_qat_fw_loader_handle *handle,
				     अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				     अचिन्हित पूर्णांक *events)
अणु
	अचिन्हित पूर्णांक cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
	*events = qat_hal_rd_ae_csr(handle, ae, CTX_WAKEUP_EVENTS_INसूचीECT);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
पूर्ण

अटल पूर्णांक qat_hal_रुको_cycles(काष्ठा icp_qat_fw_loader_handle *handle,
			       अचिन्हित अक्षर ae, अचिन्हित पूर्णांक cycles,
			       पूर्णांक chk_inactive)
अणु
	अचिन्हित पूर्णांक base_cnt = 0, cur_cnt = 0;
	अचिन्हित पूर्णांक csr = (1 << ACS_ABO_BITPOS);
	पूर्णांक बार = MAX_RETRY_TIMES;
	पूर्णांक elapsed_cycles = 0;

	base_cnt = qat_hal_rd_ae_csr(handle, ae, PROखाता_COUNT);
	base_cnt &= 0xffff;
	जबतक ((पूर्णांक)cycles > elapsed_cycles && बार--) अणु
		अगर (chk_inactive)
			csr = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);

		cur_cnt = qat_hal_rd_ae_csr(handle, ae, PROखाता_COUNT);
		cur_cnt &= 0xffff;
		elapsed_cycles = cur_cnt - base_cnt;

		अगर (elapsed_cycles < 0)
			elapsed_cycles += 0x10000;

		/* ensure at least 8 समय cycles elapsed in रुको_cycles */
		अगर (elapsed_cycles >= 8 && !(csr & (1 << ACS_ABO_BITPOS)))
			वापस 0;
	पूर्ण
	अगर (बार < 0) अणु
		pr_err("QAT: wait_num_cycles time out\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा CLR_BIT(wrd, bit) ((wrd) & ~(1 << (bit)))
#घोषणा SET_BIT(wrd, bit) ((wrd) | 1 << (bit))

पूर्णांक qat_hal_set_ae_ctx_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			    अचिन्हित अक्षर ae, अचिन्हित अक्षर mode)
अणु
	अचिन्हित पूर्णांक csr, new_csr;

	अगर (mode != 4 && mode != 8) अणु
		pr_err("QAT: bad ctx mode=%d\n", mode);
		वापस -EINVAL;
	पूर्ण

	/* Sets the accelaration engine context mode to either four or eight */
	csr = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	csr = IGNORE_W1C_MASK & csr;
	new_csr = (mode == 4) ?
		SET_BIT(csr, CE_INUSE_CONTEXTS_BITPOS) :
		CLR_BIT(csr, CE_INUSE_CONTEXTS_BITPOS);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, new_csr);
	वापस 0;
पूर्ण

पूर्णांक qat_hal_set_ae_nn_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			   अचिन्हित अक्षर ae, अचिन्हित अक्षर mode)
अणु
	अचिन्हित पूर्णांक csr, new_csr;

	csr = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	csr &= IGNORE_W1C_MASK;

	new_csr = (mode) ?
		SET_BIT(csr, CE_NN_MODE_BITPOS) :
		CLR_BIT(csr, CE_NN_MODE_BITPOS);

	अगर (new_csr != csr)
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, new_csr);

	वापस 0;
पूर्ण

पूर्णांक qat_hal_set_ae_lm_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			   अचिन्हित अक्षर ae, क्रमागत icp_qat_uof_regtype lm_type,
			   अचिन्हित अक्षर mode)
अणु
	अचिन्हित पूर्णांक csr, new_csr;

	csr = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	csr &= IGNORE_W1C_MASK;
	चयन (lm_type) अणु
	हाल ICP_LMEM0:
		new_csr = (mode) ?
			SET_BIT(csr, CE_LMADDR_0_GLOBAL_BITPOS) :
			CLR_BIT(csr, CE_LMADDR_0_GLOBAL_BITPOS);
		अवरोध;
	हाल ICP_LMEM1:
		new_csr = (mode) ?
			SET_BIT(csr, CE_LMADDR_1_GLOBAL_BITPOS) :
			CLR_BIT(csr, CE_LMADDR_1_GLOBAL_BITPOS);
		अवरोध;
	हाल ICP_LMEM2:
		new_csr = (mode) ?
			SET_BIT(csr, CE_LMADDR_2_GLOBAL_BITPOS) :
			CLR_BIT(csr, CE_LMADDR_2_GLOBAL_BITPOS);
		अवरोध;
	हाल ICP_LMEM3:
		new_csr = (mode) ?
			SET_BIT(csr, CE_LMADDR_3_GLOBAL_BITPOS) :
			CLR_BIT(csr, CE_LMADDR_3_GLOBAL_BITPOS);
		अवरोध;
	शेष:
		pr_err("QAT: lmType = 0x%x\n", lm_type);
		वापस -EINVAL;
	पूर्ण

	अगर (new_csr != csr)
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, new_csr);
	वापस 0;
पूर्ण

व्योम qat_hal_set_ae_tindex_mode(काष्ठा icp_qat_fw_loader_handle *handle,
				अचिन्हित अक्षर ae, अचिन्हित अक्षर mode)
अणु
	अचिन्हित पूर्णांक csr, new_csr;

	csr = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	csr &= IGNORE_W1C_MASK;
	new_csr = (mode) ?
		  SET_BIT(csr, CE_T_INDEX_GLOBAL_BITPOS) :
		  CLR_BIT(csr, CE_T_INDEX_GLOBAL_BITPOS);
	अगर (new_csr != csr)
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, new_csr);
पूर्ण

अटल अचिन्हित लघु qat_hal_get_reg_addr(अचिन्हित पूर्णांक type,
					   अचिन्हित लघु reg_num)
अणु
	अचिन्हित लघु reg_addr;

	चयन (type) अणु
	हाल ICP_GPA_ABS:
	हाल ICP_GPB_ABS:
		reg_addr = 0x80 | (reg_num & 0x7f);
		अवरोध;
	हाल ICP_GPA_REL:
	हाल ICP_GPB_REL:
		reg_addr = reg_num & 0x1f;
		अवरोध;
	हाल ICP_SR_RD_REL:
	हाल ICP_SR_WR_REL:
	हाल ICP_SR_REL:
		reg_addr = 0x180 | (reg_num & 0x1f);
		अवरोध;
	हाल ICP_SR_ABS:
		reg_addr = 0x140 | ((reg_num & 0x3) << 1);
		अवरोध;
	हाल ICP_DR_RD_REL:
	हाल ICP_DR_WR_REL:
	हाल ICP_DR_REL:
		reg_addr = 0x1c0 | (reg_num & 0x1f);
		अवरोध;
	हाल ICP_DR_ABS:
		reg_addr = 0x100 | ((reg_num & 0x3) << 1);
		अवरोध;
	हाल ICP_NEIGH_REL:
		reg_addr = 0x280 | (reg_num & 0x1f);
		अवरोध;
	हाल ICP_LMEM0:
		reg_addr = 0x200;
		अवरोध;
	हाल ICP_LMEM1:
		reg_addr = 0x220;
		अवरोध;
	हाल ICP_LMEM2:
		reg_addr = 0x2c0;
		अवरोध;
	हाल ICP_LMEM3:
		reg_addr = 0x2e0;
		अवरोध;
	हाल ICP_NO_DEST:
		reg_addr = 0x300 | (reg_num & 0xff);
		अवरोध;
	शेष:
		reg_addr = BAD_REGADDR;
		अवरोध;
	पूर्ण
	वापस reg_addr;
पूर्ण

व्योम qat_hal_reset(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित पूर्णांक reset_mask = handle->chip_info->icp_rst_mask;
	अचिन्हित पूर्णांक reset_csr = handle->chip_info->icp_rst_csr;
	अचिन्हित पूर्णांक csr_val;

	csr_val = GET_CAP_CSR(handle, reset_csr);
	csr_val |= reset_mask;
	SET_CAP_CSR(handle, reset_csr, csr_val);
पूर्ण

अटल व्योम qat_hal_wr_indr_csr(काष्ठा icp_qat_fw_loader_handle *handle,
				अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask,
				अचिन्हित पूर्णांक ae_csr, अचिन्हित पूर्णांक csr_val)
अणु
	अचिन्हित पूर्णांक ctx, cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);

	क्रम (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) अणु
		अगर (!(ctx_mask & (1 << ctx)))
			जारी;
		qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
		qat_hal_wr_ae_csr(handle, ae, ae_csr, csr_val);
	पूर्ण

	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
पूर्ण

अटल अचिन्हित पूर्णांक qat_hal_rd_indr_csr(काष्ठा icp_qat_fw_loader_handle *handle,
				अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				अचिन्हित पूर्णांक ae_csr)
अणु
	अचिन्हित पूर्णांक cur_ctx, csr_val;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
	csr_val = qat_hal_rd_ae_csr(handle, ae, ae_csr);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);

	वापस csr_val;
पूर्ण

अटल व्योम qat_hal_put_sig_event(काष्ठा icp_qat_fw_loader_handle *handle,
				  अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask,
				  अचिन्हित पूर्णांक events)
अणु
	अचिन्हित पूर्णांक ctx, cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	क्रम (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) अणु
		अगर (!(ctx_mask & (1 << ctx)))
			जारी;
		qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
		qat_hal_wr_ae_csr(handle, ae, CTX_SIG_EVENTS_INसूचीECT, events);
	पूर्ण
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
पूर्ण

अटल व्योम qat_hal_put_wakeup_event(काष्ठा icp_qat_fw_loader_handle *handle,
				     अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask,
				     अचिन्हित पूर्णांक events)
अणु
	अचिन्हित पूर्णांक ctx, cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	क्रम (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) अणु
		अगर (!(ctx_mask & (1 << ctx)))
			जारी;
		qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
		qat_hal_wr_ae_csr(handle, ae, CTX_WAKEUP_EVENTS_INसूचीECT,
				  events);
	पूर्ण
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
पूर्ण

अटल पूर्णांक qat_hal_check_ae_alive(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित पूर्णांक base_cnt, cur_cnt;
	अचिन्हित अक्षर ae;
	पूर्णांक बार = MAX_RETRY_TIMES;

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		base_cnt = qat_hal_rd_ae_csr(handle, ae, PROखाता_COUNT);
		base_cnt &= 0xffff;

		करो अणु
			cur_cnt = qat_hal_rd_ae_csr(handle, ae, PROखाता_COUNT);
			cur_cnt &= 0xffff;
		पूर्ण जबतक (बार-- && (cur_cnt == base_cnt));

		अगर (बार < 0) अणु
			pr_err("QAT: AE%d is inactive!!\n", ae);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qat_hal_check_ae_active(काष्ठा icp_qat_fw_loader_handle *handle,
			    अचिन्हित पूर्णांक ae)
अणु
	अचिन्हित पूर्णांक enable = 0, active = 0;

	enable = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	active = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);
	अगर ((enable & (0xff << CE_ENABLE_BITPOS)) ||
	    (active & (1 << ACS_ABO_BITPOS)))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम qat_hal_reset_बारtamp(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित पूर्णांक misc_ctl_csr, misc_ctl;
	अचिन्हित अक्षर ae;

	misc_ctl_csr = handle->chip_info->misc_ctl_csr;
	/* stop the बारtamp समयrs */
	misc_ctl = GET_CAP_CSR(handle, misc_ctl_csr);
	अगर (misc_ctl & MC_TIMESTAMP_ENABLE)
		SET_CAP_CSR(handle, misc_ctl_csr, misc_ctl &
			    (~MC_TIMESTAMP_ENABLE));

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		qat_hal_wr_ae_csr(handle, ae, TIMESTAMP_LOW, 0);
		qat_hal_wr_ae_csr(handle, ae, TIMESTAMP_HIGH, 0);
	पूर्ण
	/* start बारtamp समयrs */
	SET_CAP_CSR(handle, misc_ctl_csr, misc_ctl | MC_TIMESTAMP_ENABLE);
पूर्ण

#घोषणा ESRAM_AUTO_TINIT	BIT(2)
#घोषणा ESRAM_AUTO_TINIT_DONE	BIT(3)
#घोषणा ESRAM_AUTO_INIT_USED_CYCLES (1640)
#घोषणा ESRAM_AUTO_INIT_CSR_OFFSET 0xC1C
अटल पूर्णांक qat_hal_init_esram(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	व्योम __iomem *csr_addr =
			(व्योम __iomem *)((uपूर्णांकptr_t)handle->hal_ep_csr_addr_v +
			ESRAM_AUTO_INIT_CSR_OFFSET);
	अचिन्हित पूर्णांक csr_val;
	पूर्णांक बार = 30;

	अगर (handle->pci_dev->device != PCI_DEVICE_ID_INTEL_QAT_DH895XCC)
		वापस 0;

	csr_val = ADF_CSR_RD(csr_addr, 0);
	अगर ((csr_val & ESRAM_AUTO_TINIT) && (csr_val & ESRAM_AUTO_TINIT_DONE))
		वापस 0;

	csr_val = ADF_CSR_RD(csr_addr, 0);
	csr_val |= ESRAM_AUTO_TINIT;
	ADF_CSR_WR(csr_addr, 0, csr_val);

	करो अणु
		qat_hal_रुको_cycles(handle, 0, ESRAM_AUTO_INIT_USED_CYCLES, 0);
		csr_val = ADF_CSR_RD(csr_addr, 0);
	पूर्ण जबतक (!(csr_val & ESRAM_AUTO_TINIT_DONE) && बार--);
	अगर (बार < 0) अणु
		pr_err("QAT: Fail to init eSram!\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा SHRAM_INIT_CYCLES 2060
पूर्णांक qat_hal_clr_reset(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित पूर्णांक clk_csr = handle->chip_info->glb_clk_enable_csr;
	अचिन्हित पूर्णांक reset_mask = handle->chip_info->icp_rst_mask;
	अचिन्हित पूर्णांक reset_csr = handle->chip_info->icp_rst_csr;
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित अक्षर ae = 0;
	अचिन्हित पूर्णांक बार = 100;
	अचिन्हित पूर्णांक csr_val;

	/* ग_लिखो to the reset csr */
	csr_val = GET_CAP_CSR(handle, reset_csr);
	csr_val &= ~reset_mask;
	करो अणु
		SET_CAP_CSR(handle, reset_csr, csr_val);
		अगर (!(बार--))
			जाओ out_err;
		csr_val = GET_CAP_CSR(handle, reset_csr);
		csr_val &= reset_mask;
	पूर्ण जबतक (csr_val);
	/* enable घड़ी */
	csr_val = GET_CAP_CSR(handle, clk_csr);
	csr_val |= reset_mask;
	SET_CAP_CSR(handle, clk_csr, csr_val);
	अगर (qat_hal_check_ae_alive(handle))
		जाओ out_err;

	/* Set undefined घातer-up/reset states to reasonable शेष values */
	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES,
				  INIT_CTX_ENABLE_VALUE);
		qat_hal_wr_indr_csr(handle, ae, ICP_QAT_UCLO_AE_ALL_CTX,
				    CTX_STS_INसूचीECT,
				    handle->hal_handle->upc_mask &
				    INIT_PC_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, INIT_CTX_ARB_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, INIT_CCENABLE_VALUE);
		qat_hal_put_wakeup_event(handle, ae,
					 ICP_QAT_UCLO_AE_ALL_CTX,
					 INIT_WAKEUP_EVENTS_VALUE);
		qat_hal_put_sig_event(handle, ae,
				      ICP_QAT_UCLO_AE_ALL_CTX,
				      INIT_SIG_EVENTS_VALUE);
	पूर्ण
	अगर (qat_hal_init_esram(handle))
		जाओ out_err;
	अगर (qat_hal_रुको_cycles(handle, 0, SHRAM_INIT_CYCLES, 0))
		जाओ out_err;
	qat_hal_reset_बारtamp(handle);

	वापस 0;
out_err:
	pr_err("QAT: failed to get device out of reset\n");
	वापस -EFAULT;
पूर्ण

अटल व्योम qat_hal_disable_ctx(काष्ठा icp_qat_fw_loader_handle *handle,
				अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask)
अणु
	अचिन्हित पूर्णांक ctx;

	ctx = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx &= IGNORE_W1C_MASK &
		(~((ctx_mask & ICP_QAT_UCLO_AE_ALL_CTX) << CE_ENABLE_BITPOS));
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx);
पूर्ण

अटल u64 qat_hal_parity_64bit(u64 word)
अणु
	word ^= word >> 1;
	word ^= word >> 2;
	word ^= word >> 4;
	word ^= word >> 8;
	word ^= word >> 16;
	word ^= word >> 32;
	वापस word & 1;
पूर्ण

अटल u64 qat_hal_set_uword_ecc(u64 uword)
अणु
	u64 bit0_mask = 0xff800007fffULL, bit1_mask = 0x1f801ff801fULL,
		bit2_mask = 0xe387e0781e1ULL, bit3_mask = 0x7cb8e388e22ULL,
		bit4_mask = 0xaf5b2c93244ULL, bit5_mask = 0xf56d5525488ULL,
		bit6_mask = 0xdaf69a46910ULL;

	/* clear the ecc bits */
	uword &= ~(0x7fULL << 0x2C);
	uword |= qat_hal_parity_64bit(bit0_mask & uword) << 0x2C;
	uword |= qat_hal_parity_64bit(bit1_mask & uword) << 0x2D;
	uword |= qat_hal_parity_64bit(bit2_mask & uword) << 0x2E;
	uword |= qat_hal_parity_64bit(bit3_mask & uword) << 0x2F;
	uword |= qat_hal_parity_64bit(bit4_mask & uword) << 0x30;
	uword |= qat_hal_parity_64bit(bit5_mask & uword) << 0x31;
	uword |= qat_hal_parity_64bit(bit6_mask & uword) << 0x32;
	वापस uword;
पूर्ण

व्योम qat_hal_wr_uwords(काष्ठा icp_qat_fw_loader_handle *handle,
		       अचिन्हित अक्षर ae, अचिन्हित पूर्णांक uaddr,
		       अचिन्हित पूर्णांक words_num, u64 *uword)
अणु
	अचिन्हित पूर्णांक ustore_addr;
	अचिन्हित पूर्णांक i;

	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr |= UA_ECS;
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	क्रम (i = 0; i < words_num; i++) अणु
		अचिन्हित पूर्णांक uwrd_lo, uwrd_hi;
		u64 पंचांगp;

		पंचांगp = qat_hal_set_uword_ecc(uword[i]);
		uwrd_lo = (अचिन्हित पूर्णांक)(पंचांगp & 0xffffffff);
		uwrd_hi = (अचिन्हित पूर्णांक)(पंचांगp >> 0x20);
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_LOWER, uwrd_lo);
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_UPPER, uwrd_hi);
	पूर्ण
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
पूर्ण

अटल व्योम qat_hal_enable_ctx(काष्ठा icp_qat_fw_loader_handle *handle,
			       अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask)
अणु
	अचिन्हित पूर्णांक ctx;

	ctx = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx &= IGNORE_W1C_MASK;
	ctx_mask &= (ctx & CE_INUSE_CONTEXTS) ? 0x55 : 0xFF;
	ctx |= (ctx_mask << CE_ENABLE_BITPOS);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx);
पूर्ण

अटल व्योम qat_hal_clear_xfer(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित अक्षर ae;
	अचिन्हित लघु reg;

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		क्रम (reg = 0; reg < ICP_QAT_UCLO_MAX_GPR_REG; reg++) अणु
			qat_hal_init_rd_xfer(handle, ae, 0, ICP_SR_RD_ABS,
					     reg, 0);
			qat_hal_init_rd_xfer(handle, ae, 0, ICP_DR_RD_ABS,
					     reg, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qat_hal_clear_gpr(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	अचिन्हित अक्षर ae;
	अचिन्हित पूर्णांक ctx_mask = ICP_QAT_UCLO_AE_ALL_CTX;
	पूर्णांक बार = MAX_RETRY_TIMES;
	अचिन्हित पूर्णांक csr_val = 0;
	अचिन्हित पूर्णांक savctx = 0;
	पूर्णांक ret = 0;

	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		csr_val = qat_hal_rd_ae_csr(handle, ae, AE_MISC_CONTROL);
		csr_val &= ~(1 << MMC_SHARE_CS_BITPOS);
		qat_hal_wr_ae_csr(handle, ae, AE_MISC_CONTROL, csr_val);
		csr_val = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
		csr_val &= IGNORE_W1C_MASK;
		अगर (handle->chip_info->nn)
			csr_val |= CE_NN_MODE;

		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, csr_val);
		qat_hal_wr_uwords(handle, ae, 0, ARRAY_SIZE(inst),
				  (u64 *)inst);
		qat_hal_wr_indr_csr(handle, ae, ctx_mask, CTX_STS_INसूचीECT,
				    handle->hal_handle->upc_mask &
				    INIT_PC_VALUE);
		savctx = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS, 0);
		qat_hal_put_wakeup_event(handle, ae, ctx_mask, XCWE_VOLUNTARY);
		qat_hal_wr_indr_csr(handle, ae, ctx_mask,
				    CTX_SIG_EVENTS_INसूचीECT, 0);
		qat_hal_wr_ae_csr(handle, ae, CTX_SIG_EVENTS_ACTIVE, 0);
		qat_hal_enable_ctx(handle, ae, ctx_mask);
	पूर्ण
	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		/* रुको क्रम AE to finish */
		करो अणु
			ret = qat_hal_रुको_cycles(handle, ae, 20, 1);
		पूर्ण जबतक (ret && बार--);

		अगर (बार < 0) अणु
			pr_err("QAT: clear GPR of AE %d failed", ae);
			वापस -EINVAL;
		पूर्ण
		qat_hal_disable_ctx(handle, ae, ctx_mask);
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS,
				  savctx & ACS_ACNO);
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES,
				  INIT_CTX_ENABLE_VALUE);
		qat_hal_wr_indr_csr(handle, ae, ctx_mask, CTX_STS_INसूचीECT,
				    handle->hal_handle->upc_mask &
				    INIT_PC_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, INIT_CTX_ARB_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, INIT_CCENABLE_VALUE);
		qat_hal_put_wakeup_event(handle, ae, ctx_mask,
					 INIT_WAKEUP_EVENTS_VALUE);
		qat_hal_put_sig_event(handle, ae, ctx_mask,
				      INIT_SIG_EVENTS_VALUE);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qat_hal_chip_init(काष्ठा icp_qat_fw_loader_handle *handle,
			     काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_bar *misc_bar =
			&pci_info->pci_bars[hw_data->get_misc_bar_id(hw_data)];
	अचिन्हित पूर्णांक max_en_ae_id = 0;
	काष्ठा adf_bar *sram_bar;
	अचिन्हित पूर्णांक csr_val = 0;
	अचिन्हित दीर्घ ae_mask;
	अचिन्हित अक्षर ae = 0;
	पूर्णांक ret = 0;

	handle->pci_dev = pci_info->pci_dev;
	चयन (handle->pci_dev->device) अणु
	हाल ADF_4XXX_PCI_DEVICE_ID:
		handle->chip_info->sram_visible = false;
		handle->chip_info->nn = false;
		handle->chip_info->lm2lm3 = true;
		handle->chip_info->lm_size = ICP_QAT_UCLO_MAX_LMEM_REG_2X;
		handle->chip_info->icp_rst_csr = ICP_RESET_CPP0;
		handle->chip_info->icp_rst_mask = 0x100015;
		handle->chip_info->glb_clk_enable_csr = ICP_GLOBAL_CLK_ENABLE_CPP0;
		handle->chip_info->misc_ctl_csr = MISC_CONTROL_C4XXX;
		handle->chip_info->wakeup_event_val = 0x80000000;
		handle->chip_info->fw_auth = true;
		handle->chip_info->css_3k = true;
		handle->chip_info->tgroup_share_ustore = true;
		handle->chip_info->fcu_ctl_csr = FCU_CONTROL_4XXX;
		handle->chip_info->fcu_sts_csr = FCU_STATUS_4XXX;
		handle->chip_info->fcu_dram_addr_hi = FCU_DRAM_ADDR_HI_4XXX;
		handle->chip_info->fcu_dram_addr_lo = FCU_DRAM_ADDR_LO_4XXX;
		handle->chip_info->fcu_loaded_ae_csr = FCU_AE_LOADED_4XXX;
		handle->chip_info->fcu_loaded_ae_pos = 0;

		handle->hal_cap_g_ctl_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_CAP_OFFSET_4XXX);
		handle->hal_cap_ae_xfer_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_AE_OFFSET_4XXX);
		handle->hal_ep_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_EP_OFFSET_4XXX);
		handle->hal_cap_ae_local_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)handle->hal_cap_ae_xfer_csr_addr_v
							+ LOCAL_TO_XFER_REG_OFFSET);
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_QAT_C62X:
	हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX:
		handle->chip_info->sram_visible = false;
		handle->chip_info->nn = true;
		handle->chip_info->lm2lm3 = false;
		handle->chip_info->lm_size = ICP_QAT_UCLO_MAX_LMEM_REG;
		handle->chip_info->icp_rst_csr = ICP_RESET;
		handle->chip_info->icp_rst_mask = (hw_data->ae_mask << RST_CSR_AE_LSB) |
						  (hw_data->accel_mask << RST_CSR_QAT_LSB);
		handle->chip_info->glb_clk_enable_csr = ICP_GLOBAL_CLK_ENABLE;
		handle->chip_info->misc_ctl_csr = MISC_CONTROL;
		handle->chip_info->wakeup_event_val = WAKEUP_EVENT;
		handle->chip_info->fw_auth = true;
		handle->chip_info->css_3k = false;
		handle->chip_info->tgroup_share_ustore = false;
		handle->chip_info->fcu_ctl_csr = FCU_CONTROL;
		handle->chip_info->fcu_sts_csr = FCU_STATUS;
		handle->chip_info->fcu_dram_addr_hi = FCU_DRAM_ADDR_HI;
		handle->chip_info->fcu_dram_addr_lo = FCU_DRAM_ADDR_LO;
		handle->chip_info->fcu_loaded_ae_csr = FCU_STATUS;
		handle->chip_info->fcu_loaded_ae_pos = FCU_LOADED_AE_POS;
		handle->hal_cap_g_ctl_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_CAP_OFFSET);
		handle->hal_cap_ae_xfer_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_AE_OFFSET);
		handle->hal_ep_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_EP_OFFSET);
		handle->hal_cap_ae_local_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)handle->hal_cap_ae_xfer_csr_addr_v
			+ LOCAL_TO_XFER_REG_OFFSET);
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_QAT_DH895XCC:
		handle->chip_info->sram_visible = true;
		handle->chip_info->nn = true;
		handle->chip_info->lm2lm3 = false;
		handle->chip_info->lm_size = ICP_QAT_UCLO_MAX_LMEM_REG;
		handle->chip_info->icp_rst_csr = ICP_RESET;
		handle->chip_info->icp_rst_mask = (hw_data->ae_mask << RST_CSR_AE_LSB) |
						  (hw_data->accel_mask << RST_CSR_QAT_LSB);
		handle->chip_info->glb_clk_enable_csr = ICP_GLOBAL_CLK_ENABLE;
		handle->chip_info->misc_ctl_csr = MISC_CONTROL;
		handle->chip_info->wakeup_event_val = WAKEUP_EVENT;
		handle->chip_info->fw_auth = false;
		handle->chip_info->css_3k = false;
		handle->chip_info->tgroup_share_ustore = false;
		handle->chip_info->fcu_ctl_csr = 0;
		handle->chip_info->fcu_sts_csr = 0;
		handle->chip_info->fcu_dram_addr_hi = 0;
		handle->chip_info->fcu_dram_addr_lo = 0;
		handle->chip_info->fcu_loaded_ae_csr = 0;
		handle->chip_info->fcu_loaded_ae_pos = 0;
		handle->hal_cap_g_ctl_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_CAP_OFFSET);
		handle->hal_cap_ae_xfer_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_AE_OFFSET);
		handle->hal_ep_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)misc_bar->virt_addr +
			ICP_QAT_EP_OFFSET);
		handle->hal_cap_ae_local_csr_addr_v =
			(व्योम __iomem *)((uपूर्णांकptr_t)handle->hal_cap_ae_xfer_csr_addr_v
			+ LOCAL_TO_XFER_REG_OFFSET);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (handle->chip_info->sram_visible) अणु
		sram_bar =
			&pci_info->pci_bars[hw_data->get_sram_bar_id(hw_data)];
		handle->hal_sram_addr_v = sram_bar->virt_addr;
	पूर्ण
	handle->hal_handle->revision_id = accel_dev->accel_pci_dev.revid;
	handle->hal_handle->ae_mask = hw_data->ae_mask;
	handle->hal_handle->admin_ae_mask = hw_data->admin_ae_mask;
	handle->hal_handle->slice_mask = hw_data->accel_mask;
	handle->cfg_ae_mask = ALL_AE_MASK;
	/* create AE objects */
	handle->hal_handle->upc_mask = 0x1ffff;
	handle->hal_handle->max_ustore = 0x4000;

	ae_mask = handle->hal_handle->ae_mask;
	क्रम_each_set_bit(ae, &ae_mask, ICP_QAT_UCLO_MAX_AE) अणु
		handle->hal_handle->aes[ae].मुक्त_addr = 0;
		handle->hal_handle->aes[ae].मुक्त_size =
		    handle->hal_handle->max_ustore;
		handle->hal_handle->aes[ae].ustore_size =
		    handle->hal_handle->max_ustore;
		handle->hal_handle->aes[ae].live_ctx_mask =
						ICP_QAT_UCLO_AE_ALL_CTX;
		max_en_ae_id = ae;
	पूर्ण
	handle->hal_handle->ae_max_num = max_en_ae_id + 1;

	/* Set SIGNATURE_ENABLE[0] to 0x1 in order to enable ALU_OUT csr */
	क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
		csr_val = qat_hal_rd_ae_csr(handle, ae, SIGNATURE_ENABLE);
		csr_val |= 0x1;
		qat_hal_wr_ae_csr(handle, ae, SIGNATURE_ENABLE, csr_val);
	पूर्ण
out_err:
	वापस ret;
पूर्ण

पूर्णांक qat_hal_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा icp_qat_fw_loader_handle *handle;
	पूर्णांक ret = 0;

	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->hal_handle = kzalloc(माप(*handle->hal_handle), GFP_KERNEL);
	अगर (!handle->hal_handle) अणु
		ret = -ENOMEM;
		जाओ out_hal_handle;
	पूर्ण

	handle->chip_info = kzalloc(माप(*handle->chip_info), GFP_KERNEL);
	अगर (!handle->chip_info) अणु
		ret = -ENOMEM;
		जाओ out_chip_info;
	पूर्ण

	ret = qat_hal_chip_init(handle, accel_dev);
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev), "qat_hal_chip_init error\n");
		जाओ out_err;
	पूर्ण

	/* take all AEs out of reset */
	ret = qat_hal_clr_reset(handle);
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev), "qat_hal_clr_reset error\n");
		जाओ out_err;
	पूर्ण

	qat_hal_clear_xfer(handle);
	अगर (!handle->chip_info->fw_auth) अणु
		ret = qat_hal_clear_gpr(handle);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	accel_dev->fw_loader->fw_loader = handle;
	वापस 0;

out_err:
	kमुक्त(handle->chip_info);
out_chip_info:
	kमुक्त(handle->hal_handle);
out_hal_handle:
	kमुक्त(handle);
	वापस ret;
पूर्ण

व्योम qat_hal_deinit(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अगर (!handle)
		वापस;
	kमुक्त(handle->chip_info);
	kमुक्त(handle->hal_handle);
	kमुक्त(handle);
पूर्ण

पूर्णांक qat_hal_start(काष्ठा icp_qat_fw_loader_handle *handle)
अणु
	अचिन्हित दीर्घ ae_mask = handle->hal_handle->ae_mask;
	u32 wakeup_val = handle->chip_info->wakeup_event_val;
	u32 fcu_ctl_csr, fcu_sts_csr;
	अचिन्हित पूर्णांक fcu_sts;
	अचिन्हित अक्षर ae;
	u32 ae_ctr = 0;
	पूर्णांक retry = 0;

	अगर (handle->chip_info->fw_auth) अणु
		fcu_ctl_csr = handle->chip_info->fcu_ctl_csr;
		fcu_sts_csr = handle->chip_info->fcu_sts_csr;
		ae_ctr = hweight32(ae_mask);
		SET_CAP_CSR(handle, fcu_ctl_csr, FCU_CTRL_CMD_START);
		करो अणु
			msleep(FW_AUTH_WAIT_PERIOD);
			fcu_sts = GET_CAP_CSR(handle, fcu_sts_csr);
			अगर (((fcu_sts >> FCU_STS_DONE_POS) & 0x1))
				वापस ae_ctr;
		पूर्ण जबतक (retry++ < FW_AUTH_MAX_RETRY);
		pr_err("QAT: start error (FCU_STS = 0x%x)\n", fcu_sts);
		वापस 0;
	पूर्ण अन्यथा अणु
		क्रम_each_set_bit(ae, &ae_mask, handle->hal_handle->ae_max_num) अणु
			qat_hal_put_wakeup_event(handle, ae, 0, wakeup_val);
			qat_hal_enable_ctx(handle, ae, ICP_QAT_UCLO_AE_ALL_CTX);
			ae_ctr++;
		पूर्ण
		वापस ae_ctr;
	पूर्ण
पूर्ण

व्योम qat_hal_stop(काष्ठा icp_qat_fw_loader_handle *handle, अचिन्हित अक्षर ae,
		  अचिन्हित पूर्णांक ctx_mask)
अणु
	अगर (!handle->chip_info->fw_auth)
		qat_hal_disable_ctx(handle, ae, ctx_mask);
पूर्ण

व्योम qat_hal_set_pc(काष्ठा icp_qat_fw_loader_handle *handle,
		    अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask, अचिन्हित पूर्णांक upc)
अणु
	qat_hal_wr_indr_csr(handle, ae, ctx_mask, CTX_STS_INसूचीECT,
			    handle->hal_handle->upc_mask & upc);
पूर्ण

अटल व्योम qat_hal_get_uwords(काष्ठा icp_qat_fw_loader_handle *handle,
			       अचिन्हित अक्षर ae, अचिन्हित पूर्णांक uaddr,
			       अचिन्हित पूर्णांक words_num, u64 *uword)
अणु
	अचिन्हित पूर्णांक i, uwrd_lo, uwrd_hi;
	अचिन्हित पूर्णांक ustore_addr, misc_control;

	misc_control = qat_hal_rd_ae_csr(handle, ae, AE_MISC_CONTROL);
	qat_hal_wr_ae_csr(handle, ae, AE_MISC_CONTROL,
			  misc_control & 0xfffffffb);
	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr |= UA_ECS;
	क्रम (i = 0; i < words_num; i++) अणु
		qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
		uaddr++;
		uwrd_lo = qat_hal_rd_ae_csr(handle, ae, USTORE_DATA_LOWER);
		uwrd_hi = qat_hal_rd_ae_csr(handle, ae, USTORE_DATA_UPPER);
		uword[i] = uwrd_hi;
		uword[i] = (uword[i] << 0x20) | uwrd_lo;
	पूर्ण
	qat_hal_wr_ae_csr(handle, ae, AE_MISC_CONTROL, misc_control);
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
पूर्ण

व्योम qat_hal_wr_umem(काष्ठा icp_qat_fw_loader_handle *handle,
		     अचिन्हित अक्षर ae, अचिन्हित पूर्णांक uaddr,
		     अचिन्हित पूर्णांक words_num, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक i, ustore_addr;

	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr |= UA_ECS;
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	क्रम (i = 0; i < words_num; i++) अणु
		अचिन्हित पूर्णांक uwrd_lo, uwrd_hi, पंचांगp;

		uwrd_lo = ((data[i] & 0xfff0000) << 4) | (0x3 << 18) |
			  ((data[i] & 0xff00) << 2) |
			  (0x3 << 8) | (data[i] & 0xff);
		uwrd_hi = (0xf << 4) | ((data[i] & 0xf0000000) >> 28);
		uwrd_hi |= (hweight32(data[i] & 0xffff) & 0x1) << 8;
		पंचांगp = ((data[i] >> 0x10) & 0xffff);
		uwrd_hi |= (hweight32(पंचांगp) & 0x1) << 9;
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_LOWER, uwrd_lo);
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_UPPER, uwrd_hi);
	पूर्ण
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
पूर्ण

#घोषणा MAX_EXEC_INST 100
अटल पूर्णांक qat_hal_exec_micro_inst(काष्ठा icp_qat_fw_loader_handle *handle,
				   अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				   u64 *micro_inst, अचिन्हित पूर्णांक inst_num,
				   पूर्णांक code_off, अचिन्हित पूर्णांक max_cycle,
				   अचिन्हित पूर्णांक *endpc)
अणु
	अचिन्हित पूर्णांक ind_lm_addr_byte0 = 0, ind_lm_addr_byte1 = 0;
	अचिन्हित पूर्णांक ind_lm_addr_byte2 = 0, ind_lm_addr_byte3 = 0;
	अचिन्हित पूर्णांक ind_t_index = 0, ind_t_index_byte = 0;
	अचिन्हित पूर्णांक ind_lm_addr0 = 0, ind_lm_addr1 = 0;
	अचिन्हित पूर्णांक ind_lm_addr2 = 0, ind_lm_addr3 = 0;
	u64 savuwords[MAX_EXEC_INST];
	अचिन्हित पूर्णांक ind_cnt_sig;
	अचिन्हित पूर्णांक ind_sig, act_sig;
	अचिन्हित पूर्णांक csr_val = 0, newcsr_val;
	अचिन्हित पूर्णांक savctx;
	अचिन्हित पूर्णांक savcc, wakeup_events, savpc;
	अचिन्हित पूर्णांक ctxarb_ctl, ctx_enables;

	अगर ((inst_num > handle->hal_handle->max_ustore) || !micro_inst) अणु
		pr_err("QAT: invalid instruction num %d\n", inst_num);
		वापस -EINVAL;
	पूर्ण
	/* save current context */
	ind_lm_addr0 = qat_hal_rd_indr_csr(handle, ae, ctx, LM_ADDR_0_INसूचीECT);
	ind_lm_addr1 = qat_hal_rd_indr_csr(handle, ae, ctx, LM_ADDR_1_INसूचीECT);
	ind_lm_addr_byte0 = qat_hal_rd_indr_csr(handle, ae, ctx,
						INसूचीECT_LM_ADDR_0_BYTE_INDEX);
	ind_lm_addr_byte1 = qat_hal_rd_indr_csr(handle, ae, ctx,
						INसूचीECT_LM_ADDR_1_BYTE_INDEX);
	अगर (handle->chip_info->lm2lm3) अणु
		ind_lm_addr2 = qat_hal_rd_indr_csr(handle, ae, ctx,
						   LM_ADDR_2_INसूचीECT);
		ind_lm_addr3 = qat_hal_rd_indr_csr(handle, ae, ctx,
						   LM_ADDR_3_INसूचीECT);
		ind_lm_addr_byte2 = qat_hal_rd_indr_csr(handle, ae, ctx,
							INसूचीECT_LM_ADDR_2_BYTE_INDEX);
		ind_lm_addr_byte3 = qat_hal_rd_indr_csr(handle, ae, ctx,
							INसूचीECT_LM_ADDR_3_BYTE_INDEX);
		ind_t_index = qat_hal_rd_indr_csr(handle, ae, ctx,
						  INसूचीECT_T_INDEX);
		ind_t_index_byte = qat_hal_rd_indr_csr(handle, ae, ctx,
						       INसूचीECT_T_INDEX_BYTE_INDEX);
	पूर्ण
	अगर (inst_num <= MAX_EXEC_INST)
		qat_hal_get_uwords(handle, ae, 0, inst_num, savuwords);
	qat_hal_get_wakeup_event(handle, ae, ctx, &wakeup_events);
	savpc = qat_hal_rd_indr_csr(handle, ae, ctx, CTX_STS_INसूचीECT);
	savpc = (savpc & handle->hal_handle->upc_mask) >> 0;
	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx_enables &= IGNORE_W1C_MASK;
	savcc = qat_hal_rd_ae_csr(handle, ae, CC_ENABLE);
	savctx = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);
	ctxarb_ctl = qat_hal_rd_ae_csr(handle, ae, CTX_ARB_CNTL);
	ind_cnt_sig = qat_hal_rd_indr_csr(handle, ae, ctx,
					  FUTURE_COUNT_SIGNAL_INसूचीECT);
	ind_sig = qat_hal_rd_indr_csr(handle, ae, ctx,
				      CTX_SIG_EVENTS_INसूचीECT);
	act_sig = qat_hal_rd_ae_csr(handle, ae, CTX_SIG_EVENTS_ACTIVE);
	/* execute micro codes */
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);
	qat_hal_wr_uwords(handle, ae, 0, inst_num, micro_inst);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx), CTX_STS_INसूचीECT, 0);
	qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS, ctx & ACS_ACNO);
	अगर (code_off)
		qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, savcc & 0xffffdfff);
	qat_hal_put_wakeup_event(handle, ae, (1 << ctx), XCWE_VOLUNTARY);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx), CTX_SIG_EVENTS_INसूचीECT, 0);
	qat_hal_wr_ae_csr(handle, ae, CTX_SIG_EVENTS_ACTIVE, 0);
	qat_hal_enable_ctx(handle, ae, (1 << ctx));
	/* रुको क्रम micro codes to finish */
	अगर (qat_hal_रुको_cycles(handle, ae, max_cycle, 1) != 0)
		वापस -EFAULT;
	अगर (endpc) अणु
		अचिन्हित पूर्णांक ctx_status;

		ctx_status = qat_hal_rd_indr_csr(handle, ae, ctx,
						 CTX_STS_INसूचीECT);
		*endpc = ctx_status & handle->hal_handle->upc_mask;
	पूर्ण
	/* retore to saved context */
	qat_hal_disable_ctx(handle, ae, (1 << ctx));
	अगर (inst_num <= MAX_EXEC_INST)
		qat_hal_wr_uwords(handle, ae, 0, inst_num, savuwords);
	qat_hal_put_wakeup_event(handle, ae, (1 << ctx), wakeup_events);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx), CTX_STS_INसूचीECT,
			    handle->hal_handle->upc_mask & savpc);
	csr_val = qat_hal_rd_ae_csr(handle, ae, AE_MISC_CONTROL);
	newcsr_val = CLR_BIT(csr_val, MMC_SHARE_CS_BITPOS);
	qat_hal_wr_ae_csr(handle, ae, AE_MISC_CONTROL, newcsr_val);
	qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, savcc);
	qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS, savctx & ACS_ACNO);
	qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, ctxarb_ctl);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    LM_ADDR_0_INसूचीECT, ind_lm_addr0);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    LM_ADDR_1_INसूचीECT, ind_lm_addr1);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    INसूचीECT_LM_ADDR_0_BYTE_INDEX, ind_lm_addr_byte0);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    INसूचीECT_LM_ADDR_1_BYTE_INDEX, ind_lm_addr_byte1);
	अगर (handle->chip_info->lm2lm3) अणु
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx), LM_ADDR_2_INसूचीECT,
				    ind_lm_addr2);
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx), LM_ADDR_3_INसूचीECT,
				    ind_lm_addr3);
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx),
				    INसूचीECT_LM_ADDR_2_BYTE_INDEX,
				    ind_lm_addr_byte2);
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx),
				    INसूचीECT_LM_ADDR_3_BYTE_INDEX,
				    ind_lm_addr_byte3);
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx),
				    INसूचीECT_T_INDEX, ind_t_index);
		qat_hal_wr_indr_csr(handle, ae, BIT(ctx),
				    INसूचीECT_T_INDEX_BYTE_INDEX,
				    ind_t_index_byte);
	पूर्ण
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    FUTURE_COUNT_SIGNAL_INसूचीECT, ind_cnt_sig);
	qat_hal_wr_indr_csr(handle, ae, (1 << ctx),
			    CTX_SIG_EVENTS_INसूचीECT, ind_sig);
	qat_hal_wr_ae_csr(handle, ae, CTX_SIG_EVENTS_ACTIVE, act_sig);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);

	वापस 0;
पूर्ण

अटल पूर्णांक qat_hal_rd_rel_reg(काष्ठा icp_qat_fw_loader_handle *handle,
			      अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
			      क्रमागत icp_qat_uof_regtype reg_type,
			      अचिन्हित लघु reg_num, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक savctx, uaddr, uwrd_lo, uwrd_hi;
	अचिन्हित पूर्णांक ctxarb_cntl, ustore_addr, ctx_enables;
	अचिन्हित लघु reg_addr;
	पूर्णांक status = 0;
	u64 insts, savuword;

	reg_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	अगर (reg_addr == BAD_REGADDR) अणु
		pr_err("QAT: bad regaddr=0x%x\n", reg_addr);
		वापस -EINVAL;
	पूर्ण
	चयन (reg_type) अणु
	हाल ICP_GPA_REL:
		insts = 0xA070000000ull | (reg_addr & 0x3ff);
		अवरोध;
	शेष:
		insts = (u64)0xA030000000ull | ((reg_addr & 0x3ff) << 10);
		अवरोध;
	पूर्ण
	savctx = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);
	ctxarb_cntl = qat_hal_rd_ae_csr(handle, ae, CTX_ARB_CNTL);
	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx_enables &= IGNORE_W1C_MASK;
	अगर (ctx != (savctx & ACS_ACNO))
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS,
				  ctx & ACS_ACNO);
	qat_hal_get_uwords(handle, ae, 0, 1, &savuword);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);
	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr = UA_ECS;
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	insts = qat_hal_set_uword_ecc(insts);
	uwrd_lo = (अचिन्हित पूर्णांक)(insts & 0xffffffff);
	uwrd_hi = (अचिन्हित पूर्णांक)(insts >> 0x20);
	qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_LOWER, uwrd_lo);
	qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_UPPER, uwrd_hi);
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	/* delay क्रम at least 8 cycles */
	qat_hal_रुको_cycles(handle, ae, 0x8, 0);
	/*
	 * पढ़ो ALU output
	 * the inकाष्ठाion should have been executed
	 * prior to clearing the ECS in putUwords
	 */
	*data = qat_hal_rd_ae_csr(handle, ae, ALU_OUT);
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
	qat_hal_wr_uwords(handle, ae, 0, 1, &savuword);
	अगर (ctx != (savctx & ACS_ACNO))
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS,
				  savctx & ACS_ACNO);
	qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, ctxarb_cntl);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);

	वापस status;
पूर्ण

अटल पूर्णांक qat_hal_wr_rel_reg(काष्ठा icp_qat_fw_loader_handle *handle,
			      अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
			      क्रमागत icp_qat_uof_regtype reg_type,
			      अचिन्हित लघु reg_num, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित लघु src_hiaddr, src_lowaddr, dest_addr, data16hi, data16lo;
	u64 insts[] = अणु
		0x0F440000000ull,
		0x0F040000000ull,
		0x0F0000C0300ull,
		0x0E000010000ull
	पूर्ण;
	स्थिर पूर्णांक num_inst = ARRAY_SIZE(insts), code_off = 1;
	स्थिर पूर्णांक imm_w1 = 0, imm_w0 = 1;

	dest_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	अगर (dest_addr == BAD_REGADDR) अणु
		pr_err("QAT: bad destAddr=0x%x\n", dest_addr);
		वापस -EINVAL;
	पूर्ण

	data16lo = 0xffff & data;
	data16hi = 0xffff & (data >> 0x10);
	src_hiaddr = qat_hal_get_reg_addr(ICP_NO_DEST, (अचिन्हित लघु)
					  (0xff & data16hi));
	src_lowaddr = qat_hal_get_reg_addr(ICP_NO_DEST, (अचिन्हित लघु)
					   (0xff & data16lo));
	चयन (reg_type) अणु
	हाल ICP_GPA_REL:
		insts[imm_w1] = insts[imm_w1] | ((data16hi >> 8) << 20) |
		    ((src_hiaddr & 0x3ff) << 10) | (dest_addr & 0x3ff);
		insts[imm_w0] = insts[imm_w0] | ((data16lo >> 8) << 20) |
		    ((src_lowaddr & 0x3ff) << 10) | (dest_addr & 0x3ff);
		अवरोध;
	शेष:
		insts[imm_w1] = insts[imm_w1] | ((data16hi >> 8) << 20) |
		    ((dest_addr & 0x3ff) << 10) | (src_hiaddr & 0x3ff);

		insts[imm_w0] = insts[imm_w0] | ((data16lo >> 8) << 20) |
		    ((dest_addr & 0x3ff) << 10) | (src_lowaddr & 0x3ff);
		अवरोध;
	पूर्ण

	वापस qat_hal_exec_micro_inst(handle, ae, ctx, insts, num_inst,
				       code_off, num_inst * 0x5, शून्य);
पूर्ण

पूर्णांक qat_hal_get_ins_num(व्योम)
अणु
	वापस ARRAY_SIZE(inst_4b);
पूर्ण

अटल पूर्णांक qat_hal_concat_micro_code(u64 *micro_inst,
				     अचिन्हित पूर्णांक inst_num, अचिन्हित पूर्णांक size,
				     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक cur_value;
	स्थिर u64 *inst_arr;
	पूर्णांक fixup_offset;
	पूर्णांक usize = 0;
	पूर्णांक orig_num;

	orig_num = inst_num;
	cur_value = value[0];
	inst_arr = inst_4b;
	usize = ARRAY_SIZE(inst_4b);
	fixup_offset = inst_num;
	क्रम (i = 0; i < usize; i++)
		micro_inst[inst_num++] = inst_arr[i];
	INSERT_IMMED_GPRA_CONST(micro_inst[fixup_offset], (addr));
	fixup_offset++;
	INSERT_IMMED_GPRA_CONST(micro_inst[fixup_offset], 0);
	fixup_offset++;
	INSERT_IMMED_GPRB_CONST(micro_inst[fixup_offset], (cur_value >> 0));
	fixup_offset++;
	INSERT_IMMED_GPRB_CONST(micro_inst[fixup_offset], (cur_value >> 0x10));

	वापस inst_num - orig_num;
पूर्ण

अटल पूर्णांक qat_hal_exec_micro_init_lm(काष्ठा icp_qat_fw_loader_handle *handle,
				      अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				      पूर्णांक *pfirst_exec, u64 *micro_inst,
				      अचिन्हित पूर्णांक inst_num)
अणु
	पूर्णांक stat = 0;
	अचिन्हित पूर्णांक gpra0 = 0, gpra1 = 0, gpra2 = 0;
	अचिन्हित पूर्णांक gprb0 = 0, gprb1 = 0;

	अगर (*pfirst_exec) अणु
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0, &gpra0);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x1, &gpra1);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x2, &gpra2);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0, &gprb0);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0x1, &gprb1);
		*pfirst_exec = 0;
	पूर्ण
	stat = qat_hal_exec_micro_inst(handle, ae, ctx, micro_inst, inst_num, 1,
				       inst_num * 0x5, शून्य);
	अगर (stat != 0)
		वापस -EFAULT;
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0, gpra0);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x1, gpra1);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x2, gpra2);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0, gprb0);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0x1, gprb1);

	वापस 0;
पूर्ण

पूर्णांक qat_hal_batch_wr_lm(काष्ठा icp_qat_fw_loader_handle *handle,
			अचिन्हित अक्षर ae,
			काष्ठा icp_qat_uof_batch_init *lm_init_header)
अणु
	काष्ठा icp_qat_uof_batch_init *plm_init;
	u64 *micro_inst_arry;
	पूर्णांक micro_inst_num;
	पूर्णांक alloc_inst_size;
	पूर्णांक first_exec = 1;
	पूर्णांक stat = 0;

	plm_init = lm_init_header->next;
	alloc_inst_size = lm_init_header->size;
	अगर ((अचिन्हित पूर्णांक)alloc_inst_size > handle->hal_handle->max_ustore)
		alloc_inst_size = handle->hal_handle->max_ustore;
	micro_inst_arry = kदो_स्मृति_array(alloc_inst_size, माप(u64),
					GFP_KERNEL);
	अगर (!micro_inst_arry)
		वापस -ENOMEM;
	micro_inst_num = 0;
	जबतक (plm_init) अणु
		अचिन्हित पूर्णांक addr, *value, size;

		ae = plm_init->ae;
		addr = plm_init->addr;
		value = plm_init->value;
		size = plm_init->size;
		micro_inst_num += qat_hal_concat_micro_code(micro_inst_arry,
							    micro_inst_num,
							    size, addr, value);
		plm_init = plm_init->next;
	पूर्ण
	/* exec micro codes */
	अगर (micro_inst_arry && micro_inst_num > 0) अणु
		micro_inst_arry[micro_inst_num++] = 0x0E000010000ull;
		stat = qat_hal_exec_micro_init_lm(handle, ae, 0, &first_exec,
						  micro_inst_arry,
						  micro_inst_num);
	पूर्ण
	kमुक्त(micro_inst_arry);
	वापस stat;
पूर्ण

अटल पूर्णांक qat_hal_put_rel_rd_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
				   अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				   क्रमागत icp_qat_uof_regtype reg_type,
				   अचिन्हित लघु reg_num, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक ctx_enables;
	अचिन्हित लघु mask;
	अचिन्हित लघु dr_offset = 0x10;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	अगर (CE_INUSE_CONTEXTS & ctx_enables) अणु
		अगर (ctx & 0x1) अणु
			pr_err("QAT: bad 4-ctx mode,ctx=0x%x\n", ctx);
			वापस -EINVAL;
		पूर्ण
		mask = 0x1f;
		dr_offset = 0x20;
	पूर्ण अन्यथा अणु
		mask = 0x0f;
	पूर्ण
	अगर (reg_num & ~mask)
		वापस -EINVAL;
	reg_addr = reg_num + (ctx << 0x5);
	चयन (reg_type) अणु
	हाल ICP_SR_RD_REL:
	हाल ICP_SR_REL:
		SET_AE_XFER(handle, ae, reg_addr, val);
		अवरोध;
	हाल ICP_DR_RD_REL:
	हाल ICP_DR_REL:
		SET_AE_XFER(handle, ae, (reg_addr + dr_offset), val);
		अवरोध;
	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qat_hal_put_rel_wr_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
				   अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
				   क्रमागत icp_qat_uof_regtype reg_type,
				   अचिन्हित लघु reg_num, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक gprval, ctx_enables;
	अचिन्हित लघु src_hiaddr, src_lowaddr, gpr_addr, xfr_addr, data16hi,
	    data16low;
	अचिन्हित लघु reg_mask;
	पूर्णांक status = 0;
	u64 micro_inst[] = अणु
		0x0F440000000ull,
		0x0F040000000ull,
		0x0A000000000ull,
		0x0F0000C0300ull,
		0x0E000010000ull
	पूर्ण;
	स्थिर पूर्णांक num_inst = ARRAY_SIZE(micro_inst), code_off = 1;
	स्थिर अचिन्हित लघु gprnum = 0, dly = num_inst * 0x5;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	अगर (CE_INUSE_CONTEXTS & ctx_enables) अणु
		अगर (ctx & 0x1) अणु
			pr_err("QAT: 4-ctx mode,ctx=0x%x\n", ctx);
			वापस -EINVAL;
		पूर्ण
		reg_mask = (अचिन्हित लघु)~0x1f;
	पूर्ण अन्यथा अणु
		reg_mask = (अचिन्हित लघु)~0xf;
	पूर्ण
	अगर (reg_num & reg_mask)
		वापस -EINVAL;
	xfr_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	अगर (xfr_addr == BAD_REGADDR) अणु
		pr_err("QAT: bad xfrAddr=0x%x\n", xfr_addr);
		वापस -EINVAL;
	पूर्ण
	qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, gprnum, &gprval);
	gpr_addr = qat_hal_get_reg_addr(ICP_GPB_REL, gprnum);
	data16low = 0xffff & data;
	data16hi = 0xffff & (data >> 0x10);
	src_hiaddr = qat_hal_get_reg_addr(ICP_NO_DEST,
					  (अचिन्हित लघु)(0xff & data16hi));
	src_lowaddr = qat_hal_get_reg_addr(ICP_NO_DEST,
					   (अचिन्हित लघु)(0xff & data16low));
	micro_inst[0] = micro_inst[0x0] | ((data16hi >> 8) << 20) |
	    ((gpr_addr & 0x3ff) << 10) | (src_hiaddr & 0x3ff);
	micro_inst[1] = micro_inst[0x1] | ((data16low >> 8) << 20) |
	    ((gpr_addr & 0x3ff) << 10) | (src_lowaddr & 0x3ff);
	micro_inst[0x2] = micro_inst[0x2] |
	    ((xfr_addr & 0x3ff) << 20) | ((gpr_addr & 0x3ff) << 10);
	status = qat_hal_exec_micro_inst(handle, ae, ctx, micro_inst, num_inst,
					 code_off, dly, शून्य);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, gprnum, gprval);
	वापस status;
पूर्ण

अटल पूर्णांक qat_hal_put_rel_nn(काष्ठा icp_qat_fw_loader_handle *handle,
			      अचिन्हित अक्षर ae, अचिन्हित अक्षर ctx,
			      अचिन्हित लघु nn, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक ctx_enables;
	पूर्णांक stat = 0;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx_enables &= IGNORE_W1C_MASK;
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables | CE_NN_MODE);

	stat = qat_hal_put_rel_wr_xfer(handle, ae, ctx, ICP_NEIGH_REL, nn, val);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);
	वापस stat;
पूर्ण

अटल पूर्णांक qat_hal_convert_असल_to_rel(काष्ठा icp_qat_fw_loader_handle
				      *handle, अचिन्हित अक्षर ae,
				      अचिन्हित लघु असलreg_num,
				      अचिन्हित लघु *relreg,
				      अचिन्हित अक्षर *ctx)
अणु
	अचिन्हित पूर्णांक ctx_enables;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	अगर (ctx_enables & CE_INUSE_CONTEXTS) अणु
		/* 4-ctx mode */
		*relreg = असलreg_num & 0x1F;
		*ctx = (असलreg_num >> 0x4) & 0x6;
	पूर्ण अन्यथा अणु
		/* 8-ctx mode */
		*relreg = असलreg_num & 0x0F;
		*ctx = (असलreg_num >> 0x4) & 0x7;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qat_hal_init_gpr(काष्ठा icp_qat_fw_loader_handle *handle,
		     अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
		     क्रमागत icp_qat_uof_regtype reg_type,
		     अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata)
अणु
	पूर्णांक stat = 0;
	अचिन्हित लघु reg;
	अचिन्हित अक्षर ctx = 0;
	क्रमागत icp_qat_uof_regtype type;

	अगर (reg_num >= ICP_QAT_UCLO_MAX_GPR_REG)
		वापस -EINVAL;

	करो अणु
		अगर (ctx_mask == 0) अणु
			qat_hal_convert_असल_to_rel(handle, ae, reg_num, &reg,
						   &ctx);
			type = reg_type - 1;
		पूर्ण अन्यथा अणु
			reg = reg_num;
			type = reg_type;
			अगर (!test_bit(ctx, &ctx_mask))
				जारी;
		पूर्ण
		stat = qat_hal_wr_rel_reg(handle, ae, ctx, type, reg, regdata);
		अगर (stat) अणु
			pr_err("QAT: write gpr fail\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (ctx_mask && (ctx++ < ICP_QAT_UCLO_MAX_CTX));

	वापस 0;
पूर्ण

पूर्णांक qat_hal_init_wr_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
			 अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
			 क्रमागत icp_qat_uof_regtype reg_type,
			 अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata)
अणु
	पूर्णांक stat = 0;
	अचिन्हित लघु reg;
	अचिन्हित अक्षर ctx = 0;
	क्रमागत icp_qat_uof_regtype type;

	अगर (reg_num >= ICP_QAT_UCLO_MAX_XFER_REG)
		वापस -EINVAL;

	करो अणु
		अगर (ctx_mask == 0) अणु
			qat_hal_convert_असल_to_rel(handle, ae, reg_num, &reg,
						   &ctx);
			type = reg_type - 3;
		पूर्ण अन्यथा अणु
			reg = reg_num;
			type = reg_type;
			अगर (!test_bit(ctx, &ctx_mask))
				जारी;
		पूर्ण
		stat = qat_hal_put_rel_wr_xfer(handle, ae, ctx, type, reg,
					       regdata);
		अगर (stat) अणु
			pr_err("QAT: write wr xfer fail\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (ctx_mask && (ctx++ < ICP_QAT_UCLO_MAX_CTX));

	वापस 0;
पूर्ण

पूर्णांक qat_hal_init_rd_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
			 अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
			 क्रमागत icp_qat_uof_regtype reg_type,
			 अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata)
अणु
	पूर्णांक stat = 0;
	अचिन्हित लघु reg;
	अचिन्हित अक्षर ctx = 0;
	क्रमागत icp_qat_uof_regtype type;

	अगर (reg_num >= ICP_QAT_UCLO_MAX_XFER_REG)
		वापस -EINVAL;

	करो अणु
		अगर (ctx_mask == 0) अणु
			qat_hal_convert_असल_to_rel(handle, ae, reg_num, &reg,
						   &ctx);
			type = reg_type - 3;
		पूर्ण अन्यथा अणु
			reg = reg_num;
			type = reg_type;
			अगर (!test_bit(ctx, &ctx_mask))
				जारी;
		पूर्ण
		stat = qat_hal_put_rel_rd_xfer(handle, ae, ctx, type, reg,
					       regdata);
		अगर (stat) अणु
			pr_err("QAT: write rd xfer fail\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (ctx_mask && (ctx++ < ICP_QAT_UCLO_MAX_CTX));

	वापस 0;
पूर्ण

पूर्णांक qat_hal_init_nn(काष्ठा icp_qat_fw_loader_handle *handle,
		    अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
		    अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata)
अणु
	पूर्णांक stat = 0;
	अचिन्हित अक्षर ctx;
	अगर (!handle->chip_info->nn) अणु
		dev_err(&handle->pci_dev->dev, "QAT: No next neigh in 0x%x\n",
			handle->pci_dev->device);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx_mask == 0)
		वापस -EINVAL;

	क्रम (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) अणु
		अगर (!test_bit(ctx, &ctx_mask))
			जारी;
		stat = qat_hal_put_rel_nn(handle, ae, ctx, reg_num, regdata);
		अगर (stat) अणु
			pr_err("QAT: write neigh error\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
