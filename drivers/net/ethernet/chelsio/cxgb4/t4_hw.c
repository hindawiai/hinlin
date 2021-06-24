<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/delay.h>
#समावेश "cxgb4.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"
#समावेश "t4fw_api.h"
#समावेश "t4fw_version.h"

/**
 *	t4_रुको_op_करोne_val - रुको until an operation is completed
 *	@adapter: the adapter perक्रमming the operation
 *	@reg: the रेजिस्टर to check क्रम completion
 *	@mask: a single-bit field within @reg that indicates completion
 *	@polarity: the value of the field when the operation is completed
 *	@attempts: number of check iterations
 *	@delay: delay in usecs between iterations
 *	@valp: where to store the value of the रेजिस्टर at completion समय
 *
 *	Wait until an operation is completed by checking a bit in a रेजिस्टर
 *	up to @attempts बार.  If @valp is not शून्य the value of the रेजिस्टर
 *	at the समय it indicated completion is stored there.  Returns 0 अगर the
 *	operation completes and	-EAGAIN	otherwise.
 */
अटल पूर्णांक t4_रुको_op_करोne_val(काष्ठा adapter *adapter, पूर्णांक reg, u32 mask,
			       पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay, u32 *valp)
अणु
	जबतक (1) अणु
		u32 val = t4_पढ़ो_reg(adapter, reg);

		अगर (!!(val & mask) == polarity) अणु
			अगर (valp)
				*valp = val;
			वापस 0;
		पूर्ण
		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			udelay(delay);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक t4_रुको_op_करोne(काष्ठा adapter *adapter, पूर्णांक reg, u32 mask,
				  पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay)
अणु
	वापस t4_रुको_op_करोne_val(adapter, reg, mask, polarity, attempts,
				   delay, शून्य);
पूर्ण

/**
 *	t4_set_reg_field - set a रेजिस्टर field to a value
 *	@adapter: the adapter to program
 *	@addr: the रेजिस्टर address
 *	@mask: specअगरies the portion of the रेजिस्टर to modअगरy
 *	@val: the new value क्रम the रेजिस्टर field
 *
 *	Sets a रेजिस्टर field specअगरied by the supplied mask to the
 *	given value.
 */
व्योम t4_set_reg_field(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr, u32 mask,
		      u32 val)
अणु
	u32 v = t4_पढ़ो_reg(adapter, addr) & ~mask;

	t4_ग_लिखो_reg(adapter, addr, v | val);
	(व्योम) t4_पढ़ो_reg(adapter, addr);      /* flush */
पूर्ण

/**
 *	t4_पढ़ो_indirect - पढ़ो indirectly addressed रेजिस्टरs
 *	@adap: the adapter
 *	@addr_reg: रेजिस्टर holding the indirect address
 *	@data_reg: रेजिस्टर holding the value of the indirect रेजिस्टर
 *	@vals: where the पढ़ो रेजिस्टर values are stored
 *	@nregs: how many indirect रेजिस्टरs to पढ़ो
 *	@start_idx: index of first indirect रेजिस्टर to पढ़ो
 *
 *	Reads रेजिस्टरs that are accessed indirectly through an address/data
 *	रेजिस्टर pair.
 */
व्योम t4_पढ़ो_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr_reg,
			     अचिन्हित पूर्णांक data_reg, u32 *vals,
			     अचिन्हित पूर्णांक nregs, अचिन्हित पूर्णांक start_idx)
अणु
	जबतक (nregs--) अणु
		t4_ग_लिखो_reg(adap, addr_reg, start_idx);
		*vals++ = t4_पढ़ो_reg(adap, data_reg);
		start_idx++;
	पूर्ण
पूर्ण

/**
 *	t4_ग_लिखो_indirect - ग_लिखो indirectly addressed रेजिस्टरs
 *	@adap: the adapter
 *	@addr_reg: रेजिस्टर holding the indirect addresses
 *	@data_reg: रेजिस्टर holding the value क्रम the indirect रेजिस्टरs
 *	@vals: values to ग_लिखो
 *	@nregs: how many indirect रेजिस्टरs to ग_लिखो
 *	@start_idx: address of first indirect रेजिस्टर to ग_लिखो
 *
 *	Writes a sequential block of रेजिस्टरs that are accessed indirectly
 *	through an address/data रेजिस्टर pair.
 */
व्योम t4_ग_लिखो_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr_reg,
		       अचिन्हित पूर्णांक data_reg, स्थिर u32 *vals,
		       अचिन्हित पूर्णांक nregs, अचिन्हित पूर्णांक start_idx)
अणु
	जबतक (nregs--) अणु
		t4_ग_लिखो_reg(adap, addr_reg, start_idx++);
		t4_ग_लिखो_reg(adap, data_reg, *vals++);
	पूर्ण
पूर्ण

/*
 * Read a 32-bit PCI Configuration Space रेजिस्टर via the PCI-E backकरोor
 * mechanism.  This guarantees that we get the real value even अगर we're
 * operating within a Virtual Machine and the Hypervisor is trapping our
 * Configuration Space accesses.
 */
व्योम t4_hw_pci_पढ़ो_cfg4(काष्ठा adapter *adap, पूर्णांक reg, u32 *val)
अणु
	u32 req = FUNCTION_V(adap->pf) | REGISTER_V(reg);

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		req |= ENABLE_F;
	अन्यथा
		req |= T6_ENABLE_F;

	अगर (is_t4(adap->params.chip))
		req |= LOCALCFG_F;

	t4_ग_लिखो_reg(adap, PCIE_CFG_SPACE_REQ_A, req);
	*val = t4_पढ़ो_reg(adap, PCIE_CFG_SPACE_DATA_A);

	/* Reset ENABLE to 0 so पढ़ोs of PCIE_CFG_SPACE_DATA won't cause a
	 * Configuration Space पढ़ो.  (None of the other fields matter when
	 * ENABLE is 0 so a simple रेजिस्टर ग_लिखो is easier than a
	 * पढ़ो-modअगरy-ग_लिखो via t4_set_reg_field().)
	 */
	t4_ग_लिखो_reg(adap, PCIE_CFG_SPACE_REQ_A, 0);
पूर्ण

/*
 * t4_report_fw_error - report firmware error
 * @adap: the adapter
 *
 * The adapter firmware can indicate error conditions to the host.
 * If the firmware has indicated an error, prपूर्णांक out the reason क्रम
 * the firmware error.
 */
अटल व्योम t4_report_fw_error(काष्ठा adapter *adap)
अणु
	अटल स्थिर अक्षर *स्थिर reason[] = अणु
		"Crash",                        /* PCIE_FW_EVAL_CRASH */
		"During Device Preparation",    /* PCIE_FW_EVAL_PREP */
		"During Device Configuration",  /* PCIE_FW_EVAL_CONF */
		"During Device Initialization", /* PCIE_FW_EVAL_INIT */
		"Unexpected Event",             /* PCIE_FW_EVAL_UNEXPECTEDEVENT */
		"Insufficient Airflow",         /* PCIE_FW_EVAL_OVERHEAT */
		"Device Shutdown",              /* PCIE_FW_EVAL_DEVICESHUTDOWN */
		"Reserved",                     /* reserved */
	पूर्ण;
	u32 pcie_fw;

	pcie_fw = t4_पढ़ो_reg(adap, PCIE_FW_A);
	अगर (pcie_fw & PCIE_FW_ERR_F) अणु
		dev_err(adap->pdev_dev, "Firmware reports adapter error: %s\n",
			reason[PCIE_FW_EVAL_G(pcie_fw)]);
		adap->flags &= ~CXGB4_FW_OK;
	पूर्ण
पूर्ण

/*
 * Get the reply to a mailbox command and store it in @rpl in big-endian order.
 */
अटल व्योम get_mbox_rpl(काष्ठा adapter *adap, __be64 *rpl, पूर्णांक nflit,
			 u32 mbox_addr)
अणु
	क्रम ( ; nflit; nflit--, mbox_addr += 8)
		*rpl++ = cpu_to_be64(t4_पढ़ो_reg64(adap, mbox_addr));
पूर्ण

/*
 * Handle a FW निश्चितion reported in a mailbox.
 */
अटल व्योम fw_asrt(काष्ठा adapter *adap, u32 mbox_addr)
अणु
	काष्ठा fw_debug_cmd asrt;

	get_mbox_rpl(adap, (__be64 *)&asrt, माप(asrt) / 8, mbox_addr);
	dev_alert(adap->pdev_dev,
		  "FW assertion at %.16s:%u, val0 %#x, val1 %#x\n",
		  asrt.u.निश्चित.filename_0_7, be32_to_cpu(asrt.u.निश्चित.line),
		  be32_to_cpu(asrt.u.निश्चित.x), be32_to_cpu(asrt.u.निश्चित.y));
पूर्ण

/**
 *	t4_record_mbox - record a Firmware Mailbox Command/Reply in the log
 *	@adapter: the adapter
 *	@cmd: the Firmware Mailbox Command or Reply
 *	@size: command length in bytes
 *	@access: the समय (ms) needed to access the Firmware Mailbox
 *	@execute: the समय (ms) the command spent being executed
 */
अटल व्योम t4_record_mbox(काष्ठा adapter *adapter,
			   स्थिर __be64 *cmd, अचिन्हित पूर्णांक size,
			   पूर्णांक access, पूर्णांक execute)
अणु
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;
	काष्ठा mbox_cmd *entry;
	पूर्णांक i;

	entry = mbox_cmd_log_entry(log, log->cursor++);
	अगर (log->cursor == log->size)
		log->cursor = 0;

	क्रम (i = 0; i < size / 8; i++)
		entry->cmd[i] = be64_to_cpu(cmd[i]);
	जबतक (i < MBOX_LEN / 8)
		entry->cmd[i++] = 0;
	entry->बारtamp = jअगरfies;
	entry->seqno = log->seqno++;
	entry->access = access;
	entry->execute = execute;
पूर्ण

/**
 *	t4_wr_mbox_meat_समयout - send a command to FW through the given mailbox
 *	@adap: the adapter
 *	@mbox: index of the mailbox to use
 *	@cmd: the command to ग_लिखो
 *	@size: command length in bytes
 *	@rpl: where to optionally store the reply
 *	@sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *	@समयout: समय to रुको क्रम command to finish beक्रमe timing out
 *
 *	Sends the given command to FW through the selected mailbox and रुकोs
 *	क्रम the FW to execute the command.  If @rpl is not %शून्य it is used to
 *	store the FW's reply to the command.  The command and its optional
 *	reply are of the same length.  FW can take up to %FW_CMD_MAX_TIMEOUT ms
 *	to respond.  @sleep_ok determines whether we may sleep जबतक aरुकोing
 *	the response.  If sleeping is allowed we use progressive backoff
 *	otherwise we spin.
 *
 *	The वापस value is 0 on success or a negative त्रुटि_सं on failure.  A
 *	failure can happen either because we are not able to execute the
 *	command or FW executes it but संकेतs an error.  In the latter हाल
 *	the वापस value is the error code indicated by FW (negated).
 */
पूर्णांक t4_wr_mbox_meat_समयout(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd,
			    पूर्णांक size, व्योम *rpl, bool sleep_ok, पूर्णांक समयout)
अणु
	अटल स्थिर पूर्णांक delay[] = अणु
		1, 1, 3, 5, 10, 10, 20, 50, 100, 200
	पूर्ण;

	काष्ठा mbox_list entry;
	u16 access = 0;
	u16 execute = 0;
	u32 v;
	u64 res;
	पूर्णांक i, ms, delay_idx, ret;
	स्थिर __be64 *p = cmd;
	u32 data_reg = PF_REG(mbox, CIM_PF_MAILBOX_DATA_A);
	u32 ctl_reg = PF_REG(mbox, CIM_PF_MAILBOX_CTRL_A);
	__be64 cmd_rpl[MBOX_LEN / 8];
	u32 pcie_fw;

	अगर ((size & 15) || size > MBOX_LEN)
		वापस -EINVAL;

	/*
	 * If the device is off-line, as in EEH, commands will समय out.
	 * Fail them early so we करोn't waste समय रुकोing.
	 */
	अगर (adap->pdev->error_state != pci_channel_io_normal)
		वापस -EIO;

	/* If we have a negative समयout, that implies that we can't sleep. */
	अगर (समयout < 0) अणु
		sleep_ok = false;
		समयout = -समयout;
	पूर्ण

	/* Queue ourselves onto the mailbox access list.  When our entry is at
	 * the front of the list, we have rights to access the mailbox.  So we
	 * रुको [क्रम a जबतक] till we're at the front [or bail out with an
	 * EBUSY] ...
	 */
	spin_lock_bh(&adap->mbox_lock);
	list_add_tail(&entry.list, &adap->mlist.list);
	spin_unlock_bh(&adap->mbox_lock);

	delay_idx = 0;
	ms = delay[0];

	क्रम (i = 0; ; i += ms) अणु
		/* If we've रुकोed too दीर्घ, वापस a busy indication.  This
		 * really ought to be based on our initial position in the
		 * mailbox access list but this is a start.  We very rarely
		 * contend on access to the mailbox ...
		 */
		pcie_fw = t4_पढ़ो_reg(adap, PCIE_FW_A);
		अगर (i > FW_CMD_MAX_TIMEOUT || (pcie_fw & PCIE_FW_ERR_F)) अणु
			spin_lock_bh(&adap->mbox_lock);
			list_del(&entry.list);
			spin_unlock_bh(&adap->mbox_lock);
			ret = (pcie_fw & PCIE_FW_ERR_F) ? -ENXIO : -EBUSY;
			t4_record_mbox(adap, cmd, size, access, ret);
			वापस ret;
		पूर्ण

		/* If we're at the head, अवरोध out and start the mailbox
		 * protocol.
		 */
		अगर (list_first_entry(&adap->mlist.list, काष्ठा mbox_list,
				     list) == &entry)
			अवरोध;

		/* Delay क्रम a bit beक्रमe checking again ... */
		अगर (sleep_ok) अणु
			ms = delay[delay_idx];  /* last element may repeat */
			अगर (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		पूर्ण अन्यथा अणु
			mdelay(ms);
		पूर्ण
	पूर्ण

	/* Loop trying to get ownership of the mailbox.  Return an error
	 * अगर we can't gain ownership.
	 */
	v = MBOWNER_G(t4_पढ़ो_reg(adap, ctl_reg));
	क्रम (i = 0; v == MBOX_OWNER_NONE && i < 3; i++)
		v = MBOWNER_G(t4_पढ़ो_reg(adap, ctl_reg));
	अगर (v != MBOX_OWNER_DRV) अणु
		spin_lock_bh(&adap->mbox_lock);
		list_del(&entry.list);
		spin_unlock_bh(&adap->mbox_lock);
		ret = (v == MBOX_OWNER_FW) ? -EBUSY : -ETIMEDOUT;
		t4_record_mbox(adap, cmd, size, access, ret);
		वापस ret;
	पूर्ण

	/* Copy in the new mailbox command and send it on its way ... */
	t4_record_mbox(adap, cmd, size, access, 0);
	क्रम (i = 0; i < size; i += 8)
		t4_ग_लिखो_reg64(adap, data_reg + i, be64_to_cpu(*p++));

	t4_ग_लिखो_reg(adap, ctl_reg, MBMSGVALID_F | MBOWNER_V(MBOX_OWNER_FW));
	t4_पढ़ो_reg(adap, ctl_reg);          /* flush ग_लिखो */

	delay_idx = 0;
	ms = delay[0];

	क्रम (i = 0;
	     !((pcie_fw = t4_पढ़ो_reg(adap, PCIE_FW_A)) & PCIE_FW_ERR_F) &&
	     i < समयout;
	     i += ms) अणु
		अगर (sleep_ok) अणु
			ms = delay[delay_idx];  /* last element may repeat */
			अगर (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		पूर्ण अन्यथा
			mdelay(ms);

		v = t4_पढ़ो_reg(adap, ctl_reg);
		अगर (MBOWNER_G(v) == MBOX_OWNER_DRV) अणु
			अगर (!(v & MBMSGVALID_F)) अणु
				t4_ग_लिखो_reg(adap, ctl_reg, 0);
				जारी;
			पूर्ण

			get_mbox_rpl(adap, cmd_rpl, MBOX_LEN / 8, data_reg);
			res = be64_to_cpu(cmd_rpl[0]);

			अगर (FW_CMD_OP_G(res >> 32) == FW_DEBUG_CMD) अणु
				fw_asrt(adap, data_reg);
				res = FW_CMD_RETVAL_V(EIO);
			पूर्ण अन्यथा अगर (rpl) अणु
				स_नकल(rpl, cmd_rpl, size);
			पूर्ण

			t4_ग_लिखो_reg(adap, ctl_reg, 0);

			execute = i + ms;
			t4_record_mbox(adap, cmd_rpl,
				       MBOX_LEN, access, execute);
			spin_lock_bh(&adap->mbox_lock);
			list_del(&entry.list);
			spin_unlock_bh(&adap->mbox_lock);
			वापस -FW_CMD_RETVAL_G((पूर्णांक)res);
		पूर्ण
	पूर्ण

	ret = (pcie_fw & PCIE_FW_ERR_F) ? -ENXIO : -ETIMEDOUT;
	t4_record_mbox(adap, cmd, size, access, ret);
	dev_err(adap->pdev_dev, "command %#x in mailbox %d timed out\n",
		*(स्थिर u8 *)cmd, mbox);
	t4_report_fw_error(adap);
	spin_lock_bh(&adap->mbox_lock);
	list_del(&entry.list);
	spin_unlock_bh(&adap->mbox_lock);
	t4_fatal_err(adap);
	वापस ret;
पूर्ण

पूर्णांक t4_wr_mbox_meat(काष्ठा adapter *adap, पूर्णांक mbox, स्थिर व्योम *cmd, पूर्णांक size,
		    व्योम *rpl, bool sleep_ok)
अणु
	वापस t4_wr_mbox_meat_समयout(adap, mbox, cmd, size, rpl, sleep_ok,
				       FW_CMD_MAX_TIMEOUT);
पूर्ण

अटल पूर्णांक t4_edc_err_पढ़ो(काष्ठा adapter *adap, पूर्णांक idx)
अणु
	u32 edc_ecc_err_addr_reg;
	u32 rdata_reg;

	अगर (is_t4(adap->params.chip)) अणु
		CH_WARN(adap, "%s: T4 NOT supported.\n", __func__);
		वापस 0;
	पूर्ण
	अगर (idx != 0 && idx != 1) अणु
		CH_WARN(adap, "%s: idx %d NOT supported.\n", __func__, idx);
		वापस 0;
	पूर्ण

	edc_ecc_err_addr_reg = EDC_T5_REG(EDC_H_ECC_ERR_ADDR_A, idx);
	rdata_reg = EDC_T5_REG(EDC_H_BIST_STATUS_RDATA_A, idx);

	CH_WARN(adap,
		"edc%d err addr 0x%x: 0x%x.\n",
		idx, edc_ecc_err_addr_reg,
		t4_पढ़ो_reg(adap, edc_ecc_err_addr_reg));
	CH_WARN(adap,
		"bist: 0x%x, status %llx %llx %llx %llx %llx %llx %llx %llx %llx.\n",
		rdata_reg,
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 8),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 16),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 24),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 32),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 40),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 48),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 56),
		(अचिन्हित दीर्घ दीर्घ)t4_पढ़ो_reg64(adap, rdata_reg + 64));

	वापस 0;
पूर्ण

/**
 * t4_memory_rw_init - Get memory winकरोw relative offset, base, and size.
 * @adap: the adapter
 * @win: PCI-E Memory Winकरोw to use
 * @mtype: memory type: MEM_EDC0, MEM_EDC1, MEM_HMA or MEM_MC
 * @mem_off: memory relative offset with respect to @mtype.
 * @mem_base: configured memory base address.
 * @mem_aperture: configured memory winकरोw aperture.
 *
 * Get the configured memory winकरोw's relative offset, base, and size.
 */
पूर्णांक t4_memory_rw_init(काष्ठा adapter *adap, पूर्णांक win, पूर्णांक mtype, u32 *mem_off,
		      u32 *mem_base, u32 *mem_aperture)
अणु
	u32 edc_size, mc_size, mem_reg;

	/* Offset पूर्णांकo the region of memory which is being accessed
	 * MEM_EDC0 = 0
	 * MEM_EDC1 = 1
	 * MEM_MC   = 2 -- MEM_MC क्रम chips with only 1 memory controller
	 * MEM_MC1  = 3 -- क्रम chips with 2 memory controllers (e.g. T5)
	 * MEM_HMA  = 4
	 */
	edc_size  = EDRAM0_SIZE_G(t4_पढ़ो_reg(adap, MA_EDRAM0_BAR_A));
	अगर (mtype == MEM_HMA) अणु
		*mem_off = 2 * (edc_size * 1024 * 1024);
	पूर्ण अन्यथा अगर (mtype != MEM_MC1) अणु
		*mem_off = (mtype * (edc_size * 1024 * 1024));
	पूर्ण अन्यथा अणु
		mc_size = EXT_MEM0_SIZE_G(t4_पढ़ो_reg(adap,
						      MA_EXT_MEMORY0_BAR_A));
		*mem_off = (MEM_MC0 * edc_size + mc_size) * 1024 * 1024;
	पूर्ण

	/* Each PCI-E Memory Winकरोw is programmed with a winकरोw size -- or
	 * "aperture" -- which controls the granularity of its mapping onto
	 * adapter memory.  We need to grab that aperture in order to know
	 * how to use the specअगरied winकरोw.  The winकरोw is also programmed
	 * with the base address of the Memory Winकरोw in BAR0's address
	 * space.  For T4 this is an असलolute PCI-E Bus Address.  For T5
	 * the address is relative to BAR0.
	 */
	mem_reg = t4_पढ़ो_reg(adap,
			      PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A,
						  win));
	/* a dead adapter will वापस 0xffffffff क्रम PIO पढ़ोs */
	अगर (mem_reg == 0xffffffff)
		वापस -ENXIO;

	*mem_aperture = 1 << (WINDOW_G(mem_reg) + WINDOW_SHIFT_X);
	*mem_base = PCIखातापूर्णST_G(mem_reg) << PCIखातापूर्णST_SHIFT_X;
	अगर (is_t4(adap->params.chip))
		*mem_base -= adap->t4_bar0;

	वापस 0;
पूर्ण

/**
 * t4_memory_update_win - Move memory winकरोw to specअगरied address.
 * @adap: the adapter
 * @win: PCI-E Memory Winकरोw to use
 * @addr: location to move.
 *
 * Move memory winकरोw to specअगरied address.
 */
व्योम t4_memory_update_win(काष्ठा adapter *adap, पूर्णांक win, u32 addr)
अणु
	t4_ग_लिखो_reg(adap,
		     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win),
		     addr);
	/* Read it back to ensure that changes propagate beक्रमe we
	 * attempt to use the new value.
	 */
	t4_पढ़ो_reg(adap,
		    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win));
पूर्ण

/**
 * t4_memory_rw_residual - Read/Write residual data.
 * @adap: the adapter
 * @off: relative offset within residual to start पढ़ो/ग_लिखो.
 * @addr: address within indicated memory type.
 * @buf: host memory buffer
 * @dir: direction of transfer T4_MEMORY_READ (1) or T4_MEMORY_WRITE (0)
 *
 * Read/Write residual data less than 32-bits.
 */
व्योम t4_memory_rw_residual(काष्ठा adapter *adap, u32 off, u32 addr, u8 *buf,
			   पूर्णांक dir)
अणु
	जोड़ अणु
		u32 word;
		अक्षर byte[4];
	पूर्ण last;
	अचिन्हित अक्षर *bp;
	पूर्णांक i;

	अगर (dir == T4_MEMORY_READ) अणु
		last.word = le32_to_cpu((__क्रमce __le32)
					t4_पढ़ो_reg(adap, addr));
		क्रम (bp = (अचिन्हित अक्षर *)buf, i = off; i < 4; i++)
			bp[i] = last.byte[i];
	पूर्ण अन्यथा अणु
		last.word = *buf;
		क्रम (i = off; i < 4; i++)
			last.byte[i] = 0;
		t4_ग_लिखो_reg(adap, addr,
			     (__क्रमce u32)cpu_to_le32(last.word));
	पूर्ण
पूर्ण

/**
 *	t4_memory_rw - पढ़ो/ग_लिखो EDC 0, EDC 1 or MC via PCIE memory winकरोw
 *	@adap: the adapter
 *	@win: PCI-E Memory Winकरोw to use
 *	@mtype: memory type: MEM_EDC0, MEM_EDC1 or MEM_MC
 *	@addr: address within indicated memory type
 *	@len: amount of memory to transfer
 *	@hbuf: host memory buffer
 *	@dir: direction of transfer T4_MEMORY_READ (1) or T4_MEMORY_WRITE (0)
 *
 *	Reads/ग_लिखोs an [almost] arbitrary memory region in the firmware: the
 *	firmware memory address and host buffer must be aligned on 32-bit
 *	boundaries; the length may be arbitrary.  The memory is transferred as
 *	a raw byte sequence from/to the firmware's memory.  If this memory
 *	contains data काष्ठाures which contain multi-byte पूर्णांकegers, it's the
 *	caller's responsibility to perक्रमm appropriate byte order conversions.
 */
पूर्णांक t4_memory_rw(काष्ठा adapter *adap, पूर्णांक win, पूर्णांक mtype, u32 addr,
		 u32 len, व्योम *hbuf, पूर्णांक dir)
अणु
	u32 pos, offset, resid, memoffset;
	u32 win_pf, mem_aperture, mem_base;
	u32 *buf;
	पूर्णांक ret;

	/* Argument sanity checks ...
	 */
	अगर (addr & 0x3 || (uपूर्णांकptr_t)hbuf & 0x3)
		वापस -EINVAL;
	buf = (u32 *)hbuf;

	/* It's convenient to be able to handle lengths which aren't a
	 * multiple of 32-bits because we often end up transferring files to
	 * the firmware.  So we'll handle that by normalizing the length here
	 * and then handling any residual transfer at the end.
	 */
	resid = len & 0x3;
	len -= resid;

	ret = t4_memory_rw_init(adap, win, mtype, &memoffset, &mem_base,
				&mem_aperture);
	अगर (ret)
		वापस ret;

	/* Determine the PCIE_MEM_ACCESS_OFFSET */
	addr = addr + memoffset;

	win_pf = is_t4(adap->params.chip) ? 0 : PFNUM_V(adap->pf);

	/* Calculate our initial PCI-E Memory Winकरोw Position and Offset पूर्णांकo
	 * that Winकरोw.
	 */
	pos = addr & ~(mem_aperture - 1);
	offset = addr - pos;

	/* Set up initial PCI-E Memory Winकरोw to cover the start of our
	 * transfer.
	 */
	t4_memory_update_win(adap, win, pos | win_pf);

	/* Transfer data to/from the adapter as दीर्घ as there's an पूर्णांकegral
	 * number of 32-bit transfers to complete.
	 *
	 * A note on Endianness issues:
	 *
	 * The "register" पढ़ोs and ग_लिखोs below from/to the PCI-E Memory
	 * Winकरोw invoke the standard adapter Big-Endian to PCI-E Link
	 * Little-Endian "swizzel."  As a result, अगर we have the following
	 * data in adapter memory:
	 *
	 *     Memory:  ... | b0 | b1 | b2 | b3 | ...
	 *     Address:      i+0  i+1  i+2  i+3
	 *
	 * Then a पढ़ो of the adapter memory via the PCI-E Memory Winकरोw
	 * will yield:
	 *
	 *     x = पढ़ोl(i)
	 *         31                  0
	 *         [ b3 | b2 | b1 | b0 ]
	 *
	 * If this value is stored पूर्णांकo local memory on a Little-Endian प्रणाली
	 * it will show up correctly in local memory as:
	 *
	 *     ( ..., b0, b1, b2, b3, ... )
	 *
	 * But on a Big-Endian प्रणाली, the store will show up in memory
	 * incorrectly swizzled as:
	 *
	 *     ( ..., b3, b2, b1, b0, ... )
	 *
	 * So we need to account क्रम this in the पढ़ोs and ग_लिखोs to the
	 * PCI-E Memory Winकरोw below by unकरोing the रेजिस्टर पढ़ो/ग_लिखो
	 * swizzels.
	 */
	जबतक (len > 0) अणु
		अगर (dir == T4_MEMORY_READ)
			*buf++ = le32_to_cpu((__क्रमce __le32)t4_पढ़ो_reg(adap,
						mem_base + offset));
		अन्यथा
			t4_ग_लिखो_reg(adap, mem_base + offset,
				     (__क्रमce u32)cpu_to_le32(*buf++));
		offset += माप(__be32);
		len -= माप(__be32);

		/* If we've reached the end of our current winकरोw aperture,
		 * move the PCI-E Memory Winकरोw on to the next.  Note that
		 * करोing this here after "len" may be 0 allows us to set up
		 * the PCI-E Memory Winकरोw क्रम a possible final residual
		 * transfer below ...
		 */
		अगर (offset == mem_aperture) अणु
			pos += mem_aperture;
			offset = 0;
			t4_memory_update_win(adap, win, pos | win_pf);
		पूर्ण
	पूर्ण

	/* If the original transfer had a length which wasn't a multiple of
	 * 32-bits, now's where we need to finish off the transfer of the
	 * residual amount.  The PCI-E Memory Winकरोw has alपढ़ोy been moved
	 * above (अगर necessary) to cover this final transfer.
	 */
	अगर (resid)
		t4_memory_rw_residual(adap, resid, mem_base + offset,
				      (u8 *)buf, dir);

	वापस 0;
पूर्ण

/* Return the specअगरied PCI-E Configuration Space रेजिस्टर from our Physical
 * Function.  We try first via a Firmware LDST Command since we prefer to let
 * the firmware own all of these रेजिस्टरs, but अगर that fails we go क्रम it
 * directly ourselves.
 */
u32 t4_पढ़ो_pcie_cfg4(काष्ठा adapter *adap, पूर्णांक reg)
अणु
	u32 val, ldst_addrspace;

	/* If fw_attach != 0, स्थिरruct and send the Firmware LDST Command to
	 * retrieve the specअगरied PCI-E Configuration Space रेजिस्टर.
	 */
	काष्ठा fw_ldst_cmd ldst_cmd;
	पूर्णांक ret;

	स_रखो(&ldst_cmd, 0, माप(ldst_cmd));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_FUNC_PCIE);
	ldst_cmd.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					       FW_CMD_REQUEST_F |
					       FW_CMD_READ_F |
					       ldst_addrspace);
	ldst_cmd.cycles_to_len16 = cpu_to_be32(FW_LEN16(ldst_cmd));
	ldst_cmd.u.pcie.select_naccess = FW_LDST_CMD_NACCESS_V(1);
	ldst_cmd.u.pcie.ctrl_to_fn =
		(FW_LDST_CMD_LC_F | FW_LDST_CMD_FN_V(adap->pf));
	ldst_cmd.u.pcie.r = reg;

	/* If the LDST Command succeeds, वापस the result, otherwise
	 * fall through to पढ़ोing it directly ourselves ...
	 */
	ret = t4_wr_mbox(adap, adap->mbox, &ldst_cmd, माप(ldst_cmd),
			 &ldst_cmd);
	अगर (ret == 0)
		val = be32_to_cpu(ldst_cmd.u.pcie.data[0]);
	अन्यथा
		/* Read the desired Configuration Space रेजिस्टर via the PCI-E
		 * Backकरोor mechanism.
		 */
		t4_hw_pci_पढ़ो_cfg4(adap, reg, &val);
	वापस val;
पूर्ण

/* Get the winकरोw based on base passed to it.
 * Winकरोw aperture is currently unhandled, but there is no use हाल क्रम it
 * right now
 */
अटल u32 t4_get_winकरोw(काष्ठा adapter *adap, u32 pci_base, u64 pci_mask,
			 u32 memwin_base)
अणु
	u32 ret;

	अगर (is_t4(adap->params.chip)) अणु
		u32 bar0;

		/* Truncation पूर्णांकentional: we only पढ़ो the bottom 32-bits of
		 * the 64-bit BAR0/BAR1 ...  We use the hardware backकरोor
		 * mechanism to पढ़ो BAR0 instead of using
		 * pci_resource_start() because we could be operating from
		 * within a Virtual Machine which is trapping our accesses to
		 * our Configuration Space and we need to set up the PCI-E
		 * Memory Winकरोw decoders with the actual addresses which will
		 * be coming across the PCI-E link.
		 */
		bar0 = t4_पढ़ो_pcie_cfg4(adap, pci_base);
		bar0 &= pci_mask;
		adap->t4_bar0 = bar0;

		ret = bar0 + memwin_base;
	पूर्ण अन्यथा अणु
		/* For T5, only relative offset inside the PCIe BAR is passed */
		ret = memwin_base;
	पूर्ण
	वापस ret;
पूर्ण

/* Get the शेष utility winकरोw (win0) used by everyone */
u32 t4_get_util_winकरोw(काष्ठा adapter *adap)
अणु
	वापस t4_get_winकरोw(adap, PCI_BASE_ADDRESS_0,
			     PCI_BASE_ADDRESS_MEM_MASK, MEMWIN0_BASE);
पूर्ण

/* Set up memory winकरोw क्रम accessing adapter memory ranges.  (Read
 * back MA रेजिस्टर to ensure that changes propagate beक्रमe we attempt
 * to use the new values.)
 */
व्योम t4_setup_memwin(काष्ठा adapter *adap, u32 memwin_base, u32 winकरोw)
अणु
	t4_ग_लिखो_reg(adap,
		     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, winकरोw),
		     memwin_base | BIR_V(0) |
		     WINDOW_V(ilog2(MEMWIN0_APERTURE) - WINDOW_SHIFT_X));
	t4_पढ़ो_reg(adap,
		    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, winकरोw));
पूर्ण

/**
 *	t4_get_regs_len - वापस the size of the chips रेजिस्टर set
 *	@adapter: the adapter
 *
 *	Returns the size of the chip's BAR0 रेजिस्टर space.
 */
अचिन्हित पूर्णांक t4_get_regs_len(काष्ठा adapter *adapter)
अणु
	अचिन्हित पूर्णांक chip_version = CHELSIO_CHIP_VERSION(adapter->params.chip);

	चयन (chip_version) अणु
	हाल CHELSIO_T4:
		वापस T4_REGMAP_SIZE;

	हाल CHELSIO_T5:
	हाल CHELSIO_T6:
		वापस T5_REGMAP_SIZE;
	पूर्ण

	dev_err(adapter->pdev_dev,
		"Unsupported chip version %d\n", chip_version);
	वापस 0;
पूर्ण

/**
 *	t4_get_regs - पढ़ो chip रेजिस्टरs पूर्णांकo provided buffer
 *	@adap: the adapter
 *	@buf: रेजिस्टर buffer
 *	@buf_size: size (in bytes) of रेजिस्टर buffer
 *
 *	If the provided रेजिस्टर buffer isn't large enough for the chip's
 *	full रेजिस्टर range, the रेजिस्टर dump will be truncated to the
 *	रेजिस्टर buffer's size.
 */
व्योम t4_get_regs(काष्ठा adapter *adap, व्योम *buf, माप_प्रकार buf_size)
अणु
	अटल स्थिर अचिन्हित पूर्णांक t4_reg_ranges[] = अणु
		0x1008, 0x1108,
		0x1180, 0x1184,
		0x1190, 0x1194,
		0x11a0, 0x11a4,
		0x11b0, 0x11b4,
		0x11fc, 0x123c,
		0x1300, 0x173c,
		0x1800, 0x18fc,
		0x3000, 0x30d8,
		0x30e0, 0x30e4,
		0x30ec, 0x5910,
		0x5920, 0x5924,
		0x5960, 0x5960,
		0x5968, 0x5968,
		0x5970, 0x5970,
		0x5978, 0x5978,
		0x5980, 0x5980,
		0x5988, 0x5988,
		0x5990, 0x5990,
		0x5998, 0x5998,
		0x59a0, 0x59d4,
		0x5a00, 0x5ae0,
		0x5ae8, 0x5ae8,
		0x5af0, 0x5af0,
		0x5af8, 0x5af8,
		0x6000, 0x6098,
		0x6100, 0x6150,
		0x6200, 0x6208,
		0x6240, 0x6248,
		0x6280, 0x62b0,
		0x62c0, 0x6338,
		0x6370, 0x638c,
		0x6400, 0x643c,
		0x6500, 0x6524,
		0x6a00, 0x6a04,
		0x6a14, 0x6a38,
		0x6a60, 0x6a70,
		0x6a78, 0x6a78,
		0x6b00, 0x6b0c,
		0x6b1c, 0x6b84,
		0x6bf0, 0x6bf8,
		0x6c00, 0x6c0c,
		0x6c1c, 0x6c84,
		0x6cf0, 0x6cf8,
		0x6d00, 0x6d0c,
		0x6d1c, 0x6d84,
		0x6df0, 0x6df8,
		0x6e00, 0x6e0c,
		0x6e1c, 0x6e84,
		0x6ef0, 0x6ef8,
		0x6f00, 0x6f0c,
		0x6f1c, 0x6f84,
		0x6ff0, 0x6ff8,
		0x7000, 0x700c,
		0x701c, 0x7084,
		0x70f0, 0x70f8,
		0x7100, 0x710c,
		0x711c, 0x7184,
		0x71f0, 0x71f8,
		0x7200, 0x720c,
		0x721c, 0x7284,
		0x72f0, 0x72f8,
		0x7300, 0x730c,
		0x731c, 0x7384,
		0x73f0, 0x73f8,
		0x7400, 0x7450,
		0x7500, 0x7530,
		0x7600, 0x760c,
		0x7614, 0x761c,
		0x7680, 0x76cc,
		0x7700, 0x7798,
		0x77c0, 0x77fc,
		0x7900, 0x79fc,
		0x7b00, 0x7b58,
		0x7b60, 0x7b84,
		0x7b8c, 0x7c38,
		0x7d00, 0x7d38,
		0x7d40, 0x7d80,
		0x7d8c, 0x7ddc,
		0x7de4, 0x7e04,
		0x7e10, 0x7e1c,
		0x7e24, 0x7e38,
		0x7e40, 0x7e44,
		0x7e4c, 0x7e78,
		0x7e80, 0x7ea4,
		0x7eac, 0x7edc,
		0x7ee8, 0x7efc,
		0x8dc0, 0x8e04,
		0x8e10, 0x8e1c,
		0x8e30, 0x8e78,
		0x8ea0, 0x8eb8,
		0x8ec0, 0x8f6c,
		0x8fc0, 0x9008,
		0x9010, 0x9058,
		0x9060, 0x9060,
		0x9068, 0x9074,
		0x90fc, 0x90fc,
		0x9400, 0x9408,
		0x9410, 0x9458,
		0x9600, 0x9600,
		0x9608, 0x9638,
		0x9640, 0x96bc,
		0x9800, 0x9808,
		0x9820, 0x983c,
		0x9850, 0x9864,
		0x9c00, 0x9c6c,
		0x9c80, 0x9cec,
		0x9d00, 0x9d6c,
		0x9d80, 0x9dec,
		0x9e00, 0x9e6c,
		0x9e80, 0x9eec,
		0x9f00, 0x9f6c,
		0x9f80, 0x9fec,
		0xd004, 0xd004,
		0xd010, 0xd03c,
		0xdfc0, 0xdfe0,
		0xe000, 0xea7c,
		0xf000, 0x11110,
		0x11118, 0x11190,
		0x19040, 0x1906c,
		0x19078, 0x19080,
		0x1908c, 0x190e4,
		0x190f0, 0x190f8,
		0x19100, 0x19110,
		0x19120, 0x19124,
		0x19150, 0x19194,
		0x1919c, 0x191b0,
		0x191d0, 0x191e8,
		0x19238, 0x1924c,
		0x193f8, 0x1943c,
		0x1944c, 0x19474,
		0x19490, 0x194e0,
		0x194f0, 0x194f8,
		0x19800, 0x19c08,
		0x19c10, 0x19c90,
		0x19ca0, 0x19ce4,
		0x19cf0, 0x19d40,
		0x19d50, 0x19d94,
		0x19da0, 0x19de8,
		0x19df0, 0x19e40,
		0x19e50, 0x19e90,
		0x19ea0, 0x19f4c,
		0x1a000, 0x1a004,
		0x1a010, 0x1a06c,
		0x1a0b0, 0x1a0e4,
		0x1a0ec, 0x1a0f4,
		0x1a100, 0x1a108,
		0x1a114, 0x1a120,
		0x1a128, 0x1a130,
		0x1a138, 0x1a138,
		0x1a190, 0x1a1c4,
		0x1a1fc, 0x1a1fc,
		0x1e040, 0x1e04c,
		0x1e284, 0x1e28c,
		0x1e2c0, 0x1e2c0,
		0x1e2e0, 0x1e2e0,
		0x1e300, 0x1e384,
		0x1e3c0, 0x1e3c8,
		0x1e440, 0x1e44c,
		0x1e684, 0x1e68c,
		0x1e6c0, 0x1e6c0,
		0x1e6e0, 0x1e6e0,
		0x1e700, 0x1e784,
		0x1e7c0, 0x1e7c8,
		0x1e840, 0x1e84c,
		0x1ea84, 0x1ea8c,
		0x1eac0, 0x1eac0,
		0x1eae0, 0x1eae0,
		0x1eb00, 0x1eb84,
		0x1ebc0, 0x1ebc8,
		0x1ec40, 0x1ec4c,
		0x1ee84, 0x1ee8c,
		0x1eec0, 0x1eec0,
		0x1eee0, 0x1eee0,
		0x1ef00, 0x1ef84,
		0x1efc0, 0x1efc8,
		0x1f040, 0x1f04c,
		0x1f284, 0x1f28c,
		0x1f2c0, 0x1f2c0,
		0x1f2e0, 0x1f2e0,
		0x1f300, 0x1f384,
		0x1f3c0, 0x1f3c8,
		0x1f440, 0x1f44c,
		0x1f684, 0x1f68c,
		0x1f6c0, 0x1f6c0,
		0x1f6e0, 0x1f6e0,
		0x1f700, 0x1f784,
		0x1f7c0, 0x1f7c8,
		0x1f840, 0x1f84c,
		0x1fa84, 0x1fa8c,
		0x1fac0, 0x1fac0,
		0x1fae0, 0x1fae0,
		0x1fb00, 0x1fb84,
		0x1fbc0, 0x1fbc8,
		0x1fc40, 0x1fc4c,
		0x1fe84, 0x1fe8c,
		0x1fec0, 0x1fec0,
		0x1fee0, 0x1fee0,
		0x1ff00, 0x1ff84,
		0x1ffc0, 0x1ffc8,
		0x20000, 0x2002c,
		0x20100, 0x2013c,
		0x20190, 0x201a0,
		0x201a8, 0x201b8,
		0x201c4, 0x201c8,
		0x20200, 0x20318,
		0x20400, 0x204b4,
		0x204c0, 0x20528,
		0x20540, 0x20614,
		0x21000, 0x21040,
		0x2104c, 0x21060,
		0x210c0, 0x210ec,
		0x21200, 0x21268,
		0x21270, 0x21284,
		0x212fc, 0x21388,
		0x21400, 0x21404,
		0x21500, 0x21500,
		0x21510, 0x21518,
		0x2152c, 0x21530,
		0x2153c, 0x2153c,
		0x21550, 0x21554,
		0x21600, 0x21600,
		0x21608, 0x2161c,
		0x21624, 0x21628,
		0x21630, 0x21634,
		0x2163c, 0x2163c,
		0x21700, 0x2171c,
		0x21780, 0x2178c,
		0x21800, 0x21818,
		0x21820, 0x21828,
		0x21830, 0x21848,
		0x21850, 0x21854,
		0x21860, 0x21868,
		0x21870, 0x21870,
		0x21878, 0x21898,
		0x218a0, 0x218a8,
		0x218b0, 0x218c8,
		0x218d0, 0x218d4,
		0x218e0, 0x218e8,
		0x218f0, 0x218f0,
		0x218f8, 0x21a18,
		0x21a20, 0x21a28,
		0x21a30, 0x21a48,
		0x21a50, 0x21a54,
		0x21a60, 0x21a68,
		0x21a70, 0x21a70,
		0x21a78, 0x21a98,
		0x21aa0, 0x21aa8,
		0x21ab0, 0x21ac8,
		0x21ad0, 0x21ad4,
		0x21ae0, 0x21ae8,
		0x21af0, 0x21af0,
		0x21af8, 0x21c18,
		0x21c20, 0x21c20,
		0x21c28, 0x21c30,
		0x21c38, 0x21c38,
		0x21c80, 0x21c98,
		0x21ca0, 0x21ca8,
		0x21cb0, 0x21cc8,
		0x21cd0, 0x21cd4,
		0x21ce0, 0x21ce8,
		0x21cf0, 0x21cf0,
		0x21cf8, 0x21d7c,
		0x21e00, 0x21e04,
		0x22000, 0x2202c,
		0x22100, 0x2213c,
		0x22190, 0x221a0,
		0x221a8, 0x221b8,
		0x221c4, 0x221c8,
		0x22200, 0x22318,
		0x22400, 0x224b4,
		0x224c0, 0x22528,
		0x22540, 0x22614,
		0x23000, 0x23040,
		0x2304c, 0x23060,
		0x230c0, 0x230ec,
		0x23200, 0x23268,
		0x23270, 0x23284,
		0x232fc, 0x23388,
		0x23400, 0x23404,
		0x23500, 0x23500,
		0x23510, 0x23518,
		0x2352c, 0x23530,
		0x2353c, 0x2353c,
		0x23550, 0x23554,
		0x23600, 0x23600,
		0x23608, 0x2361c,
		0x23624, 0x23628,
		0x23630, 0x23634,
		0x2363c, 0x2363c,
		0x23700, 0x2371c,
		0x23780, 0x2378c,
		0x23800, 0x23818,
		0x23820, 0x23828,
		0x23830, 0x23848,
		0x23850, 0x23854,
		0x23860, 0x23868,
		0x23870, 0x23870,
		0x23878, 0x23898,
		0x238a0, 0x238a8,
		0x238b0, 0x238c8,
		0x238d0, 0x238d4,
		0x238e0, 0x238e8,
		0x238f0, 0x238f0,
		0x238f8, 0x23a18,
		0x23a20, 0x23a28,
		0x23a30, 0x23a48,
		0x23a50, 0x23a54,
		0x23a60, 0x23a68,
		0x23a70, 0x23a70,
		0x23a78, 0x23a98,
		0x23aa0, 0x23aa8,
		0x23ab0, 0x23ac8,
		0x23ad0, 0x23ad4,
		0x23ae0, 0x23ae8,
		0x23af0, 0x23af0,
		0x23af8, 0x23c18,
		0x23c20, 0x23c20,
		0x23c28, 0x23c30,
		0x23c38, 0x23c38,
		0x23c80, 0x23c98,
		0x23ca0, 0x23ca8,
		0x23cb0, 0x23cc8,
		0x23cd0, 0x23cd4,
		0x23ce0, 0x23ce8,
		0x23cf0, 0x23cf0,
		0x23cf8, 0x23d7c,
		0x23e00, 0x23e04,
		0x24000, 0x2402c,
		0x24100, 0x2413c,
		0x24190, 0x241a0,
		0x241a8, 0x241b8,
		0x241c4, 0x241c8,
		0x24200, 0x24318,
		0x24400, 0x244b4,
		0x244c0, 0x24528,
		0x24540, 0x24614,
		0x25000, 0x25040,
		0x2504c, 0x25060,
		0x250c0, 0x250ec,
		0x25200, 0x25268,
		0x25270, 0x25284,
		0x252fc, 0x25388,
		0x25400, 0x25404,
		0x25500, 0x25500,
		0x25510, 0x25518,
		0x2552c, 0x25530,
		0x2553c, 0x2553c,
		0x25550, 0x25554,
		0x25600, 0x25600,
		0x25608, 0x2561c,
		0x25624, 0x25628,
		0x25630, 0x25634,
		0x2563c, 0x2563c,
		0x25700, 0x2571c,
		0x25780, 0x2578c,
		0x25800, 0x25818,
		0x25820, 0x25828,
		0x25830, 0x25848,
		0x25850, 0x25854,
		0x25860, 0x25868,
		0x25870, 0x25870,
		0x25878, 0x25898,
		0x258a0, 0x258a8,
		0x258b0, 0x258c8,
		0x258d0, 0x258d4,
		0x258e0, 0x258e8,
		0x258f0, 0x258f0,
		0x258f8, 0x25a18,
		0x25a20, 0x25a28,
		0x25a30, 0x25a48,
		0x25a50, 0x25a54,
		0x25a60, 0x25a68,
		0x25a70, 0x25a70,
		0x25a78, 0x25a98,
		0x25aa0, 0x25aa8,
		0x25ab0, 0x25ac8,
		0x25ad0, 0x25ad4,
		0x25ae0, 0x25ae8,
		0x25af0, 0x25af0,
		0x25af8, 0x25c18,
		0x25c20, 0x25c20,
		0x25c28, 0x25c30,
		0x25c38, 0x25c38,
		0x25c80, 0x25c98,
		0x25ca0, 0x25ca8,
		0x25cb0, 0x25cc8,
		0x25cd0, 0x25cd4,
		0x25ce0, 0x25ce8,
		0x25cf0, 0x25cf0,
		0x25cf8, 0x25d7c,
		0x25e00, 0x25e04,
		0x26000, 0x2602c,
		0x26100, 0x2613c,
		0x26190, 0x261a0,
		0x261a8, 0x261b8,
		0x261c4, 0x261c8,
		0x26200, 0x26318,
		0x26400, 0x264b4,
		0x264c0, 0x26528,
		0x26540, 0x26614,
		0x27000, 0x27040,
		0x2704c, 0x27060,
		0x270c0, 0x270ec,
		0x27200, 0x27268,
		0x27270, 0x27284,
		0x272fc, 0x27388,
		0x27400, 0x27404,
		0x27500, 0x27500,
		0x27510, 0x27518,
		0x2752c, 0x27530,
		0x2753c, 0x2753c,
		0x27550, 0x27554,
		0x27600, 0x27600,
		0x27608, 0x2761c,
		0x27624, 0x27628,
		0x27630, 0x27634,
		0x2763c, 0x2763c,
		0x27700, 0x2771c,
		0x27780, 0x2778c,
		0x27800, 0x27818,
		0x27820, 0x27828,
		0x27830, 0x27848,
		0x27850, 0x27854,
		0x27860, 0x27868,
		0x27870, 0x27870,
		0x27878, 0x27898,
		0x278a0, 0x278a8,
		0x278b0, 0x278c8,
		0x278d0, 0x278d4,
		0x278e0, 0x278e8,
		0x278f0, 0x278f0,
		0x278f8, 0x27a18,
		0x27a20, 0x27a28,
		0x27a30, 0x27a48,
		0x27a50, 0x27a54,
		0x27a60, 0x27a68,
		0x27a70, 0x27a70,
		0x27a78, 0x27a98,
		0x27aa0, 0x27aa8,
		0x27ab0, 0x27ac8,
		0x27ad0, 0x27ad4,
		0x27ae0, 0x27ae8,
		0x27af0, 0x27af0,
		0x27af8, 0x27c18,
		0x27c20, 0x27c20,
		0x27c28, 0x27c30,
		0x27c38, 0x27c38,
		0x27c80, 0x27c98,
		0x27ca0, 0x27ca8,
		0x27cb0, 0x27cc8,
		0x27cd0, 0x27cd4,
		0x27ce0, 0x27ce8,
		0x27cf0, 0x27cf0,
		0x27cf8, 0x27d7c,
		0x27e00, 0x27e04,
	पूर्ण;

	अटल स्थिर अचिन्हित पूर्णांक t5_reg_ranges[] = अणु
		0x1008, 0x10c0,
		0x10cc, 0x10f8,
		0x1100, 0x1100,
		0x110c, 0x1148,
		0x1180, 0x1184,
		0x1190, 0x1194,
		0x11a0, 0x11a4,
		0x11b0, 0x11b4,
		0x11fc, 0x123c,
		0x1280, 0x173c,
		0x1800, 0x18fc,
		0x3000, 0x3028,
		0x3060, 0x30b0,
		0x30b8, 0x30d8,
		0x30e0, 0x30fc,
		0x3140, 0x357c,
		0x35a8, 0x35cc,
		0x35ec, 0x35ec,
		0x3600, 0x5624,
		0x56cc, 0x56ec,
		0x56f4, 0x5720,
		0x5728, 0x575c,
		0x580c, 0x5814,
		0x5890, 0x589c,
		0x58a4, 0x58ac,
		0x58b8, 0x58bc,
		0x5940, 0x59c8,
		0x59d0, 0x59dc,
		0x59fc, 0x5a18,
		0x5a60, 0x5a70,
		0x5a80, 0x5a9c,
		0x5b94, 0x5bfc,
		0x6000, 0x6020,
		0x6028, 0x6040,
		0x6058, 0x609c,
		0x60a8, 0x614c,
		0x7700, 0x7798,
		0x77c0, 0x78fc,
		0x7b00, 0x7b58,
		0x7b60, 0x7b84,
		0x7b8c, 0x7c54,
		0x7d00, 0x7d38,
		0x7d40, 0x7d80,
		0x7d8c, 0x7ddc,
		0x7de4, 0x7e04,
		0x7e10, 0x7e1c,
		0x7e24, 0x7e38,
		0x7e40, 0x7e44,
		0x7e4c, 0x7e78,
		0x7e80, 0x7edc,
		0x7ee8, 0x7efc,
		0x8dc0, 0x8de0,
		0x8df8, 0x8e04,
		0x8e10, 0x8e84,
		0x8ea0, 0x8f84,
		0x8fc0, 0x9058,
		0x9060, 0x9060,
		0x9068, 0x90f8,
		0x9400, 0x9408,
		0x9410, 0x9470,
		0x9600, 0x9600,
		0x9608, 0x9638,
		0x9640, 0x96f4,
		0x9800, 0x9808,
		0x9810, 0x9864,
		0x9c00, 0x9c6c,
		0x9c80, 0x9cec,
		0x9d00, 0x9d6c,
		0x9d80, 0x9dec,
		0x9e00, 0x9e6c,
		0x9e80, 0x9eec,
		0x9f00, 0x9f6c,
		0x9f80, 0xa020,
		0xd000, 0xd004,
		0xd010, 0xd03c,
		0xdfc0, 0xdfe0,
		0xe000, 0x1106c,
		0x11074, 0x11088,
		0x1109c, 0x1117c,
		0x11190, 0x11204,
		0x19040, 0x1906c,
		0x19078, 0x19080,
		0x1908c, 0x190e8,
		0x190f0, 0x190f8,
		0x19100, 0x19110,
		0x19120, 0x19124,
		0x19150, 0x19194,
		0x1919c, 0x191b0,
		0x191d0, 0x191e8,
		0x19238, 0x19290,
		0x193f8, 0x19428,
		0x19430, 0x19444,
		0x1944c, 0x1946c,
		0x19474, 0x19474,
		0x19490, 0x194cc,
		0x194f0, 0x194f8,
		0x19c00, 0x19c08,
		0x19c10, 0x19c60,
		0x19c94, 0x19ce4,
		0x19cf0, 0x19d40,
		0x19d50, 0x19d94,
		0x19da0, 0x19de8,
		0x19df0, 0x19e10,
		0x19e50, 0x19e90,
		0x19ea0, 0x19f24,
		0x19f34, 0x19f34,
		0x19f40, 0x19f50,
		0x19f90, 0x19fb4,
		0x19fc4, 0x19fe4,
		0x1a000, 0x1a004,
		0x1a010, 0x1a06c,
		0x1a0b0, 0x1a0e4,
		0x1a0ec, 0x1a0f8,
		0x1a100, 0x1a108,
		0x1a114, 0x1a130,
		0x1a138, 0x1a1c4,
		0x1a1fc, 0x1a1fc,
		0x1e008, 0x1e00c,
		0x1e040, 0x1e044,
		0x1e04c, 0x1e04c,
		0x1e284, 0x1e290,
		0x1e2c0, 0x1e2c0,
		0x1e2e0, 0x1e2e0,
		0x1e300, 0x1e384,
		0x1e3c0, 0x1e3c8,
		0x1e408, 0x1e40c,
		0x1e440, 0x1e444,
		0x1e44c, 0x1e44c,
		0x1e684, 0x1e690,
		0x1e6c0, 0x1e6c0,
		0x1e6e0, 0x1e6e0,
		0x1e700, 0x1e784,
		0x1e7c0, 0x1e7c8,
		0x1e808, 0x1e80c,
		0x1e840, 0x1e844,
		0x1e84c, 0x1e84c,
		0x1ea84, 0x1ea90,
		0x1eac0, 0x1eac0,
		0x1eae0, 0x1eae0,
		0x1eb00, 0x1eb84,
		0x1ebc0, 0x1ebc8,
		0x1ec08, 0x1ec0c,
		0x1ec40, 0x1ec44,
		0x1ec4c, 0x1ec4c,
		0x1ee84, 0x1ee90,
		0x1eec0, 0x1eec0,
		0x1eee0, 0x1eee0,
		0x1ef00, 0x1ef84,
		0x1efc0, 0x1efc8,
		0x1f008, 0x1f00c,
		0x1f040, 0x1f044,
		0x1f04c, 0x1f04c,
		0x1f284, 0x1f290,
		0x1f2c0, 0x1f2c0,
		0x1f2e0, 0x1f2e0,
		0x1f300, 0x1f384,
		0x1f3c0, 0x1f3c8,
		0x1f408, 0x1f40c,
		0x1f440, 0x1f444,
		0x1f44c, 0x1f44c,
		0x1f684, 0x1f690,
		0x1f6c0, 0x1f6c0,
		0x1f6e0, 0x1f6e0,
		0x1f700, 0x1f784,
		0x1f7c0, 0x1f7c8,
		0x1f808, 0x1f80c,
		0x1f840, 0x1f844,
		0x1f84c, 0x1f84c,
		0x1fa84, 0x1fa90,
		0x1fac0, 0x1fac0,
		0x1fae0, 0x1fae0,
		0x1fb00, 0x1fb84,
		0x1fbc0, 0x1fbc8,
		0x1fc08, 0x1fc0c,
		0x1fc40, 0x1fc44,
		0x1fc4c, 0x1fc4c,
		0x1fe84, 0x1fe90,
		0x1fec0, 0x1fec0,
		0x1fee0, 0x1fee0,
		0x1ff00, 0x1ff84,
		0x1ffc0, 0x1ffc8,
		0x30000, 0x30030,
		0x30100, 0x30144,
		0x30190, 0x301a0,
		0x301a8, 0x301b8,
		0x301c4, 0x301c8,
		0x301d0, 0x301d0,
		0x30200, 0x30318,
		0x30400, 0x304b4,
		0x304c0, 0x3052c,
		0x30540, 0x3061c,
		0x30800, 0x30828,
		0x30834, 0x30834,
		0x308c0, 0x30908,
		0x30910, 0x309ac,
		0x30a00, 0x30a14,
		0x30a1c, 0x30a2c,
		0x30a44, 0x30a50,
		0x30a74, 0x30a74,
		0x30a7c, 0x30afc,
		0x30b08, 0x30c24,
		0x30d00, 0x30d00,
		0x30d08, 0x30d14,
		0x30d1c, 0x30d20,
		0x30d3c, 0x30d3c,
		0x30d48, 0x30d50,
		0x31200, 0x3120c,
		0x31220, 0x31220,
		0x31240, 0x31240,
		0x31600, 0x3160c,
		0x31a00, 0x31a1c,
		0x31e00, 0x31e20,
		0x31e38, 0x31e3c,
		0x31e80, 0x31e80,
		0x31e88, 0x31ea8,
		0x31eb0, 0x31eb4,
		0x31ec8, 0x31ed4,
		0x31fb8, 0x32004,
		0x32200, 0x32200,
		0x32208, 0x32240,
		0x32248, 0x32280,
		0x32288, 0x322c0,
		0x322c8, 0x322fc,
		0x32600, 0x32630,
		0x32a00, 0x32abc,
		0x32b00, 0x32b10,
		0x32b20, 0x32b30,
		0x32b40, 0x32b50,
		0x32b60, 0x32b70,
		0x33000, 0x33028,
		0x33030, 0x33048,
		0x33060, 0x33068,
		0x33070, 0x3309c,
		0x330f0, 0x33128,
		0x33130, 0x33148,
		0x33160, 0x33168,
		0x33170, 0x3319c,
		0x331f0, 0x33238,
		0x33240, 0x33240,
		0x33248, 0x33250,
		0x3325c, 0x33264,
		0x33270, 0x332b8,
		0x332c0, 0x332e4,
		0x332f8, 0x33338,
		0x33340, 0x33340,
		0x33348, 0x33350,
		0x3335c, 0x33364,
		0x33370, 0x333b8,
		0x333c0, 0x333e4,
		0x333f8, 0x33428,
		0x33430, 0x33448,
		0x33460, 0x33468,
		0x33470, 0x3349c,
		0x334f0, 0x33528,
		0x33530, 0x33548,
		0x33560, 0x33568,
		0x33570, 0x3359c,
		0x335f0, 0x33638,
		0x33640, 0x33640,
		0x33648, 0x33650,
		0x3365c, 0x33664,
		0x33670, 0x336b8,
		0x336c0, 0x336e4,
		0x336f8, 0x33738,
		0x33740, 0x33740,
		0x33748, 0x33750,
		0x3375c, 0x33764,
		0x33770, 0x337b8,
		0x337c0, 0x337e4,
		0x337f8, 0x337fc,
		0x33814, 0x33814,
		0x3382c, 0x3382c,
		0x33880, 0x3388c,
		0x338e8, 0x338ec,
		0x33900, 0x33928,
		0x33930, 0x33948,
		0x33960, 0x33968,
		0x33970, 0x3399c,
		0x339f0, 0x33a38,
		0x33a40, 0x33a40,
		0x33a48, 0x33a50,
		0x33a5c, 0x33a64,
		0x33a70, 0x33ab8,
		0x33ac0, 0x33ae4,
		0x33af8, 0x33b10,
		0x33b28, 0x33b28,
		0x33b3c, 0x33b50,
		0x33bf0, 0x33c10,
		0x33c28, 0x33c28,
		0x33c3c, 0x33c50,
		0x33cf0, 0x33cfc,
		0x34000, 0x34030,
		0x34100, 0x34144,
		0x34190, 0x341a0,
		0x341a8, 0x341b8,
		0x341c4, 0x341c8,
		0x341d0, 0x341d0,
		0x34200, 0x34318,
		0x34400, 0x344b4,
		0x344c0, 0x3452c,
		0x34540, 0x3461c,
		0x34800, 0x34828,
		0x34834, 0x34834,
		0x348c0, 0x34908,
		0x34910, 0x349ac,
		0x34a00, 0x34a14,
		0x34a1c, 0x34a2c,
		0x34a44, 0x34a50,
		0x34a74, 0x34a74,
		0x34a7c, 0x34afc,
		0x34b08, 0x34c24,
		0x34d00, 0x34d00,
		0x34d08, 0x34d14,
		0x34d1c, 0x34d20,
		0x34d3c, 0x34d3c,
		0x34d48, 0x34d50,
		0x35200, 0x3520c,
		0x35220, 0x35220,
		0x35240, 0x35240,
		0x35600, 0x3560c,
		0x35a00, 0x35a1c,
		0x35e00, 0x35e20,
		0x35e38, 0x35e3c,
		0x35e80, 0x35e80,
		0x35e88, 0x35ea8,
		0x35eb0, 0x35eb4,
		0x35ec8, 0x35ed4,
		0x35fb8, 0x36004,
		0x36200, 0x36200,
		0x36208, 0x36240,
		0x36248, 0x36280,
		0x36288, 0x362c0,
		0x362c8, 0x362fc,
		0x36600, 0x36630,
		0x36a00, 0x36abc,
		0x36b00, 0x36b10,
		0x36b20, 0x36b30,
		0x36b40, 0x36b50,
		0x36b60, 0x36b70,
		0x37000, 0x37028,
		0x37030, 0x37048,
		0x37060, 0x37068,
		0x37070, 0x3709c,
		0x370f0, 0x37128,
		0x37130, 0x37148,
		0x37160, 0x37168,
		0x37170, 0x3719c,
		0x371f0, 0x37238,
		0x37240, 0x37240,
		0x37248, 0x37250,
		0x3725c, 0x37264,
		0x37270, 0x372b8,
		0x372c0, 0x372e4,
		0x372f8, 0x37338,
		0x37340, 0x37340,
		0x37348, 0x37350,
		0x3735c, 0x37364,
		0x37370, 0x373b8,
		0x373c0, 0x373e4,
		0x373f8, 0x37428,
		0x37430, 0x37448,
		0x37460, 0x37468,
		0x37470, 0x3749c,
		0x374f0, 0x37528,
		0x37530, 0x37548,
		0x37560, 0x37568,
		0x37570, 0x3759c,
		0x375f0, 0x37638,
		0x37640, 0x37640,
		0x37648, 0x37650,
		0x3765c, 0x37664,
		0x37670, 0x376b8,
		0x376c0, 0x376e4,
		0x376f8, 0x37738,
		0x37740, 0x37740,
		0x37748, 0x37750,
		0x3775c, 0x37764,
		0x37770, 0x377b8,
		0x377c0, 0x377e4,
		0x377f8, 0x377fc,
		0x37814, 0x37814,
		0x3782c, 0x3782c,
		0x37880, 0x3788c,
		0x378e8, 0x378ec,
		0x37900, 0x37928,
		0x37930, 0x37948,
		0x37960, 0x37968,
		0x37970, 0x3799c,
		0x379f0, 0x37a38,
		0x37a40, 0x37a40,
		0x37a48, 0x37a50,
		0x37a5c, 0x37a64,
		0x37a70, 0x37ab8,
		0x37ac0, 0x37ae4,
		0x37af8, 0x37b10,
		0x37b28, 0x37b28,
		0x37b3c, 0x37b50,
		0x37bf0, 0x37c10,
		0x37c28, 0x37c28,
		0x37c3c, 0x37c50,
		0x37cf0, 0x37cfc,
		0x38000, 0x38030,
		0x38100, 0x38144,
		0x38190, 0x381a0,
		0x381a8, 0x381b8,
		0x381c4, 0x381c8,
		0x381d0, 0x381d0,
		0x38200, 0x38318,
		0x38400, 0x384b4,
		0x384c0, 0x3852c,
		0x38540, 0x3861c,
		0x38800, 0x38828,
		0x38834, 0x38834,
		0x388c0, 0x38908,
		0x38910, 0x389ac,
		0x38a00, 0x38a14,
		0x38a1c, 0x38a2c,
		0x38a44, 0x38a50,
		0x38a74, 0x38a74,
		0x38a7c, 0x38afc,
		0x38b08, 0x38c24,
		0x38d00, 0x38d00,
		0x38d08, 0x38d14,
		0x38d1c, 0x38d20,
		0x38d3c, 0x38d3c,
		0x38d48, 0x38d50,
		0x39200, 0x3920c,
		0x39220, 0x39220,
		0x39240, 0x39240,
		0x39600, 0x3960c,
		0x39a00, 0x39a1c,
		0x39e00, 0x39e20,
		0x39e38, 0x39e3c,
		0x39e80, 0x39e80,
		0x39e88, 0x39ea8,
		0x39eb0, 0x39eb4,
		0x39ec8, 0x39ed4,
		0x39fb8, 0x3a004,
		0x3a200, 0x3a200,
		0x3a208, 0x3a240,
		0x3a248, 0x3a280,
		0x3a288, 0x3a2c0,
		0x3a2c8, 0x3a2fc,
		0x3a600, 0x3a630,
		0x3aa00, 0x3aabc,
		0x3ab00, 0x3ab10,
		0x3ab20, 0x3ab30,
		0x3ab40, 0x3ab50,
		0x3ab60, 0x3ab70,
		0x3b000, 0x3b028,
		0x3b030, 0x3b048,
		0x3b060, 0x3b068,
		0x3b070, 0x3b09c,
		0x3b0f0, 0x3b128,
		0x3b130, 0x3b148,
		0x3b160, 0x3b168,
		0x3b170, 0x3b19c,
		0x3b1f0, 0x3b238,
		0x3b240, 0x3b240,
		0x3b248, 0x3b250,
		0x3b25c, 0x3b264,
		0x3b270, 0x3b2b8,
		0x3b2c0, 0x3b2e4,
		0x3b2f8, 0x3b338,
		0x3b340, 0x3b340,
		0x3b348, 0x3b350,
		0x3b35c, 0x3b364,
		0x3b370, 0x3b3b8,
		0x3b3c0, 0x3b3e4,
		0x3b3f8, 0x3b428,
		0x3b430, 0x3b448,
		0x3b460, 0x3b468,
		0x3b470, 0x3b49c,
		0x3b4f0, 0x3b528,
		0x3b530, 0x3b548,
		0x3b560, 0x3b568,
		0x3b570, 0x3b59c,
		0x3b5f0, 0x3b638,
		0x3b640, 0x3b640,
		0x3b648, 0x3b650,
		0x3b65c, 0x3b664,
		0x3b670, 0x3b6b8,
		0x3b6c0, 0x3b6e4,
		0x3b6f8, 0x3b738,
		0x3b740, 0x3b740,
		0x3b748, 0x3b750,
		0x3b75c, 0x3b764,
		0x3b770, 0x3b7b8,
		0x3b7c0, 0x3b7e4,
		0x3b7f8, 0x3b7fc,
		0x3b814, 0x3b814,
		0x3b82c, 0x3b82c,
		0x3b880, 0x3b88c,
		0x3b8e8, 0x3b8ec,
		0x3b900, 0x3b928,
		0x3b930, 0x3b948,
		0x3b960, 0x3b968,
		0x3b970, 0x3b99c,
		0x3b9f0, 0x3ba38,
		0x3ba40, 0x3ba40,
		0x3ba48, 0x3ba50,
		0x3ba5c, 0x3ba64,
		0x3ba70, 0x3bab8,
		0x3bac0, 0x3bae4,
		0x3baf8, 0x3bb10,
		0x3bb28, 0x3bb28,
		0x3bb3c, 0x3bb50,
		0x3bbf0, 0x3bc10,
		0x3bc28, 0x3bc28,
		0x3bc3c, 0x3bc50,
		0x3bcf0, 0x3bcfc,
		0x3c000, 0x3c030,
		0x3c100, 0x3c144,
		0x3c190, 0x3c1a0,
		0x3c1a8, 0x3c1b8,
		0x3c1c4, 0x3c1c8,
		0x3c1d0, 0x3c1d0,
		0x3c200, 0x3c318,
		0x3c400, 0x3c4b4,
		0x3c4c0, 0x3c52c,
		0x3c540, 0x3c61c,
		0x3c800, 0x3c828,
		0x3c834, 0x3c834,
		0x3c8c0, 0x3c908,
		0x3c910, 0x3c9ac,
		0x3ca00, 0x3ca14,
		0x3ca1c, 0x3ca2c,
		0x3ca44, 0x3ca50,
		0x3ca74, 0x3ca74,
		0x3ca7c, 0x3cafc,
		0x3cb08, 0x3cc24,
		0x3cd00, 0x3cd00,
		0x3cd08, 0x3cd14,
		0x3cd1c, 0x3cd20,
		0x3cd3c, 0x3cd3c,
		0x3cd48, 0x3cd50,
		0x3d200, 0x3d20c,
		0x3d220, 0x3d220,
		0x3d240, 0x3d240,
		0x3d600, 0x3d60c,
		0x3da00, 0x3da1c,
		0x3de00, 0x3de20,
		0x3de38, 0x3de3c,
		0x3de80, 0x3de80,
		0x3de88, 0x3dea8,
		0x3deb0, 0x3deb4,
		0x3dec8, 0x3ded4,
		0x3dfb8, 0x3e004,
		0x3e200, 0x3e200,
		0x3e208, 0x3e240,
		0x3e248, 0x3e280,
		0x3e288, 0x3e2c0,
		0x3e2c8, 0x3e2fc,
		0x3e600, 0x3e630,
		0x3ea00, 0x3eabc,
		0x3eb00, 0x3eb10,
		0x3eb20, 0x3eb30,
		0x3eb40, 0x3eb50,
		0x3eb60, 0x3eb70,
		0x3f000, 0x3f028,
		0x3f030, 0x3f048,
		0x3f060, 0x3f068,
		0x3f070, 0x3f09c,
		0x3f0f0, 0x3f128,
		0x3f130, 0x3f148,
		0x3f160, 0x3f168,
		0x3f170, 0x3f19c,
		0x3f1f0, 0x3f238,
		0x3f240, 0x3f240,
		0x3f248, 0x3f250,
		0x3f25c, 0x3f264,
		0x3f270, 0x3f2b8,
		0x3f2c0, 0x3f2e4,
		0x3f2f8, 0x3f338,
		0x3f340, 0x3f340,
		0x3f348, 0x3f350,
		0x3f35c, 0x3f364,
		0x3f370, 0x3f3b8,
		0x3f3c0, 0x3f3e4,
		0x3f3f8, 0x3f428,
		0x3f430, 0x3f448,
		0x3f460, 0x3f468,
		0x3f470, 0x3f49c,
		0x3f4f0, 0x3f528,
		0x3f530, 0x3f548,
		0x3f560, 0x3f568,
		0x3f570, 0x3f59c,
		0x3f5f0, 0x3f638,
		0x3f640, 0x3f640,
		0x3f648, 0x3f650,
		0x3f65c, 0x3f664,
		0x3f670, 0x3f6b8,
		0x3f6c0, 0x3f6e4,
		0x3f6f8, 0x3f738,
		0x3f740, 0x3f740,
		0x3f748, 0x3f750,
		0x3f75c, 0x3f764,
		0x3f770, 0x3f7b8,
		0x3f7c0, 0x3f7e4,
		0x3f7f8, 0x3f7fc,
		0x3f814, 0x3f814,
		0x3f82c, 0x3f82c,
		0x3f880, 0x3f88c,
		0x3f8e8, 0x3f8ec,
		0x3f900, 0x3f928,
		0x3f930, 0x3f948,
		0x3f960, 0x3f968,
		0x3f970, 0x3f99c,
		0x3f9f0, 0x3fa38,
		0x3fa40, 0x3fa40,
		0x3fa48, 0x3fa50,
		0x3fa5c, 0x3fa64,
		0x3fa70, 0x3fab8,
		0x3fac0, 0x3fae4,
		0x3faf8, 0x3fb10,
		0x3fb28, 0x3fb28,
		0x3fb3c, 0x3fb50,
		0x3fbf0, 0x3fc10,
		0x3fc28, 0x3fc28,
		0x3fc3c, 0x3fc50,
		0x3fcf0, 0x3fcfc,
		0x40000, 0x4000c,
		0x40040, 0x40050,
		0x40060, 0x40068,
		0x4007c, 0x4008c,
		0x40094, 0x400b0,
		0x400c0, 0x40144,
		0x40180, 0x4018c,
		0x40200, 0x40254,
		0x40260, 0x40264,
		0x40270, 0x40288,
		0x40290, 0x40298,
		0x402ac, 0x402c8,
		0x402d0, 0x402e0,
		0x402f0, 0x402f0,
		0x40300, 0x4033c,
		0x403f8, 0x403fc,
		0x41304, 0x413c4,
		0x41400, 0x4140c,
		0x41414, 0x4141c,
		0x41480, 0x414d0,
		0x44000, 0x44054,
		0x4405c, 0x44078,
		0x440c0, 0x44174,
		0x44180, 0x441ac,
		0x441b4, 0x441b8,
		0x441c0, 0x44254,
		0x4425c, 0x44278,
		0x442c0, 0x44374,
		0x44380, 0x443ac,
		0x443b4, 0x443b8,
		0x443c0, 0x44454,
		0x4445c, 0x44478,
		0x444c0, 0x44574,
		0x44580, 0x445ac,
		0x445b4, 0x445b8,
		0x445c0, 0x44654,
		0x4465c, 0x44678,
		0x446c0, 0x44774,
		0x44780, 0x447ac,
		0x447b4, 0x447b8,
		0x447c0, 0x44854,
		0x4485c, 0x44878,
		0x448c0, 0x44974,
		0x44980, 0x449ac,
		0x449b4, 0x449b8,
		0x449c0, 0x449fc,
		0x45000, 0x45004,
		0x45010, 0x45030,
		0x45040, 0x45060,
		0x45068, 0x45068,
		0x45080, 0x45084,
		0x450a0, 0x450b0,
		0x45200, 0x45204,
		0x45210, 0x45230,
		0x45240, 0x45260,
		0x45268, 0x45268,
		0x45280, 0x45284,
		0x452a0, 0x452b0,
		0x460c0, 0x460e4,
		0x47000, 0x4703c,
		0x47044, 0x4708c,
		0x47200, 0x47250,
		0x47400, 0x47408,
		0x47414, 0x47420,
		0x47600, 0x47618,
		0x47800, 0x47814,
		0x48000, 0x4800c,
		0x48040, 0x48050,
		0x48060, 0x48068,
		0x4807c, 0x4808c,
		0x48094, 0x480b0,
		0x480c0, 0x48144,
		0x48180, 0x4818c,
		0x48200, 0x48254,
		0x48260, 0x48264,
		0x48270, 0x48288,
		0x48290, 0x48298,
		0x482ac, 0x482c8,
		0x482d0, 0x482e0,
		0x482f0, 0x482f0,
		0x48300, 0x4833c,
		0x483f8, 0x483fc,
		0x49304, 0x493c4,
		0x49400, 0x4940c,
		0x49414, 0x4941c,
		0x49480, 0x494d0,
		0x4c000, 0x4c054,
		0x4c05c, 0x4c078,
		0x4c0c0, 0x4c174,
		0x4c180, 0x4c1ac,
		0x4c1b4, 0x4c1b8,
		0x4c1c0, 0x4c254,
		0x4c25c, 0x4c278,
		0x4c2c0, 0x4c374,
		0x4c380, 0x4c3ac,
		0x4c3b4, 0x4c3b8,
		0x4c3c0, 0x4c454,
		0x4c45c, 0x4c478,
		0x4c4c0, 0x4c574,
		0x4c580, 0x4c5ac,
		0x4c5b4, 0x4c5b8,
		0x4c5c0, 0x4c654,
		0x4c65c, 0x4c678,
		0x4c6c0, 0x4c774,
		0x4c780, 0x4c7ac,
		0x4c7b4, 0x4c7b8,
		0x4c7c0, 0x4c854,
		0x4c85c, 0x4c878,
		0x4c8c0, 0x4c974,
		0x4c980, 0x4c9ac,
		0x4c9b4, 0x4c9b8,
		0x4c9c0, 0x4c9fc,
		0x4d000, 0x4d004,
		0x4d010, 0x4d030,
		0x4d040, 0x4d060,
		0x4d068, 0x4d068,
		0x4d080, 0x4d084,
		0x4d0a0, 0x4d0b0,
		0x4d200, 0x4d204,
		0x4d210, 0x4d230,
		0x4d240, 0x4d260,
		0x4d268, 0x4d268,
		0x4d280, 0x4d284,
		0x4d2a0, 0x4d2b0,
		0x4e0c0, 0x4e0e4,
		0x4f000, 0x4f03c,
		0x4f044, 0x4f08c,
		0x4f200, 0x4f250,
		0x4f400, 0x4f408,
		0x4f414, 0x4f420,
		0x4f600, 0x4f618,
		0x4f800, 0x4f814,
		0x50000, 0x50084,
		0x50090, 0x500cc,
		0x50400, 0x50400,
		0x50800, 0x50884,
		0x50890, 0x508cc,
		0x50c00, 0x50c00,
		0x51000, 0x5101c,
		0x51300, 0x51308,
	पूर्ण;

	अटल स्थिर अचिन्हित पूर्णांक t6_reg_ranges[] = अणु
		0x1008, 0x101c,
		0x1024, 0x10a8,
		0x10b4, 0x10f8,
		0x1100, 0x1114,
		0x111c, 0x112c,
		0x1138, 0x113c,
		0x1144, 0x114c,
		0x1180, 0x1184,
		0x1190, 0x1194,
		0x11a0, 0x11a4,
		0x11b0, 0x11b4,
		0x11fc, 0x123c,
		0x1254, 0x1274,
		0x1280, 0x133c,
		0x1800, 0x18fc,
		0x3000, 0x302c,
		0x3060, 0x30b0,
		0x30b8, 0x30d8,
		0x30e0, 0x30fc,
		0x3140, 0x357c,
		0x35a8, 0x35cc,
		0x35ec, 0x35ec,
		0x3600, 0x5624,
		0x56cc, 0x56ec,
		0x56f4, 0x5720,
		0x5728, 0x575c,
		0x580c, 0x5814,
		0x5890, 0x589c,
		0x58a4, 0x58ac,
		0x58b8, 0x58bc,
		0x5940, 0x595c,
		0x5980, 0x598c,
		0x59b0, 0x59c8,
		0x59d0, 0x59dc,
		0x59fc, 0x5a18,
		0x5a60, 0x5a6c,
		0x5a80, 0x5a8c,
		0x5a94, 0x5a9c,
		0x5b94, 0x5bfc,
		0x5c10, 0x5e48,
		0x5e50, 0x5e94,
		0x5ea0, 0x5eb0,
		0x5ec0, 0x5ec0,
		0x5ec8, 0x5ed0,
		0x5ee0, 0x5ee0,
		0x5ef0, 0x5ef0,
		0x5f00, 0x5f00,
		0x6000, 0x6020,
		0x6028, 0x6040,
		0x6058, 0x609c,
		0x60a8, 0x619c,
		0x7700, 0x7798,
		0x77c0, 0x7880,
		0x78cc, 0x78fc,
		0x7b00, 0x7b58,
		0x7b60, 0x7b84,
		0x7b8c, 0x7c54,
		0x7d00, 0x7d38,
		0x7d40, 0x7d84,
		0x7d8c, 0x7ddc,
		0x7de4, 0x7e04,
		0x7e10, 0x7e1c,
		0x7e24, 0x7e38,
		0x7e40, 0x7e44,
		0x7e4c, 0x7e78,
		0x7e80, 0x7edc,
		0x7ee8, 0x7efc,
		0x8dc0, 0x8de4,
		0x8df8, 0x8e04,
		0x8e10, 0x8e84,
		0x8ea0, 0x8f88,
		0x8fb8, 0x9058,
		0x9060, 0x9060,
		0x9068, 0x90f8,
		0x9100, 0x9124,
		0x9400, 0x9470,
		0x9600, 0x9600,
		0x9608, 0x9638,
		0x9640, 0x9704,
		0x9710, 0x971c,
		0x9800, 0x9808,
		0x9810, 0x9864,
		0x9c00, 0x9c6c,
		0x9c80, 0x9cec,
		0x9d00, 0x9d6c,
		0x9d80, 0x9dec,
		0x9e00, 0x9e6c,
		0x9e80, 0x9eec,
		0x9f00, 0x9f6c,
		0x9f80, 0xa020,
		0xd000, 0xd03c,
		0xd100, 0xd118,
		0xd200, 0xd214,
		0xd220, 0xd234,
		0xd240, 0xd254,
		0xd260, 0xd274,
		0xd280, 0xd294,
		0xd2a0, 0xd2b4,
		0xd2c0, 0xd2d4,
		0xd2e0, 0xd2f4,
		0xd300, 0xd31c,
		0xdfc0, 0xdfe0,
		0xe000, 0xf008,
		0xf010, 0xf018,
		0xf020, 0xf028,
		0x11000, 0x11014,
		0x11048, 0x1106c,
		0x11074, 0x11088,
		0x11098, 0x11120,
		0x1112c, 0x1117c,
		0x11190, 0x112e0,
		0x11300, 0x1130c,
		0x12000, 0x1206c,
		0x19040, 0x1906c,
		0x19078, 0x19080,
		0x1908c, 0x190e8,
		0x190f0, 0x190f8,
		0x19100, 0x19110,
		0x19120, 0x19124,
		0x19150, 0x19194,
		0x1919c, 0x191b0,
		0x191d0, 0x191e8,
		0x19238, 0x19290,
		0x192a4, 0x192b0,
		0x192bc, 0x192bc,
		0x19348, 0x1934c,
		0x193f8, 0x19418,
		0x19420, 0x19428,
		0x19430, 0x19444,
		0x1944c, 0x1946c,
		0x19474, 0x19474,
		0x19490, 0x194cc,
		0x194f0, 0x194f8,
		0x19c00, 0x19c48,
		0x19c50, 0x19c80,
		0x19c94, 0x19c98,
		0x19ca0, 0x19cbc,
		0x19ce4, 0x19ce4,
		0x19cf0, 0x19cf8,
		0x19d00, 0x19d28,
		0x19d50, 0x19d78,
		0x19d94, 0x19d98,
		0x19da0, 0x19dc8,
		0x19df0, 0x19e10,
		0x19e50, 0x19e6c,
		0x19ea0, 0x19ebc,
		0x19ec4, 0x19ef4,
		0x19f04, 0x19f2c,
		0x19f34, 0x19f34,
		0x19f40, 0x19f50,
		0x19f90, 0x19fac,
		0x19fc4, 0x19fc8,
		0x19fd0, 0x19fe4,
		0x1a000, 0x1a004,
		0x1a010, 0x1a06c,
		0x1a0b0, 0x1a0e4,
		0x1a0ec, 0x1a0f8,
		0x1a100, 0x1a108,
		0x1a114, 0x1a130,
		0x1a138, 0x1a1c4,
		0x1a1fc, 0x1a1fc,
		0x1e008, 0x1e00c,
		0x1e040, 0x1e044,
		0x1e04c, 0x1e04c,
		0x1e284, 0x1e290,
		0x1e2c0, 0x1e2c0,
		0x1e2e0, 0x1e2e0,
		0x1e300, 0x1e384,
		0x1e3c0, 0x1e3c8,
		0x1e408, 0x1e40c,
		0x1e440, 0x1e444,
		0x1e44c, 0x1e44c,
		0x1e684, 0x1e690,
		0x1e6c0, 0x1e6c0,
		0x1e6e0, 0x1e6e0,
		0x1e700, 0x1e784,
		0x1e7c0, 0x1e7c8,
		0x1e808, 0x1e80c,
		0x1e840, 0x1e844,
		0x1e84c, 0x1e84c,
		0x1ea84, 0x1ea90,
		0x1eac0, 0x1eac0,
		0x1eae0, 0x1eae0,
		0x1eb00, 0x1eb84,
		0x1ebc0, 0x1ebc8,
		0x1ec08, 0x1ec0c,
		0x1ec40, 0x1ec44,
		0x1ec4c, 0x1ec4c,
		0x1ee84, 0x1ee90,
		0x1eec0, 0x1eec0,
		0x1eee0, 0x1eee0,
		0x1ef00, 0x1ef84,
		0x1efc0, 0x1efc8,
		0x1f008, 0x1f00c,
		0x1f040, 0x1f044,
		0x1f04c, 0x1f04c,
		0x1f284, 0x1f290,
		0x1f2c0, 0x1f2c0,
		0x1f2e0, 0x1f2e0,
		0x1f300, 0x1f384,
		0x1f3c0, 0x1f3c8,
		0x1f408, 0x1f40c,
		0x1f440, 0x1f444,
		0x1f44c, 0x1f44c,
		0x1f684, 0x1f690,
		0x1f6c0, 0x1f6c0,
		0x1f6e0, 0x1f6e0,
		0x1f700, 0x1f784,
		0x1f7c0, 0x1f7c8,
		0x1f808, 0x1f80c,
		0x1f840, 0x1f844,
		0x1f84c, 0x1f84c,
		0x1fa84, 0x1fa90,
		0x1fac0, 0x1fac0,
		0x1fae0, 0x1fae0,
		0x1fb00, 0x1fb84,
		0x1fbc0, 0x1fbc8,
		0x1fc08, 0x1fc0c,
		0x1fc40, 0x1fc44,
		0x1fc4c, 0x1fc4c,
		0x1fe84, 0x1fe90,
		0x1fec0, 0x1fec0,
		0x1fee0, 0x1fee0,
		0x1ff00, 0x1ff84,
		0x1ffc0, 0x1ffc8,
		0x30000, 0x30030,
		0x30100, 0x30168,
		0x30190, 0x301a0,
		0x301a8, 0x301b8,
		0x301c4, 0x301c8,
		0x301d0, 0x301d0,
		0x30200, 0x30320,
		0x30400, 0x304b4,
		0x304c0, 0x3052c,
		0x30540, 0x3061c,
		0x30800, 0x308a0,
		0x308c0, 0x30908,
		0x30910, 0x309b8,
		0x30a00, 0x30a04,
		0x30a0c, 0x30a14,
		0x30a1c, 0x30a2c,
		0x30a44, 0x30a50,
		0x30a74, 0x30a74,
		0x30a7c, 0x30afc,
		0x30b08, 0x30c24,
		0x30d00, 0x30d14,
		0x30d1c, 0x30d3c,
		0x30d44, 0x30d4c,
		0x30d54, 0x30d74,
		0x30d7c, 0x30d7c,
		0x30de0, 0x30de0,
		0x30e00, 0x30ed4,
		0x30f00, 0x30fa4,
		0x30fc0, 0x30fc4,
		0x31000, 0x31004,
		0x31080, 0x310fc,
		0x31208, 0x31220,
		0x3123c, 0x31254,
		0x31300, 0x31300,
		0x31308, 0x3131c,
		0x31338, 0x3133c,
		0x31380, 0x31380,
		0x31388, 0x313a8,
		0x313b4, 0x313b4,
		0x31400, 0x31420,
		0x31438, 0x3143c,
		0x31480, 0x31480,
		0x314a8, 0x314a8,
		0x314b0, 0x314b4,
		0x314c8, 0x314d4,
		0x31a40, 0x31a4c,
		0x31af0, 0x31b20,
		0x31b38, 0x31b3c,
		0x31b80, 0x31b80,
		0x31ba8, 0x31ba8,
		0x31bb0, 0x31bb4,
		0x31bc8, 0x31bd4,
		0x32140, 0x3218c,
		0x321f0, 0x321f4,
		0x32200, 0x32200,
		0x32218, 0x32218,
		0x32400, 0x32400,
		0x32408, 0x3241c,
		0x32618, 0x32620,
		0x32664, 0x32664,
		0x326a8, 0x326a8,
		0x326ec, 0x326ec,
		0x32a00, 0x32abc,
		0x32b00, 0x32b18,
		0x32b20, 0x32b38,
		0x32b40, 0x32b58,
		0x32b60, 0x32b78,
		0x32c00, 0x32c00,
		0x32c08, 0x32c3c,
		0x33000, 0x3302c,
		0x33034, 0x33050,
		0x33058, 0x33058,
		0x33060, 0x3308c,
		0x3309c, 0x330ac,
		0x330c0, 0x330c0,
		0x330c8, 0x330d0,
		0x330d8, 0x330e0,
		0x330ec, 0x3312c,
		0x33134, 0x33150,
		0x33158, 0x33158,
		0x33160, 0x3318c,
		0x3319c, 0x331ac,
		0x331c0, 0x331c0,
		0x331c8, 0x331d0,
		0x331d8, 0x331e0,
		0x331ec, 0x33290,
		0x33298, 0x332c4,
		0x332e4, 0x33390,
		0x33398, 0x333c4,
		0x333e4, 0x3342c,
		0x33434, 0x33450,
		0x33458, 0x33458,
		0x33460, 0x3348c,
		0x3349c, 0x334ac,
		0x334c0, 0x334c0,
		0x334c8, 0x334d0,
		0x334d8, 0x334e0,
		0x334ec, 0x3352c,
		0x33534, 0x33550,
		0x33558, 0x33558,
		0x33560, 0x3358c,
		0x3359c, 0x335ac,
		0x335c0, 0x335c0,
		0x335c8, 0x335d0,
		0x335d8, 0x335e0,
		0x335ec, 0x33690,
		0x33698, 0x336c4,
		0x336e4, 0x33790,
		0x33798, 0x337c4,
		0x337e4, 0x337fc,
		0x33814, 0x33814,
		0x33854, 0x33868,
		0x33880, 0x3388c,
		0x338c0, 0x338d0,
		0x338e8, 0x338ec,
		0x33900, 0x3392c,
		0x33934, 0x33950,
		0x33958, 0x33958,
		0x33960, 0x3398c,
		0x3399c, 0x339ac,
		0x339c0, 0x339c0,
		0x339c8, 0x339d0,
		0x339d8, 0x339e0,
		0x339ec, 0x33a90,
		0x33a98, 0x33ac4,
		0x33ae4, 0x33b10,
		0x33b24, 0x33b28,
		0x33b38, 0x33b50,
		0x33bf0, 0x33c10,
		0x33c24, 0x33c28,
		0x33c38, 0x33c50,
		0x33cf0, 0x33cfc,
		0x34000, 0x34030,
		0x34100, 0x34168,
		0x34190, 0x341a0,
		0x341a8, 0x341b8,
		0x341c4, 0x341c8,
		0x341d0, 0x341d0,
		0x34200, 0x34320,
		0x34400, 0x344b4,
		0x344c0, 0x3452c,
		0x34540, 0x3461c,
		0x34800, 0x348a0,
		0x348c0, 0x34908,
		0x34910, 0x349b8,
		0x34a00, 0x34a04,
		0x34a0c, 0x34a14,
		0x34a1c, 0x34a2c,
		0x34a44, 0x34a50,
		0x34a74, 0x34a74,
		0x34a7c, 0x34afc,
		0x34b08, 0x34c24,
		0x34d00, 0x34d14,
		0x34d1c, 0x34d3c,
		0x34d44, 0x34d4c,
		0x34d54, 0x34d74,
		0x34d7c, 0x34d7c,
		0x34de0, 0x34de0,
		0x34e00, 0x34ed4,
		0x34f00, 0x34fa4,
		0x34fc0, 0x34fc4,
		0x35000, 0x35004,
		0x35080, 0x350fc,
		0x35208, 0x35220,
		0x3523c, 0x35254,
		0x35300, 0x35300,
		0x35308, 0x3531c,
		0x35338, 0x3533c,
		0x35380, 0x35380,
		0x35388, 0x353a8,
		0x353b4, 0x353b4,
		0x35400, 0x35420,
		0x35438, 0x3543c,
		0x35480, 0x35480,
		0x354a8, 0x354a8,
		0x354b0, 0x354b4,
		0x354c8, 0x354d4,
		0x35a40, 0x35a4c,
		0x35af0, 0x35b20,
		0x35b38, 0x35b3c,
		0x35b80, 0x35b80,
		0x35ba8, 0x35ba8,
		0x35bb0, 0x35bb4,
		0x35bc8, 0x35bd4,
		0x36140, 0x3618c,
		0x361f0, 0x361f4,
		0x36200, 0x36200,
		0x36218, 0x36218,
		0x36400, 0x36400,
		0x36408, 0x3641c,
		0x36618, 0x36620,
		0x36664, 0x36664,
		0x366a8, 0x366a8,
		0x366ec, 0x366ec,
		0x36a00, 0x36abc,
		0x36b00, 0x36b18,
		0x36b20, 0x36b38,
		0x36b40, 0x36b58,
		0x36b60, 0x36b78,
		0x36c00, 0x36c00,
		0x36c08, 0x36c3c,
		0x37000, 0x3702c,
		0x37034, 0x37050,
		0x37058, 0x37058,
		0x37060, 0x3708c,
		0x3709c, 0x370ac,
		0x370c0, 0x370c0,
		0x370c8, 0x370d0,
		0x370d8, 0x370e0,
		0x370ec, 0x3712c,
		0x37134, 0x37150,
		0x37158, 0x37158,
		0x37160, 0x3718c,
		0x3719c, 0x371ac,
		0x371c0, 0x371c0,
		0x371c8, 0x371d0,
		0x371d8, 0x371e0,
		0x371ec, 0x37290,
		0x37298, 0x372c4,
		0x372e4, 0x37390,
		0x37398, 0x373c4,
		0x373e4, 0x3742c,
		0x37434, 0x37450,
		0x37458, 0x37458,
		0x37460, 0x3748c,
		0x3749c, 0x374ac,
		0x374c0, 0x374c0,
		0x374c8, 0x374d0,
		0x374d8, 0x374e0,
		0x374ec, 0x3752c,
		0x37534, 0x37550,
		0x37558, 0x37558,
		0x37560, 0x3758c,
		0x3759c, 0x375ac,
		0x375c0, 0x375c0,
		0x375c8, 0x375d0,
		0x375d8, 0x375e0,
		0x375ec, 0x37690,
		0x37698, 0x376c4,
		0x376e4, 0x37790,
		0x37798, 0x377c4,
		0x377e4, 0x377fc,
		0x37814, 0x37814,
		0x37854, 0x37868,
		0x37880, 0x3788c,
		0x378c0, 0x378d0,
		0x378e8, 0x378ec,
		0x37900, 0x3792c,
		0x37934, 0x37950,
		0x37958, 0x37958,
		0x37960, 0x3798c,
		0x3799c, 0x379ac,
		0x379c0, 0x379c0,
		0x379c8, 0x379d0,
		0x379d8, 0x379e0,
		0x379ec, 0x37a90,
		0x37a98, 0x37ac4,
		0x37ae4, 0x37b10,
		0x37b24, 0x37b28,
		0x37b38, 0x37b50,
		0x37bf0, 0x37c10,
		0x37c24, 0x37c28,
		0x37c38, 0x37c50,
		0x37cf0, 0x37cfc,
		0x40040, 0x40040,
		0x40080, 0x40084,
		0x40100, 0x40100,
		0x40140, 0x401bc,
		0x40200, 0x40214,
		0x40228, 0x40228,
		0x40240, 0x40258,
		0x40280, 0x40280,
		0x40304, 0x40304,
		0x40330, 0x4033c,
		0x41304, 0x413c8,
		0x413d0, 0x413dc,
		0x413f0, 0x413f0,
		0x41400, 0x4140c,
		0x41414, 0x4141c,
		0x41480, 0x414d0,
		0x44000, 0x4407c,
		0x440c0, 0x441ac,
		0x441b4, 0x4427c,
		0x442c0, 0x443ac,
		0x443b4, 0x4447c,
		0x444c0, 0x445ac,
		0x445b4, 0x4467c,
		0x446c0, 0x447ac,
		0x447b4, 0x4487c,
		0x448c0, 0x449ac,
		0x449b4, 0x44a7c,
		0x44ac0, 0x44bac,
		0x44bb4, 0x44c7c,
		0x44cc0, 0x44dac,
		0x44db4, 0x44e7c,
		0x44ec0, 0x44fac,
		0x44fb4, 0x4507c,
		0x450c0, 0x451ac,
		0x451b4, 0x451fc,
		0x45800, 0x45804,
		0x45810, 0x45830,
		0x45840, 0x45860,
		0x45868, 0x45868,
		0x45880, 0x45884,
		0x458a0, 0x458b0,
		0x45a00, 0x45a04,
		0x45a10, 0x45a30,
		0x45a40, 0x45a60,
		0x45a68, 0x45a68,
		0x45a80, 0x45a84,
		0x45aa0, 0x45ab0,
		0x460c0, 0x460e4,
		0x47000, 0x4703c,
		0x47044, 0x4708c,
		0x47200, 0x47250,
		0x47400, 0x47408,
		0x47414, 0x47420,
		0x47600, 0x47618,
		0x47800, 0x47814,
		0x47820, 0x4782c,
		0x50000, 0x50084,
		0x50090, 0x500cc,
		0x50300, 0x50384,
		0x50400, 0x50400,
		0x50800, 0x50884,
		0x50890, 0x508cc,
		0x50b00, 0x50b84,
		0x50c00, 0x50c00,
		0x51000, 0x51020,
		0x51028, 0x510b0,
		0x51300, 0x51324,
	पूर्ण;

	u32 *buf_end = (u32 *)((अक्षर *)buf + buf_size);
	स्थिर अचिन्हित पूर्णांक *reg_ranges;
	पूर्णांक reg_ranges_size, range;
	अचिन्हित पूर्णांक chip_version = CHELSIO_CHIP_VERSION(adap->params.chip);

	/* Select the right set of रेजिस्टर ranges to dump depending on the
	 * adapter chip type.
	 */
	चयन (chip_version) अणु
	हाल CHELSIO_T4:
		reg_ranges = t4_reg_ranges;
		reg_ranges_size = ARRAY_SIZE(t4_reg_ranges);
		अवरोध;

	हाल CHELSIO_T5:
		reg_ranges = t5_reg_ranges;
		reg_ranges_size = ARRAY_SIZE(t5_reg_ranges);
		अवरोध;

	हाल CHELSIO_T6:
		reg_ranges = t6_reg_ranges;
		reg_ranges_size = ARRAY_SIZE(t6_reg_ranges);
		अवरोध;

	शेष:
		dev_err(adap->pdev_dev,
			"Unsupported chip version %d\n", chip_version);
		वापस;
	पूर्ण

	/* Clear the रेजिस्टर buffer and insert the appropriate रेजिस्टर
	 * values selected by the above रेजिस्टर ranges.
	 */
	स_रखो(buf, 0, buf_size);
	क्रम (range = 0; range < reg_ranges_size; range += 2) अणु
		अचिन्हित पूर्णांक reg = reg_ranges[range];
		अचिन्हित पूर्णांक last_reg = reg_ranges[range + 1];
		u32 *bufp = (u32 *)((अक्षर *)buf + reg);

		/* Iterate across the रेजिस्टर range filling in the रेजिस्टर
		 * buffer but करोn't ग_लिखो past the end of the रेजिस्टर buffer.
		 */
		जबतक (reg <= last_reg && bufp < buf_end) अणु
			*bufp++ = t4_पढ़ो_reg(adap, reg);
			reg += माप(u32);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा EEPROM_STAT_ADDR   0x7bfc
#घोषणा VPD_BASE           0x400
#घोषणा VPD_BASE_OLD       0
#घोषणा VPD_LEN            1024

/**
 * t4_eeprom_ptov - translate a physical EEPROM address to भव
 * @phys_addr: the physical EEPROM address
 * @fn: the PCI function number
 * @sz: size of function-specअगरic area
 *
 * Translate a physical EEPROM address to भव.  The first 1K is
 * accessed through भव addresses starting at 31K, the rest is
 * accessed through भव addresses starting at 0.
 *
 * The mapping is as follows:
 * [0..1K) -> [31K..32K)
 * [1K..1K+A) -> [31K-A..31K)
 * [1K+A..ES) -> [0..ES-A-1K)
 *
 * where A = @fn * @sz, and ES = EEPROM size.
 */
पूर्णांक t4_eeprom_ptov(अचिन्हित पूर्णांक phys_addr, अचिन्हित पूर्णांक fn, अचिन्हित पूर्णांक sz)
अणु
	fn *= sz;
	अगर (phys_addr < 1024)
		वापस phys_addr + (31 << 10);
	अगर (phys_addr < 1024 + fn)
		वापस 31744 - fn + phys_addr - 1024;
	अगर (phys_addr < EEPROMSIZE)
		वापस phys_addr - 1024 - fn;
	वापस -EINVAL;
पूर्ण

/**
 *	t4_seeprom_wp - enable/disable EEPROM ग_लिखो protection
 *	@adapter: the adapter
 *	@enable: whether to enable or disable ग_लिखो protection
 *
 *	Enables or disables ग_लिखो protection on the serial EEPROM.
 */
पूर्णांक t4_seeprom_wp(काष्ठा adapter *adapter, bool enable)
अणु
	अचिन्हित पूर्णांक v = enable ? 0xc : 0;
	पूर्णांक ret = pci_ग_लिखो_vpd(adapter->pdev, EEPROM_STAT_ADDR, 4, &v);
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 *	t4_get_raw_vpd_params - पढ़ो VPD parameters from VPD EEPROM
 *	@adapter: adapter to पढ़ो
 *	@p: where to store the parameters
 *
 *	Reads card parameters stored in VPD EEPROM.
 */
पूर्णांक t4_get_raw_vpd_params(काष्ठा adapter *adapter, काष्ठा vpd_params *p)
अणु
	पूर्णांक i, ret = 0, addr;
	पूर्णांक ec, sn, pn, na;
	u8 *vpd, csum, base_val = 0;
	अचिन्हित पूर्णांक vpdr_len, kw_offset, id_len;

	vpd = vदो_स्मृति(VPD_LEN);
	अगर (!vpd)
		वापस -ENOMEM;

	/* Card inक्रमmation normally starts at VPD_BASE but early cards had
	 * it at 0.
	 */
	ret = pci_पढ़ो_vpd(adapter->pdev, VPD_BASE, 1, &base_val);
	अगर (ret < 0)
		जाओ out;

	addr = base_val == PCI_VPD_LRDT_ID_STRING ? VPD_BASE : VPD_BASE_OLD;

	ret = pci_पढ़ो_vpd(adapter->pdev, addr, VPD_LEN, vpd);
	अगर (ret < 0)
		जाओ out;

	अगर (vpd[0] != PCI_VPD_LRDT_ID_STRING) अणु
		dev_err(adapter->pdev_dev, "missing VPD ID string\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	id_len = pci_vpd_lrdt_size(vpd);
	अगर (id_len > ID_LEN)
		id_len = ID_LEN;

	i = pci_vpd_find_tag(vpd, VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	अगर (i < 0) अणु
		dev_err(adapter->pdev_dev, "missing VPD-R section\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	vpdr_len = pci_vpd_lrdt_size(&vpd[i]);
	kw_offset = i + PCI_VPD_LRDT_TAG_SIZE;
	अगर (vpdr_len + kw_offset > VPD_LEN) अणु
		dev_err(adapter->pdev_dev, "bad VPD-R length %u\n", vpdr_len);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

#घोषणा FIND_VPD_KW(var, name) करो अणु \
	var = pci_vpd_find_info_keyword(vpd, kw_offset, vpdr_len, name); \
	अगर (var < 0) अणु \
		dev_err(adapter->pdev_dev, "missing VPD keyword " name "\n"); \
		ret = -EINVAL; \
		जाओ out; \
	पूर्ण \
	var += PCI_VPD_INFO_FLD_HDR_SIZE; \
पूर्ण जबतक (0)

	FIND_VPD_KW(i, "RV");
	क्रम (csum = 0; i >= 0; i--)
		csum += vpd[i];

	अगर (csum) अणु
		dev_err(adapter->pdev_dev,
			"corrupted VPD EEPROM, actual csum %u\n", csum);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	FIND_VPD_KW(ec, "EC");
	FIND_VPD_KW(sn, "SN");
	FIND_VPD_KW(pn, "PN");
	FIND_VPD_KW(na, "NA");
#अघोषित FIND_VPD_KW

	स_नकल(p->id, vpd + PCI_VPD_LRDT_TAG_SIZE, id_len);
	strim(p->id);
	स_नकल(p->ec, vpd + ec, EC_LEN);
	strim(p->ec);
	i = pci_vpd_info_field_size(vpd + sn - PCI_VPD_INFO_FLD_HDR_SIZE);
	स_नकल(p->sn, vpd + sn, min(i, SERNUM_LEN));
	strim(p->sn);
	i = pci_vpd_info_field_size(vpd + pn - PCI_VPD_INFO_FLD_HDR_SIZE);
	स_नकल(p->pn, vpd + pn, min(i, PN_LEN));
	strim(p->pn);
	स_नकल(p->na, vpd + na, min(i, MACADDR_LEN));
	strim((अक्षर *)p->na);

out:
	vमुक्त(vpd);
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 *	t4_get_vpd_params - पढ़ो VPD parameters & retrieve Core Clock
 *	@adapter: adapter to पढ़ो
 *	@p: where to store the parameters
 *
 *	Reads card parameters stored in VPD EEPROM and retrieves the Core
 *	Clock.  This can only be called after a connection to the firmware
 *	is established.
 */
पूर्णांक t4_get_vpd_params(काष्ठा adapter *adapter, काष्ठा vpd_params *p)
अणु
	u32 cclk_param, cclk_val;
	पूर्णांक ret;

	/* Grab the raw VPD parameters.
	 */
	ret = t4_get_raw_vpd_params(adapter, p);
	अगर (ret)
		वापस ret;

	/* Ask firmware क्रम the Core Clock since it knows how to translate the
	 * Reference Clock ('V2') VPD field पूर्णांकo a Core Clock value ...
	 */
	cclk_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		      FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CCLK));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &cclk_param, &cclk_val);

	अगर (ret)
		वापस ret;
	p->cclk = cclk_val;

	वापस 0;
पूर्ण

/**
 *	t4_get_pfres - retrieve VF resource limits
 *	@adapter: the adapter
 *
 *	Retrieves configured resource limits and capabilities क्रम a physical
 *	function.  The results are stored in @adapter->pfres.
 */
पूर्णांक t4_get_pfres(काष्ठा adapter *adapter)
अणु
	काष्ठा pf_resources *pfres = &adapter->params.pfres;
	काष्ठा fw_pfvf_cmd cmd, rpl;
	पूर्णांक v;
	u32 word;

	/* Execute PFVF Read command to get VF resource limits; bail out early
	 * with error on command failure.
	 */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F |
				    FW_PFVF_CMD_PFN_V(adapter->pf) |
				    FW_PFVF_CMD_VFN_V(0));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4_wr_mbox(adapter, adapter->mbox, &cmd, माप(cmd), &rpl);
	अगर (v != FW_SUCCESS)
		वापस v;

	/* Extract PF resource limits and वापस success.
	 */
	word = be32_to_cpu(rpl.niqflपूर्णांक_niq);
	pfres->niqflपूर्णांक = FW_PFVF_CMD_NIQFLINT_G(word);
	pfres->niq = FW_PFVF_CMD_NIQ_G(word);

	word = be32_to_cpu(rpl.type_to_neq);
	pfres->neq = FW_PFVF_CMD_NEQ_G(word);
	pfres->pmask = FW_PFVF_CMD_PMASK_G(word);

	word = be32_to_cpu(rpl.tc_to_nexactf);
	pfres->tc = FW_PFVF_CMD_TC_G(word);
	pfres->nvi = FW_PFVF_CMD_NVI_G(word);
	pfres->nexactf = FW_PFVF_CMD_NEXACTF_G(word);

	word = be32_to_cpu(rpl.r_caps_to_nethctrl);
	pfres->r_caps = FW_PFVF_CMD_R_CAPS_G(word);
	pfres->wx_caps = FW_PFVF_CMD_WX_CAPS_G(word);
	pfres->nethctrl = FW_PFVF_CMD_NETHCTRL_G(word);

	वापस 0;
पूर्ण

/* serial flash and firmware स्थिरants */
क्रमागत अणु
	SF_ATTEMPTS = 10,             /* max retries क्रम SF operations */

	/* flash command opcodes */
	SF_PROG_PAGE    = 2,          /* program page */
	SF_WR_DISABLE   = 4,          /* disable ग_लिखोs */
	SF_RD_STATUS    = 5,          /* पढ़ो status रेजिस्टर */
	SF_WR_ENABLE    = 6,          /* enable ग_लिखोs */
	SF_RD_DATA_FAST = 0xb,        /* पढ़ो flash */
	SF_RD_ID        = 0x9f,       /* पढ़ो ID */
	SF_ERASE_SECTOR = 0xd8,       /* erase sector */
पूर्ण;

/**
 *	sf1_पढ़ो - पढ़ो data from the serial flash
 *	@adapter: the adapter
 *	@byte_cnt: number of bytes to पढ़ो
 *	@cont: whether another operation will be chained
 *	@lock: whether to lock SF क्रम PL access only
 *	@valp: where to store the पढ़ो data
 *
 *	Reads up to 4 bytes of data from the serial flash.  The location of
 *	the पढ़ो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक sf1_पढ़ो(काष्ठा adapter *adapter, अचिन्हित पूर्णांक byte_cnt, पूर्णांक cont,
		    पूर्णांक lock, u32 *valp)
अणु
	पूर्णांक ret;

	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (t4_पढ़ो_reg(adapter, SF_OP_A) & SF_BUSY_F)
		वापस -EBUSY;
	t4_ग_लिखो_reg(adapter, SF_OP_A, SF_LOCK_V(lock) |
		     SF_CONT_V(cont) | BYTECNT_V(byte_cnt - 1));
	ret = t4_रुको_op_करोne(adapter, SF_OP_A, SF_BUSY_F, 0, SF_ATTEMPTS, 5);
	अगर (!ret)
		*valp = t4_पढ़ो_reg(adapter, SF_DATA_A);
	वापस ret;
पूर्ण

/**
 *	sf1_ग_लिखो - ग_लिखो data to the serial flash
 *	@adapter: the adapter
 *	@byte_cnt: number of bytes to ग_लिखो
 *	@cont: whether another operation will be chained
 *	@lock: whether to lock SF क्रम PL access only
 *	@val: value to ग_लिखो
 *
 *	Writes up to 4 bytes of data to the serial flash.  The location of
 *	the ग_लिखो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक sf1_ग_लिखो(काष्ठा adapter *adapter, अचिन्हित पूर्णांक byte_cnt, पूर्णांक cont,
		     पूर्णांक lock, u32 val)
अणु
	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (t4_पढ़ो_reg(adapter, SF_OP_A) & SF_BUSY_F)
		वापस -EBUSY;
	t4_ग_लिखो_reg(adapter, SF_DATA_A, val);
	t4_ग_लिखो_reg(adapter, SF_OP_A, SF_LOCK_V(lock) |
		     SF_CONT_V(cont) | BYTECNT_V(byte_cnt - 1) | OP_V(1));
	वापस t4_रुको_op_करोne(adapter, SF_OP_A, SF_BUSY_F, 0, SF_ATTEMPTS, 5);
पूर्ण

/**
 *	flash_रुको_op - रुको क्रम a flash operation to complete
 *	@adapter: the adapter
 *	@attempts: max number of polls of the status रेजिस्टर
 *	@delay: delay between polls in ms
 *
 *	Wait क्रम a flash operation to complete by polling the status रेजिस्टर.
 */
अटल पूर्णांक flash_रुको_op(काष्ठा adapter *adapter, पूर्णांक attempts, पूर्णांक delay)
अणु
	पूर्णांक ret;
	u32 status;

	जबतक (1) अणु
		अगर ((ret = sf1_ग_लिखो(adapter, 1, 1, 1, SF_RD_STATUS)) != 0 ||
		    (ret = sf1_पढ़ो(adapter, 1, 0, 1, &status)) != 0)
			वापस ret;
		अगर (!(status & 1))
			वापस 0;
		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			msleep(delay);
	पूर्ण
पूर्ण

/**
 *	t4_पढ़ो_flash - पढ़ो words from serial flash
 *	@adapter: the adapter
 *	@addr: the start address क्रम the पढ़ो
 *	@nwords: how many 32-bit words to पढ़ो
 *	@data: where to store the पढ़ो data
 *	@byte_oriented: whether to store data as bytes or as words
 *
 *	Read the specअगरied number of 32-bit words from the serial flash.
 *	If @byte_oriented is set the पढ़ो data is stored as a byte array
 *	(i.e., big-endian), otherwise as 32-bit words in the platक्रमm's
 *	natural endianness.
 */
पूर्णांक t4_पढ़ो_flash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr,
		  अचिन्हित पूर्णांक nwords, u32 *data, पूर्णांक byte_oriented)
अणु
	पूर्णांक ret;

	अगर (addr + nwords * माप(u32) > adapter->params.sf_size || (addr & 3))
		वापस -EINVAL;

	addr = swab32(addr) | SF_RD_DATA_FAST;

	अगर ((ret = sf1_ग_लिखो(adapter, 4, 1, 0, addr)) != 0 ||
	    (ret = sf1_पढ़ो(adapter, 1, 1, 0, data)) != 0)
		वापस ret;

	क्रम ( ; nwords; nwords--, data++) अणु
		ret = sf1_पढ़ो(adapter, 4, nwords > 1, nwords == 1, data);
		अगर (nwords == 1)
			t4_ग_लिखो_reg(adapter, SF_OP_A, 0);    /* unlock SF */
		अगर (ret)
			वापस ret;
		अगर (byte_oriented)
			*data = (__क्रमce __u32)(cpu_to_be32(*data));
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4_ग_लिखो_flash - ग_लिखो up to a page of data to the serial flash
 *	@adapter: the adapter
 *	@addr: the start address to ग_लिखो
 *	@n: length of data to ग_लिखो in bytes
 *	@data: the data to ग_लिखो
 *	@byte_oriented: whether to store data as bytes or as words
 *
 *	Writes up to a page of data (256 bytes) to the serial flash starting
 *	at the given address.  All the data must be written to the same page.
 *	If @byte_oriented is set the ग_लिखो data is stored as byte stream
 *	(i.e. matches what on disk), otherwise in big-endian.
 */
अटल पूर्णांक t4_ग_लिखो_flash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr,
			  अचिन्हित पूर्णांक n, स्थिर u8 *data, bool byte_oriented)
अणु
	अचिन्हित पूर्णांक i, c, left, val, offset = addr & 0xff;
	u32 buf[64];
	पूर्णांक ret;

	अगर (addr >= adapter->params.sf_size || offset + n > SF_PAGE_SIZE)
		वापस -EINVAL;

	val = swab32(addr) | SF_PROG_PAGE;

	अगर ((ret = sf1_ग_लिखो(adapter, 1, 0, 1, SF_WR_ENABLE)) != 0 ||
	    (ret = sf1_ग_लिखो(adapter, 4, 1, 1, val)) != 0)
		जाओ unlock;

	क्रम (left = n; left; left -= c, data += c) अणु
		c = min(left, 4U);
		क्रम (val = 0, i = 0; i < c; ++i) अणु
			अगर (byte_oriented)
				val = (val << 8) + data[i];
			अन्यथा
				val = (val << 8) + data[c - i - 1];
		पूर्ण

		ret = sf1_ग_लिखो(adapter, c, c != left, 1, val);
		अगर (ret)
			जाओ unlock;
	पूर्ण
	ret = flash_रुको_op(adapter, 8, 1);
	अगर (ret)
		जाओ unlock;

	t4_ग_लिखो_reg(adapter, SF_OP_A, 0);    /* unlock SF */

	/* Read the page to verअगरy the ग_लिखो succeeded */
	ret = t4_पढ़ो_flash(adapter, addr & ~0xff, ARRAY_SIZE(buf), buf,
			    byte_oriented);
	अगर (ret)
		वापस ret;

	अगर (स_भेद(data - n, (u8 *)buf + offset, n)) अणु
		dev_err(adapter->pdev_dev,
			"failed to correctly write the flash page at %#x\n",
			addr);
		वापस -EIO;
	पूर्ण
	वापस 0;

unlock:
	t4_ग_लिखो_reg(adapter, SF_OP_A, 0);    /* unlock SF */
	वापस ret;
पूर्ण

/**
 *	t4_get_fw_version - पढ़ो the firmware version
 *	@adapter: the adapter
 *	@vers: where to place the version
 *
 *	Reads the FW version from flash.
 */
पूर्णांक t4_get_fw_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	वापस t4_पढ़ो_flash(adapter, FLASH_FW_START +
			     दुरत्व(काष्ठा fw_hdr, fw_ver), 1,
			     vers, 0);
पूर्ण

/**
 *	t4_get_bs_version - पढ़ो the firmware bootstrap version
 *	@adapter: the adapter
 *	@vers: where to place the version
 *
 *	Reads the FW Bootstrap version from flash.
 */
पूर्णांक t4_get_bs_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	वापस t4_पढ़ो_flash(adapter, FLASH_FWBOOTSTRAP_START +
			     दुरत्व(काष्ठा fw_hdr, fw_ver), 1,
			     vers, 0);
पूर्ण

/**
 *	t4_get_tp_version - पढ़ो the TP microcode version
 *	@adapter: the adapter
 *	@vers: where to place the version
 *
 *	Reads the TP microcode version from flash.
 */
पूर्णांक t4_get_tp_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	वापस t4_पढ़ो_flash(adapter, FLASH_FW_START +
			     दुरत्व(काष्ठा fw_hdr, tp_microcode_ver),
			     1, vers, 0);
पूर्ण

/**
 *	t4_get_exprom_version - वापस the Expansion ROM version (अगर any)
 *	@adap: the adapter
 *	@vers: where to place the version
 *
 *	Reads the Expansion ROM header from FLASH and वापसs the version
 *	number (अगर present) through the @vers वापस value poपूर्णांकer.  We वापस
 *	this in the Firmware Version Format since it's convenient.  Return
 *	0 on success, -ENOENT अगर no Expansion ROM is present.
 */
पूर्णांक t4_get_exprom_version(काष्ठा adapter *adap, u32 *vers)
अणु
	काष्ठा exprom_header अणु
		अचिन्हित अक्षर hdr_arr[16];	/* must start with 0x55aa */
		अचिन्हित अक्षर hdr_ver[4];	/* Expansion ROM version */
	पूर्ण *hdr;
	u32 exprom_header_buf[DIV_ROUND_UP(माप(काष्ठा exprom_header),
					   माप(u32))];
	पूर्णांक ret;

	ret = t4_पढ़ो_flash(adap, FLASH_EXP_ROM_START,
			    ARRAY_SIZE(exprom_header_buf), exprom_header_buf,
			    0);
	अगर (ret)
		वापस ret;

	hdr = (काष्ठा exprom_header *)exprom_header_buf;
	अगर (hdr->hdr_arr[0] != 0x55 || hdr->hdr_arr[1] != 0xaa)
		वापस -ENOENT;

	*vers = (FW_HDR_FW_VER_MAJOR_V(hdr->hdr_ver[0]) |
		 FW_HDR_FW_VER_MINOR_V(hdr->hdr_ver[1]) |
		 FW_HDR_FW_VER_MICRO_V(hdr->hdr_ver[2]) |
		 FW_HDR_FW_VER_BUILD_V(hdr->hdr_ver[3]));
	वापस 0;
पूर्ण

/**
 *      t4_get_vpd_version - वापस the VPD version
 *      @adapter: the adapter
 *      @vers: where to place the version
 *
 *      Reads the VPD via the Firmware पूर्णांकerface (thus this can only be called
 *      once we're पढ़ोy to issue Firmware commands).  The क्रमmat of the
 *      VPD version is adapter specअगरic.  Returns 0 on success, an error on
 *      failure.
 *
 *      Note that early versions of the Firmware didn't include the ability
 *      to retrieve the VPD version, so we zero-out the वापस-value parameter
 *      in that हाल to aव्योम leaving it with garbage in it.
 *
 *      Also note that the Firmware will वापस its cached copy of the VPD
 *      Revision ID, not the actual Revision ID as written in the Serial
 *      EEPROM.  This is only an issue अगर a new VPD has been written and the
 *      Firmware/Chip haven't yet gone through a RESET sequence.  So it's best
 *      to defer calling this routine till after a FW_RESET_CMD has been issued
 *      अगर the Host Driver will be perक्रमming a full adapter initialization.
 */
पूर्णांक t4_get_vpd_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	u32 vpdrev_param;
	पूर्णांक ret;

	vpdrev_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_VPDREV));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &vpdrev_param, vers);
	अगर (ret)
		*vers = 0;
	वापस ret;
पूर्ण

/**
 *      t4_get_scfg_version - वापस the Serial Configuration version
 *      @adapter: the adapter
 *      @vers: where to place the version
 *
 *      Reads the Serial Configuration Version via the Firmware पूर्णांकerface
 *      (thus this can only be called once we're पढ़ोy to issue Firmware
 *      commands).  The क्रमmat of the Serial Configuration version is
 *      adapter specअगरic.  Returns 0 on success, an error on failure.
 *
 *      Note that early versions of the Firmware didn't include the ability
 *      to retrieve the Serial Configuration version, so we zero-out the
 *      वापस-value parameter in that हाल to aव्योम leaving it with
 *      garbage in it.
 *
 *      Also note that the Firmware will वापस its cached copy of the Serial
 *      Initialization Revision ID, not the actual Revision ID as written in
 *      the Serial EEPROM.  This is only an issue अगर a new VPD has been written
 *      and the Firmware/Chip haven't yet gone through a RESET sequence.  So
 *      it's best to defer calling this routine till after a FW_RESET_CMD has
 *      been issued अगर the Host Driver will be perक्रमming a full adapter
 *      initialization.
 */
पूर्णांक t4_get_scfg_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	u32 scfgrev_param;
	पूर्णांक ret;

	scfgrev_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_SCFGREV));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &scfgrev_param, vers);
	अगर (ret)
		*vers = 0;
	वापस ret;
पूर्ण

/**
 *      t4_get_version_info - extract various chip/firmware version inक्रमmation
 *      @adapter: the adapter
 *
 *      Reads various chip/firmware version numbers and stores them पूर्णांकo the
 *      adapter Adapter Parameters काष्ठाure.  If any of the efक्रमts fails
 *      the first failure will be वापसed, but all of the version numbers
 *      will be पढ़ो.
 */
पूर्णांक t4_get_version_info(काष्ठा adapter *adapter)
अणु
	पूर्णांक ret = 0;

	#घोषणा FIRST_RET(__getvinfo) \
	करो अणु \
		पूर्णांक __ret = __getvinfo; \
		अगर (__ret && !ret) \
			ret = __ret; \
	पूर्ण जबतक (0)

	FIRST_RET(t4_get_fw_version(adapter, &adapter->params.fw_vers));
	FIRST_RET(t4_get_bs_version(adapter, &adapter->params.bs_vers));
	FIRST_RET(t4_get_tp_version(adapter, &adapter->params.tp_vers));
	FIRST_RET(t4_get_exprom_version(adapter, &adapter->params.er_vers));
	FIRST_RET(t4_get_scfg_version(adapter, &adapter->params.scfg_vers));
	FIRST_RET(t4_get_vpd_version(adapter, &adapter->params.vpd_vers));

	#अघोषित FIRST_RET
	वापस ret;
पूर्ण

/**
 *      t4_dump_version_info - dump all of the adapter configuration IDs
 *      @adapter: the adapter
 *
 *      Dumps all of the various bits of adapter configuration version/revision
 *      IDs inक्रमmation.  This is typically called at some poपूर्णांक after
 *      t4_get_version_info() has been called.
 */
व्योम t4_dump_version_info(काष्ठा adapter *adapter)
अणु
	/* Device inक्रमmation */
	dev_info(adapter->pdev_dev, "Chelsio %s rev %d\n",
		 adapter->params.vpd.id,
		 CHELSIO_CHIP_RELEASE(adapter->params.chip));
	dev_info(adapter->pdev_dev, "S/N: %s, P/N: %s\n",
		 adapter->params.vpd.sn, adapter->params.vpd.pn);

	/* Firmware Version */
	अगर (!adapter->params.fw_vers)
		dev_warn(adapter->pdev_dev, "No firmware loaded\n");
	अन्यथा
		dev_info(adapter->pdev_dev, "Firmware version: %u.%u.%u.%u\n",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.fw_vers));

	/* Bootstrap Firmware Version. (Some adapters करोn't have Bootstrap
	 * Firmware, so dev_info() is more appropriate here.)
	 */
	अगर (!adapter->params.bs_vers)
		dev_info(adapter->pdev_dev, "No bootstrap loaded\n");
	अन्यथा
		dev_info(adapter->pdev_dev, "Bootstrap version: %u.%u.%u.%u\n",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.bs_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.bs_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.bs_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.bs_vers));

	/* TP Microcode Version */
	अगर (!adapter->params.tp_vers)
		dev_warn(adapter->pdev_dev, "No TP Microcode loaded\n");
	अन्यथा
		dev_info(adapter->pdev_dev,
			 "TP Microcode version: %u.%u.%u.%u\n",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.tp_vers));

	/* Expansion ROM version */
	अगर (!adapter->params.er_vers)
		dev_info(adapter->pdev_dev, "No Expansion ROM loaded\n");
	अन्यथा
		dev_info(adapter->pdev_dev,
			 "Expansion ROM version: %u.%u.%u.%u\n",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.er_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.er_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.er_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.er_vers));

	/* Serial Configuration version */
	dev_info(adapter->pdev_dev, "Serial Configuration version: %#x\n",
		 adapter->params.scfg_vers);

	/* VPD Version */
	dev_info(adapter->pdev_dev, "VPD version: %#x\n",
		 adapter->params.vpd_vers);
पूर्ण

/**
 *	t4_check_fw_version - check अगर the FW is supported with this driver
 *	@adap: the adapter
 *
 *	Checks अगर an adapter's FW is compatible with the driver.  Returns 0
 *	अगर there's exact match, a negative error अगर the version could not be
 *	पढ़ो or there's a major version mismatch
 */
पूर्णांक t4_check_fw_version(काष्ठा adapter *adap)
अणु
	पूर्णांक i, ret, major, minor, micro;
	पूर्णांक exp_major, exp_minor, exp_micro;
	अचिन्हित पूर्णांक chip_version = CHELSIO_CHIP_VERSION(adap->params.chip);

	ret = t4_get_fw_version(adap, &adap->params.fw_vers);
	/* Try multiple बार beक्रमe वापसing error */
	क्रम (i = 0; (ret == -EBUSY || ret == -EAGAIN) && i < 3; i++)
		ret = t4_get_fw_version(adap, &adap->params.fw_vers);

	अगर (ret)
		वापस ret;

	major = FW_HDR_FW_VER_MAJOR_G(adap->params.fw_vers);
	minor = FW_HDR_FW_VER_MINOR_G(adap->params.fw_vers);
	micro = FW_HDR_FW_VER_MICRO_G(adap->params.fw_vers);

	चयन (chip_version) अणु
	हाल CHELSIO_T4:
		exp_major = T4FW_MIN_VERSION_MAJOR;
		exp_minor = T4FW_MIN_VERSION_MINOR;
		exp_micro = T4FW_MIN_VERSION_MICRO;
		अवरोध;
	हाल CHELSIO_T5:
		exp_major = T5FW_MIN_VERSION_MAJOR;
		exp_minor = T5FW_MIN_VERSION_MINOR;
		exp_micro = T5FW_MIN_VERSION_MICRO;
		अवरोध;
	हाल CHELSIO_T6:
		exp_major = T6FW_MIN_VERSION_MAJOR;
		exp_minor = T6FW_MIN_VERSION_MINOR;
		exp_micro = T6FW_MIN_VERSION_MICRO;
		अवरोध;
	शेष:
		dev_err(adap->pdev_dev, "Unsupported chip type, %x\n",
			adap->chip);
		वापस -EINVAL;
	पूर्ण

	अगर (major < exp_major || (major == exp_major && minor < exp_minor) ||
	    (major == exp_major && minor == exp_minor && micro < exp_micro)) अणु
		dev_err(adap->pdev_dev,
			"Card has firmware version %u.%u.%u, minimum "
			"supported firmware is %u.%u.%u.\n", major, minor,
			micro, exp_major, exp_minor, exp_micro);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/* Is the given firmware API compatible with the one the driver was compiled
 * with?
 */
अटल पूर्णांक fw_compatible(स्थिर काष्ठा fw_hdr *hdr1, स्थिर काष्ठा fw_hdr *hdr2)
अणु

	/* लघु circuit अगर it's the exact same firmware version */
	अगर (hdr1->chip == hdr2->chip && hdr1->fw_ver == hdr2->fw_ver)
		वापस 1;

#घोषणा SAME_INTF(x) (hdr1->पूर्णांकfver_##x == hdr2->पूर्णांकfver_##x)
	अगर (hdr1->chip == hdr2->chip && SAME_INTF(nic) && SAME_INTF(vnic) &&
	    SAME_INTF(ri) && SAME_INTF(iscsi) && SAME_INTF(fcoe))
		वापस 1;
#अघोषित SAME_INTF

	वापस 0;
पूर्ण

/* The firmware in the fileप्रणाली is usable, but should it be installed?
 * This routine explains itself in detail अगर it indicates the fileप्रणाली
 * firmware should be installed.
 */
अटल पूर्णांक should_install_fs_fw(काष्ठा adapter *adap, पूर्णांक card_fw_usable,
				पूर्णांक k, पूर्णांक c)
अणु
	स्थिर अक्षर *reason;

	अगर (!card_fw_usable) अणु
		reason = "incompatible or unusable";
		जाओ install;
	पूर्ण

	अगर (k > c) अणु
		reason = "older than the version supported with this driver";
		जाओ install;
	पूर्ण

	वापस 0;

install:
	dev_err(adap->pdev_dev, "firmware on card (%u.%u.%u.%u) is %s, "
		"installing firmware %u.%u.%u.%u on card.\n",
		FW_HDR_FW_VER_MAJOR_G(c), FW_HDR_FW_VER_MINOR_G(c),
		FW_HDR_FW_VER_MICRO_G(c), FW_HDR_FW_VER_BUILD_G(c), reason,
		FW_HDR_FW_VER_MAJOR_G(k), FW_HDR_FW_VER_MINOR_G(k),
		FW_HDR_FW_VER_MICRO_G(k), FW_HDR_FW_VER_BUILD_G(k));

	वापस 1;
पूर्ण

पूर्णांक t4_prep_fw(काष्ठा adapter *adap, काष्ठा fw_info *fw_info,
	       स्थिर u8 *fw_data, अचिन्हित पूर्णांक fw_size,
	       काष्ठा fw_hdr *card_fw, क्रमागत dev_state state,
	       पूर्णांक *reset)
अणु
	पूर्णांक ret, card_fw_usable, fs_fw_usable;
	स्थिर काष्ठा fw_hdr *fs_fw;
	स्थिर काष्ठा fw_hdr *drv_fw;

	drv_fw = &fw_info->fw_hdr;

	/* Read the header of the firmware on the card */
	ret = t4_पढ़ो_flash(adap, FLASH_FW_START,
			    माप(*card_fw) / माप(uपूर्णांक32_t),
			    (uपूर्णांक32_t *)card_fw, 1);
	अगर (ret == 0) अणु
		card_fw_usable = fw_compatible(drv_fw, (स्थिर व्योम *)card_fw);
	पूर्ण अन्यथा अणु
		dev_err(adap->pdev_dev,
			"Unable to read card's firmware header: %d\n", ret);
		card_fw_usable = 0;
	पूर्ण

	अगर (fw_data != शून्य) अणु
		fs_fw = (स्थिर व्योम *)fw_data;
		fs_fw_usable = fw_compatible(drv_fw, fs_fw);
	पूर्ण अन्यथा अणु
		fs_fw = शून्य;
		fs_fw_usable = 0;
	पूर्ण

	अगर (card_fw_usable && card_fw->fw_ver == drv_fw->fw_ver &&
	    (!fs_fw_usable || fs_fw->fw_ver == drv_fw->fw_ver)) अणु
		/* Common हाल: the firmware on the card is an exact match and
		 * the fileप्रणाली one is an exact match too, or the fileप्रणाली
		 * one is असलent/incompatible.
		 */
	पूर्ण अन्यथा अगर (fs_fw_usable && state == DEV_STATE_UNINIT &&
		   should_install_fs_fw(adap, card_fw_usable,
					be32_to_cpu(fs_fw->fw_ver),
					be32_to_cpu(card_fw->fw_ver))) अणु
		ret = t4_fw_upgrade(adap, adap->mbox, fw_data,
				    fw_size, 0);
		अगर (ret != 0) अणु
			dev_err(adap->pdev_dev,
				"failed to install firmware: %d\n", ret);
			जाओ bye;
		पूर्ण

		/* Installed successfully, update the cached header too. */
		*card_fw = *fs_fw;
		card_fw_usable = 1;
		*reset = 0;	/* alपढ़ोy reset as part of load_fw */
	पूर्ण

	अगर (!card_fw_usable) अणु
		uपूर्णांक32_t d, c, k;

		d = be32_to_cpu(drv_fw->fw_ver);
		c = be32_to_cpu(card_fw->fw_ver);
		k = fs_fw ? be32_to_cpu(fs_fw->fw_ver) : 0;

		dev_err(adap->pdev_dev, "Cannot find a usable firmware: "
			"chip state %d, "
			"driver compiled with %d.%d.%d.%d, "
			"card has %d.%d.%d.%d, filesystem has %d.%d.%d.%d\n",
			state,
			FW_HDR_FW_VER_MAJOR_G(d), FW_HDR_FW_VER_MINOR_G(d),
			FW_HDR_FW_VER_MICRO_G(d), FW_HDR_FW_VER_BUILD_G(d),
			FW_HDR_FW_VER_MAJOR_G(c), FW_HDR_FW_VER_MINOR_G(c),
			FW_HDR_FW_VER_MICRO_G(c), FW_HDR_FW_VER_BUILD_G(c),
			FW_HDR_FW_VER_MAJOR_G(k), FW_HDR_FW_VER_MINOR_G(k),
			FW_HDR_FW_VER_MICRO_G(k), FW_HDR_FW_VER_BUILD_G(k));
		ret = -EINVAL;
		जाओ bye;
	पूर्ण

	/* We're using whatever's on the card and it's known to be good. */
	adap->params.fw_vers = be32_to_cpu(card_fw->fw_ver);
	adap->params.tp_vers = be32_to_cpu(card_fw->tp_microcode_ver);

bye:
	वापस ret;
पूर्ण

/**
 *	t4_flash_erase_sectors - erase a range of flash sectors
 *	@adapter: the adapter
 *	@start: the first sector to erase
 *	@end: the last sector to erase
 *
 *	Erases the sectors in the given inclusive range.
 */
अटल पूर्णांक t4_flash_erase_sectors(काष्ठा adapter *adapter, पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक ret = 0;

	अगर (end >= adapter->params.sf_nsec)
		वापस -EINVAL;

	जबतक (start <= end) अणु
		अगर ((ret = sf1_ग_लिखो(adapter, 1, 0, 1, SF_WR_ENABLE)) != 0 ||
		    (ret = sf1_ग_लिखो(adapter, 4, 0, 1,
				     SF_ERASE_SECTOR | (start << 8))) != 0 ||
		    (ret = flash_रुको_op(adapter, 14, 500)) != 0) अणु
			dev_err(adapter->pdev_dev,
				"erase of flash sector %d failed, error %d\n",
				start, ret);
			अवरोध;
		पूर्ण
		start++;
	पूर्ण
	t4_ग_लिखो_reg(adapter, SF_OP_A, 0);    /* unlock SF */
	वापस ret;
पूर्ण

/**
 *	t4_flash_cfg_addr - वापस the address of the flash configuration file
 *	@adapter: the adapter
 *
 *	Return the address within the flash where the Firmware Configuration
 *	File is stored.
 */
अचिन्हित पूर्णांक t4_flash_cfg_addr(काष्ठा adapter *adapter)
अणु
	अगर (adapter->params.sf_size == 0x100000)
		वापस FLASH_FPGA_CFG_START;
	अन्यथा
		वापस FLASH_CFG_START;
पूर्ण

/* Return TRUE अगर the specअगरied firmware matches the adapter.  I.e. T4
 * firmware क्रम T4 adapters, T5 firmware क्रम T5 adapters, etc.  We go ahead
 * and emit an error message क्रम mismatched firmware to save our caller the
 * efक्रमt ...
 */
अटल bool t4_fw_matches_chip(स्थिर काष्ठा adapter *adap,
			       स्थिर काष्ठा fw_hdr *hdr)
अणु
	/* The expression below will वापस FALSE क्रम any unsupported adapter
	 * which will keep us "honest" in the future ...
	 */
	अगर ((is_t4(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T4) ||
	    (is_t5(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T5) ||
	    (is_t6(adap->params.chip) && hdr->chip == FW_HDR_CHIP_T6))
		वापस true;

	dev_err(adap->pdev_dev,
		"FW image (%d) is not suitable for this adapter (%d)\n",
		hdr->chip, CHELSIO_CHIP_VERSION(adap->params.chip));
	वापस false;
पूर्ण

/**
 *	t4_load_fw - करोwnload firmware
 *	@adap: the adapter
 *	@fw_data: the firmware image to ग_लिखो
 *	@size: image size
 *
 *	Write the supplied firmware image to the card's serial flash.
 */
पूर्णांक t4_load_fw(काष्ठा adapter *adap, स्थिर u8 *fw_data, अचिन्हित पूर्णांक size)
अणु
	u32 csum;
	पूर्णांक ret, addr;
	अचिन्हित पूर्णांक i;
	u8 first_page[SF_PAGE_SIZE];
	स्थिर __be32 *p = (स्थिर __be32 *)fw_data;
	स्थिर काष्ठा fw_hdr *hdr = (स्थिर काष्ठा fw_hdr *)fw_data;
	अचिन्हित पूर्णांक sf_sec_size = adap->params.sf_size / adap->params.sf_nsec;
	अचिन्हित पूर्णांक fw_start_sec = FLASH_FW_START_SEC;
	अचिन्हित पूर्णांक fw_size = FLASH_FW_MAX_SIZE;
	अचिन्हित पूर्णांक fw_start = FLASH_FW_START;

	अगर (!size) अणु
		dev_err(adap->pdev_dev, "FW image has no data\n");
		वापस -EINVAL;
	पूर्ण
	अगर (size & 511) अणु
		dev_err(adap->pdev_dev,
			"FW image size not multiple of 512 bytes\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((अचिन्हित पूर्णांक)be16_to_cpu(hdr->len512) * 512 != size) अणु
		dev_err(adap->pdev_dev,
			"FW image size differs from size in FW header\n");
		वापस -EINVAL;
	पूर्ण
	अगर (size > fw_size) अणु
		dev_err(adap->pdev_dev, "FW image too large, max is %u bytes\n",
			fw_size);
		वापस -EFBIG;
	पूर्ण
	अगर (!t4_fw_matches_chip(adap, hdr))
		वापस -EINVAL;

	क्रम (csum = 0, i = 0; i < size / माप(csum); i++)
		csum += be32_to_cpu(p[i]);

	अगर (csum != 0xffffffff) अणु
		dev_err(adap->pdev_dev,
			"corrupted firmware image, checksum %#x\n", csum);
		वापस -EINVAL;
	पूर्ण

	i = DIV_ROUND_UP(size, sf_sec_size);        /* # of sectors spanned */
	ret = t4_flash_erase_sectors(adap, fw_start_sec, fw_start_sec + i - 1);
	अगर (ret)
		जाओ out;

	/*
	 * We ग_लिखो the correct version at the end so the driver can see a bad
	 * version अगर the FW ग_लिखो fails.  Start by writing a copy of the
	 * first page with a bad version.
	 */
	स_नकल(first_page, fw_data, SF_PAGE_SIZE);
	((काष्ठा fw_hdr *)first_page)->fw_ver = cpu_to_be32(0xffffffff);
	ret = t4_ग_लिखो_flash(adap, fw_start, SF_PAGE_SIZE, first_page, true);
	अगर (ret)
		जाओ out;

	addr = fw_start;
	क्रम (size -= SF_PAGE_SIZE; size; size -= SF_PAGE_SIZE) अणु
		addr += SF_PAGE_SIZE;
		fw_data += SF_PAGE_SIZE;
		ret = t4_ग_लिखो_flash(adap, addr, SF_PAGE_SIZE, fw_data, true);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = t4_ग_लिखो_flash(adap, fw_start + दुरत्व(काष्ठा fw_hdr, fw_ver),
			     माप(hdr->fw_ver), (स्थिर u8 *)&hdr->fw_ver,
			     true);
out:
	अगर (ret)
		dev_err(adap->pdev_dev, "firmware download failed, error %d\n",
			ret);
	अन्यथा
		ret = t4_get_fw_version(adap, &adap->params.fw_vers);
	वापस ret;
पूर्ण

/**
 *	t4_phy_fw_ver - वापस current PHY firmware version
 *	@adap: the adapter
 *	@phy_fw_ver: वापस value buffer क्रम PHY firmware version
 *
 *	Returns the current version of बाह्यal PHY firmware on the
 *	adapter.
 */
पूर्णांक t4_phy_fw_ver(काष्ठा adapter *adap, पूर्णांक *phy_fw_ver)
अणु
	u32 param, val;
	पूर्णांक ret;

	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PHYFW) |
		 FW_PARAMS_PARAM_Y_V(adap->params.portvec) |
		 FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_PHYFW_VERSION));
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
			      &param, &val);
	अगर (ret)
		वापस ret;
	*phy_fw_ver = val;
	वापस 0;
पूर्ण

/**
 *	t4_load_phy_fw - करोwnload port PHY firmware
 *	@adap: the adapter
 *	@win: the PCI-E Memory Winकरोw index to use क्रम t4_memory_rw()
 *	@phy_fw_version: function to check PHY firmware versions
 *	@phy_fw_data: the PHY firmware image to ग_लिखो
 *	@phy_fw_size: image size
 *
 *	Transfer the specअगरied PHY firmware to the adapter.  If a non-शून्य
 *	@phy_fw_version is supplied, then it will be used to determine अगर
 *	it's necessary to perक्रमm the transfer by comparing the version
 *	of any existing adapter PHY firmware with that of the passed in
 *	PHY firmware image.
 *
 *	A negative error number will be वापसed अगर an error occurs.  If
 *	version number support is available and there's no need to upgrade
 *	the firmware, 0 will be वापसed.  If firmware is successfully
 *	transferred to the adapter, 1 will be वापसed.
 *
 *	NOTE: some adapters only have local RAM to store the PHY firmware.  As
 *	a result, a RESET of the adapter would cause that RAM to lose its
 *	contents.  Thus, loading PHY firmware on such adapters must happen
 *	after any FW_RESET_CMDs ...
 */
पूर्णांक t4_load_phy_fw(काष्ठा adapter *adap, पूर्णांक win,
		   पूर्णांक (*phy_fw_version)(स्थिर u8 *, माप_प्रकार),
		   स्थिर u8 *phy_fw_data, माप_प्रकार phy_fw_size)
अणु
	पूर्णांक cur_phy_fw_ver = 0, new_phy_fw_vers = 0;
	अचिन्हित दीर्घ mtype = 0, maddr = 0;
	u32 param, val;
	पूर्णांक ret;

	/* If we have version number support, then check to see अगर the adapter
	 * alपढ़ोy has up-to-date PHY firmware loaded.
	 */
	अगर (phy_fw_version) अणु
		new_phy_fw_vers = phy_fw_version(phy_fw_data, phy_fw_size);
		ret = t4_phy_fw_ver(adap, &cur_phy_fw_ver);
		अगर (ret < 0)
			वापस ret;

		अगर (cur_phy_fw_ver >= new_phy_fw_vers) अणु
			CH_WARN(adap, "PHY Firmware already up-to-date, "
				"version %#x\n", cur_phy_fw_ver);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Ask the firmware where it wants us to copy the PHY firmware image.
	 * The size of the file requires a special version of the READ command
	 * which will pass the file size via the values field in PARAMS_CMD and
	 * retrieve the वापस value from firmware and place it in the same
	 * buffer values
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PHYFW) |
		 FW_PARAMS_PARAM_Y_V(adap->params.portvec) |
		 FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD));
	val = phy_fw_size;
	ret = t4_query_params_rw(adap, adap->mbox, adap->pf, 0, 1,
				 &param, &val, 1, true);
	अगर (ret < 0)
		वापस ret;
	mtype = val >> 8;
	maddr = (val & 0xff) << 16;

	/* Copy the supplied PHY Firmware image to the adapter memory location
	 * allocated by the adapter firmware.
	 */
	spin_lock_bh(&adap->win0_lock);
	ret = t4_memory_rw(adap, win, mtype, maddr,
			   phy_fw_size, (__be32 *)phy_fw_data,
			   T4_MEMORY_WRITE);
	spin_unlock_bh(&adap->win0_lock);
	अगर (ret)
		वापस ret;

	/* Tell the firmware that the PHY firmware image has been written to
	 * RAM and it can now start copying it over to the PHYs.  The chip
	 * firmware will RESET the affected PHYs as part of this operation
	 * leaving them running the new PHY firmware image.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PHYFW) |
		 FW_PARAMS_PARAM_Y_V(adap->params.portvec) |
		 FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD));
	ret = t4_set_params_समयout(adap, adap->mbox, adap->pf, 0, 1,
				    &param, &val, 30000);

	/* If we have version number support, then check to see that the new
	 * firmware got loaded properly.
	 */
	अगर (phy_fw_version) अणु
		ret = t4_phy_fw_ver(adap, &cur_phy_fw_ver);
		अगर (ret < 0)
			वापस ret;

		अगर (cur_phy_fw_ver != new_phy_fw_vers) अणु
			CH_WARN(adap, "PHY Firmware did not update: "
				"version on adapter %#x, "
				"version flashed %#x\n",
				cur_phy_fw_ver, new_phy_fw_vers);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/**
 *	t4_fwcache - firmware cache operation
 *	@adap: the adapter
 *	@op  : the operation (flush or flush and invalidate)
 */
पूर्णांक t4_fwcache(काष्ठा adapter *adap, क्रमागत fw_params_param_dev_fwcache op)
अणु
	काष्ठा fw_params_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn =
		cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
			    FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
			    FW_PARAMS_CMD_PFN_V(adap->pf) |
			    FW_PARAMS_CMD_VFN_V(0));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.param[0].mnem =
		cpu_to_be32(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_FWCACHE));
	c.param[0].val = cpu_to_be32(op);

	वापस t4_wr_mbox(adap, adap->mbox, &c, माप(c), शून्य);
पूर्ण

व्योम t4_cim_पढ़ो_pअगर_la(काष्ठा adapter *adap, u32 *pअगर_req, u32 *pअगर_rsp,
			अचिन्हित पूर्णांक *pअगर_req_wrptr,
			अचिन्हित पूर्णांक *pअगर_rsp_wrptr)
अणु
	पूर्णांक i, j;
	u32 cfg, val, req, rsp;

	cfg = t4_पढ़ो_reg(adap, CIM_DEBUGCFG_A);
	अगर (cfg & LADBGEN_F)
		t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, cfg ^ LADBGEN_F);

	val = t4_पढ़ो_reg(adap, CIM_DEBUGSTS_A);
	req = POLADBGWRPTR_G(val);
	rsp = PILADBGWRPTR_G(val);
	अगर (pअगर_req_wrptr)
		*pअगर_req_wrptr = req;
	अगर (pअगर_rsp_wrptr)
		*pअगर_rsp_wrptr = rsp;

	क्रम (i = 0; i < CIM_PIFLA_SIZE; i++) अणु
		क्रम (j = 0; j < 6; j++) अणु
			t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, POLADBGRDPTR_V(req) |
				     PILADBGRDPTR_V(rsp));
			*pअगर_req++ = t4_पढ़ो_reg(adap, CIM_PO_LA_DEBUGDATA_A);
			*pअगर_rsp++ = t4_पढ़ो_reg(adap, CIM_PI_LA_DEBUGDATA_A);
			req++;
			rsp++;
		पूर्ण
		req = (req + 2) & POLADBGRDPTR_M;
		rsp = (rsp + 2) & PILADBGRDPTR_M;
	पूर्ण
	t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, cfg);
पूर्ण

व्योम t4_cim_पढ़ो_ma_la(काष्ठा adapter *adap, u32 *ma_req, u32 *ma_rsp)
अणु
	u32 cfg;
	पूर्णांक i, j, idx;

	cfg = t4_पढ़ो_reg(adap, CIM_DEBUGCFG_A);
	अगर (cfg & LADBGEN_F)
		t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, cfg ^ LADBGEN_F);

	क्रम (i = 0; i < CIM_MALA_SIZE; i++) अणु
		क्रम (j = 0; j < 5; j++) अणु
			idx = 8 * i + j;
			t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, POLADBGRDPTR_V(idx) |
				     PILADBGRDPTR_V(idx));
			*ma_req++ = t4_पढ़ो_reg(adap, CIM_PO_LA_MADEBUGDATA_A);
			*ma_rsp++ = t4_पढ़ो_reg(adap, CIM_PI_LA_MADEBUGDATA_A);
		पूर्ण
	पूर्ण
	t4_ग_लिखो_reg(adap, CIM_DEBUGCFG_A, cfg);
पूर्ण

व्योम t4_ulprx_पढ़ो_la(काष्ठा adapter *adap, u32 *la_buf)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < 8; i++) अणु
		u32 *p = la_buf + i;

		t4_ग_लिखो_reg(adap, ULP_RX_LA_CTL_A, i);
		j = t4_पढ़ो_reg(adap, ULP_RX_LA_WRPTR_A);
		t4_ग_लिखो_reg(adap, ULP_RX_LA_RDPTR_A, j);
		क्रम (j = 0; j < ULPRX_LA_SIZE; j++, p += 8)
			*p = t4_पढ़ो_reg(adap, ULP_RX_LA_RDDATA_A);
	पूर्ण
पूर्ण

/* The ADVERT_MASK is used to mask out all of the Advertised Firmware Port
 * Capabilities which we control with separate controls -- see, क्रम instance,
 * Pause Frames and Forward Error Correction.  In order to determine what the
 * full set of Advertised Port Capabilities are, the base Advertised Port
 * Capabilities (masked by ADVERT_MASK) must be combined with the Advertised
 * Port Capabilities associated with those other controls.  See
 * t4_link_acaps() क्रम how this is करोne.
 */
#घोषणा ADVERT_MASK (FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_M) | \
		     FW_PORT_CAP32_ANEG)

/**
 *	fwcaps16_to_caps32 - convert 16-bit Port Capabilities to 32-bits
 *	@caps16: a 16-bit Port Capabilities value
 *
 *	Returns the equivalent 32-bit Port Capabilities value.
 */
अटल fw_port_cap32_t fwcaps16_to_caps32(fw_port_cap16_t caps16)
अणु
	fw_port_cap32_t caps32 = 0;

	#घोषणा CAP16_TO_CAP32(__cap) \
		करो अणु \
			अगर (caps16 & FW_PORT_CAP_##__cap) \
				caps32 |= FW_PORT_CAP32_##__cap; \
		पूर्ण जबतक (0)

	CAP16_TO_CAP32(SPEED_100M);
	CAP16_TO_CAP32(SPEED_1G);
	CAP16_TO_CAP32(SPEED_25G);
	CAP16_TO_CAP32(SPEED_10G);
	CAP16_TO_CAP32(SPEED_40G);
	CAP16_TO_CAP32(SPEED_100G);
	CAP16_TO_CAP32(FC_RX);
	CAP16_TO_CAP32(FC_TX);
	CAP16_TO_CAP32(ANEG);
	CAP16_TO_CAP32(FORCE_PAUSE);
	CAP16_TO_CAP32(MDIAUTO);
	CAP16_TO_CAP32(MDISTRAIGHT);
	CAP16_TO_CAP32(FEC_RS);
	CAP16_TO_CAP32(FEC_BASER_RS);
	CAP16_TO_CAP32(802_3_PAUSE);
	CAP16_TO_CAP32(802_3_ASM_सूची);

	#अघोषित CAP16_TO_CAP32

	वापस caps32;
पूर्ण

/**
 *	fwcaps32_to_caps16 - convert 32-bit Port Capabilities to 16-bits
 *	@caps32: a 32-bit Port Capabilities value
 *
 *	Returns the equivalent 16-bit Port Capabilities value.  Note that
 *	not all 32-bit Port Capabilities can be represented in the 16-bit
 *	Port Capabilities and some fields/values may not make it.
 */
अटल fw_port_cap16_t fwcaps32_to_caps16(fw_port_cap32_t caps32)
अणु
	fw_port_cap16_t caps16 = 0;

	#घोषणा CAP32_TO_CAP16(__cap) \
		करो अणु \
			अगर (caps32 & FW_PORT_CAP32_##__cap) \
				caps16 |= FW_PORT_CAP_##__cap; \
		पूर्ण जबतक (0)

	CAP32_TO_CAP16(SPEED_100M);
	CAP32_TO_CAP16(SPEED_1G);
	CAP32_TO_CAP16(SPEED_10G);
	CAP32_TO_CAP16(SPEED_25G);
	CAP32_TO_CAP16(SPEED_40G);
	CAP32_TO_CAP16(SPEED_100G);
	CAP32_TO_CAP16(FC_RX);
	CAP32_TO_CAP16(FC_TX);
	CAP32_TO_CAP16(802_3_PAUSE);
	CAP32_TO_CAP16(802_3_ASM_सूची);
	CAP32_TO_CAP16(ANEG);
	CAP32_TO_CAP16(FORCE_PAUSE);
	CAP32_TO_CAP16(MDIAUTO);
	CAP32_TO_CAP16(MDISTRAIGHT);
	CAP32_TO_CAP16(FEC_RS);
	CAP32_TO_CAP16(FEC_BASER_RS);

	#अघोषित CAP32_TO_CAP16

	वापस caps16;
पूर्ण

/* Translate Firmware Port Capabilities Pause specअगरication to Common Code */
अटल अंतरभूत क्रमागत cc_छोड़ो fwcap_to_cc_छोड़ो(fw_port_cap32_t fw_छोड़ो)
अणु
	क्रमागत cc_छोड़ो cc_छोड़ो = 0;

	अगर (fw_छोड़ो & FW_PORT_CAP32_FC_RX)
		cc_छोड़ो |= PAUSE_RX;
	अगर (fw_छोड़ो & FW_PORT_CAP32_FC_TX)
		cc_छोड़ो |= PAUSE_TX;

	वापस cc_छोड़ो;
पूर्ण

/* Translate Common Code Pause specअगरication पूर्णांकo Firmware Port Capabilities */
अटल अंतरभूत fw_port_cap32_t cc_to_fwcap_छोड़ो(क्रमागत cc_छोड़ो cc_छोड़ो)
अणु
	/* Translate orthogonal RX/TX Pause Controls क्रम L1 Configure
	 * commands, etc.
	 */
	fw_port_cap32_t fw_छोड़ो = 0;

	अगर (cc_छोड़ो & PAUSE_RX)
		fw_छोड़ो |= FW_PORT_CAP32_FC_RX;
	अगर (cc_छोड़ो & PAUSE_TX)
		fw_छोड़ो |= FW_PORT_CAP32_FC_TX;
	अगर (!(cc_छोड़ो & PAUSE_AUTONEG))
		fw_छोड़ो |= FW_PORT_CAP32_FORCE_PAUSE;

	/* Translate orthogonal Pause controls पूर्णांकo IEEE 802.3 Pause,
	 * Asymmetrical Pause क्रम use in reporting to upper layer OS code, etc.
	 * Note that these bits are ignored in L1 Configure commands.
	 */
	अगर (cc_छोड़ो & PAUSE_RX) अणु
		अगर (cc_छोड़ो & PAUSE_TX)
			fw_छोड़ो |= FW_PORT_CAP32_802_3_PAUSE;
		अन्यथा
			fw_छोड़ो |= FW_PORT_CAP32_802_3_ASM_सूची |
				    FW_PORT_CAP32_802_3_PAUSE;
	पूर्ण अन्यथा अगर (cc_छोड़ो & PAUSE_TX) अणु
		fw_छोड़ो |= FW_PORT_CAP32_802_3_ASM_सूची;
	पूर्ण

	वापस fw_छोड़ो;
पूर्ण

/* Translate Firmware Forward Error Correction specअगरication to Common Code */
अटल अंतरभूत क्रमागत cc_fec fwcap_to_cc_fec(fw_port_cap32_t fw_fec)
अणु
	क्रमागत cc_fec cc_fec = 0;

	अगर (fw_fec & FW_PORT_CAP32_FEC_RS)
		cc_fec |= FEC_RS;
	अगर (fw_fec & FW_PORT_CAP32_FEC_BASER_RS)
		cc_fec |= FEC_BASER_RS;

	वापस cc_fec;
पूर्ण

/* Translate Common Code Forward Error Correction specअगरication to Firmware */
अटल अंतरभूत fw_port_cap32_t cc_to_fwcap_fec(क्रमागत cc_fec cc_fec)
अणु
	fw_port_cap32_t fw_fec = 0;

	अगर (cc_fec & FEC_RS)
		fw_fec |= FW_PORT_CAP32_FEC_RS;
	अगर (cc_fec & FEC_BASER_RS)
		fw_fec |= FW_PORT_CAP32_FEC_BASER_RS;

	वापस fw_fec;
पूर्ण

/**
 *	t4_link_acaps - compute Link Advertised Port Capabilities
 *	@adapter: the adapter
 *	@port: the Port ID
 *	@lc: the Port's Link Configuration
 *
 *	Synthesize the Advertised Port Capabilities we'll be using based on
 *	the base Advertised Port Capabilities (which have been filtered by
 *	ADVERT_MASK) plus the inभागidual controls क्रम things like Pause
 *	Frames, Forward Error Correction, MDI, etc.
 */
fw_port_cap32_t t4_link_acaps(काष्ठा adapter *adapter, अचिन्हित पूर्णांक port,
			      काष्ठा link_config *lc)
अणु
	fw_port_cap32_t fw_fc, fw_fec, acaps;
	अचिन्हित पूर्णांक fw_mdi;
	अक्षर cc_fec;

	fw_mdi = (FW_PORT_CAP32_MDI_V(FW_PORT_CAP32_MDI_AUTO) & lc->pcaps);

	/* Convert driver coding of Pause Frame Flow Control settings पूर्णांकo the
	 * Firmware's API.
	 */
	fw_fc = cc_to_fwcap_छोड़ो(lc->requested_fc);

	/* Convert Common Code Forward Error Control settings पूर्णांकo the
	 * Firmware's API.  If the current Requested FEC has "Automatic"
	 * (IEEE 802.3) specअगरied, then we use whatever the Firmware
	 * sent us as part of its IEEE 802.3-based पूर्णांकerpretation of
	 * the Transceiver Module EPROM FEC parameters.  Otherwise we
	 * use whatever is in the current Requested FEC settings.
	 */
	अगर (lc->requested_fec & FEC_AUTO)
		cc_fec = fwcap_to_cc_fec(lc->def_acaps);
	अन्यथा
		cc_fec = lc->requested_fec;
	fw_fec = cc_to_fwcap_fec(cc_fec);

	/* Figure out what our Requested Port Capabilities are going to be.
	 * Note parallel काष्ठाure in t4_handle_get_port_info() and
	 * init_link_config().
	 */
	अगर (!(lc->pcaps & FW_PORT_CAP32_ANEG)) अणु
		acaps = lc->acaps | fw_fc | fw_fec;
		lc->fc = lc->requested_fc & ~PAUSE_AUTONEG;
		lc->fec = cc_fec;
	पूर्ण अन्यथा अगर (lc->स्वतःneg == AUTONEG_DISABLE) अणु
		acaps = lc->speed_caps | fw_fc | fw_fec | fw_mdi;
		lc->fc = lc->requested_fc & ~PAUSE_AUTONEG;
		lc->fec = cc_fec;
	पूर्ण अन्यथा अणु
		acaps = lc->acaps | fw_fc | fw_fec | fw_mdi;
	पूर्ण

	/* Some Requested Port Capabilities are trivially wrong अगर they exceed
	 * the Physical Port Capabilities.  We can check that here and provide
	 * moderately useful feedback in the प्रणाली log.
	 *
	 * Note that older Firmware करोesn't have FW_PORT_CAP32_FORCE_PAUSE, so
	 * we need to exclude this from this check in order to मुख्यtain
	 * compatibility ...
	 */
	अगर ((acaps & ~lc->pcaps) & ~FW_PORT_CAP32_FORCE_PAUSE) अणु
		dev_err(adapter->pdev_dev, "Requested Port Capabilities %#x exceed Physical Port Capabilities %#x\n",
			acaps, lc->pcaps);
		वापस -EINVAL;
	पूर्ण

	वापस acaps;
पूर्ण

/**
 *	t4_link_l1cfg_core - apply link configuration to MAC/PHY
 *	@adapter: the adapter
 *	@mbox: the Firmware Mailbox to use
 *	@port: the Port ID
 *	@lc: the Port's Link Configuration
 *	@sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *	@समयout: समय to रुको क्रम command to finish beक्रमe timing out
 *		(negative implies @sleep_ok=false)
 *
 *	Set up a port's MAC and PHY according to a desired link configuration.
 *	- If the PHY can स्वतः-negotiate first decide what to advertise, then
 *	  enable/disable स्वतः-negotiation as desired, and reset.
 *	- If the PHY करोes not स्वतः-negotiate just reset it.
 *	- If स्वतः-negotiation is off set the MAC to the proper speed/duplex/FC,
 *	  otherwise करो it later based on the outcome of स्वतः-negotiation.
 */
पूर्णांक t4_link_l1cfg_core(काष्ठा adapter *adapter, अचिन्हित पूर्णांक mbox,
		       अचिन्हित पूर्णांक port, काष्ठा link_config *lc,
		       u8 sleep_ok, पूर्णांक समयout)
अणु
	अचिन्हित पूर्णांक fw_caps = adapter->params.fw_caps_support;
	काष्ठा fw_port_cmd cmd;
	fw_port_cap32_t rcap;
	पूर्णांक ret;

	अगर (!(lc->pcaps & FW_PORT_CAP32_ANEG) &&
	    lc->स्वतःneg == AUTONEG_ENABLE) अणु
		वापस -EINVAL;
	पूर्ण

	/* Compute our Requested Port Capabilities and send that on to the
	 * Firmware.
	 */
	rcap = t4_link_acaps(adapter, port, lc);
	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				       FW_PORT_CMD_PORTID_V(port));
	cmd.action_to_len16 =
		cpu_to_be32(FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
						 ? FW_PORT_ACTION_L1_CFG
						 : FW_PORT_ACTION_L1_CFG32) |
						 FW_LEN16(cmd));
	अगर (fw_caps == FW_CAPS16)
		cmd.u.l1cfg.rcap = cpu_to_be32(fwcaps32_to_caps16(rcap));
	अन्यथा
		cmd.u.l1cfg32.rcap32 = cpu_to_be32(rcap);

	ret = t4_wr_mbox_meat_समयout(adapter, mbox, &cmd, माप(cmd), शून्य,
				      sleep_ok, समयout);

	/* Unक्रमtunately, even अगर the Requested Port Capabilities "fit" within
	 * the Physical Port Capabilities, some combinations of features may
	 * still not be legal.  For example, 40Gb/s and Reed-Solomon Forward
	 * Error Correction.  So अगर the Firmware rejects the L1 Configure
	 * request, flag that here.
	 */
	अगर (ret) अणु
		dev_err(adapter->pdev_dev,
			"Requested Port Capabilities %#x rejected, error %d\n",
			rcap, -ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4_restart_aneg - restart स्वतःnegotiation
 *	@adap: the adapter
 *	@mbox: mbox to use क्रम the FW command
 *	@port: the port id
 *
 *	Restarts स्वतःnegotiation क्रम the selected port.
 */
पूर्णांक t4_restart_aneg(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक port)
अणु
	अचिन्हित पूर्णांक fw_caps = adap->params.fw_caps_support;
	काष्ठा fw_port_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
				     FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				     FW_PORT_CMD_PORTID_V(port));
	c.action_to_len16 =
		cpu_to_be32(FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
						 ? FW_PORT_ACTION_L1_CFG
						 : FW_PORT_ACTION_L1_CFG32) |
			    FW_LEN16(c));
	अगर (fw_caps == FW_CAPS16)
		c.u.l1cfg.rcap = cpu_to_be32(FW_PORT_CAP_ANEG);
	अन्यथा
		c.u.l1cfg32.rcap32 = cpu_to_be32(FW_PORT_CAP32_ANEG);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

प्रकार व्योम (*पूर्णांक_handler_t)(काष्ठा adapter *adap);

काष्ठा पूर्णांकr_info अणु
	अचिन्हित पूर्णांक mask;       /* bits to check in पूर्णांकerrupt status */
	स्थिर अक्षर *msg;         /* message to prपूर्णांक or शून्य */
	लघु stat_idx;          /* stat counter to increment or -1 */
	अचिन्हित लघु fatal;    /* whether the condition reported is fatal */
	पूर्णांक_handler_t पूर्णांक_handler; /* platक्रमm-specअगरic पूर्णांक handler */
पूर्ण;

/**
 *	t4_handle_पूर्णांकr_status - table driven पूर्णांकerrupt handler
 *	@adapter: the adapter that generated the पूर्णांकerrupt
 *	@reg: the पूर्णांकerrupt status रेजिस्टर to process
 *	@acts: table of पूर्णांकerrupt actions
 *
 *	A table driven पूर्णांकerrupt handler that applies a set of masks to an
 *	पूर्णांकerrupt status word and perक्रमms the corresponding actions अगर the
 *	पूर्णांकerrupts described by the mask have occurred.  The actions include
 *	optionally emitting a warning or alert message.  The table is terminated
 *	by an entry specअगरying mask 0.  Returns the number of fatal पूर्णांकerrupt
 *	conditions.
 */
अटल पूर्णांक t4_handle_पूर्णांकr_status(काष्ठा adapter *adapter, अचिन्हित पूर्णांक reg,
				 स्थिर काष्ठा पूर्णांकr_info *acts)
अणु
	पूर्णांक fatal = 0;
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक status = t4_पढ़ो_reg(adapter, reg);

	क्रम ( ; acts->mask; ++acts) अणु
		अगर (!(status & acts->mask))
			जारी;
		अगर (acts->fatal) अणु
			fatal++;
			dev_alert(adapter->pdev_dev, "%s (0x%x)\n", acts->msg,
				  status & acts->mask);
		पूर्ण अन्यथा अगर (acts->msg && prपूर्णांकk_ratelimit())
			dev_warn(adapter->pdev_dev, "%s (0x%x)\n", acts->msg,
				 status & acts->mask);
		अगर (acts->पूर्णांक_handler)
			acts->पूर्णांक_handler(adapter);
		mask |= acts->mask;
	पूर्ण
	status &= mask;
	अगर (status)                           /* clear processed पूर्णांकerrupts */
		t4_ग_लिखो_reg(adapter, reg, status);
	वापस fatal;
पूर्ण

/*
 * Interrupt handler क्रम the PCIE module.
 */
अटल व्योम pcie_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info sysbus_पूर्णांकr_info[] = अणु
		अणु RNPP_F, "RXNP array parity error", -1, 1 पूर्ण,
		अणु RPCP_F, "RXPC array parity error", -1, 1 पूर्ण,
		अणु RCIP_F, "RXCIF array parity error", -1, 1 पूर्ण,
		अणु RCCP_F, "Rx completions control array parity error", -1, 1 पूर्ण,
		अणु RFTP_F, "RXFT array parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info pcie_port_पूर्णांकr_info[] = अणु
		अणु TPCP_F, "TXPC array parity error", -1, 1 पूर्ण,
		अणु TNPP_F, "TXNP array parity error", -1, 1 पूर्ण,
		अणु TFTP_F, "TXFT array parity error", -1, 1 पूर्ण,
		अणु TCAP_F, "TXCA array parity error", -1, 1 पूर्ण,
		अणु TCIP_F, "TXCIF array parity error", -1, 1 पूर्ण,
		अणु RCAP_F, "RXCA array parity error", -1, 1 पूर्ण,
		अणु OTDD_F, "outbound request TLP discarded", -1, 1 पूर्ण,
		अणु RDPE_F, "Rx data parity error", -1, 1 पूर्ण,
		अणु TDUE_F, "Tx uncorrectable data error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info pcie_पूर्णांकr_info[] = अणु
		अणु MSIADDRLPERR_F, "MSI AddrL parity error", -1, 1 पूर्ण,
		अणु MSIADDRHPERR_F, "MSI AddrH parity error", -1, 1 पूर्ण,
		अणु MSIDATAPERR_F, "MSI data parity error", -1, 1 पूर्ण,
		अणु MSIXADDRLPERR_F, "MSI-X AddrL parity error", -1, 1 पूर्ण,
		अणु MSIXADDRHPERR_F, "MSI-X AddrH parity error", -1, 1 पूर्ण,
		अणु MSIXDATAPERR_F, "MSI-X data parity error", -1, 1 पूर्ण,
		अणु MSIXDIPERR_F, "MSI-X DI parity error", -1, 1 पूर्ण,
		अणु PIOCPLPERR_F, "PCI PIO completion FIFO parity error", -1, 1 पूर्ण,
		अणु PIOREQPERR_F, "PCI PIO request FIFO parity error", -1, 1 पूर्ण,
		अणु TARTAGPERR_F, "PCI PCI target tag FIFO parity error", -1, 1 पूर्ण,
		अणु CCNTPERR_F, "PCI CMD channel count parity error", -1, 1 पूर्ण,
		अणु CREQPERR_F, "PCI CMD channel request parity error", -1, 1 पूर्ण,
		अणु CRSPPERR_F, "PCI CMD channel response parity error", -1, 1 पूर्ण,
		अणु DCNTPERR_F, "PCI DMA channel count parity error", -1, 1 पूर्ण,
		अणु DREQPERR_F, "PCI DMA channel request parity error", -1, 1 पूर्ण,
		अणु DRSPPERR_F, "PCI DMA channel response parity error", -1, 1 पूर्ण,
		अणु HCNTPERR_F, "PCI HMA channel count parity error", -1, 1 पूर्ण,
		अणु HREQPERR_F, "PCI HMA channel request parity error", -1, 1 पूर्ण,
		अणु HRSPPERR_F, "PCI HMA channel response parity error", -1, 1 पूर्ण,
		अणु CFGSNPPERR_F, "PCI config snoop FIFO parity error", -1, 1 पूर्ण,
		अणु FIDPERR_F, "PCI FID parity error", -1, 1 पूर्ण,
		अणु INTXCLRPERR_F, "PCI INTx clear parity error", -1, 1 पूर्ण,
		अणु MATAGPERR_F, "PCI MA tag parity error", -1, 1 पूर्ण,
		अणु PIOTAGPERR_F, "PCI PIO tag parity error", -1, 1 पूर्ण,
		अणु RXCPLPERR_F, "PCI Rx completion parity error", -1, 1 पूर्ण,
		अणु RXWRPERR_F, "PCI Rx write parity error", -1, 1 पूर्ण,
		अणु RPLPERR_F, "PCI replay buffer parity error", -1, 1 पूर्ण,
		अणु PCIESINT_F, "PCI core secondary fault", -1, 1 पूर्ण,
		अणु PCIEPINT_F, "PCI core primary fault", -1, 1 पूर्ण,
		अणु UNXSPLCPLERR_F, "PCI unexpected split completion error",
		  -1, 0 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अटल काष्ठा पूर्णांकr_info t5_pcie_पूर्णांकr_info[] = अणु
		अणु MSTGRPPERR_F, "Master Response Read Queue parity error",
		  -1, 1 पूर्ण,
		अणु MSTTIMEOUTPERR_F, "Master Timeout FIFO parity error", -1, 1 पूर्ण,
		अणु MSIXSTIPERR_F, "MSI-X STI SRAM parity error", -1, 1 पूर्ण,
		अणु MSIXADDRLPERR_F, "MSI-X AddrL parity error", -1, 1 पूर्ण,
		अणु MSIXADDRHPERR_F, "MSI-X AddrH parity error", -1, 1 पूर्ण,
		अणु MSIXDATAPERR_F, "MSI-X data parity error", -1, 1 पूर्ण,
		अणु MSIXDIPERR_F, "MSI-X DI parity error", -1, 1 पूर्ण,
		अणु PIOCPLGRPPERR_F, "PCI PIO completion Group FIFO parity error",
		  -1, 1 पूर्ण,
		अणु PIOREQGRPPERR_F, "PCI PIO request Group FIFO parity error",
		  -1, 1 पूर्ण,
		अणु TARTAGPERR_F, "PCI PCI target tag FIFO parity error", -1, 1 पूर्ण,
		अणु MSTTAGQPERR_F, "PCI master tag queue parity error", -1, 1 पूर्ण,
		अणु CREQPERR_F, "PCI CMD channel request parity error", -1, 1 पूर्ण,
		अणु CRSPPERR_F, "PCI CMD channel response parity error", -1, 1 पूर्ण,
		अणु DREQWRPERR_F, "PCI DMA channel write request parity error",
		  -1, 1 पूर्ण,
		अणु DREQPERR_F, "PCI DMA channel request parity error", -1, 1 पूर्ण,
		अणु DRSPPERR_F, "PCI DMA channel response parity error", -1, 1 पूर्ण,
		अणु HREQWRPERR_F, "PCI HMA channel count parity error", -1, 1 पूर्ण,
		अणु HREQPERR_F, "PCI HMA channel request parity error", -1, 1 पूर्ण,
		अणु HRSPPERR_F, "PCI HMA channel response parity error", -1, 1 पूर्ण,
		अणु CFGSNPPERR_F, "PCI config snoop FIFO parity error", -1, 1 पूर्ण,
		अणु FIDPERR_F, "PCI FID parity error", -1, 1 पूर्ण,
		अणु VFIDPERR_F, "PCI INTx clear parity error", -1, 1 पूर्ण,
		अणु MAGRPPERR_F, "PCI MA group FIFO parity error", -1, 1 पूर्ण,
		अणु PIOTAGPERR_F, "PCI PIO tag parity error", -1, 1 पूर्ण,
		अणु IPRXHDRGRPPERR_F, "PCI IP Rx header group parity error",
		  -1, 1 पूर्ण,
		अणु IPRXDATAGRPPERR_F, "PCI IP Rx data group parity error",
		  -1, 1 पूर्ण,
		अणु RPLPERR_F, "PCI IP replay buffer parity error", -1, 1 पूर्ण,
		अणु IPSOTPERR_F, "PCI IP SOT buffer parity error", -1, 1 पूर्ण,
		अणु TRGT1GRPPERR_F, "PCI TRGT1 group FIFOs parity error", -1, 1 पूर्ण,
		अणु READRSPERR_F, "Outbound read error", -1, 0 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	पूर्णांक fat;

	अगर (is_t4(adapter->params.chip))
		fat = t4_handle_पूर्णांकr_status(adapter,
				PCIE_CORE_UTL_SYSTEM_BUS_AGENT_STATUS_A,
				sysbus_पूर्णांकr_info) +
			t4_handle_पूर्णांकr_status(adapter,
					PCIE_CORE_UTL_PCI_EXPRESS_PORT_STATUS_A,
					pcie_port_पूर्णांकr_info) +
			t4_handle_पूर्णांकr_status(adapter, PCIE_INT_CAUSE_A,
					      pcie_पूर्णांकr_info);
	अन्यथा
		fat = t4_handle_पूर्णांकr_status(adapter, PCIE_INT_CAUSE_A,
					    t5_pcie_पूर्णांकr_info);

	अगर (fat)
		t4_fatal_err(adapter);
पूर्ण

/*
 * TP पूर्णांकerrupt handler.
 */
अटल व्योम tp_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info tp_पूर्णांकr_info[] = अणु
		अणु 0x3fffffff, "TP parity error", -1, 1 पूर्ण,
		अणु FLMTXFLSTEMPTY_F, "TP out of Tx pages", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, TP_INT_CAUSE_A, tp_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * SGE पूर्णांकerrupt handler.
 */
अटल व्योम sge_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	u32 v = 0, perr;
	u32 err;

	अटल स्थिर काष्ठा पूर्णांकr_info sge_पूर्णांकr_info[] = अणु
		अणु ERR_CPL_EXCEED_IQE_SIZE_F,
		  "SGE received CPL exceeding IQE size", -1, 1 पूर्ण,
		अणु ERR_INVALID_CIDX_INC_F,
		  "SGE GTS CIDX increment too large", -1, 0 पूर्ण,
		अणु ERR_CPL_OPCODE_0_F, "SGE received 0-length CPL", -1, 0 पूर्ण,
		अणु DBFIFO_LP_INT_F, शून्य, -1, 0, t4_db_full पूर्ण,
		अणु ERR_DATA_CPL_ON_HIGH_QID1_F | ERR_DATA_CPL_ON_HIGH_QID0_F,
		  "SGE IQID > 1023 received CPL for FL", -1, 0 पूर्ण,
		अणु ERR_BAD_DB_PIDX3_F, "SGE DBP 3 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX2_F, "SGE DBP 2 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX1_F, "SGE DBP 1 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX0_F, "SGE DBP 0 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_ING_CTXT_PRIO_F,
		  "SGE too many priority ingress contexts", -1, 0 पूर्ण,
		अणु INGRESS_SIZE_ERR_F, "SGE illegal ingress QID", -1, 0 पूर्ण,
		अणु EGRESS_SIZE_ERR_F, "SGE illegal egress QID", -1, 0 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अटल काष्ठा पूर्णांकr_info t4t5_sge_पूर्णांकr_info[] = अणु
		अणु ERR_DROPPED_DB_F, शून्य, -1, 0, t4_db_dropped पूर्ण,
		अणु DBFIFO_HP_INT_F, शून्य, -1, 0, t4_db_full पूर्ण,
		अणु ERR_EGR_CTXT_PRIO_F,
		  "SGE too many priority egress contexts", -1, 0 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	perr = t4_पढ़ो_reg(adapter, SGE_INT_CAUSE1_A);
	अगर (perr) अणु
		v |= perr;
		dev_alert(adapter->pdev_dev, "SGE Cause1 Parity Error %#x\n",
			  perr);
	पूर्ण

	perr = t4_पढ़ो_reg(adapter, SGE_INT_CAUSE2_A);
	अगर (perr) अणु
		v |= perr;
		dev_alert(adapter->pdev_dev, "SGE Cause2 Parity Error %#x\n",
			  perr);
	पूर्ण

	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) >= CHELSIO_T5) अणु
		perr = t4_पढ़ो_reg(adapter, SGE_INT_CAUSE5_A);
		/* Parity error (CRC) क्रम err_T_RxCRC is trivial, ignore it */
		perr &= ~ERR_T_RXCRC_F;
		अगर (perr) अणु
			v |= perr;
			dev_alert(adapter->pdev_dev,
				  "SGE Cause5 Parity Error %#x\n", perr);
		पूर्ण
	पूर्ण

	v |= t4_handle_पूर्णांकr_status(adapter, SGE_INT_CAUSE3_A, sge_पूर्णांकr_info);
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
		v |= t4_handle_पूर्णांकr_status(adapter, SGE_INT_CAUSE3_A,
					   t4t5_sge_पूर्णांकr_info);

	err = t4_पढ़ो_reg(adapter, SGE_ERROR_STATS_A);
	अगर (err & ERROR_QID_VALID_F) अणु
		dev_err(adapter->pdev_dev, "SGE error for queue %u\n",
			ERROR_QID_G(err));
		अगर (err & UNCAPTURED_ERROR_F)
			dev_err(adapter->pdev_dev,
				"SGE UNCAPTURED_ERROR set (clearing)\n");
		t4_ग_लिखो_reg(adapter, SGE_ERROR_STATS_A, ERROR_QID_VALID_F |
			     UNCAPTURED_ERROR_F);
	पूर्ण

	अगर (v != 0)
		t4_fatal_err(adapter);
पूर्ण

#घोषणा CIM_OBQ_INTR (OBQULP0PARERR_F | OBQULP1PARERR_F | OBQULP2PARERR_F |\
		      OBQULP3PARERR_F | OBQSGEPARERR_F | OBQNCSIPARERR_F)
#घोषणा CIM_IBQ_INTR (IBQTP0PARERR_F | IBQTP1PARERR_F | IBQULPPARERR_F |\
		      IBQSGEHIPARERR_F | IBQSGELOPARERR_F | IBQNCSIPARERR_F)

/*
 * CIM पूर्णांकerrupt handler.
 */
अटल व्योम cim_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info cim_पूर्णांकr_info[] = अणु
		अणु PREFDROPINT_F, "CIM control register prefetch drop", -1, 1 पूर्ण,
		अणु CIM_OBQ_INTR, "CIM OBQ parity error", -1, 1 पूर्ण,
		अणु CIM_IBQ_INTR, "CIM IBQ parity error", -1, 1 पूर्ण,
		अणु MBUPPARERR_F, "CIM mailbox uP parity error", -1, 1 पूर्ण,
		अणु MBHOSTPARERR_F, "CIM mailbox host parity error", -1, 1 पूर्ण,
		अणु TIEQINPARERRINT_F, "CIM TIEQ outgoing parity error", -1, 1 पूर्ण,
		अणु TIEQOUTPARERRINT_F, "CIM TIEQ incoming parity error", -1, 1 पूर्ण,
		अणु TIMER0INT_F, "CIM TIMER0 interrupt", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info cim_upपूर्णांकr_info[] = अणु
		अणु RSVDSPACEINT_F, "CIM reserved space access", -1, 1 पूर्ण,
		अणु ILLTRANSINT_F, "CIM illegal transaction", -1, 1 पूर्ण,
		अणु ILLWRINT_F, "CIM illegal write", -1, 1 पूर्ण,
		अणु ILLRDINT_F, "CIM illegal read", -1, 1 पूर्ण,
		अणु ILLRDBEINT_F, "CIM illegal read BE", -1, 1 पूर्ण,
		अणु ILLWRBEINT_F, "CIM illegal write BE", -1, 1 पूर्ण,
		अणु SGLRDBOOTINT_F, "CIM single read from boot space", -1, 1 पूर्ण,
		अणु SGLWRBOOTINT_F, "CIM single write to boot space", -1, 1 पूर्ण,
		अणु BLKWRBOOTINT_F, "CIM block write to boot space", -1, 1 पूर्ण,
		अणु SGLRDFLASHINT_F, "CIM single read from flash space", -1, 1 पूर्ण,
		अणु SGLWRFLASHINT_F, "CIM single write to flash space", -1, 1 पूर्ण,
		अणु BLKWRFLASHINT_F, "CIM block write to flash space", -1, 1 पूर्ण,
		अणु SGLRDEEPROMINT_F, "CIM single EEPROM read", -1, 1 पूर्ण,
		अणु SGLWREEPROMINT_F, "CIM single EEPROM write", -1, 1 पूर्ण,
		अणु BLKRDEEPROMINT_F, "CIM block EEPROM read", -1, 1 पूर्ण,
		अणु BLKWREEPROMINT_F, "CIM block EEPROM write", -1, 1 पूर्ण,
		अणु SGLRDCTLINT_F, "CIM single read from CTL space", -1, 1 पूर्ण,
		अणु SGLWRCTLINT_F, "CIM single write to CTL space", -1, 1 पूर्ण,
		अणु BLKRDCTLINT_F, "CIM block read from CTL space", -1, 1 पूर्ण,
		अणु BLKWRCTLINT_F, "CIM block write to CTL space", -1, 1 पूर्ण,
		अणु SGLRDPLINT_F, "CIM single read from PL space", -1, 1 पूर्ण,
		अणु SGLWRPLINT_F, "CIM single write to PL space", -1, 1 पूर्ण,
		अणु BLKRDPLINT_F, "CIM block read from PL space", -1, 1 पूर्ण,
		अणु BLKWRPLINT_F, "CIM block write to PL space", -1, 1 पूर्ण,
		अणु REQOVRLOOKUPINT_F, "CIM request FIFO overwrite", -1, 1 पूर्ण,
		अणु RSPOVRLOOKUPINT_F, "CIM response FIFO overwrite", -1, 1 पूर्ण,
		अणु TIMEOUTINT_F, "CIM PIF timeout", -1, 1 पूर्ण,
		अणु TIMEOUTMAINT_F, "CIM PIF MA timeout", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	u32 val, fw_err;
	पूर्णांक fat;

	fw_err = t4_पढ़ो_reg(adapter, PCIE_FW_A);
	अगर (fw_err & PCIE_FW_ERR_F)
		t4_report_fw_error(adapter);

	/* When the Firmware detects an पूर्णांकernal error which normally
	 * wouldn't उठाओ a Host Interrupt, it क्रमces a CIM Timer0 पूर्णांकerrupt
	 * in order to make sure the Host sees the Firmware Crash.  So
	 * अगर we have a Timer0 पूर्णांकerrupt and करोn't see a Firmware Crash,
	 * ignore the Timer0 पूर्णांकerrupt.
	 */

	val = t4_पढ़ो_reg(adapter, CIM_HOST_INT_CAUSE_A);
	अगर (val & TIMER0INT_F)
		अगर (!(fw_err & PCIE_FW_ERR_F) ||
		    (PCIE_FW_EVAL_G(fw_err) != PCIE_FW_EVAL_CRASH))
			t4_ग_लिखो_reg(adapter, CIM_HOST_INT_CAUSE_A,
				     TIMER0INT_F);

	fat = t4_handle_पूर्णांकr_status(adapter, CIM_HOST_INT_CAUSE_A,
				    cim_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, CIM_HOST_UPACC_INT_CAUSE_A,
				    cim_upपूर्णांकr_info);
	अगर (fat)
		t4_fatal_err(adapter);
पूर्ण

/*
 * ULP RX पूर्णांकerrupt handler.
 */
अटल व्योम ulprx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info ulprx_पूर्णांकr_info[] = अणु
		अणु 0x1800000, "ULPRX context error", -1, 1 पूर्ण,
		अणु 0x7fffff, "ULPRX parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, ULP_RX_INT_CAUSE_A, ulprx_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * ULP TX पूर्णांकerrupt handler.
 */
अटल व्योम ulptx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info ulptx_पूर्णांकr_info[] = अणु
		अणु PBL_BOUND_ERR_CH3_F, "ULPTX channel 3 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH2_F, "ULPTX channel 2 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH1_F, "ULPTX channel 1 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH0_F, "ULPTX channel 0 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु 0xfffffff, "ULPTX parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, ULP_TX_INT_CAUSE_A, ulptx_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * PM TX पूर्णांकerrupt handler.
 */
अटल व्योम pmtx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pmtx_पूर्णांकr_info[] = अणु
		अणु PCMD_LEN_OVFL0_F, "PMTX channel 0 pcmd too large", -1, 1 पूर्ण,
		अणु PCMD_LEN_OVFL1_F, "PMTX channel 1 pcmd too large", -1, 1 पूर्ण,
		अणु PCMD_LEN_OVFL2_F, "PMTX channel 2 pcmd too large", -1, 1 पूर्ण,
		अणु ZERO_C_CMD_ERROR_F, "PMTX 0-length pcmd", -1, 1 पूर्ण,
		अणु PMTX_FRAMING_ERROR_F, "PMTX framing error", -1, 1 पूर्ण,
		अणु OESPI_PAR_ERROR_F, "PMTX oespi parity error", -1, 1 पूर्ण,
		अणु DB_OPTIONS_PAR_ERROR_F, "PMTX db_options parity error",
		  -1, 1 पूर्ण,
		अणु ICSPI_PAR_ERROR_F, "PMTX icspi parity error", -1, 1 पूर्ण,
		अणु PMTX_C_PCMD_PAR_ERROR_F, "PMTX c_pcmd parity error", -1, 1पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, PM_TX_INT_CAUSE_A, pmtx_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * PM RX पूर्णांकerrupt handler.
 */
अटल व्योम pmrx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pmrx_पूर्णांकr_info[] = अणु
		अणु ZERO_E_CMD_ERROR_F, "PMRX 0-length pcmd", -1, 1 पूर्ण,
		अणु PMRX_FRAMING_ERROR_F, "PMRX framing error", -1, 1 पूर्ण,
		अणु OCSPI_PAR_ERROR_F, "PMRX ocspi parity error", -1, 1 पूर्ण,
		अणु DB_OPTIONS_PAR_ERROR_F, "PMRX db_options parity error",
		  -1, 1 पूर्ण,
		अणु IESPI_PAR_ERROR_F, "PMRX iespi parity error", -1, 1 पूर्ण,
		अणु PMRX_E_PCMD_PAR_ERROR_F, "PMRX e_pcmd parity error", -1, 1पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, PM_RX_INT_CAUSE_A, pmrx_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * CPL चयन पूर्णांकerrupt handler.
 */
अटल व्योम cplsw_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info cplsw_पूर्णांकr_info[] = अणु
		अणु CIM_OP_MAP_PERR_F, "CPLSW CIM op_map parity error", -1, 1 पूर्ण,
		अणु CIM_OVFL_ERROR_F, "CPLSW CIM overflow", -1, 1 पूर्ण,
		अणु TP_FRAMING_ERROR_F, "CPLSW TP framing error", -1, 1 पूर्ण,
		अणु SGE_FRAMING_ERROR_F, "CPLSW SGE framing error", -1, 1 पूर्ण,
		अणु CIM_FRAMING_ERROR_F, "CPLSW CIM framing error", -1, 1 पूर्ण,
		अणु ZERO_SWITCH_ERROR_F, "CPLSW no-switch error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adapter, CPL_INTR_CAUSE_A, cplsw_पूर्णांकr_info))
		t4_fatal_err(adapter);
पूर्ण

/*
 * LE पूर्णांकerrupt handler.
 */
अटल व्योम le_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	क्रमागत chip_type chip = CHELSIO_CHIP_VERSION(adap->params.chip);
	अटल स्थिर काष्ठा पूर्णांकr_info le_पूर्णांकr_info[] = अणु
		अणु LIPMISS_F, "LE LIP miss", -1, 0 पूर्ण,
		अणु LIP0_F, "LE 0 LIP error", -1, 0 पूर्ण,
		अणु PARITYERR_F, "LE parity error", -1, 1 पूर्ण,
		अणु UNKNOWNCMD_F, "LE unknown command", -1, 1 पूर्ण,
		अणु REQQPARERR_F, "LE request queue parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अटल काष्ठा पूर्णांकr_info t6_le_पूर्णांकr_info[] = अणु
		अणु T6_LIPMISS_F, "LE LIP miss", -1, 0 पूर्ण,
		अणु T6_LIP0_F, "LE 0 LIP error", -1, 0 पूर्ण,
		अणु CMDTIDERR_F, "LE cmd tid error", -1, 1 पूर्ण,
		अणु TCAMINTPERR_F, "LE parity error", -1, 1 पूर्ण,
		अणु T6_UNKNOWNCMD_F, "LE unknown command", -1, 1 पूर्ण,
		अणु SSRAMINTPERR_F, "LE request queue parity error", -1, 1 पूर्ण,
		अणु HASHTBLMEMCRCERR_F, "LE hash table mem crc error", -1, 0 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adap, LE_DB_INT_CAUSE_A,
				  (chip <= CHELSIO_T5) ?
				  le_पूर्णांकr_info : t6_le_पूर्णांकr_info))
		t4_fatal_err(adap);
पूर्ण

/*
 * MPS पूर्णांकerrupt handler.
 */
अटल व्योम mps_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info mps_rx_पूर्णांकr_info[] = अणु
		अणु 0xffffff, "MPS Rx parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_tx_पूर्णांकr_info[] = अणु
		अणु TPFIFO_V(TPFIFO_M), "MPS Tx TP FIFO parity error", -1, 1 पूर्ण,
		अणु NCSIFIFO_F, "MPS Tx NC-SI FIFO parity error", -1, 1 पूर्ण,
		अणु TXDATAFIFO_V(TXDATAFIFO_M), "MPS Tx data FIFO parity error",
		  -1, 1 पूर्ण,
		अणु TXDESCFIFO_V(TXDESCFIFO_M), "MPS Tx desc FIFO parity error",
		  -1, 1 पूर्ण,
		अणु BUBBLE_F, "MPS Tx underflow", -1, 1 पूर्ण,
		अणु SECNTERR_F, "MPS Tx SOP/EOP error", -1, 1 पूर्ण,
		अणु FRMERR_F, "MPS Tx framing error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info t6_mps_tx_पूर्णांकr_info[] = अणु
		अणु TPFIFO_V(TPFIFO_M), "MPS Tx TP FIFO parity error", -1, 1 पूर्ण,
		अणु NCSIFIFO_F, "MPS Tx NC-SI FIFO parity error", -1, 1 पूर्ण,
		अणु TXDATAFIFO_V(TXDATAFIFO_M), "MPS Tx data FIFO parity error",
		  -1, 1 पूर्ण,
		अणु TXDESCFIFO_V(TXDESCFIFO_M), "MPS Tx desc FIFO parity error",
		  -1, 1 पूर्ण,
		/* MPS Tx Bubble is normal क्रम T6 */
		अणु SECNTERR_F, "MPS Tx SOP/EOP error", -1, 1 पूर्ण,
		अणु FRMERR_F, "MPS Tx framing error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_trc_पूर्णांकr_info[] = अणु
		अणु FILTMEM_V(FILTMEM_M), "MPS TRC filter parity error", -1, 1 पूर्ण,
		अणु PKTFIFO_V(PKTFIFO_M), "MPS TRC packet FIFO parity error",
		  -1, 1 पूर्ण,
		अणु MISCPERR_F, "MPS TRC misc parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_stat_sram_पूर्णांकr_info[] = अणु
		अणु 0x1fffff, "MPS statistics SRAM parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_stat_tx_पूर्णांकr_info[] = अणु
		अणु 0xfffff, "MPS statistics Tx FIFO parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_stat_rx_पूर्णांकr_info[] = अणु
		अणु 0xffffff, "MPS statistics Rx FIFO parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा पूर्णांकr_info mps_cls_पूर्णांकr_info[] = अणु
		अणु MATCHSRAM_F, "MPS match SRAM parity error", -1, 1 पूर्ण,
		अणु MATCHTCAM_F, "MPS match TCAM parity error", -1, 1 पूर्ण,
		अणु HASHSRAM_F, "MPS hash SRAM parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	पूर्णांक fat;

	fat = t4_handle_पूर्णांकr_status(adapter, MPS_RX_PERR_INT_CAUSE_A,
				    mps_rx_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_TX_INT_CAUSE_A,
				    is_t6(adapter->params.chip)
				    ? t6_mps_tx_पूर्णांकr_info
				    : mps_tx_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_TRC_INT_CAUSE_A,
				    mps_trc_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_STAT_PERR_INT_CAUSE_SRAM_A,
				    mps_stat_sram_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_STAT_PERR_INT_CAUSE_TX_FIFO_A,
				    mps_stat_tx_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_STAT_PERR_INT_CAUSE_RX_FIFO_A,
				    mps_stat_rx_पूर्णांकr_info) +
	      t4_handle_पूर्णांकr_status(adapter, MPS_CLS_INT_CAUSE_A,
				    mps_cls_पूर्णांकr_info);

	t4_ग_लिखो_reg(adapter, MPS_INT_CAUSE_A, 0);
	t4_पढ़ो_reg(adapter, MPS_INT_CAUSE_A);                    /* flush */
	अगर (fat)
		t4_fatal_err(adapter);
पूर्ण

#घोषणा MEM_INT_MASK (PERR_INT_CAUSE_F | ECC_CE_INT_CAUSE_F | \
		      ECC_UE_INT_CAUSE_F)

/*
 * EDC/MC पूर्णांकerrupt handler.
 */
अटल व्योम mem_पूर्णांकr_handler(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	अटल स्थिर अक्षर name[4][7] = अणु "EDC0", "EDC1", "MC/MC0", "MC1" पूर्ण;

	अचिन्हित पूर्णांक addr, cnt_addr, v;

	अगर (idx <= MEM_EDC1) अणु
		addr = EDC_REG(EDC_INT_CAUSE_A, idx);
		cnt_addr = EDC_REG(EDC_ECC_STATUS_A, idx);
	पूर्ण अन्यथा अगर (idx == MEM_MC) अणु
		अगर (is_t4(adapter->params.chip)) अणु
			addr = MC_INT_CAUSE_A;
			cnt_addr = MC_ECC_STATUS_A;
		पूर्ण अन्यथा अणु
			addr = MC_P_INT_CAUSE_A;
			cnt_addr = MC_P_ECC_STATUS_A;
		पूर्ण
	पूर्ण अन्यथा अणु
		addr = MC_REG(MC_P_INT_CAUSE_A, 1);
		cnt_addr = MC_REG(MC_P_ECC_STATUS_A, 1);
	पूर्ण

	v = t4_पढ़ो_reg(adapter, addr) & MEM_INT_MASK;
	अगर (v & PERR_INT_CAUSE_F)
		dev_alert(adapter->pdev_dev, "%s FIFO parity error\n",
			  name[idx]);
	अगर (v & ECC_CE_INT_CAUSE_F) अणु
		u32 cnt = ECC_CECNT_G(t4_पढ़ो_reg(adapter, cnt_addr));

		t4_edc_err_पढ़ो(adapter, idx);

		t4_ग_लिखो_reg(adapter, cnt_addr, ECC_CECNT_V(ECC_CECNT_M));
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(adapter->pdev_dev,
				 "%u %s correctable ECC data error%s\n",
				 cnt, name[idx], cnt > 1 ? "s" : "");
	पूर्ण
	अगर (v & ECC_UE_INT_CAUSE_F)
		dev_alert(adapter->pdev_dev,
			  "%s uncorrectable ECC data error\n", name[idx]);

	t4_ग_लिखो_reg(adapter, addr, v);
	अगर (v & (PERR_INT_CAUSE_F | ECC_UE_INT_CAUSE_F))
		t4_fatal_err(adapter);
पूर्ण

/*
 * MA पूर्णांकerrupt handler.
 */
अटल व्योम ma_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	u32 v, status = t4_पढ़ो_reg(adap, MA_INT_CAUSE_A);

	अगर (status & MEM_PERR_INT_CAUSE_F) अणु
		dev_alert(adap->pdev_dev,
			  "MA parity error, parity status %#x\n",
			  t4_पढ़ो_reg(adap, MA_PARITY_ERROR_STATUS1_A));
		अगर (is_t5(adap->params.chip))
			dev_alert(adap->pdev_dev,
				  "MA parity error, parity status %#x\n",
				  t4_पढ़ो_reg(adap,
					      MA_PARITY_ERROR_STATUS2_A));
	पूर्ण
	अगर (status & MEM_WRAP_INT_CAUSE_F) अणु
		v = t4_पढ़ो_reg(adap, MA_INT_WRAP_STATUS_A);
		dev_alert(adap->pdev_dev, "MA address wrap-around error by "
			  "client %u to address %#x\n",
			  MEM_WRAP_CLIENT_NUM_G(v),
			  MEM_WRAP_ADDRESS_G(v) << 4);
	पूर्ण
	t4_ग_लिखो_reg(adap, MA_INT_CAUSE_A, status);
	t4_fatal_err(adap);
पूर्ण

/*
 * SMB पूर्णांकerrupt handler.
 */
अटल व्योम smb_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info smb_पूर्णांकr_info[] = अणु
		अणु MSTTXFIFOPARINT_F, "SMB master Tx FIFO parity error", -1, 1 पूर्ण,
		अणु MSTRXFIFOPARINT_F, "SMB master Rx FIFO parity error", -1, 1 पूर्ण,
		अणु SLVFIFOPARINT_F, "SMB slave FIFO parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adap, SMB_INT_CAUSE_A, smb_पूर्णांकr_info))
		t4_fatal_err(adap);
पूर्ण

/*
 * NC-SI पूर्णांकerrupt handler.
 */
अटल व्योम ncsi_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info ncsi_पूर्णांकr_info[] = अणु
		अणु CIM_DM_PRTY_ERR_F, "NC-SI CIM parity error", -1, 1 पूर्ण,
		अणु MPS_DM_PRTY_ERR_F, "NC-SI MPS parity error", -1, 1 पूर्ण,
		अणु TXFIFO_PRTY_ERR_F, "NC-SI Tx FIFO parity error", -1, 1 पूर्ण,
		अणु RXFIFO_PRTY_ERR_F, "NC-SI Rx FIFO parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adap, NCSI_INT_CAUSE_A, ncsi_पूर्णांकr_info))
		t4_fatal_err(adap);
पूर्ण

/*
 * XGMAC पूर्णांकerrupt handler.
 */
अटल व्योम xgmac_पूर्णांकr_handler(काष्ठा adapter *adap, पूर्णांक port)
अणु
	u32 v, पूर्णांक_cause_reg;

	अगर (is_t4(adap->params.chip))
		पूर्णांक_cause_reg = PORT_REG(port, XGMAC_PORT_INT_CAUSE_A);
	अन्यथा
		पूर्णांक_cause_reg = T5_PORT_REG(port, MAC_PORT_INT_CAUSE_A);

	v = t4_पढ़ो_reg(adap, पूर्णांक_cause_reg);

	v &= TXFIFO_PRTY_ERR_F | RXFIFO_PRTY_ERR_F;
	अगर (!v)
		वापस;

	अगर (v & TXFIFO_PRTY_ERR_F)
		dev_alert(adap->pdev_dev, "XGMAC %d Tx FIFO parity error\n",
			  port);
	अगर (v & RXFIFO_PRTY_ERR_F)
		dev_alert(adap->pdev_dev, "XGMAC %d Rx FIFO parity error\n",
			  port);
	t4_ग_लिखो_reg(adap, PORT_REG(port, XGMAC_PORT_INT_CAUSE_A), v);
	t4_fatal_err(adap);
पूर्ण

/*
 * PL पूर्णांकerrupt handler.
 */
अटल व्योम pl_पूर्णांकr_handler(काष्ठा adapter *adap)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pl_पूर्णांकr_info[] = अणु
		अणु FATALPERR_F, "T4 fatal parity error", -1, 1 पूर्ण,
		अणु PERRVFID_F, "PL VFID_MAP parity error", -1, 1 पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;

	अगर (t4_handle_पूर्णांकr_status(adap, PL_PL_INT_CAUSE_A, pl_पूर्णांकr_info))
		t4_fatal_err(adap);
पूर्ण

#घोषणा PF_INTR_MASK (PFSW_F)
#घोषणा GLBL_INTR_MASK (CIM_F | MPS_F | PL_F | PCIE_F | MC_F | EDC0_F | \
		EDC1_F | LE_F | TP_F | MA_F | PM_TX_F | PM_RX_F | ULP_RX_F | \
		CPL_SWITCH_F | SGE_F | ULP_TX_F | SF_F)

/**
 *	t4_slow_पूर्णांकr_handler - control path पूर्णांकerrupt handler
 *	@adapter: the adapter
 *
 *	T4 पूर्णांकerrupt handler क्रम non-data global पूर्णांकerrupt events, e.g., errors.
 *	The designation 'slow' is because it involves रेजिस्टर पढ़ोs, जबतक
 *	data पूर्णांकerrupts typically करोn't involve any MMIOs.
 */
पूर्णांक t4_slow_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	/* There are rare हालs where a PL_INT_CAUSE bit may end up getting
	 * set when the corresponding PL_INT_ENABLE bit isn't set.  It's
	 * easiest just to mask that हाल here.
	 */
	u32 raw_cause = t4_पढ़ो_reg(adapter, PL_INT_CAUSE_A);
	u32 enable = t4_पढ़ो_reg(adapter, PL_INT_ENABLE_A);
	u32 cause = raw_cause & enable;

	अगर (!(cause & GLBL_INTR_MASK))
		वापस 0;
	अगर (cause & CIM_F)
		cim_पूर्णांकr_handler(adapter);
	अगर (cause & MPS_F)
		mps_पूर्णांकr_handler(adapter);
	अगर (cause & NCSI_F)
		ncsi_पूर्णांकr_handler(adapter);
	अगर (cause & PL_F)
		pl_पूर्णांकr_handler(adapter);
	अगर (cause & SMB_F)
		smb_पूर्णांकr_handler(adapter);
	अगर (cause & XGMAC0_F)
		xgmac_पूर्णांकr_handler(adapter, 0);
	अगर (cause & XGMAC1_F)
		xgmac_पूर्णांकr_handler(adapter, 1);
	अगर (cause & XGMAC_KR0_F)
		xgmac_पूर्णांकr_handler(adapter, 2);
	अगर (cause & XGMAC_KR1_F)
		xgmac_पूर्णांकr_handler(adapter, 3);
	अगर (cause & PCIE_F)
		pcie_पूर्णांकr_handler(adapter);
	अगर (cause & MC_F)
		mem_पूर्णांकr_handler(adapter, MEM_MC);
	अगर (is_t5(adapter->params.chip) && (cause & MC1_F))
		mem_पूर्णांकr_handler(adapter, MEM_MC1);
	अगर (cause & EDC0_F)
		mem_पूर्णांकr_handler(adapter, MEM_EDC0);
	अगर (cause & EDC1_F)
		mem_पूर्णांकr_handler(adapter, MEM_EDC1);
	अगर (cause & LE_F)
		le_पूर्णांकr_handler(adapter);
	अगर (cause & TP_F)
		tp_पूर्णांकr_handler(adapter);
	अगर (cause & MA_F)
		ma_पूर्णांकr_handler(adapter);
	अगर (cause & PM_TX_F)
		pmtx_पूर्णांकr_handler(adapter);
	अगर (cause & PM_RX_F)
		pmrx_पूर्णांकr_handler(adapter);
	अगर (cause & ULP_RX_F)
		ulprx_पूर्णांकr_handler(adapter);
	अगर (cause & CPL_SWITCH_F)
		cplsw_पूर्णांकr_handler(adapter);
	अगर (cause & SGE_F)
		sge_पूर्णांकr_handler(adapter);
	अगर (cause & ULP_TX_F)
		ulptx_पूर्णांकr_handler(adapter);

	/* Clear the पूर्णांकerrupts just processed क्रम which we are the master. */
	t4_ग_लिखो_reg(adapter, PL_INT_CAUSE_A, raw_cause & GLBL_INTR_MASK);
	(व्योम)t4_पढ़ो_reg(adapter, PL_INT_CAUSE_A); /* flush */
	वापस 1;
पूर्ण

/**
 *	t4_पूर्णांकr_enable - enable पूर्णांकerrupts
 *	@adapter: the adapter whose पूर्णांकerrupts should be enabled
 *
 *	Enable PF-specअगरic पूर्णांकerrupts क्रम the calling function and the top-level
 *	पूर्णांकerrupt concentrator क्रम global पूर्णांकerrupts.  Interrupts are alपढ़ोy
 *	enabled at each module,	here we just enable the roots of the पूर्णांकerrupt
 *	hierarchies.
 *
 *	Note: this function should be called only when the driver manages
 *	non PF-specअगरic पूर्णांकerrupts from the various HW modules.  Only one PCI
 *	function at a समय should be करोing this.
 */
व्योम t4_पूर्णांकr_enable(काष्ठा adapter *adapter)
अणु
	u32 val = 0;
	u32 whoami = t4_पढ़ो_reg(adapter, PL_WHOAMI_A);
	u32 pf = CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5 ?
			SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami);

	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
		val = ERR_DROPPED_DB_F | ERR_EGR_CTXT_PRIO_F | DBFIFO_HP_INT_F;
	t4_ग_लिखो_reg(adapter, SGE_INT_ENABLE3_A, ERR_CPL_EXCEED_IQE_SIZE_F |
		     ERR_INVALID_CIDX_INC_F | ERR_CPL_OPCODE_0_F |
		     ERR_DATA_CPL_ON_HIGH_QID1_F | INGRESS_SIZE_ERR_F |
		     ERR_DATA_CPL_ON_HIGH_QID0_F | ERR_BAD_DB_PIDX3_F |
		     ERR_BAD_DB_PIDX2_F | ERR_BAD_DB_PIDX1_F |
		     ERR_BAD_DB_PIDX0_F | ERR_ING_CTXT_PRIO_F |
		     DBFIFO_LP_INT_F | EGRESS_SIZE_ERR_F | val);
	t4_ग_लिखो_reg(adapter, MYPF_REG(PL_PF_INT_ENABLE_A), PF_INTR_MASK);
	t4_set_reg_field(adapter, PL_INT_MAP0_A, 0, 1 << pf);
पूर्ण

/**
 *	t4_पूर्णांकr_disable - disable पूर्णांकerrupts
 *	@adapter: the adapter whose पूर्णांकerrupts should be disabled
 *
 *	Disable पूर्णांकerrupts.  We only disable the top-level पूर्णांकerrupt
 *	concentrators.  The caller must be a PCI function managing global
 *	पूर्णांकerrupts.
 */
व्योम t4_पूर्णांकr_disable(काष्ठा adapter *adapter)
अणु
	u32 whoami, pf;

	अगर (pci_channel_offline(adapter->pdev))
		वापस;

	whoami = t4_पढ़ो_reg(adapter, PL_WHOAMI_A);
	pf = CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5 ?
			SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami);

	t4_ग_लिखो_reg(adapter, MYPF_REG(PL_PF_INT_ENABLE_A), 0);
	t4_set_reg_field(adapter, PL_INT_MAP0_A, 1 << pf, 0);
पूर्ण

अचिन्हित पूर्णांक t4_chip_rss_size(काष्ठा adapter *adap)
अणु
	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		वापस RSS_NENTRIES;
	अन्यथा
		वापस T6_RSS_NENTRIES;
पूर्ण

/**
 *	t4_config_rss_range - configure a portion of the RSS mapping table
 *	@adapter: the adapter
 *	@mbox: mbox to use क्रम the FW command
 *	@viid: भव पूर्णांकerface whose RSS subtable is to be written
 *	@start: start entry in the table to ग_लिखो
 *	@n: how many table entries to ग_लिखो
 *	@rspq: values क्रम the response queue lookup table
 *	@nrspq: number of values in @rspq
 *
 *	Programs the selected part of the VI's RSS mapping table with the
 *	provided values.  If @nrspq < @n the supplied values are used repeatedly
 *	until the full table range is populated.
 *
 *	The caller must ensure the values in @rspq are in the range allowed क्रम
 *	@viid.
 */
पूर्णांक t4_config_rss_range(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक viid,
			पूर्णांक start, पूर्णांक n, स्थिर u16 *rspq, अचिन्हित पूर्णांक nrspq)
अणु
	पूर्णांक ret;
	स्थिर u16 *rsp = rspq;
	स्थिर u16 *rsp_end = rspq + nrspq;
	काष्ठा fw_rss_ind_tbl_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_IND_TBL_CMD) |
			       FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
			       FW_RSS_IND_TBL_CMD_VIID_V(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	/* each fw_rss_ind_tbl_cmd takes up to 32 entries */
	जबतक (n > 0) अणु
		पूर्णांक nq = min(n, 32);
		__be32 *qp = &cmd.iq0_to_iq2;

		cmd.niqid = cpu_to_be16(nq);
		cmd.startidx = cpu_to_be16(start);

		start += nq;
		n -= nq;

		जबतक (nq > 0) अणु
			अचिन्हित पूर्णांक v;

			v = FW_RSS_IND_TBL_CMD_IQ0_V(*rsp);
			अगर (++rsp >= rsp_end)
				rsp = rspq;
			v |= FW_RSS_IND_TBL_CMD_IQ1_V(*rsp);
			अगर (++rsp >= rsp_end)
				rsp = rspq;
			v |= FW_RSS_IND_TBL_CMD_IQ2_V(*rsp);
			अगर (++rsp >= rsp_end)
				rsp = rspq;

			*qp++ = cpu_to_be32(v);
			nq -= 3;
		पूर्ण

		ret = t4_wr_mbox(adapter, mbox, &cmd, माप(cmd), शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4_config_glbl_rss - configure the global RSS mode
 *	@adapter: the adapter
 *	@mbox: mbox to use क्रम the FW command
 *	@mode: global RSS mode
 *	@flags: mode-specअगरic flags
 *
 *	Sets the global RSS mode.
 */
पूर्णांक t4_config_glbl_rss(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक mode,
		       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fw_rss_glb_config_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_RSS_GLB_CONFIG_CMD) |
				    FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	अगर (mode == FW_RSS_GLB_CONFIG_CMD_MODE_MANUAL) अणु
		c.u.manual.mode_pkd =
			cpu_to_be32(FW_RSS_GLB_CONFIG_CMD_MODE_V(mode));
	पूर्ण अन्यथा अगर (mode == FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL) अणु
		c.u.basicभव.mode_pkd =
			cpu_to_be32(FW_RSS_GLB_CONFIG_CMD_MODE_V(mode));
		c.u.basicभव.synmapen_to_hashtoeplitz = cpu_to_be32(flags);
	पूर्ण अन्यथा
		वापस -EINVAL;
	वापस t4_wr_mbox(adapter, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_config_vi_rss - configure per VI RSS settings
 *	@adapter: the adapter
 *	@mbox: mbox to use क्रम the FW command
 *	@viid: the VI id
 *	@flags: RSS flags
 *	@defq: id of the शेष RSS queue क्रम the VI.
 *
 *	Configures VI-specअगरic RSS properties.
 */
पूर्णांक t4_config_vi_rss(काष्ठा adapter *adapter, पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक defq)
अणु
	काष्ठा fw_rss_vi_config_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_RSS_VI_CONFIG_CMD_VIID_V(viid));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.basicभव.शेषq_to_udpen = cpu_to_be32(flags |
					FW_RSS_VI_CONFIG_CMD_DEFAULTQ_V(defq));
	वापस t4_wr_mbox(adapter, mbox, &c, माप(c), शून्य);
पूर्ण

/* Read an RSS table row */
अटल पूर्णांक rd_rss_row(काष्ठा adapter *adap, पूर्णांक row, u32 *val)
अणु
	t4_ग_लिखो_reg(adap, TP_RSS_LKP_TABLE_A, 0xfff00000 | row);
	वापस t4_रुको_op_करोne_val(adap, TP_RSS_LKP_TABLE_A, LKPTBLROWVLD_F, 1,
				   5, 0, val);
पूर्ण

/**
 *	t4_पढ़ो_rss - पढ़ो the contents of the RSS mapping table
 *	@adapter: the adapter
 *	@map: holds the contents of the RSS mapping table
 *
 *	Reads the contents of the RSS hash->queue mapping table.
 */
पूर्णांक t4_पढ़ो_rss(काष्ठा adapter *adapter, u16 *map)
अणु
	पूर्णांक i, ret, nentries;
	u32 val;

	nentries = t4_chip_rss_size(adapter);
	क्रम (i = 0; i < nentries / 2; ++i) अणु
		ret = rd_rss_row(adapter, i, &val);
		अगर (ret)
			वापस ret;
		*map++ = LKPTBLQUEUE0_G(val);
		*map++ = LKPTBLQUEUE1_G(val);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक t4_use_ldst(काष्ठा adapter *adap)
अणु
	वापस (adap->flags & CXGB4_FW_OK) && !adap->use_bd;
पूर्ण

/**
 * t4_tp_fw_ldst_rw - Access TP indirect रेजिस्टर through LDST
 * @adap: the adapter
 * @cmd: TP fw ldst address space type
 * @vals: where the indirect रेजिस्टर values are stored/written
 * @nregs: how many indirect रेजिस्टरs to पढ़ो/ग_लिखो
 * @start_index: index of first indirect रेजिस्टर to पढ़ो/ग_लिखो
 * @rw: Read (1) or Write (0)
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Access TP indirect रेजिस्टरs through LDST
 */
अटल पूर्णांक t4_tp_fw_ldst_rw(काष्ठा adapter *adap, पूर्णांक cmd, u32 *vals,
			    अचिन्हित पूर्णांक nregs, अचिन्हित पूर्णांक start_index,
			    अचिन्हित पूर्णांक rw, bool sleep_ok)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा fw_ldst_cmd c;

	क्रम (i = 0; i < nregs; i++) अणु
		स_रखो(&c, 0, माप(c));
		c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
						FW_CMD_REQUEST_F |
						(rw ? FW_CMD_READ_F :
						      FW_CMD_WRITE_F) |
						FW_LDST_CMD_ADDRSPACE_V(cmd));
		c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));

		c.u.addrval.addr = cpu_to_be32(start_index + i);
		c.u.addrval.val  = rw ? 0 : cpu_to_be32(vals[i]);
		ret = t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c,
				      sleep_ok);
		अगर (ret)
			वापस ret;

		अगर (rw)
			vals[i] = be32_to_cpu(c.u.addrval.val);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * t4_tp_indirect_rw - Read/Write TP indirect रेजिस्टर through LDST or backकरोor
 * @adap: the adapter
 * @reg_addr: Address Register
 * @reg_data: Data रेजिस्टर
 * @buff: where the indirect रेजिस्टर values are stored/written
 * @nregs: how many indirect रेजिस्टरs to पढ़ो/ग_लिखो
 * @start_index: index of first indirect रेजिस्टर to पढ़ो/ग_लिखो
 * @rw: READ(1) or WRITE(0)
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Read/Write TP indirect रेजिस्टरs through LDST अगर possible.
 * Else, use backकरोor access
 **/
अटल व्योम t4_tp_indirect_rw(काष्ठा adapter *adap, u32 reg_addr, u32 reg_data,
			      u32 *buff, u32 nregs, u32 start_index, पूर्णांक rw,
			      bool sleep_ok)
अणु
	पूर्णांक rc = -EINVAL;
	पूर्णांक cmd;

	चयन (reg_addr) अणु
	हाल TP_PIO_ADDR_A:
		cmd = FW_LDST_ADDRSPC_TP_PIO;
		अवरोध;
	हाल TP_TM_PIO_ADDR_A:
		cmd = FW_LDST_ADDRSPC_TP_TM_PIO;
		अवरोध;
	हाल TP_MIB_INDEX_A:
		cmd = FW_LDST_ADDRSPC_TP_MIB;
		अवरोध;
	शेष:
		जाओ indirect_access;
	पूर्ण

	अगर (t4_use_ldst(adap))
		rc = t4_tp_fw_ldst_rw(adap, cmd, buff, nregs, start_index, rw,
				      sleep_ok);

indirect_access:

	अगर (rc) अणु
		अगर (rw)
			t4_पढ़ो_indirect(adap, reg_addr, reg_data, buff, nregs,
					 start_index);
		अन्यथा
			t4_ग_लिखो_indirect(adap, reg_addr, reg_data, buff, nregs,
					  start_index);
	पूर्ण
पूर्ण

/**
 * t4_tp_pio_पढ़ो - Read TP PIO रेजिस्टरs
 * @adap: the adapter
 * @buff: where the indirect रेजिस्टर values are written
 * @nregs: how many indirect रेजिस्टरs to पढ़ो
 * @start_index: index of first indirect रेजिस्टर to पढ़ो
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Read TP PIO Registers
 **/
व्योम t4_tp_pio_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
		    u32 start_index, bool sleep_ok)
अणु
	t4_tp_indirect_rw(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A, buff, nregs,
			  start_index, 1, sleep_ok);
पूर्ण

/**
 * t4_tp_pio_ग_लिखो - Write TP PIO रेजिस्टरs
 * @adap: the adapter
 * @buff: where the indirect रेजिस्टर values are stored
 * @nregs: how many indirect रेजिस्टरs to ग_लिखो
 * @start_index: index of first indirect रेजिस्टर to ग_लिखो
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Write TP PIO Registers
 **/
अटल व्योम t4_tp_pio_ग_लिखो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
			    u32 start_index, bool sleep_ok)
अणु
	t4_tp_indirect_rw(adap, TP_PIO_ADDR_A, TP_PIO_DATA_A, buff, nregs,
			  start_index, 0, sleep_ok);
पूर्ण

/**
 * t4_tp_पंचांग_pio_पढ़ो - Read TP TM PIO रेजिस्टरs
 * @adap: the adapter
 * @buff: where the indirect रेजिस्टर values are written
 * @nregs: how many indirect रेजिस्टरs to पढ़ो
 * @start_index: index of first indirect रेजिस्टर to पढ़ो
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Read TP TM PIO Registers
 **/
व्योम t4_tp_पंचांग_pio_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs,
		       u32 start_index, bool sleep_ok)
अणु
	t4_tp_indirect_rw(adap, TP_TM_PIO_ADDR_A, TP_TM_PIO_DATA_A, buff,
			  nregs, start_index, 1, sleep_ok);
पूर्ण

/**
 * t4_tp_mib_पढ़ो - Read TP MIB रेजिस्टरs
 * @adap: the adapter
 * @buff: where the indirect रेजिस्टर values are written
 * @nregs: how many indirect रेजिस्टरs to पढ़ो
 * @start_index: index of first indirect रेजिस्टर to पढ़ो
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Read TP MIB Registers
 **/
व्योम t4_tp_mib_पढ़ो(काष्ठा adapter *adap, u32 *buff, u32 nregs, u32 start_index,
		    bool sleep_ok)
अणु
	t4_tp_indirect_rw(adap, TP_MIB_INDEX_A, TP_MIB_DATA_A, buff, nregs,
			  start_index, 1, sleep_ok);
पूर्ण

/**
 *	t4_पढ़ो_rss_key - पढ़ो the global RSS key
 *	@adap: the adapter
 *	@key: 10-entry array holding the 320-bit RSS key
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Reads the global 320-bit RSS key.
 */
व्योम t4_पढ़ो_rss_key(काष्ठा adapter *adap, u32 *key, bool sleep_ok)
अणु
	t4_tp_pio_पढ़ो(adap, key, 10, TP_RSS_SECRET_KEY0_A, sleep_ok);
पूर्ण

/**
 *	t4_ग_लिखो_rss_key - program one of the RSS keys
 *	@adap: the adapter
 *	@key: 10-entry array holding the 320-bit RSS key
 *	@idx: which RSS key to ग_लिखो
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Writes one of the RSS keys with the given 320-bit value.  If @idx is
 *	0..15 the corresponding entry in the RSS key table is written,
 *	otherwise the global RSS key is written.
 */
व्योम t4_ग_लिखो_rss_key(काष्ठा adapter *adap, स्थिर u32 *key, पूर्णांक idx,
		      bool sleep_ok)
अणु
	u8 rss_key_addr_cnt = 16;
	u32 vrt = t4_पढ़ो_reg(adap, TP_RSS_CONFIG_VRT_A);

	/* T6 and later: क्रम KeyMode 3 (per-vf and per-vf scramble),
	 * allows access to key addresses 16-63 by using KeyWrAddrX
	 * as index[5:4](upper 2) पूर्णांकo key table
	 */
	अगर ((CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) &&
	    (vrt & KEYEXTEND_F) && (KEYMODE_G(vrt) == 3))
		rss_key_addr_cnt = 32;

	t4_tp_pio_ग_लिखो(adap, (व्योम *)key, 10, TP_RSS_SECRET_KEY0_A, sleep_ok);

	अगर (idx >= 0 && idx < rss_key_addr_cnt) अणु
		अगर (rss_key_addr_cnt > 16)
			t4_ग_लिखो_reg(adap, TP_RSS_CONFIG_VRT_A,
				     KEYWRADDRX_V(idx >> 4) |
				     T6_VFWRADDR_V(idx) | KEYWREN_F);
		अन्यथा
			t4_ग_लिखो_reg(adap, TP_RSS_CONFIG_VRT_A,
				     KEYWRADDR_V(idx) | KEYWREN_F);
	पूर्ण
पूर्ण

/**
 *	t4_पढ़ो_rss_pf_config - पढ़ो PF RSS Configuration Table
 *	@adapter: the adapter
 *	@index: the entry in the PF RSS table to पढ़ो
 *	@valp: where to store the वापसed value
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Reads the PF RSS Configuration Table at the specअगरied index and वापसs
 *	the value found there.
 */
व्योम t4_पढ़ो_rss_pf_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक index,
			   u32 *valp, bool sleep_ok)
अणु
	t4_tp_pio_पढ़ो(adapter, valp, 1, TP_RSS_PF0_CONFIG_A + index, sleep_ok);
पूर्ण

/**
 *	t4_पढ़ो_rss_vf_config - पढ़ो VF RSS Configuration Table
 *	@adapter: the adapter
 *	@index: the entry in the VF RSS table to पढ़ो
 *	@vfl: where to store the वापसed VFL
 *	@vfh: where to store the वापसed VFH
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Reads the VF RSS Configuration Table at the specअगरied index and वापसs
 *	the (VFL, VFH) values found there.
 */
व्योम t4_पढ़ो_rss_vf_config(काष्ठा adapter *adapter, अचिन्हित पूर्णांक index,
			   u32 *vfl, u32 *vfh, bool sleep_ok)
अणु
	u32 vrt, mask, data;

	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5) अणु
		mask = VFWRADDR_V(VFWRADDR_M);
		data = VFWRADDR_V(index);
	पूर्ण अन्यथा अणु
		 mask =  T6_VFWRADDR_V(T6_VFWRADDR_M);
		 data = T6_VFWRADDR_V(index);
	पूर्ण

	/* Request that the index'th VF Table values be पढ़ो पूर्णांकo VFL/VFH.
	 */
	vrt = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_VRT_A);
	vrt &= ~(VFRDRG_F | VFWREN_F | KEYWREN_F | mask);
	vrt |= data | VFRDEN_F;
	t4_ग_लिखो_reg(adapter, TP_RSS_CONFIG_VRT_A, vrt);

	/* Grab the VFL/VFH values ...
	 */
	t4_tp_pio_पढ़ो(adapter, vfl, 1, TP_RSS_VFL_CONFIG_A, sleep_ok);
	t4_tp_pio_पढ़ो(adapter, vfh, 1, TP_RSS_VFH_CONFIG_A, sleep_ok);
पूर्ण

/**
 *	t4_पढ़ो_rss_pf_map - पढ़ो PF RSS Map
 *	@adapter: the adapter
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Reads the PF RSS Map रेजिस्टर and वापसs its value.
 */
u32 t4_पढ़ो_rss_pf_map(काष्ठा adapter *adapter, bool sleep_ok)
अणु
	u32 pfmap;

	t4_tp_pio_पढ़ो(adapter, &pfmap, 1, TP_RSS_PF_MAP_A, sleep_ok);
	वापस pfmap;
पूर्ण

/**
 *	t4_पढ़ो_rss_pf_mask - पढ़ो PF RSS Mask
 *	@adapter: the adapter
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Reads the PF RSS Mask रेजिस्टर and वापसs its value.
 */
u32 t4_पढ़ो_rss_pf_mask(काष्ठा adapter *adapter, bool sleep_ok)
अणु
	u32 pfmask;

	t4_tp_pio_पढ़ो(adapter, &pfmask, 1, TP_RSS_PF_MSK_A, sleep_ok);
	वापस pfmask;
पूर्ण

/**
 *	t4_tp_get_tcp_stats - पढ़ो TP's TCP MIB counters
 *	@adap: the adapter
 *	@v4: holds the TCP/IP counter values
 *	@v6: holds the TCP/IPv6 counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's TCP/IP and TCP/IPv6 MIB counters.
 *	Either @v4 or @v6 may be %शून्य to skip the corresponding stats.
 */
व्योम t4_tp_get_tcp_stats(काष्ठा adapter *adap, काष्ठा tp_tcp_stats *v4,
			 काष्ठा tp_tcp_stats *v6, bool sleep_ok)
अणु
	u32 val[TP_MIB_TCP_RXT_SEG_LO_A - TP_MIB_TCP_OUT_RST_A + 1];

#घोषणा STAT_IDX(x) ((TP_MIB_TCP_##x##_A) - TP_MIB_TCP_OUT_RST_A)
#घोषणा STAT(x)     val[STAT_IDX(x)]
#घोषणा STAT64(x)   (((u64)STAT(x##_HI) << 32) | STAT(x##_LO))

	अगर (v4) अणु
		t4_tp_mib_पढ़ो(adap, val, ARRAY_SIZE(val),
			       TP_MIB_TCP_OUT_RST_A, sleep_ok);
		v4->tcp_out_rsts = STAT(OUT_RST);
		v4->tcp_in_segs  = STAT64(IN_SEG);
		v4->tcp_out_segs = STAT64(OUT_SEG);
		v4->tcp_retrans_segs = STAT64(RXT_SEG);
	पूर्ण
	अगर (v6) अणु
		t4_tp_mib_पढ़ो(adap, val, ARRAY_SIZE(val),
			       TP_MIB_TCP_V6OUT_RST_A, sleep_ok);
		v6->tcp_out_rsts = STAT(OUT_RST);
		v6->tcp_in_segs  = STAT64(IN_SEG);
		v6->tcp_out_segs = STAT64(OUT_SEG);
		v6->tcp_retrans_segs = STAT64(RXT_SEG);
	पूर्ण
#अघोषित STAT64
#अघोषित STAT
#अघोषित STAT_IDX
पूर्ण

/**
 *	t4_tp_get_err_stats - पढ़ो TP's error MIB counters
 *	@adap: the adapter
 *	@st: holds the counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's error counters.
 */
व्योम t4_tp_get_err_stats(काष्ठा adapter *adap, काष्ठा tp_err_stats *st,
			 bool sleep_ok)
अणु
	पूर्णांक nchan = adap->params.arch.nchan;

	t4_tp_mib_पढ़ो(adap, st->mac_in_errs, nchan, TP_MIB_MAC_IN_ERR_0_A,
		       sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->hdr_in_errs, nchan, TP_MIB_HDR_IN_ERR_0_A,
		       sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->tcp_in_errs, nchan, TP_MIB_TCP_IN_ERR_0_A,
		       sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->tnl_cong_drops, nchan,
		       TP_MIB_TNL_CNG_DROP_0_A, sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->ofld_chan_drops, nchan,
		       TP_MIB_OFD_CHN_DROP_0_A, sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->tnl_tx_drops, nchan, TP_MIB_TNL_DROP_0_A,
		       sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->ofld_vlan_drops, nchan,
		       TP_MIB_OFD_VLN_DROP_0_A, sleep_ok);
	t4_tp_mib_पढ़ो(adap, st->tcp6_in_errs, nchan,
		       TP_MIB_TCP_V6IN_ERR_0_A, sleep_ok);
	t4_tp_mib_पढ़ो(adap, &st->ofld_no_neigh, 2, TP_MIB_OFD_ARP_DROP_A,
		       sleep_ok);
पूर्ण

/**
 *	t4_tp_get_cpl_stats - पढ़ो TP's CPL MIB counters
 *	@adap: the adapter
 *	@st: holds the counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's CPL counters.
 */
व्योम t4_tp_get_cpl_stats(काष्ठा adapter *adap, काष्ठा tp_cpl_stats *st,
			 bool sleep_ok)
अणु
	पूर्णांक nchan = adap->params.arch.nchan;

	t4_tp_mib_पढ़ो(adap, st->req, nchan, TP_MIB_CPL_IN_REQ_0_A, sleep_ok);

	t4_tp_mib_पढ़ो(adap, st->rsp, nchan, TP_MIB_CPL_OUT_RSP_0_A, sleep_ok);
पूर्ण

/**
 *	t4_tp_get_rdma_stats - पढ़ो TP's RDMA MIB counters
 *	@adap: the adapter
 *	@st: holds the counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's RDMA counters.
 */
व्योम t4_tp_get_rdma_stats(काष्ठा adapter *adap, काष्ठा tp_rdma_stats *st,
			  bool sleep_ok)
अणु
	t4_tp_mib_पढ़ो(adap, &st->rqe_dfr_pkt, 2, TP_MIB_RQE_DFR_PKT_A,
		       sleep_ok);
पूर्ण

/**
 *	t4_get_fcoe_stats - पढ़ो TP's FCoE MIB counters क्रम a port
 *	@adap: the adapter
 *	@idx: the port index
 *	@st: holds the counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's FCoE counters क्रम the selected port.
 */
व्योम t4_get_fcoe_stats(काष्ठा adapter *adap, अचिन्हित पूर्णांक idx,
		       काष्ठा tp_fcoe_stats *st, bool sleep_ok)
अणु
	u32 val[2];

	t4_tp_mib_पढ़ो(adap, &st->frames_ddp, 1, TP_MIB_FCOE_DDP_0_A + idx,
		       sleep_ok);

	t4_tp_mib_पढ़ो(adap, &st->frames_drop, 1,
		       TP_MIB_FCOE_DROP_0_A + idx, sleep_ok);

	t4_tp_mib_पढ़ो(adap, val, 2, TP_MIB_FCOE_BYTE_0_HI_A + 2 * idx,
		       sleep_ok);

	st->octets_ddp = ((u64)val[0] << 32) | val[1];
पूर्ण

/**
 *	t4_get_usm_stats - पढ़ो TP's non-TCP DDP MIB counters
 *	@adap: the adapter
 *	@st: holds the counter values
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Returns the values of TP's counters क्रम non-TCP directly-placed packets.
 */
व्योम t4_get_usm_stats(काष्ठा adapter *adap, काष्ठा tp_usm_stats *st,
		      bool sleep_ok)
अणु
	u32 val[4];

	t4_tp_mib_पढ़ो(adap, val, 4, TP_MIB_USM_PKTS_A, sleep_ok);
	st->frames = val[0];
	st->drops = val[1];
	st->octets = ((u64)val[2] << 32) | val[3];
पूर्ण

/**
 *	t4_पढ़ो_mtu_tbl - वापसs the values in the HW path MTU table
 *	@adap: the adapter
 *	@mtus: where to store the MTU values
 *	@mtu_log: where to store the MTU base-2 log (may be %शून्य)
 *
 *	Reads the HW path MTU table.
 */
व्योम t4_पढ़ो_mtu_tbl(काष्ठा adapter *adap, u16 *mtus, u8 *mtu_log)
अणु
	u32 v;
	पूर्णांक i;

	क्रम (i = 0; i < NMTUS; ++i) अणु
		t4_ग_लिखो_reg(adap, TP_MTU_TABLE_A,
			     MTUINDEX_V(0xff) | MTUVALUE_V(i));
		v = t4_पढ़ो_reg(adap, TP_MTU_TABLE_A);
		mtus[i] = MTUVALUE_G(v);
		अगर (mtu_log)
			mtu_log[i] = MTUWIDTH_G(v);
	पूर्ण
पूर्ण

/**
 *	t4_पढ़ो_cong_tbl - पढ़ोs the congestion control table
 *	@adap: the adapter
 *	@incr: where to store the alpha values
 *
 *	Reads the additive increments programmed पूर्णांकo the HW congestion
 *	control table.
 */
व्योम t4_पढ़ो_cong_tbl(काष्ठा adapter *adap, u16 incr[NMTUS][NCCTRL_WIN])
अणु
	अचिन्हित पूर्णांक mtu, w;

	क्रम (mtu = 0; mtu < NMTUS; ++mtu)
		क्रम (w = 0; w < NCCTRL_WIN; ++w) अणु
			t4_ग_लिखो_reg(adap, TP_CCTRL_TABLE_A,
				     ROWINDEX_V(0xffff) | (mtu << 5) | w);
			incr[mtu][w] = (u16)t4_पढ़ो_reg(adap,
						TP_CCTRL_TABLE_A) & 0x1fff;
		पूर्ण
पूर्ण

/**
 *	t4_tp_wr_bits_indirect - set/clear bits in an indirect TP रेजिस्टर
 *	@adap: the adapter
 *	@addr: the indirect TP रेजिस्टर address
 *	@mask: specअगरies the field within the रेजिस्टर to modअगरy
 *	@val: new value क्रम the field
 *
 *	Sets a field of an indirect TP रेजिस्टर to the given value.
 */
व्योम t4_tp_wr_bits_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
			    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	t4_ग_लिखो_reg(adap, TP_PIO_ADDR_A, addr);
	val |= t4_पढ़ो_reg(adap, TP_PIO_DATA_A) & ~mask;
	t4_ग_लिखो_reg(adap, TP_PIO_DATA_A, val);
पूर्ण

/**
 *	init_cong_ctrl - initialize congestion control parameters
 *	@a: the alpha values क्रम congestion control
 *	@b: the beta values क्रम congestion control
 *
 *	Initialize the congestion control parameters.
 */
अटल व्योम init_cong_ctrl(अचिन्हित लघु *a, अचिन्हित लघु *b)
अणु
	a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = a[6] = a[7] = a[8] = 1;
	a[9] = 2;
	a[10] = 3;
	a[11] = 4;
	a[12] = 5;
	a[13] = 6;
	a[14] = 7;
	a[15] = 8;
	a[16] = 9;
	a[17] = 10;
	a[18] = 14;
	a[19] = 17;
	a[20] = 21;
	a[21] = 25;
	a[22] = 30;
	a[23] = 35;
	a[24] = 45;
	a[25] = 60;
	a[26] = 80;
	a[27] = 100;
	a[28] = 200;
	a[29] = 300;
	a[30] = 400;
	a[31] = 500;

	b[0] = b[1] = b[2] = b[3] = b[4] = b[5] = b[6] = b[7] = b[8] = 0;
	b[9] = b[10] = 1;
	b[11] = b[12] = 2;
	b[13] = b[14] = b[15] = b[16] = 3;
	b[17] = b[18] = b[19] = b[20] = b[21] = 4;
	b[22] = b[23] = b[24] = b[25] = b[26] = b[27] = 5;
	b[28] = b[29] = 6;
	b[30] = b[31] = 7;
पूर्ण

/* The minimum additive increment value क्रम the congestion control table */
#घोषणा CC_MIN_INCR 2U

/**
 *	t4_load_mtus - ग_लिखो the MTU and congestion control HW tables
 *	@adap: the adapter
 *	@mtus: the values क्रम the MTU table
 *	@alpha: the values क्रम the congestion control alpha parameter
 *	@beta: the values क्रम the congestion control beta parameter
 *
 *	Write the HW MTU table with the supplied MTUs and the high-speed
 *	congestion control table with the supplied alpha, beta, and MTUs.
 *	We ग_लिखो the two tables together because the additive increments
 *	depend on the MTUs.
 */
व्योम t4_load_mtus(काष्ठा adapter *adap, स्थिर अचिन्हित लघु *mtus,
		  स्थिर अचिन्हित लघु *alpha, स्थिर अचिन्हित लघु *beta)
अणु
	अटल स्थिर अचिन्हित पूर्णांक avg_pkts[NCCTRL_WIN] = अणु
		2, 6, 10, 14, 20, 28, 40, 56, 80, 112, 160, 224, 320, 448, 640,
		896, 1281, 1792, 2560, 3584, 5120, 7168, 10240, 14336, 20480,
		28672, 40960, 57344, 81920, 114688, 163840, 229376
	पूर्ण;

	अचिन्हित पूर्णांक i, w;

	क्रम (i = 0; i < NMTUS; ++i) अणु
		अचिन्हित पूर्णांक mtu = mtus[i];
		अचिन्हित पूर्णांक log2 = fls(mtu);

		अगर (!(mtu & ((1 << log2) >> 2)))     /* round */
			log2--;
		t4_ग_लिखो_reg(adap, TP_MTU_TABLE_A, MTUINDEX_V(i) |
			     MTUWIDTH_V(log2) | MTUVALUE_V(mtu));

		क्रम (w = 0; w < NCCTRL_WIN; ++w) अणु
			अचिन्हित पूर्णांक inc;

			inc = max(((mtu - 40) * alpha[w]) / avg_pkts[w],
				  CC_MIN_INCR);

			t4_ग_लिखो_reg(adap, TP_CCTRL_TABLE_A, (i << 21) |
				     (w << 16) | (beta[w] << 13) | inc);
		पूर्ण
	पूर्ण
पूर्ण

/* Calculates a rate in bytes/s given the number of 256-byte units per 4K core
 * घड़ीs.  The क्रमmula is
 *
 * bytes/s = bytes256 * 256 * ClkFreq / 4096
 *
 * which is equivalent to
 *
 * bytes/s = 62.5 * bytes256 * ClkFreq_ms
 */
अटल u64 chan_rate(काष्ठा adapter *adap, अचिन्हित पूर्णांक bytes256)
अणु
	u64 v = bytes256 * adap->params.vpd.cclk;

	वापस v * 62 + v / 2;
पूर्ण

/**
 *	t4_get_chan_txrate - get the current per channel Tx rates
 *	@adap: the adapter
 *	@nic_rate: rates क्रम NIC traffic
 *	@ofld_rate: rates क्रम offloaded traffic
 *
 *	Return the current Tx rates in bytes/s क्रम NIC and offloaded traffic
 *	क्रम each channel.
 */
व्योम t4_get_chan_txrate(काष्ठा adapter *adap, u64 *nic_rate, u64 *ofld_rate)
अणु
	u32 v;

	v = t4_पढ़ो_reg(adap, TP_TX_TRATE_A);
	nic_rate[0] = chan_rate(adap, TNLRATE0_G(v));
	nic_rate[1] = chan_rate(adap, TNLRATE1_G(v));
	अगर (adap->params.arch.nchan == NCHAN) अणु
		nic_rate[2] = chan_rate(adap, TNLRATE2_G(v));
		nic_rate[3] = chan_rate(adap, TNLRATE3_G(v));
	पूर्ण

	v = t4_पढ़ो_reg(adap, TP_TX_ORATE_A);
	ofld_rate[0] = chan_rate(adap, OFDRATE0_G(v));
	ofld_rate[1] = chan_rate(adap, OFDRATE1_G(v));
	अगर (adap->params.arch.nchan == NCHAN) अणु
		ofld_rate[2] = chan_rate(adap, OFDRATE2_G(v));
		ofld_rate[3] = chan_rate(adap, OFDRATE3_G(v));
	पूर्ण
पूर्ण

/**
 *	t4_set_trace_filter - configure one of the tracing filters
 *	@adap: the adapter
 *	@tp: the desired trace filter parameters
 *	@idx: which filter to configure
 *	@enable: whether to enable or disable the filter
 *
 *	Configures one of the tracing filters available in HW.  If @enable is
 *	%0 @tp is not examined and may be %शून्य. The user is responsible to
 *	set the single/multiple trace mode by writing to MPS_TRC_CFG_A रेजिस्टर
 */
पूर्णांक t4_set_trace_filter(काष्ठा adapter *adap, स्थिर काष्ठा trace_params *tp,
			पूर्णांक idx, पूर्णांक enable)
अणु
	पूर्णांक i, ofst = idx * 4;
	u32 data_reg, mask_reg, cfg;

	अगर (!enable) अणु
		t4_ग_लिखो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst, 0);
		वापस 0;
	पूर्ण

	cfg = t4_पढ़ो_reg(adap, MPS_TRC_CFG_A);
	अगर (cfg & TRCMULTIFILTER_F) अणु
		/* If multiple tracers are enabled, then maximum
		 * capture size is 2.5KB (FIFO size of a single channel)
		 * minus 2 flits क्रम CPL_TRACE_PKT header.
		 */
		अगर (tp->snap_len > ((10 * 1024 / 4) - (2 * 8)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* If multiple tracers are disabled, to aव्योम deadlocks
		 * maximum packet capture size of 9600 bytes is recommended.
		 * Also in this mode, only trace0 can be enabled and running.
		 */
		अगर (tp->snap_len > 9600 || idx)
			वापस -EINVAL;
	पूर्ण

	अगर (tp->port > (is_t4(adap->params.chip) ? 11 : 19) || tp->invert > 1 ||
	    tp->skip_len > TFLENGTH_M || tp->skip_ofst > TFOFFSET_M ||
	    tp->min_len > TFMINPKTSIZE_M)
		वापस -EINVAL;

	/* stop the tracer we'll be changing */
	t4_ग_लिखो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst, 0);

	idx *= (MPS_TRC_FILTER1_MATCH_A - MPS_TRC_FILTER0_MATCH_A);
	data_reg = MPS_TRC_FILTER0_MATCH_A + idx;
	mask_reg = MPS_TRC_FILTER0_DONT_CARE_A + idx;

	क्रम (i = 0; i < TRACE_LEN / 4; i++, data_reg += 4, mask_reg += 4) अणु
		t4_ग_लिखो_reg(adap, data_reg, tp->data[i]);
		t4_ग_लिखो_reg(adap, mask_reg, ~tp->mask[i]);
	पूर्ण
	t4_ग_लिखो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_B_A + ofst,
		     TFCAPTUREMAX_V(tp->snap_len) |
		     TFMINPKTSIZE_V(tp->min_len));
	t4_ग_लिखो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst,
		     TFOFFSET_V(tp->skip_ofst) | TFLENGTH_V(tp->skip_len) |
		     (is_t4(adap->params.chip) ?
		     TFPORT_V(tp->port) | TFEN_F | TFINVERTMATCH_V(tp->invert) :
		     T5_TFPORT_V(tp->port) | T5_TFEN_F |
		     T5_TFINVERTMATCH_V(tp->invert)));

	वापस 0;
पूर्ण

/**
 *	t4_get_trace_filter - query one of the tracing filters
 *	@adap: the adapter
 *	@tp: the current trace filter parameters
 *	@idx: which trace filter to query
 *	@enabled: non-zero अगर the filter is enabled
 *
 *	Returns the current settings of one of the HW tracing filters.
 */
व्योम t4_get_trace_filter(काष्ठा adapter *adap, काष्ठा trace_params *tp, पूर्णांक idx,
			 पूर्णांक *enabled)
अणु
	u32 ctla, ctlb;
	पूर्णांक i, ofst = idx * 4;
	u32 data_reg, mask_reg;

	ctla = t4_पढ़ो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_A_A + ofst);
	ctlb = t4_पढ़ो_reg(adap, MPS_TRC_FILTER_MATCH_CTL_B_A + ofst);

	अगर (is_t4(adap->params.chip)) अणु
		*enabled = !!(ctla & TFEN_F);
		tp->port =  TFPORT_G(ctla);
		tp->invert = !!(ctla & TFINVERTMATCH_F);
	पूर्ण अन्यथा अणु
		*enabled = !!(ctla & T5_TFEN_F);
		tp->port = T5_TFPORT_G(ctla);
		tp->invert = !!(ctla & T5_TFINVERTMATCH_F);
	पूर्ण
	tp->snap_len = TFCAPTUREMAX_G(ctlb);
	tp->min_len = TFMINPKTSIZE_G(ctlb);
	tp->skip_ofst = TFOFFSET_G(ctla);
	tp->skip_len = TFLENGTH_G(ctla);

	ofst = (MPS_TRC_FILTER1_MATCH_A - MPS_TRC_FILTER0_MATCH_A) * idx;
	data_reg = MPS_TRC_FILTER0_MATCH_A + ofst;
	mask_reg = MPS_TRC_FILTER0_DONT_CARE_A + ofst;

	क्रम (i = 0; i < TRACE_LEN / 4; i++, data_reg += 4, mask_reg += 4) अणु
		tp->mask[i] = ~t4_पढ़ो_reg(adap, mask_reg);
		tp->data[i] = t4_पढ़ो_reg(adap, data_reg) & tp->mask[i];
	पूर्ण
पूर्ण

/**
 *	t4_pmtx_get_stats - वापसs the HW stats from PMTX
 *	@adap: the adapter
 *	@cnt: where to store the count statistics
 *	@cycles: where to store the cycle statistics
 *
 *	Returns perक्रमmance statistics from PMTX.
 */
व्योम t4_pmtx_get_stats(काष्ठा adapter *adap, u32 cnt[], u64 cycles[])
अणु
	पूर्णांक i;
	u32 data[2];

	क्रम (i = 0; i < adap->params.arch.pm_stats_cnt; i++) अणु
		t4_ग_लिखो_reg(adap, PM_TX_STAT_CONFIG_A, i + 1);
		cnt[i] = t4_पढ़ो_reg(adap, PM_TX_STAT_COUNT_A);
		अगर (is_t4(adap->params.chip)) अणु
			cycles[i] = t4_पढ़ो_reg64(adap, PM_TX_STAT_LSB_A);
		पूर्ण अन्यथा अणु
			t4_पढ़ो_indirect(adap, PM_TX_DBG_CTRL_A,
					 PM_TX_DBG_DATA_A, data, 2,
					 PM_TX_DBG_STAT_MSB_A);
			cycles[i] = (((u64)data[0] << 32) | data[1]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	t4_pmrx_get_stats - वापसs the HW stats from PMRX
 *	@adap: the adapter
 *	@cnt: where to store the count statistics
 *	@cycles: where to store the cycle statistics
 *
 *	Returns perक्रमmance statistics from PMRX.
 */
व्योम t4_pmrx_get_stats(काष्ठा adapter *adap, u32 cnt[], u64 cycles[])
अणु
	पूर्णांक i;
	u32 data[2];

	क्रम (i = 0; i < adap->params.arch.pm_stats_cnt; i++) अणु
		t4_ग_लिखो_reg(adap, PM_RX_STAT_CONFIG_A, i + 1);
		cnt[i] = t4_पढ़ो_reg(adap, PM_RX_STAT_COUNT_A);
		अगर (is_t4(adap->params.chip)) अणु
			cycles[i] = t4_पढ़ो_reg64(adap, PM_RX_STAT_LSB_A);
		पूर्ण अन्यथा अणु
			t4_पढ़ो_indirect(adap, PM_RX_DBG_CTRL_A,
					 PM_RX_DBG_DATA_A, data, 2,
					 PM_RX_DBG_STAT_MSB_A);
			cycles[i] = (((u64)data[0] << 32) | data[1]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	compute_mps_bg_map - compute the MPS Buffer Group Map क्रम a Port
 *	@adapter: the adapter
 *	@pidx: the port index
 *
 *	Computes and वापसs a biपंचांगap indicating which MPS buffer groups are
 *	associated with the given Port.  Bit i is set अगर buffer group i is
 *	used by the Port.
 */
अटल अंतरभूत अचिन्हित पूर्णांक compute_mps_bg_map(काष्ठा adapter *adapter,
					      पूर्णांक pidx)
अणु
	अचिन्हित पूर्णांक chip_version, nports;

	chip_version = CHELSIO_CHIP_VERSION(adapter->params.chip);
	nports = 1 << NUMPORTS_G(t4_पढ़ो_reg(adapter, MPS_CMN_CTL_A));

	चयन (chip_version) अणु
	हाल CHELSIO_T4:
	हाल CHELSIO_T5:
		चयन (nports) अणु
		हाल 1: वापस 0xf;
		हाल 2: वापस 3 << (2 * pidx);
		हाल 4: वापस 1 << pidx;
		पूर्ण
		अवरोध;

	हाल CHELSIO_T6:
		चयन (nports) अणु
		हाल 2: वापस 1 << (2 * pidx);
		पूर्ण
		अवरोध;
	पूर्ण

	dev_err(adapter->pdev_dev, "Need MPS Buffer Group Map for Chip %0x, Nports %d\n",
		chip_version, nports);

	वापस 0;
पूर्ण

/**
 *	t4_get_mps_bg_map - वापस the buffer groups associated with a port
 *	@adapter: the adapter
 *	@pidx: the port index
 *
 *	Returns a biपंचांगap indicating which MPS buffer groups are associated
 *	with the given Port.  Bit i is set अगर buffer group i is used by the
 *	Port.
 */
अचिन्हित पूर्णांक t4_get_mps_bg_map(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	u8 *mps_bg_map;
	अचिन्हित पूर्णांक nports;

	nports = 1 << NUMPORTS_G(t4_पढ़ो_reg(adapter, MPS_CMN_CTL_A));
	अगर (pidx >= nports) अणु
		CH_WARN(adapter, "MPS Port Index %d >= Nports %d\n",
			pidx, nports);
		वापस 0;
	पूर्ण

	/* If we've alपढ़ोy retrieved/computed this, just वापस the result.
	 */
	mps_bg_map = adapter->params.mps_bg_map;
	अगर (mps_bg_map[pidx])
		वापस mps_bg_map[pidx];

	/* Newer Firmware can tell us what the MPS Buffer Group Map is.
	 * If we're talking to such Firmware, let it tell us.  If the new
	 * API isn't supported, revert back to old hardcoded way.  The value
	 * obtained from Firmware is encoded in below क्रमmat:
	 *
	 * val = (( MPSBGMAP[Port 3] << 24 ) |
	 *        ( MPSBGMAP[Port 2] << 16 ) |
	 *        ( MPSBGMAP[Port 1] <<  8 ) |
	 *        ( MPSBGMAP[Port 0] <<  0 ))
	 */
	अगर (adapter->flags & CXGB4_FW_OK) अणु
		u32 param, val;
		पूर्णांक ret;

		param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_MPSBGMAP));
		ret = t4_query_params_ns(adapter, adapter->mbox, adapter->pf,
					 0, 1, &param, &val);
		अगर (!ret) अणु
			पूर्णांक p;

			/* Store the BG Map क्रम all of the Ports in order to
			 * aव्योम more calls to the Firmware in the future.
			 */
			क्रम (p = 0; p < MAX_NPORTS; p++, val >>= 8)
				mps_bg_map[p] = val & 0xff;

			वापस mps_bg_map[pidx];
		पूर्ण
	पूर्ण

	/* Either we're not talking to the Firmware or we're dealing with
	 * older Firmware which करोesn't support the new API to get the MPS
	 * Buffer Group Map.  Fall back to computing it ourselves.
	 */
	mps_bg_map[pidx] = compute_mps_bg_map(adapter, pidx);
	वापस mps_bg_map[pidx];
पूर्ण

/**
 *      t4_get_tp_e2c_map - वापस the E2C channel map associated with a port
 *      @adapter: the adapter
 *      @pidx: the port index
 */
अटल अचिन्हित पूर्णांक t4_get_tp_e2c_map(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	अचिन्हित पूर्णांक nports;
	u32 param, val = 0;
	पूर्णांक ret;

	nports = 1 << NUMPORTS_G(t4_पढ़ो_reg(adapter, MPS_CMN_CTL_A));
	अगर (pidx >= nports) अणु
		CH_WARN(adapter, "TP E2C Channel Port Index %d >= Nports %d\n",
			pidx, nports);
		वापस 0;
	पूर्ण

	/* FW version >= 1.16.44.0 can determine E2C channel map using
	 * FW_PARAMS_PARAM_DEV_TPCHMAP API.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_TPCHMAP));
	ret = t4_query_params_ns(adapter, adapter->mbox, adapter->pf,
				 0, 1, &param, &val);
	अगर (!ret)
		वापस (val >> (8 * pidx)) & 0xff;

	वापस 0;
पूर्ण

/**
 *	t4_get_tp_ch_map - वापस TP ingress channels associated with a port
 *	@adap: the adapter
 *	@pidx: the port index
 *
 *	Returns a biपंचांगap indicating which TP Ingress Channels are associated
 *	with a given Port.  Bit i is set अगर TP Ingress Channel i is used by
 *	the Port.
 */
अचिन्हित पूर्णांक t4_get_tp_ch_map(काष्ठा adapter *adap, पूर्णांक pidx)
अणु
	अचिन्हित पूर्णांक chip_version = CHELSIO_CHIP_VERSION(adap->params.chip);
	अचिन्हित पूर्णांक nports = 1 << NUMPORTS_G(t4_पढ़ो_reg(adap, MPS_CMN_CTL_A));

	अगर (pidx >= nports) अणु
		dev_warn(adap->pdev_dev, "TP Port Index %d >= Nports %d\n",
			 pidx, nports);
		वापस 0;
	पूर्ण

	चयन (chip_version) अणु
	हाल CHELSIO_T4:
	हाल CHELSIO_T5:
		/* Note that this happens to be the same values as the MPS
		 * Buffer Group Map क्रम these Chips.  But we replicate the code
		 * here because they're really separate concepts.
		 */
		चयन (nports) अणु
		हाल 1: वापस 0xf;
		हाल 2: वापस 3 << (2 * pidx);
		हाल 4: वापस 1 << pidx;
		पूर्ण
		अवरोध;

	हाल CHELSIO_T6:
		चयन (nports) अणु
		हाल 1:
		हाल 2: वापस 1 << pidx;
		पूर्ण
		अवरोध;
	पूर्ण

	dev_err(adap->pdev_dev, "Need TP Channel Map for Chip %0x, Nports %d\n",
		chip_version, nports);
	वापस 0;
पूर्ण

/**
 *      t4_get_port_type_description - वापस Port Type string description
 *      @port_type: firmware Port Type क्रमागतeration
 */
स्थिर अक्षर *t4_get_port_type_description(क्रमागत fw_port_type port_type)
अणु
	अटल स्थिर अक्षर *स्थिर port_type_description[] = अणु
		"Fiber_XFI",
		"Fiber_XAUI",
		"BT_SGMII",
		"BT_XFI",
		"BT_XAUI",
		"KX4",
		"CX4",
		"KX",
		"KR",
		"SFP",
		"BP_AP",
		"BP4_AP",
		"QSFP_10G",
		"QSA",
		"QSFP",
		"BP40_BA",
		"KR4_100G",
		"CR4_QSFP",
		"CR_QSFP",
		"CR2_QSFP",
		"SFP28",
		"KR_SFP28",
		"KR_XLAUI"
	पूर्ण;

	अगर (port_type < ARRAY_SIZE(port_type_description))
		वापस port_type_description[port_type];
	वापस "UNKNOWN";
पूर्ण

/**
 *      t4_get_port_stats_offset - collect port stats relative to a previous
 *                                 snapshot
 *      @adap: The adapter
 *      @idx: The port
 *      @stats: Current stats to fill
 *      @offset: Previous stats snapshot
 */
व्योम t4_get_port_stats_offset(काष्ठा adapter *adap, पूर्णांक idx,
			      काष्ठा port_stats *stats,
			      काष्ठा port_stats *offset)
अणु
	u64 *s, *o;
	पूर्णांक i;

	t4_get_port_stats(adap, idx, stats);
	क्रम (i = 0, s = (u64 *)stats, o = (u64 *)offset;
			i < (माप(काष्ठा port_stats) / माप(u64));
			i++, s++, o++)
		*s -= *o;
पूर्ण

/**
 *	t4_get_port_stats - collect port statistics
 *	@adap: the adapter
 *	@idx: the port index
 *	@p: the stats काष्ठाure to fill
 *
 *	Collect statistics related to the given port from HW.
 */
व्योम t4_get_port_stats(काष्ठा adapter *adap, पूर्णांक idx, काष्ठा port_stats *p)
अणु
	u32 bgmap = t4_get_mps_bg_map(adap, idx);
	u32 stat_ctl = t4_पढ़ो_reg(adap, MPS_STAT_CTL_A);

#घोषणा GET_STAT(name) \
	t4_पढ़ो_reg64(adap, \
	(is_t4(adap->params.chip) ? PORT_REG(idx, MPS_PORT_STAT_##name##_L) : \
	T5_PORT_REG(idx, MPS_PORT_STAT_##name##_L)))
#घोषणा GET_STAT_COM(name) t4_पढ़ो_reg64(adap, MPS_STAT_##name##_L)

	p->tx_octets           = GET_STAT(TX_PORT_BYTES);
	p->tx_frames           = GET_STAT(TX_PORT_FRAMES);
	p->tx_bcast_frames     = GET_STAT(TX_PORT_BCAST);
	p->tx_mcast_frames     = GET_STAT(TX_PORT_MCAST);
	p->tx_ucast_frames     = GET_STAT(TX_PORT_UCAST);
	p->tx_error_frames     = GET_STAT(TX_PORT_ERROR);
	p->tx_frames_64        = GET_STAT(TX_PORT_64B);
	p->tx_frames_65_127    = GET_STAT(TX_PORT_65B_127B);
	p->tx_frames_128_255   = GET_STAT(TX_PORT_128B_255B);
	p->tx_frames_256_511   = GET_STAT(TX_PORT_256B_511B);
	p->tx_frames_512_1023  = GET_STAT(TX_PORT_512B_1023B);
	p->tx_frames_1024_1518 = GET_STAT(TX_PORT_1024B_1518B);
	p->tx_frames_1519_max  = GET_STAT(TX_PORT_1519B_MAX);
	p->tx_drop             = GET_STAT(TX_PORT_DROP);
	p->tx_छोड़ो            = GET_STAT(TX_PORT_PAUSE);
	p->tx_ppp0             = GET_STAT(TX_PORT_PPP0);
	p->tx_ppp1             = GET_STAT(TX_PORT_PPP1);
	p->tx_ppp2             = GET_STAT(TX_PORT_PPP2);
	p->tx_ppp3             = GET_STAT(TX_PORT_PPP3);
	p->tx_ppp4             = GET_STAT(TX_PORT_PPP4);
	p->tx_ppp5             = GET_STAT(TX_PORT_PPP5);
	p->tx_ppp6             = GET_STAT(TX_PORT_PPP6);
	p->tx_ppp7             = GET_STAT(TX_PORT_PPP7);

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) >= CHELSIO_T5) अणु
		अगर (stat_ctl & COUNTPAUSESTATTX_F)
			p->tx_frames_64 -= p->tx_छोड़ो;
		अगर (stat_ctl & COUNTPAUSEMCTX_F)
			p->tx_mcast_frames -= p->tx_छोड़ो;
	पूर्ण
	p->rx_octets           = GET_STAT(RX_PORT_BYTES);
	p->rx_frames           = GET_STAT(RX_PORT_FRAMES);
	p->rx_bcast_frames     = GET_STAT(RX_PORT_BCAST);
	p->rx_mcast_frames     = GET_STAT(RX_PORT_MCAST);
	p->rx_ucast_frames     = GET_STAT(RX_PORT_UCAST);
	p->rx_too_दीर्घ         = GET_STAT(RX_PORT_MTU_ERROR);
	p->rx_jabber           = GET_STAT(RX_PORT_MTU_CRC_ERROR);
	p->rx_fcs_err          = GET_STAT(RX_PORT_CRC_ERROR);
	p->rx_len_err          = GET_STAT(RX_PORT_LEN_ERROR);
	p->rx_symbol_err       = GET_STAT(RX_PORT_SYM_ERROR);
	p->rx_runt             = GET_STAT(RX_PORT_LESS_64B);
	p->rx_frames_64        = GET_STAT(RX_PORT_64B);
	p->rx_frames_65_127    = GET_STAT(RX_PORT_65B_127B);
	p->rx_frames_128_255   = GET_STAT(RX_PORT_128B_255B);
	p->rx_frames_256_511   = GET_STAT(RX_PORT_256B_511B);
	p->rx_frames_512_1023  = GET_STAT(RX_PORT_512B_1023B);
	p->rx_frames_1024_1518 = GET_STAT(RX_PORT_1024B_1518B);
	p->rx_frames_1519_max  = GET_STAT(RX_PORT_1519B_MAX);
	p->rx_छोड़ो            = GET_STAT(RX_PORT_PAUSE);
	p->rx_ppp0             = GET_STAT(RX_PORT_PPP0);
	p->rx_ppp1             = GET_STAT(RX_PORT_PPP1);
	p->rx_ppp2             = GET_STAT(RX_PORT_PPP2);
	p->rx_ppp3             = GET_STAT(RX_PORT_PPP3);
	p->rx_ppp4             = GET_STAT(RX_PORT_PPP4);
	p->rx_ppp5             = GET_STAT(RX_PORT_PPP5);
	p->rx_ppp6             = GET_STAT(RX_PORT_PPP6);
	p->rx_ppp7             = GET_STAT(RX_PORT_PPP7);

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) >= CHELSIO_T5) अणु
		अगर (stat_ctl & COUNTPAUSESTATRX_F)
			p->rx_frames_64 -= p->rx_छोड़ो;
		अगर (stat_ctl & COUNTPAUSEMCRX_F)
			p->rx_mcast_frames -= p->rx_छोड़ो;
	पूर्ण

	p->rx_ovflow0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_MAC_DROP_FRAME) : 0;
	p->rx_ovflow1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_MAC_DROP_FRAME) : 0;
	p->rx_ovflow2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_MAC_DROP_FRAME) : 0;
	p->rx_ovflow3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_MAC_DROP_FRAME) : 0;
	p->rx_trunc0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_MAC_TRUNC_FRAME) : 0;

#अघोषित GET_STAT
#अघोषित GET_STAT_COM
पूर्ण

/**
 *	t4_get_lb_stats - collect loopback port statistics
 *	@adap: the adapter
 *	@idx: the loopback port index
 *	@p: the stats काष्ठाure to fill
 *
 *	Return HW statistics क्रम the given loopback port.
 */
व्योम t4_get_lb_stats(काष्ठा adapter *adap, पूर्णांक idx, काष्ठा lb_port_stats *p)
अणु
	u32 bgmap = t4_get_mps_bg_map(adap, idx);

#घोषणा GET_STAT(name) \
	t4_पढ़ो_reg64(adap, \
	(is_t4(adap->params.chip) ? \
	PORT_REG(idx, MPS_PORT_STAT_LB_PORT_##name##_L) : \
	T5_PORT_REG(idx, MPS_PORT_STAT_LB_PORT_##name##_L)))
#घोषणा GET_STAT_COM(name) t4_पढ़ो_reg64(adap, MPS_STAT_##name##_L)

	p->octets           = GET_STAT(BYTES);
	p->frames           = GET_STAT(FRAMES);
	p->bcast_frames     = GET_STAT(BCAST);
	p->mcast_frames     = GET_STAT(MCAST);
	p->ucast_frames     = GET_STAT(UCAST);
	p->error_frames     = GET_STAT(ERROR);

	p->frames_64        = GET_STAT(64B);
	p->frames_65_127    = GET_STAT(65B_127B);
	p->frames_128_255   = GET_STAT(128B_255B);
	p->frames_256_511   = GET_STAT(256B_511B);
	p->frames_512_1023  = GET_STAT(512B_1023B);
	p->frames_1024_1518 = GET_STAT(1024B_1518B);
	p->frames_1519_max  = GET_STAT(1519B_MAX);
	p->drop             = GET_STAT(DROP_FRAMES);

	p->ovflow0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_LB_DROP_FRAME) : 0;
	p->ovflow1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_LB_DROP_FRAME) : 0;
	p->ovflow2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_LB_DROP_FRAME) : 0;
	p->ovflow3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_LB_DROP_FRAME) : 0;
	p->trunc0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_LB_TRUNC_FRAME) : 0;
	p->trunc1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_LB_TRUNC_FRAME) : 0;
	p->trunc2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_LB_TRUNC_FRAME) : 0;
	p->trunc3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_LB_TRUNC_FRAME) : 0;

#अघोषित GET_STAT
#अघोषित GET_STAT_COM
पूर्ण

/*     t4_mk_filtdelwr - create a delete filter WR
 *     @ftid: the filter ID
 *     @wr: the filter work request to populate
 *     @qid: ingress queue to receive the delete notअगरication
 *
 *     Creates a filter work request to delete the supplied filter.  If @qid is
 *     negative the delete notअगरication is suppressed.
 */
व्योम t4_mk_filtdelwr(अचिन्हित पूर्णांक ftid, काष्ठा fw_filter_wr *wr, पूर्णांक qid)
अणु
	स_रखो(wr, 0, माप(*wr));
	wr->op_pkd = cpu_to_be32(FW_WR_OP_V(FW_FILTER_WR));
	wr->len16_pkd = cpu_to_be32(FW_WR_LEN16_V(माप(*wr) / 16));
	wr->tid_to_iq = cpu_to_be32(FW_FILTER_WR_TID_V(ftid) |
				    FW_FILTER_WR_NOREPLY_V(qid < 0));
	wr->del_filter_to_l2tix = cpu_to_be32(FW_FILTER_WR_DEL_FILTER_F);
	अगर (qid >= 0)
		wr->rx_chan_rx_rpl_iq =
			cpu_to_be16(FW_FILTER_WR_RX_RPL_IQ_V(qid));
पूर्ण

#घोषणा INIT_CMD(var, cmd, rd_wr) करो अणु \
	(var).op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_##cmd##_CMD) | \
					FW_CMD_REQUEST_F | \
					FW_CMD_##rd_wr##_F); \
	(var).retval_len16 = cpu_to_be32(FW_LEN16(var)); \
पूर्ण जबतक (0)

पूर्णांक t4_fwaddrspace_ग_लिखो(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			  u32 addr, u32 val)
अणु
	u32 ldst_addrspace;
	काष्ठा fw_ldst_cmd c;

	स_रखो(&c, 0, माप(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_FIRMWARE);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F |
					FW_CMD_WRITE_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.addrval.addr = cpu_to_be32(addr);
	c.u.addrval.val = cpu_to_be32(val);

	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_mdio_rd - पढ़ो a PHY रेजिस्टर through MDIO
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@phy_addr: the PHY address
 *	@mmd: the PHY MMD to access (0 क्रम clause 22 PHYs)
 *	@reg: the रेजिस्टर to पढ़ो
 *	@valp: where to store the value
 *
 *	Issues a FW command through the given mailbox to पढ़ो a PHY रेजिस्टर.
 */
पूर्णांक t4_mdio_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक phy_addr,
	       अचिन्हित पूर्णांक mmd, अचिन्हित पूर्णांक reg, u16 *valp)
अणु
	पूर्णांक ret;
	u32 ldst_addrspace;
	काष्ठा fw_ldst_cmd c;

	स_रखो(&c, 0, माप(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_MDIO);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F | FW_CMD_READ_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.mdio.paddr_mmd = cpu_to_be16(FW_LDST_CMD_PADDR_V(phy_addr) |
					 FW_LDST_CMD_MMD_V(mmd));
	c.u.mdio.raddr = cpu_to_be16(reg);

	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	अगर (ret == 0)
		*valp = be16_to_cpu(c.u.mdio.rval);
	वापस ret;
पूर्ण

/**
 *	t4_mdio_wr - ग_लिखो a PHY रेजिस्टर through MDIO
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@phy_addr: the PHY address
 *	@mmd: the PHY MMD to access (0 क्रम clause 22 PHYs)
 *	@reg: the रेजिस्टर to ग_लिखो
 *	@val: value to ग_लिखो
 *
 *	Issues a FW command through the given mailbox to ग_लिखो a PHY रेजिस्टर.
 */
पूर्णांक t4_mdio_wr(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक phy_addr,
	       अचिन्हित पूर्णांक mmd, अचिन्हित पूर्णांक reg, u16 val)
अणु
	u32 ldst_addrspace;
	काष्ठा fw_ldst_cmd c;

	स_रखो(&c, 0, माप(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_MDIO);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.mdio.paddr_mmd = cpu_to_be16(FW_LDST_CMD_PADDR_V(phy_addr) |
					 FW_LDST_CMD_MMD_V(mmd));
	c.u.mdio.raddr = cpu_to_be16(reg);
	c.u.mdio.rval = cpu_to_be16(val);

	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_sge_decode_idma_state - decode the idma state
 *	@adapter: the adapter
 *	@state: the state idma is stuck in
 */
व्योम t4_sge_decode_idma_state(काष्ठा adapter *adapter, पूर्णांक state)
अणु
	अटल स्थिर अक्षर * स्थिर t4_decode[] = अणु
		"IDMA_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"Not used",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATA_FL_PREP",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
		"IDMA_FL_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATAFL_DONE",
		"IDMA_FL_REQ_HEADERFL_DONE",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर t5_decode[] = अणु
		"IDMA_IDLE",
		"IDMA_ALMOST_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"IDMA_SGEFLRFLUSH_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_DROP_SEND_INC",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर t6_decode[] = अणु
		"IDMA_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"IDMA_SGEFLRFLUSH_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_DROP_SEND_INC",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
	पूर्ण;
	अटल स्थिर u32 sge_regs[] = अणु
		SGE_DEBUG_DATA_LOW_INDEX_2_A,
		SGE_DEBUG_DATA_LOW_INDEX_3_A,
		SGE_DEBUG_DATA_HIGH_INDEX_10_A,
	पूर्ण;
	स्थिर अक्षर **sge_idma_decode;
	पूर्णांक sge_idma_decode_nstates;
	पूर्णांक i;
	अचिन्हित पूर्णांक chip_version = CHELSIO_CHIP_VERSION(adapter->params.chip);

	/* Select the right set of decode strings to dump depending on the
	 * adapter chip type.
	 */
	चयन (chip_version) अणु
	हाल CHELSIO_T4:
		sge_idma_decode = (स्थिर अक्षर **)t4_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t4_decode);
		अवरोध;

	हाल CHELSIO_T5:
		sge_idma_decode = (स्थिर अक्षर **)t5_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t5_decode);
		अवरोध;

	हाल CHELSIO_T6:
		sge_idma_decode = (स्थिर अक्षर **)t6_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t6_decode);
		अवरोध;

	शेष:
		dev_err(adapter->pdev_dev,
			"Unsupported chip version %d\n", chip_version);
		वापस;
	पूर्ण

	अगर (is_t4(adapter->params.chip)) अणु
		sge_idma_decode = (स्थिर अक्षर **)t4_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t4_decode);
	पूर्ण अन्यथा अणु
		sge_idma_decode = (स्थिर अक्षर **)t5_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t5_decode);
	पूर्ण

	अगर (state < sge_idma_decode_nstates)
		CH_WARN(adapter, "idma state %s\n", sge_idma_decode[state]);
	अन्यथा
		CH_WARN(adapter, "idma state %d unknown\n", state);

	क्रम (i = 0; i < ARRAY_SIZE(sge_regs); i++)
		CH_WARN(adapter, "SGE register %#x value %#x\n",
			sge_regs[i], t4_पढ़ो_reg(adapter, sge_regs[i]));
पूर्ण

/**
 *      t4_sge_ctxt_flush - flush the SGE context cache
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @ctxt_type: Egress or Ingress
 *
 *      Issues a FW command through the given mailbox to flush the
 *      SGE context cache.
 */
पूर्णांक t4_sge_ctxt_flush(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक ctxt_type)
अणु
	पूर्णांक ret;
	u32 ldst_addrspace;
	काष्ठा fw_ldst_cmd c;

	स_रखो(&c, 0, माप(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(ctxt_type == CTXT_EGRESS ?
						 FW_LDST_ADDRSPC_SGE_EGRC :
						 FW_LDST_ADDRSPC_SGE_INGC);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F | FW_CMD_READ_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.idctxt.msg_ctxtflush = cpu_to_be32(FW_LDST_CMD_CTXTFLUSH_F);

	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	वापस ret;
पूर्ण

/**
 *	t4_पढ़ो_sge_dbqसमयrs - पढ़ो SGE Doorbell Queue Timer values
 *	@adap: the adapter
 *	@ndbqसमयrs: size of the provided SGE Doorbell Queue Timer table
 *	@dbqसमयrs: SGE Doorbell Queue Timer table
 *
 *	Reads the SGE Doorbell Queue Timer values पूर्णांकo the provided table.
 *	Returns 0 on success (Firmware and Hardware support this feature),
 *	an error on failure.
 */
पूर्णांक t4_पढ़ो_sge_dbqसमयrs(काष्ठा adapter *adap, अचिन्हित पूर्णांक ndbqसमयrs,
			  u16 *dbqसमयrs)
अणु
	पूर्णांक ret, dbqसमयrix;

	ret = 0;
	dbqसमयrix = 0;
	जबतक (dbqसमयrix < ndbqसमयrs) अणु
		पूर्णांक nparams, param;
		u32 params[7], vals[7];

		nparams = ndbqसमयrs - dbqसमयrix;
		अगर (nparams > ARRAY_SIZE(params))
			nparams = ARRAY_SIZE(params);

		क्रम (param = 0; param < nparams; param++)
			params[param] =
			  (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			   FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DBQ_TIMER) |
			   FW_PARAMS_PARAM_Y_V(dbqसमयrix + param));
		ret = t4_query_params(adap, adap->mbox, adap->pf, 0,
				      nparams, params, vals);
		अगर (ret)
			अवरोध;

		क्रम (param = 0; param < nparams; param++)
			dbqसमयrs[dbqसमयrix++] = vals[param];
	पूर्ण
	वापस ret;
पूर्ण

/**
 *      t4_fw_hello - establish communication with FW
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @evt_mbox: mailbox to receive async FW events
 *      @master: specअगरies the caller's willingness to be the device master
 *	@state: वापसs the current device state (अगर non-शून्य)
 *
 *	Issues a command to establish communication with FW.  Returns either
 *	an error (negative पूर्णांकeger) or the mailbox of the Master PF.
 */
पूर्णांक t4_fw_hello(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक evt_mbox,
		क्रमागत dev_master master, क्रमागत dev_state *state)
अणु
	पूर्णांक ret;
	काष्ठा fw_hello_cmd c;
	u32 v;
	अचिन्हित पूर्णांक master_mbox;
	पूर्णांक retries = FW_CMD_HELLO_RETRIES;

retry:
	स_रखो(&c, 0, माप(c));
	INIT_CMD(c, HELLO, WRITE);
	c.err_to_clearinit = cpu_to_be32(
		FW_HELLO_CMD_MASTERDIS_V(master == MASTER_CANT) |
		FW_HELLO_CMD_MASTERFORCE_V(master == MASTER_MUST) |
		FW_HELLO_CMD_MBMASTER_V(master == MASTER_MUST ?
					mbox : FW_HELLO_CMD_MBMASTER_M) |
		FW_HELLO_CMD_MBASYNCNOT_V(evt_mbox) |
		FW_HELLO_CMD_STAGE_V(fw_hello_cmd_stage_os) |
		FW_HELLO_CMD_CLEARINIT_F);

	/*
	 * Issue the HELLO command to the firmware.  If it's not successful
	 * but indicates that we got a "busy" or "timeout" condition, retry
	 * the HELLO until we exhaust our retry limit.  If we करो exceed our
	 * retry limit, check to see अगर the firmware left us any error
	 * inक्रमmation and report that अगर so.
	 */
	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	अगर (ret < 0) अणु
		अगर ((ret == -EBUSY || ret == -ETIMEDOUT) && retries-- > 0)
			जाओ retry;
		अगर (t4_पढ़ो_reg(adap, PCIE_FW_A) & PCIE_FW_ERR_F)
			t4_report_fw_error(adap);
		वापस ret;
	पूर्ण

	v = be32_to_cpu(c.err_to_clearinit);
	master_mbox = FW_HELLO_CMD_MBMASTER_G(v);
	अगर (state) अणु
		अगर (v & FW_HELLO_CMD_ERR_F)
			*state = DEV_STATE_ERR;
		अन्यथा अगर (v & FW_HELLO_CMD_INIT_F)
			*state = DEV_STATE_INIT;
		अन्यथा
			*state = DEV_STATE_UNINIT;
	पूर्ण

	/*
	 * If we're not the Master PF then we need to रुको around क्रम the
	 * Master PF Driver to finish setting up the adapter.
	 *
	 * Note that we also करो this रुको अगर we're a non-Master-capable PF and
	 * there is no current Master PF; a Master PF may show up momentarily
	 * and we wouldn't want to fail poपूर्णांकlessly.  (This can happen when an
	 * OS loads lots of dअगरferent drivers rapidly at the same समय).  In
	 * this हाल, the Master PF वापसed by the firmware will be
	 * PCIE_FW_MASTER_M so the test below will work ...
	 */
	अगर ((v & (FW_HELLO_CMD_ERR_F|FW_HELLO_CMD_INIT_F)) == 0 &&
	    master_mbox != mbox) अणु
		पूर्णांक रुकोing = FW_CMD_HELLO_TIMEOUT;

		/*
		 * Wait क्रम the firmware to either indicate an error or
		 * initialized state.  If we see either of these we bail out
		 * and report the issue to the caller.  If we exhaust the
		 * "hello timeout" and we haven't exhausted our retries, try
		 * again.  Otherwise bail with a समयout error.
		 */
		क्रम (;;) अणु
			u32 pcie_fw;

			msleep(50);
			रुकोing -= 50;

			/*
			 * If neither Error nor Initialized are indicated
			 * by the firmware keep रुकोing till we exhaust our
			 * समयout ... and then retry अगर we haven't exhausted
			 * our retries ...
			 */
			pcie_fw = t4_पढ़ो_reg(adap, PCIE_FW_A);
			अगर (!(pcie_fw & (PCIE_FW_ERR_F|PCIE_FW_INIT_F))) अणु
				अगर (रुकोing <= 0) अणु
					अगर (retries-- > 0)
						जाओ retry;

					वापस -ETIMEDOUT;
				पूर्ण
				जारी;
			पूर्ण

			/*
			 * We either have an Error or Initialized condition
			 * report errors preferentially.
			 */
			अगर (state) अणु
				अगर (pcie_fw & PCIE_FW_ERR_F)
					*state = DEV_STATE_ERR;
				अन्यथा अगर (pcie_fw & PCIE_FW_INIT_F)
					*state = DEV_STATE_INIT;
			पूर्ण

			/*
			 * If we arrived beक्रमe a Master PF was selected and
			 * there's not a valid Master PF, grab its identity
			 * क्रम our caller.
			 */
			अगर (master_mbox == PCIE_FW_MASTER_M &&
			    (pcie_fw & PCIE_FW_MASTER_VLD_F))
				master_mbox = PCIE_FW_MASTER_G(pcie_fw);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस master_mbox;
पूर्ण

/**
 *	t4_fw_bye - end communication with FW
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *
 *	Issues a command to terminate communication with FW.
 */
पूर्णांक t4_fw_bye(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox)
अणु
	काष्ठा fw_bye_cmd c;

	स_रखो(&c, 0, माप(c));
	INIT_CMD(c, BYE, WRITE);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_init_cmd - ask FW to initialize the device
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *
 *	Issues a command to FW to partially initialize the device.  This
 *	perक्रमms initialization that generally करोesn't depend on user input.
 */
पूर्णांक t4_early_init(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox)
अणु
	काष्ठा fw_initialize_cmd c;

	स_रखो(&c, 0, माप(c));
	INIT_CMD(c, INITIALIZE, WRITE);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_fw_reset - issue a reset to FW
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@reset: specअगरies the type of reset to perक्रमm
 *
 *	Issues a reset command of the specअगरied type to FW.
 */
पूर्णांक t4_fw_reset(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक reset)
अणु
	काष्ठा fw_reset_cmd c;

	स_रखो(&c, 0, माप(c));
	INIT_CMD(c, RESET, WRITE);
	c.val = cpu_to_be32(reset);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_fw_halt - issue a reset/halt to FW and put uP पूर्णांकo RESET
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW RESET command (अगर desired)
 *	@क्रमce: क्रमce uP पूर्णांकo RESET even अगर FW RESET command fails
 *
 *	Issues a RESET command to firmware (अगर desired) with a HALT indication
 *	and then माला_दो the microprocessor पूर्णांकo RESET state.  The RESET command
 *	will only be issued अगर a legitimate mailbox is provided (mbox <=
 *	PCIE_FW_MASTER_M).
 *
 *	This is generally used in order क्रम the host to safely manipulate the
 *	adapter without fear of conflicting with whatever the firmware might
 *	be करोing.  The only way out of this state is to RESTART the firmware
 *	...
 */
अटल पूर्णांक t4_fw_halt(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक क्रमce)
अणु
	पूर्णांक ret = 0;

	/*
	 * If a legitimate mailbox is provided, issue a RESET command
	 * with a HALT indication.
	 */
	अगर (mbox <= PCIE_FW_MASTER_M) अणु
		काष्ठा fw_reset_cmd c;

		स_रखो(&c, 0, माप(c));
		INIT_CMD(c, RESET, WRITE);
		c.val = cpu_to_be32(PIORST_F | PIORSTMODE_F);
		c.halt_pkd = cpu_to_be32(FW_RESET_CMD_HALT_F);
		ret = t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
	पूर्ण

	/*
	 * Normally we won't complete the operation अगर the firmware RESET
	 * command fails but अगर our caller insists we'll go ahead and put the
	 * uP पूर्णांकo RESET.  This can be useful अगर the firmware is hung or even
	 * missing ...  We'll have to take the risk of putting the uP पूर्णांकo
	 * RESET without the cooperation of firmware in that हाल.
	 *
	 * We also क्रमce the firmware's HALT flag to be on in हाल we bypassed
	 * the firmware RESET command above or we're dealing with old firmware
	 * which करोesn't have the HALT capability.  This will serve as a flag
	 * क्रम the incoming firmware to know that it's coming out of a HALT
	 * rather than a RESET ... अगर it's new enough to understand that ...
	 */
	अगर (ret == 0 || क्रमce) अणु
		t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, UPCRST_F);
		t4_set_reg_field(adap, PCIE_FW_A, PCIE_FW_HALT_F,
				 PCIE_FW_HALT_F);
	पूर्ण

	/*
	 * And we always वापस the result of the firmware RESET command
	 * even when we क्रमce the uP पूर्णांकo RESET ...
	 */
	वापस ret;
पूर्ण

/**
 *	t4_fw_restart - restart the firmware by taking the uP out of RESET
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@reset: अगर we want to करो a RESET to restart things
 *
 *	Restart firmware previously halted by t4_fw_halt().  On successful
 *	वापस the previous PF Master reमुख्यs as the new PF Master and there
 *	is no need to issue a new HELLO command, etc.
 *
 *	We करो this in two ways:
 *
 *	 1. If we're dealing with newer firmware we'll simply want to take
 *	    the chip's microprocessor out of RESET.  This will cause the
 *	    firmware to start up from its start vector.  And then we'll loop
 *	    until the firmware indicates it's started again (PCIE_FW.HALT
 *	    reset to 0) or we समयout.
 *
 *	 2. If we're dealing with older firmware then we'll need to RESET
 *	    the chip since older firmware won't recognize the PCIE_FW.HALT
 *	    flag and स्वतःmatically RESET itself on startup.
 */
अटल पूर्णांक t4_fw_restart(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक reset)
अणु
	अगर (reset) अणु
		/*
		 * Since we're directing the RESET instead of the firmware
		 * करोing it स्वतःmatically, we need to clear the PCIE_FW.HALT
		 * bit.
		 */
		t4_set_reg_field(adap, PCIE_FW_A, PCIE_FW_HALT_F, 0);

		/*
		 * If we've been given a valid mailbox, first try to get the
		 * firmware to करो the RESET.  If that works, great and we can
		 * वापस success.  Otherwise, अगर we haven't been given a
		 * valid mailbox or the RESET command failed, fall back to
		 * hitting the chip with a hammer.
		 */
		अगर (mbox <= PCIE_FW_MASTER_M) अणु
			t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, 0);
			msleep(100);
			अगर (t4_fw_reset(adap, mbox,
					PIORST_F | PIORSTMODE_F) == 0)
				वापस 0;
		पूर्ण

		t4_ग_लिखो_reg(adap, PL_RST_A, PIORST_F | PIORSTMODE_F);
		msleep(2000);
	पूर्ण अन्यथा अणु
		पूर्णांक ms;

		t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, 0);
		क्रम (ms = 0; ms < FW_CMD_MAX_TIMEOUT; ) अणु
			अगर (!(t4_पढ़ो_reg(adap, PCIE_FW_A) & PCIE_FW_HALT_F))
				वापस 0;
			msleep(100);
			ms += 100;
		पूर्ण
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4_fw_upgrade - perक्रमm all of the steps necessary to upgrade FW
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW RESET command (अगर desired)
 *	@fw_data: the firmware image to ग_लिखो
 *	@size: image size
 *	@क्रमce: क्रमce upgrade even अगर firmware करोesn't cooperate
 *
 *	Perक्रमm all of the steps necessary क्रम upgrading an adapter's
 *	firmware image.  Normally this requires the cooperation of the
 *	existing firmware in order to halt all existing activities
 *	but अगर an invalid mailbox token is passed in we skip that step
 *	(though we'll still put the adapter microprocessor पूर्णांकo RESET in
 *	that हाल).
 *
 *	On successful वापस the new firmware will have been loaded and
 *	the adapter will have been fully RESET losing all previous setup
 *	state.  On unsuccessful वापस the adapter may be completely hosed ...
 *	positive त्रुटि_सं indicates that the adapter is ~probably~ पूर्णांकact, a
 *	negative त्रुटि_सं indicates that things are looking bad ...
 */
पूर्णांक t4_fw_upgrade(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		  स्थिर u8 *fw_data, अचिन्हित पूर्णांक size, पूर्णांक क्रमce)
अणु
	स्थिर काष्ठा fw_hdr *fw_hdr = (स्थिर काष्ठा fw_hdr *)fw_data;
	पूर्णांक reset, ret;

	अगर (!t4_fw_matches_chip(adap, fw_hdr))
		वापस -EINVAL;

	/* Disable CXGB4_FW_OK flag so that mbox commands with CXGB4_FW_OK flag
	 * set wont be sent when we are flashing FW.
	 */
	adap->flags &= ~CXGB4_FW_OK;

	ret = t4_fw_halt(adap, mbox, क्रमce);
	अगर (ret < 0 && !क्रमce)
		जाओ out;

	ret = t4_load_fw(adap, fw_data, size);
	अगर (ret < 0)
		जाओ out;

	/*
	 * If there was a Firmware Configuration File stored in FLASH,
	 * there's a good chance that it won't be compatible with the new
	 * Firmware.  In order to prevent dअगरficult to diagnose adapter
	 * initialization issues, we clear out the Firmware Configuration File
	 * portion of the FLASH .  The user will need to re-FLASH a new
	 * Firmware Configuration File which is compatible with the new
	 * Firmware अगर that's desired.
	 */
	(व्योम)t4_load_cfg(adap, शून्य, 0);

	/*
	 * Older versions of the firmware करोn't understand the new
	 * PCIE_FW.HALT flag and so won't know to perक्रमm a RESET when they
	 * restart.  So क्रम newly loaded older firmware we'll have to करो the
	 * RESET क्रम it so it starts up on a clean slate.  We can tell अगर
	 * the newly loaded firmware will handle this right by checking
	 * its header flags to see अगर it advertises the capability.
	 */
	reset = ((be32_to_cpu(fw_hdr->flags) & FW_HDR_FLAGS_RESET_HALT) == 0);
	ret = t4_fw_restart(adap, mbox, reset);

	/* Grab potentially new Firmware Device Log parameters so we can see
	 * how healthy the new Firmware is.  It's okay to contact the new
	 * Firmware क्रम these parameters even though, as far as it's
	 * concerned, we've never said "HELLO" to it ...
	 */
	(व्योम)t4_init_devlog_params(adap);
out:
	adap->flags |= CXGB4_FW_OK;
	वापस ret;
पूर्ण

/**
 *	t4_fl_pkt_align - वापस the fl packet alignment
 *	@adap: the adapter
 *
 *	T4 has a single field to specअगरy the packing and padding boundary.
 *	T5 onwards has separate fields क्रम this and hence the alignment क्रम
 *	next packet offset is maximum of these two.
 *
 */
पूर्णांक t4_fl_pkt_align(काष्ठा adapter *adap)
अणु
	u32 sge_control, sge_control2;
	अचिन्हित पूर्णांक ingpadboundary, ingpackboundary, fl_align, ingpad_shअगरt;

	sge_control = t4_पढ़ो_reg(adap, SGE_CONTROL_A);

	/* T4 uses a single control field to specअगरy both the PCIe Padding and
	 * Packing Boundary.  T5 पूर्णांकroduced the ability to specअगरy these
	 * separately.  The actual Ingress Packet Data alignment boundary
	 * within Packed Buffer Mode is the maximum of these two
	 * specअगरications.  (Note that it makes no real practical sense to
	 * have the Padding Boundary be larger than the Packing Boundary but you
	 * could set the chip up that way and, in fact, legacy T4 code would
	 * end करोing this because it would initialize the Padding Boundary and
	 * leave the Packing Boundary initialized to 0 (16 bytes).)
	 * Padding Boundary values in T6 starts from 8B,
	 * where as it is 32B क्रम T4 and T5.
	 */
	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		ingpad_shअगरt = INGPADBOUNDARY_SHIFT_X;
	अन्यथा
		ingpad_shअगरt = T6_INGPADBOUNDARY_SHIFT_X;

	ingpadboundary = 1 << (INGPADBOUNDARY_G(sge_control) + ingpad_shअगरt);

	fl_align = ingpadboundary;
	अगर (!is_t4(adap->params.chip)) अणु
		/* T5 has a weird पूर्णांकerpretation of one of the PCIe Packing
		 * Boundary values.  No idea why ...
		 */
		sge_control2 = t4_पढ़ो_reg(adap, SGE_CONTROL2_A);
		ingpackboundary = INGPACKBOUNDARY_G(sge_control2);
		अगर (ingpackboundary == INGPACKBOUNDARY_16B_X)
			ingpackboundary = 16;
		अन्यथा
			ingpackboundary = 1 << (ingpackboundary +
						INGPACKBOUNDARY_SHIFT_X);

		fl_align = max(ingpadboundary, ingpackboundary);
	पूर्ण
	वापस fl_align;
पूर्ण

/**
 *	t4_fixup_host_params - fix up host-dependent parameters
 *	@adap: the adapter
 *	@page_size: the host's Base Page Size
 *	@cache_line_size: the host's Cache Line Size
 *
 *	Various रेजिस्टरs in T4 contain values which are dependent on the
 *	host's Base Page and Cache Line Sizes.  This function will fix all of
 *	those रेजिस्टरs with the appropriate values as passed in ...
 */
पूर्णांक t4_fixup_host_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक page_size,
			 अचिन्हित पूर्णांक cache_line_size)
अणु
	अचिन्हित पूर्णांक page_shअगरt = fls(page_size) - 1;
	अचिन्हित पूर्णांक sge_hps = page_shअगरt - 10;
	अचिन्हित पूर्णांक stat_len = cache_line_size > 64 ? 128 : 64;
	अचिन्हित पूर्णांक fl_align = cache_line_size < 32 ? 32 : cache_line_size;
	अचिन्हित पूर्णांक fl_align_log = fls(fl_align) - 1;

	t4_ग_लिखो_reg(adap, SGE_HOST_PAGE_SIZE_A,
		     HOSTPAGESIZEPF0_V(sge_hps) |
		     HOSTPAGESIZEPF1_V(sge_hps) |
		     HOSTPAGESIZEPF2_V(sge_hps) |
		     HOSTPAGESIZEPF3_V(sge_hps) |
		     HOSTPAGESIZEPF4_V(sge_hps) |
		     HOSTPAGESIZEPF5_V(sge_hps) |
		     HOSTPAGESIZEPF6_V(sge_hps) |
		     HOSTPAGESIZEPF7_V(sge_hps));

	अगर (is_t4(adap->params.chip)) अणु
		t4_set_reg_field(adap, SGE_CONTROL_A,
				 INGPADBOUNDARY_V(INGPADBOUNDARY_M) |
				 EGRSTATUSPAGESIZE_F,
				 INGPADBOUNDARY_V(fl_align_log -
						  INGPADBOUNDARY_SHIFT_X) |
				 EGRSTATUSPAGESIZE_V(stat_len != 64));
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pack_align;
		अचिन्हित पूर्णांक ingpad, ingpack;

		/* T5 पूर्णांकroduced the separation of the Free List Padding and
		 * Packing Boundaries.  Thus, we can select a smaller Padding
		 * Boundary to aव्योम uselessly chewing up PCIe Link and Memory
		 * Bandwidth, and use a Packing Boundary which is large enough
		 * to aव्योम false sharing between CPUs, etc.
		 *
		 * For the PCI Link, the smaller the Padding Boundary the
		 * better.  For the Memory Controller, a smaller Padding
		 * Boundary is better until we cross under the Memory Line
		 * Size (the minimum unit of transfer to/from Memory).  If we
		 * have a Padding Boundary which is smaller than the Memory
		 * Line Size, that'll involve a Read-Modअगरy-Write cycle on the
		 * Memory Controller which is never good.
		 */

		/* We want the Packing Boundary to be based on the Cache Line
		 * Size in order to help aव्योम False Sharing perक्रमmance
		 * issues between CPUs, etc.  We also want the Packing
		 * Boundary to incorporate the PCI-E Maximum Payload Size.  We
		 * get best perक्रमmance when the Packing Boundary is a
		 * multiple of the Maximum Payload Size.
		 */
		pack_align = fl_align;
		अगर (pci_is_pcie(adap->pdev)) अणु
			अचिन्हित पूर्णांक mps, mps_log;
			u16 devctl;

			/* The PCIe Device Control Maximum Payload Size field
			 * [bits 7:5] encodes sizes as घातers of 2 starting at
			 * 128 bytes.
			 */
			pcie_capability_पढ़ो_word(adap->pdev, PCI_EXP_DEVCTL,
						  &devctl);
			mps_log = ((devctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5) + 7;
			mps = 1 << mps_log;
			अगर (mps > pack_align)
				pack_align = mps;
		पूर्ण

		/* N.B. T5/T6 have a crazy special पूर्णांकerpretation of the "0"
		 * value क्रम the Packing Boundary.  This corresponds to 16
		 * bytes instead of the expected 32 bytes.  So अगर we want 32
		 * bytes, the best we can really करो is 64 bytes ...
		 */
		अगर (pack_align <= 16) अणु
			ingpack = INGPACKBOUNDARY_16B_X;
			fl_align = 16;
		पूर्ण अन्यथा अगर (pack_align == 32) अणु
			ingpack = INGPACKBOUNDARY_64B_X;
			fl_align = 64;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक pack_align_log = fls(pack_align) - 1;

			ingpack = pack_align_log - INGPACKBOUNDARY_SHIFT_X;
			fl_align = pack_align;
		पूर्ण

		/* Use the smallest Ingress Padding which isn't smaller than
		 * the Memory Controller Read/Write Size.  We'll take that as
		 * being 8 bytes since we करोn't know of any प्रणाली with a
		 * wider Memory Controller Bus Width.
		 */
		अगर (is_t5(adap->params.chip))
			ingpad = INGPADBOUNDARY_32B_X;
		अन्यथा
			ingpad = T6_INGPADBOUNDARY_8B_X;

		t4_set_reg_field(adap, SGE_CONTROL_A,
				 INGPADBOUNDARY_V(INGPADBOUNDARY_M) |
				 EGRSTATUSPAGESIZE_F,
				 INGPADBOUNDARY_V(ingpad) |
				 EGRSTATUSPAGESIZE_V(stat_len != 64));
		t4_set_reg_field(adap, SGE_CONTROL2_A,
				 INGPACKBOUNDARY_V(INGPACKBOUNDARY_M),
				 INGPACKBOUNDARY_V(ingpack));
	पूर्ण
	/*
	 * Adjust various SGE Free List Host Buffer Sizes.
	 *
	 * This is something of a crock since we're using fixed indices पूर्णांकo
	 * the array which are also known by the sge.c code and the T4
	 * Firmware Configuration File.  We need to come up with a much better
	 * approach to managing this array.  For now, the first four entries
	 * are:
	 *
	 *   0: Host Page Size
	 *   1: 64KB
	 *   2: Buffer size corresponding to 1500 byte MTU (unpacked mode)
	 *   3: Buffer size corresponding to 9000 byte MTU (unpacked mode)
	 *
	 * For the single-MTU buffers in unpacked mode we need to include
	 * space क्रम the SGE Control Packet Shअगरt, 14 byte Ethernet header,
	 * possible 4 byte VLAN tag, all rounded up to the next Ingress Packet
	 * Padding boundary.  All of these are accommodated in the Factory
	 * Default Firmware Configuration File but we need to adjust it क्रम
	 * this host's cache line size.
	 */
	t4_ग_लिखो_reg(adap, SGE_FL_BUFFER_SIZE0_A, page_size);
	t4_ग_लिखो_reg(adap, SGE_FL_BUFFER_SIZE2_A,
		     (t4_पढ़ो_reg(adap, SGE_FL_BUFFER_SIZE2_A) + fl_align-1)
		     & ~(fl_align-1));
	t4_ग_लिखो_reg(adap, SGE_FL_BUFFER_SIZE3_A,
		     (t4_पढ़ो_reg(adap, SGE_FL_BUFFER_SIZE3_A) + fl_align-1)
		     & ~(fl_align-1));

	t4_ग_लिखो_reg(adap, ULP_RX_TDDP_PSZ_A, HPZ0_V(page_shअगरt - 12));

	वापस 0;
पूर्ण

/**
 *	t4_fw_initialize - ask FW to initialize the device
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *
 *	Issues a command to FW to partially initialize the device.  This
 *	perक्रमms initialization that generally करोesn't depend on user input.
 */
पूर्णांक t4_fw_initialize(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox)
अणु
	काष्ठा fw_initialize_cmd c;

	स_रखो(&c, 0, माप(c));
	INIT_CMD(c, INITIALIZE, WRITE);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_query_params_rw - query FW or device parameters
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF
 *	@vf: the VF
 *	@nparams: the number of parameters
 *	@params: the parameter names
 *	@val: the parameter values
 *	@rw: Write and पढ़ो flag
 *	@sleep_ok: अगर true, we may sleep aरुकोing mbox cmd completion
 *
 *	Reads the value of FW or device parameters.  Up to 7 parameters can be
 *	queried at once.
 */
पूर्णांक t4_query_params_rw(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		       u32 *val, पूर्णांक rw, bool sleep_ok)
अणु
	पूर्णांक i, ret;
	काष्ठा fw_params_cmd c;
	__be32 *p = &c.param[0].mnem;

	अगर (nparams > 7)
		वापस -EINVAL;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_READ_F |
				  FW_PARAMS_CMD_PFN_V(pf) |
				  FW_PARAMS_CMD_VFN_V(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));

	क्रम (i = 0; i < nparams; i++) अणु
		*p++ = cpu_to_be32(*params++);
		अगर (rw)
			*p = cpu_to_be32(*(val + i));
		p++;
	पूर्ण

	ret = t4_wr_mbox_meat(adap, mbox, &c, माप(c), &c, sleep_ok);
	अगर (ret == 0)
		क्रम (i = 0, p = &c.param[0].val; i < nparams; i++, p += 2)
			*val++ = be32_to_cpu(*p);
	वापस ret;
पूर्ण

पूर्णांक t4_query_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		    u32 *val)
अणु
	वापस t4_query_params_rw(adap, mbox, pf, vf, nparams, params, val, 0,
				  true);
पूर्ण

पूर्णांक t4_query_params_ns(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		       u32 *val)
अणु
	वापस t4_query_params_rw(adap, mbox, pf, vf, nparams, params, val, 0,
				  false);
पूर्ण

/**
 *      t4_set_params_समयout - sets FW or device parameters
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @pf: the PF
 *      @vf: the VF
 *      @nparams: the number of parameters
 *      @params: the parameter names
 *      @val: the parameter values
 *      @समयout: the समयout समय
 *
 *      Sets the value of FW or device parameters.  Up to 7 parameters can be
 *      specअगरied at once.
 */
पूर्णांक t4_set_params_समयout(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			  अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf,
			  अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
			  स्थिर u32 *val, पूर्णांक समयout)
अणु
	काष्ठा fw_params_cmd c;
	__be32 *p = &c.param[0].mnem;

	अगर (nparams > 7)
		वापस -EINVAL;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				  FW_PARAMS_CMD_PFN_V(pf) |
				  FW_PARAMS_CMD_VFN_V(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));

	जबतक (nparams--) अणु
		*p++ = cpu_to_be32(*params++);
		*p++ = cpu_to_be32(*val++);
	पूर्ण

	वापस t4_wr_mbox_समयout(adap, mbox, &c, माप(c), शून्य, समयout);
पूर्ण

/**
 *	t4_set_params - sets FW or device parameters
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF
 *	@vf: the VF
 *	@nparams: the number of parameters
 *	@params: the parameter names
 *	@val: the parameter values
 *
 *	Sets the value of FW or device parameters.  Up to 7 parameters can be
 *	specअगरied at once.
 */
पूर्णांक t4_set_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		  अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nparams, स्थिर u32 *params,
		  स्थिर u32 *val)
अणु
	वापस t4_set_params_समयout(adap, mbox, pf, vf, nparams, params, val,
				     FW_CMD_MAX_TIMEOUT);
पूर्ण

/**
 *	t4_cfg_pfvf - configure PF/VF resource limits
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF being configured
 *	@vf: the VF being configured
 *	@txq: the max number of egress queues
 *	@txq_eth_ctrl: the max number of egress Ethernet or control queues
 *	@rxqi: the max number of पूर्णांकerrupt-capable ingress queues
 *	@rxq: the max number of पूर्णांकerruptless ingress queues
 *	@tc: the PCI traffic class
 *	@vi: the max number of भव पूर्णांकerfaces
 *	@cmask: the channel access rights mask क्रम the PF/VF
 *	@pmask: the port access rights mask क्रम the PF/VF
 *	@nexact: the maximum number of exact MPS filters
 *	@rcaps: पढ़ो capabilities
 *	@wxcaps: ग_लिखो/execute capabilities
 *
 *	Configures resource limits and capabilities क्रम a physical or भव
 *	function.
 */
पूर्णांक t4_cfg_pfvf(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक txq, अचिन्हित पूर्णांक txq_eth_ctrl,
		अचिन्हित पूर्णांक rxqi, अचिन्हित पूर्णांक rxq, अचिन्हित पूर्णांक tc,
		अचिन्हित पूर्णांक vi, अचिन्हित पूर्णांक cmask, अचिन्हित पूर्णांक pmask,
		अचिन्हित पूर्णांक nexact, अचिन्हित पूर्णांक rcaps, अचिन्हित पूर्णांक wxcaps)
अणु
	काष्ठा fw_pfvf_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) | FW_CMD_REQUEST_F |
				  FW_CMD_WRITE_F | FW_PFVF_CMD_PFN_V(pf) |
				  FW_PFVF_CMD_VFN_V(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.niqflपूर्णांक_niq = cpu_to_be32(FW_PFVF_CMD_NIQFLINT_V(rxqi) |
				     FW_PFVF_CMD_NIQ_V(rxq));
	c.type_to_neq = cpu_to_be32(FW_PFVF_CMD_CMASK_V(cmask) |
				    FW_PFVF_CMD_PMASK_V(pmask) |
				    FW_PFVF_CMD_NEQ_V(txq));
	c.tc_to_nexactf = cpu_to_be32(FW_PFVF_CMD_TC_V(tc) |
				      FW_PFVF_CMD_NVI_V(vi) |
				      FW_PFVF_CMD_NEXACTF_V(nexact));
	c.r_caps_to_nethctrl = cpu_to_be32(FW_PFVF_CMD_R_CAPS_V(rcaps) |
					FW_PFVF_CMD_WX_CAPS_V(wxcaps) |
					FW_PFVF_CMD_NETHCTRL_V(txq_eth_ctrl));
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_alloc_vi - allocate a भव पूर्णांकerface
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@port: physical port associated with the VI
 *	@pf: the PF owning the VI
 *	@vf: the VF owning the VI
 *	@nmac: number of MAC addresses needed (1 to 5)
 *	@mac: the MAC addresses of the VI
 *	@rss_size: size of RSS table slice associated with this VI
 *	@vivld: the destination to store the VI Valid value.
 *	@vin: the destination to store the VIN value.
 *
 *	Allocates a भव पूर्णांकerface क्रम the given physical port.  If @mac is
 *	not %शून्य it contains the MAC addresses of the VI as asचिन्हित by FW.
 *	@mac should be large enough to hold @nmac Ethernet addresses, they are
 *	stored consecutively so the space needed is @nmac * 6 bytes.
 *	Returns a negative error number or the non-negative VI id.
 */
पूर्णांक t4_alloc_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक port,
		अचिन्हित पूर्णांक pf, अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक nmac, u8 *mac,
		अचिन्हित पूर्णांक *rss_size, u8 *vivld, u8 *vin)
अणु
	पूर्णांक ret;
	काष्ठा fw_vi_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) | FW_CMD_REQUEST_F |
				  FW_CMD_WRITE_F | FW_CMD_EXEC_F |
				  FW_VI_CMD_PFN_V(pf) | FW_VI_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_VI_CMD_ALLOC_F | FW_LEN16(c));
	c.portid_pkd = FW_VI_CMD_PORTID_V(port);
	c.nmac = nmac - 1;

	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	अगर (ret)
		वापस ret;

	अगर (mac) अणु
		स_नकल(mac, c.mac, माप(c.mac));
		चयन (nmac) अणु
		हाल 5:
			स_नकल(mac + 24, c.nmac3, माप(c.nmac3));
			fallthrough;
		हाल 4:
			स_नकल(mac + 18, c.nmac2, माप(c.nmac2));
			fallthrough;
		हाल 3:
			स_नकल(mac + 12, c.nmac1, माप(c.nmac1));
			fallthrough;
		हाल 2:
			स_नकल(mac + 6,  c.nmac0, माप(c.nmac0));
		पूर्ण
	पूर्ण
	अगर (rss_size)
		*rss_size = FW_VI_CMD_RSSSIZE_G(be16_to_cpu(c.rsssize_pkd));

	अगर (vivld)
		*vivld = FW_VI_CMD_VFVLD_G(be32_to_cpu(c.alloc_to_len16));

	अगर (vin)
		*vin = FW_VI_CMD_VIN_G(be32_to_cpu(c.alloc_to_len16));

	वापस FW_VI_CMD_VIID_G(be16_to_cpu(c.type_viid));
पूर्ण

/**
 *	t4_मुक्त_vi - मुक्त a भव पूर्णांकerface
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the VI
 *	@vf: the VF owning the VI
 *	@viid: भव पूर्णांकerface identअगरiler
 *
 *	Free a previously allocated भव पूर्णांकerface.
 */
पूर्णांक t4_मुक्त_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
	       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक viid)
अणु
	काष्ठा fw_vi_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_VI_CMD) |
				  FW_CMD_REQUEST_F |
				  FW_CMD_EXEC_F |
				  FW_VI_CMD_PFN_V(pf) |
				  FW_VI_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_VI_CMD_FREE_F | FW_LEN16(c));
	c.type_viid = cpu_to_be16(FW_VI_CMD_VIID_V(viid));

	वापस t4_wr_mbox(adap, mbox, &c, माप(c), &c);
पूर्ण

/**
 *	t4_set_rxmode - set Rx properties of a भव पूर्णांकerface
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@viid_mirror: the mirror VI id
 *	@mtu: the new MTU or -1
 *	@promisc: 1 to enable promiscuous mode, 0 to disable it, -1 no change
 *	@all_multi: 1 to enable all-multi mode, 0 to disable it, -1 no change
 *	@bcast: 1 to enable broadcast Rx, 0 to disable it, -1 no change
 *	@vlanex: 1 to enable HW VLAN extraction, 0 to disable it, -1 no change
 *	@sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *	Sets Rx properties of a भव पूर्णांकerface.
 */
पूर्णांक t4_set_rxmode(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		  अचिन्हित पूर्णांक viid_mirror, पूर्णांक mtu, पूर्णांक promisc, पूर्णांक all_multi,
		  पूर्णांक bcast, पूर्णांक vlanex, bool sleep_ok)
अणु
	काष्ठा fw_vi_rxmode_cmd c, c_mirror;
	पूर्णांक ret;

	/* convert to FW values */
	अगर (mtu < 0)
		mtu = FW_RXMODE_MTU_NO_CHG;
	अगर (promisc < 0)
		promisc = FW_VI_RXMODE_CMD_PROMISCEN_M;
	अगर (all_multi < 0)
		all_multi = FW_VI_RXMODE_CMD_ALLMULTIEN_M;
	अगर (bcast < 0)
		bcast = FW_VI_RXMODE_CMD_BROADCASTEN_M;
	अगर (vlanex < 0)
		vlanex = FW_VI_RXMODE_CMD_VLANEXEN_M;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_RXMODE_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_RXMODE_CMD_VIID_V(viid));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.mtu_to_vlanexen =
		cpu_to_be32(FW_VI_RXMODE_CMD_MTU_V(mtu) |
			    FW_VI_RXMODE_CMD_PROMISCEN_V(promisc) |
			    FW_VI_RXMODE_CMD_ALLMULTIEN_V(all_multi) |
			    FW_VI_RXMODE_CMD_BROADCASTEN_V(bcast) |
			    FW_VI_RXMODE_CMD_VLANEXEN_V(vlanex));

	अगर (viid_mirror) अणु
		स_नकल(&c_mirror, &c, माप(c_mirror));
		c_mirror.op_to_viid =
			cpu_to_be32(FW_CMD_OP_V(FW_VI_RXMODE_CMD) |
				    FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				    FW_VI_RXMODE_CMD_VIID_V(viid_mirror));
	पूर्ण

	ret = t4_wr_mbox_meat(adap, mbox, &c, माप(c), शून्य, sleep_ok);
	अगर (ret)
		वापस ret;

	अगर (viid_mirror)
		ret = t4_wr_mbox_meat(adap, mbox, &c_mirror, माप(c_mirror),
				      शून्य, sleep_ok);

	वापस ret;
पूर्ण

/**
 *      t4_मुक्त_encap_mac_filt - मुक्तs MPS entry at given index
 *      @adap: the adapter
 *      @viid: the VI id
 *      @idx: index of MPS entry to be मुक्तd
 *      @sleep_ok: call is allowed to sleep
 *
 *      Frees the MPS entry at supplied index
 *
 *      Returns a negative error number or zero on success
 */
पूर्णांक t4_मुक्त_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			   पूर्णांक idx, bool sleep_ok)
अणु
	काष्ठा fw_vi_mac_exact *p;
	u8 addr[] = अणु0, 0, 0, 0, 0, 0पूर्ण;
	काष्ठा fw_vi_mac_cmd c;
	पूर्णांक ret = 0;
	u32 exact;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_CMD_EXEC_V(0) |
				   FW_VI_MAC_CMD_VIID_V(viid));
	exact = FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_EXACTMAC);
	c.मुक्तmacs_to_len16 = cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(0) |
					  exact |
					  FW_CMD_LEN16_V(1));
	p = c.u.exact;
	p->valid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
				      FW_VI_MAC_CMD_IDX_V(idx));
	स_नकल(p->macaddr, addr, माप(p->macaddr));
	ret = t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, sleep_ok);
	वापस ret;
पूर्ण

/**
 *	t4_मुक्त_raw_mac_filt - Frees a raw mac entry in mps tcam
 *	@adap: the adapter
 *	@viid: the VI id
 *	@addr: the MAC address
 *	@mask: the mask
 *	@idx: index of the entry in mps tcam
 *	@lookup_type: MAC address क्रम inner (1) or outer (0) header
 *	@port_id: the port index
 *	@sleep_ok: call is allowed to sleep
 *
 *	Removes the mac entry at the specअगरied index using raw mac पूर्णांकerface.
 *
 *	Returns a negative error number on failure.
 */
पूर्णांक t4_मुक्त_raw_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			 स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक idx,
			 u8 lookup_type, u8 port_id, bool sleep_ok)
अणु
	काष्ठा fw_vi_mac_cmd c;
	काष्ठा fw_vi_mac_raw *p = &c.u.raw;
	u32 val;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_CMD_EXEC_V(0) |
				   FW_VI_MAC_CMD_VIID_V(viid));
	val = FW_CMD_LEN16_V(1) |
	      FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_RAW);
	c.मुक्तmacs_to_len16 = cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(0) |
					  FW_CMD_LEN16_V(val));

	p->raw_idx_pkd = cpu_to_be32(FW_VI_MAC_CMD_RAW_IDX_V(idx) |
				     FW_VI_MAC_ID_BASED_FREE);

	/* Lookup Type. Outer header: 0, Inner header: 1 */
	p->data0_pkd = cpu_to_be32(DATALKPTYPE_V(lookup_type) |
				   DATAPORTNUM_V(port_id));
	/* Lookup mask and port mask */
	p->data0m_pkd = cpu_to_be64(DATALKPTYPE_V(DATALKPTYPE_M) |
				    DATAPORTNUM_V(DATAPORTNUM_M));

	/* Copy the address and the mask */
	स_नकल((u8 *)&p->data1[0] + 2, addr, ETH_ALEN);
	स_नकल((u8 *)&p->data1m[0] + 2, mask, ETH_ALEN);

	वापस t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, sleep_ok);
पूर्ण

/**
 *      t4_alloc_encap_mac_filt - Adds a mac entry in mps tcam with VNI support
 *      @adap: the adapter
 *      @viid: the VI id
 *      @addr: the MAC address
 *      @mask: the mask
 *      @vni: the VNI id क्रम the tunnel protocol
 *      @vni_mask: mask क्रम the VNI id
 *      @dip_hit: to enable DIP match क्रम the MPS entry
 *      @lookup_type: MAC address क्रम inner (1) or outer (0) header
 *      @sleep_ok: call is allowed to sleep
 *
 *      Allocates an MPS entry with specअगरied MAC address and VNI value.
 *
 *      Returns a negative error number or the allocated index क्रम this mac.
 */
पूर्णांक t4_alloc_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			    स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक vni,
			    अचिन्हित पूर्णांक vni_mask, u8 dip_hit, u8 lookup_type,
			    bool sleep_ok)
अणु
	काष्ठा fw_vi_mac_cmd c;
	काष्ठा fw_vi_mac_vni *p = c.u.exact_vni;
	पूर्णांक ret = 0;
	u32 val;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_MAC_CMD_VIID_V(viid));
	val = FW_CMD_LEN16_V(1) |
	      FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_EXACTMAC_VNI);
	c.मुक्तmacs_to_len16 = cpu_to_be32(val);
	p->valid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
				      FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_ADD_MAC));
	स_नकल(p->macaddr, addr, माप(p->macaddr));
	स_नकल(p->macaddr_mask, mask, माप(p->macaddr_mask));

	p->lookup_type_to_vni =
		cpu_to_be32(FW_VI_MAC_CMD_VNI_V(vni) |
			    FW_VI_MAC_CMD_DIP_HIT_V(dip_hit) |
			    FW_VI_MAC_CMD_LOOKUP_TYPE_V(lookup_type));
	p->vni_mask_pkd = cpu_to_be32(FW_VI_MAC_CMD_VNI_MASK_V(vni_mask));
	ret = t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, sleep_ok);
	अगर (ret == 0)
		ret = FW_VI_MAC_CMD_IDX_G(be16_to_cpu(p->valid_to_idx));
	वापस ret;
पूर्ण

/**
 *	t4_alloc_raw_mac_filt - Adds a mac entry in mps tcam
 *	@adap: the adapter
 *	@viid: the VI id
 *	@addr: the MAC address
 *	@mask: the mask
 *	@idx: index at which to add this entry
 *	@lookup_type: MAC address क्रम inner (1) or outer (0) header
 *	@port_id: the port index
 *	@sleep_ok: call is allowed to sleep
 *
 *	Adds the mac entry at the specअगरied index using raw mac पूर्णांकerface.
 *
 *	Returns a negative error number or the allocated index क्रम this mac.
 */
पूर्णांक t4_alloc_raw_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			  स्थिर u8 *addr, स्थिर u8 *mask, अचिन्हित पूर्णांक idx,
			  u8 lookup_type, u8 port_id, bool sleep_ok)
अणु
	पूर्णांक ret = 0;
	काष्ठा fw_vi_mac_cmd c;
	काष्ठा fw_vi_mac_raw *p = &c.u.raw;
	u32 val;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_MAC_CMD_VIID_V(viid));
	val = FW_CMD_LEN16_V(1) |
	      FW_VI_MAC_CMD_ENTRY_TYPE_V(FW_VI_MAC_TYPE_RAW);
	c.मुक्तmacs_to_len16 = cpu_to_be32(val);

	/* Specअगरy that this is an inner mac address */
	p->raw_idx_pkd = cpu_to_be32(FW_VI_MAC_CMD_RAW_IDX_V(idx));

	/* Lookup Type. Outer header: 0, Inner header: 1 */
	p->data0_pkd = cpu_to_be32(DATALKPTYPE_V(lookup_type) |
				   DATAPORTNUM_V(port_id));
	/* Lookup mask and port mask */
	p->data0m_pkd = cpu_to_be64(DATALKPTYPE_V(DATALKPTYPE_M) |
				    DATAPORTNUM_V(DATAPORTNUM_M));

	/* Copy the address and the mask */
	स_नकल((u8 *)&p->data1[0] + 2, addr, ETH_ALEN);
	स_नकल((u8 *)&p->data1m[0] + 2, mask, ETH_ALEN);

	ret = t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, sleep_ok);
	अगर (ret == 0) अणु
		ret = FW_VI_MAC_CMD_RAW_IDX_G(be32_to_cpu(p->raw_idx_pkd));
		अगर (ret != idx)
			ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *	t4_alloc_mac_filt - allocates exact-match filters क्रम MAC addresses
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@मुक्त: अगर true any existing filters क्रम this VI id are first हटाओd
 *	@naddr: the number of MAC addresses to allocate filters क्रम (up to 7)
 *	@addr: the MAC address(es)
 *	@idx: where to store the index of each allocated filter
 *	@hash: poपूर्णांकer to hash address filter biपंचांगap
 *	@sleep_ok: call is allowed to sleep
 *
 *	Allocates an exact-match filter क्रम each of the supplied addresses and
 *	sets it to the corresponding address.  If @idx is not %शून्य it should
 *	have at least @naddr entries, each of which will be set to the index of
 *	the filter allocated क्रम the corresponding MAC address.  If a filter
 *	could not be allocated क्रम an address its index is set to 0xffff.
 *	If @hash is not %शून्य addresses that fail to allocate an exact filter
 *	are hashed and update the hash filter biपंचांगap poपूर्णांकed at by @hash.
 *
 *	Returns a negative error number or the number of filters allocated.
 */
पूर्णांक t4_alloc_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		      अचिन्हित पूर्णांक viid, bool मुक्त, अचिन्हित पूर्णांक naddr,
		      स्थिर u8 **addr, u16 *idx, u64 *hash, bool sleep_ok)
अणु
	पूर्णांक offset, ret = 0;
	काष्ठा fw_vi_mac_cmd c;
	अचिन्हित पूर्णांक nfilters = 0;
	अचिन्हित पूर्णांक max_naddr = adap->params.arch.mps_tcam_size;
	अचिन्हित पूर्णांक rem = naddr;

	अगर (naddr > max_naddr)
		वापस -EINVAL;

	क्रम (offset = 0; offset < naddr ; /**/) अणु
		अचिन्हित पूर्णांक fw_naddr = (rem < ARRAY_SIZE(c.u.exact) ?
					 rem : ARRAY_SIZE(c.u.exact));
		माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
						     u.exact[fw_naddr]), 16);
		काष्ठा fw_vi_mac_exact *p;
		पूर्णांक i;

		स_रखो(&c, 0, माप(c));
		c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
					   FW_CMD_REQUEST_F |
					   FW_CMD_WRITE_F |
					   FW_CMD_EXEC_V(मुक्त) |
					   FW_VI_MAC_CMD_VIID_V(viid));
		c.मुक्तmacs_to_len16 =
			cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(मुक्त) |
				    FW_CMD_LEN16_V(len16));

		क्रम (i = 0, p = c.u.exact; i < fw_naddr; i++, p++) अणु
			p->valid_to_idx =
				cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
					    FW_VI_MAC_CMD_IDX_V(
						    FW_VI_MAC_ADD_MAC));
			स_नकल(p->macaddr, addr[offset + i],
			       माप(p->macaddr));
		पूर्ण

		/* It's okay अगर we run out of space in our MAC address arena.
		 * Some of the addresses we submit may get stored so we need
		 * to run through the reply to see what the results were ...
		 */
		ret = t4_wr_mbox_meat(adap, mbox, &c, माप(c), &c, sleep_ok);
		अगर (ret && ret != -FW_ENOMEM)
			अवरोध;

		क्रम (i = 0, p = c.u.exact; i < fw_naddr; i++, p++) अणु
			u16 index = FW_VI_MAC_CMD_IDX_G(
					be16_to_cpu(p->valid_to_idx));

			अगर (idx)
				idx[offset + i] = (index >= max_naddr ?
						   0xffff : index);
			अगर (index < max_naddr)
				nfilters++;
			अन्यथा अगर (hash)
				*hash |= (1ULL <<
					  hash_mac_addr(addr[offset + i]));
		पूर्ण

		मुक्त = false;
		offset += fw_naddr;
		rem -= fw_naddr;
	पूर्ण

	अगर (ret == 0 || ret == -FW_ENOMEM)
		ret = nfilters;
	वापस ret;
पूर्ण

/**
 *	t4_मुक्त_mac_filt - मुक्तs exact-match filters of given MAC addresses
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@naddr: the number of MAC addresses to allocate filters क्रम (up to 7)
 *	@addr: the MAC address(es)
 *	@sleep_ok: call is allowed to sleep
 *
 *	Frees the exact-match filter क्रम each of the supplied addresses
 *
 *	Returns a negative error number or the number of filters मुक्तd.
 */
पूर्णांक t4_मुक्त_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
		     अचिन्हित पूर्णांक viid, अचिन्हित पूर्णांक naddr,
		     स्थिर u8 **addr, bool sleep_ok)
अणु
	पूर्णांक offset, ret = 0;
	काष्ठा fw_vi_mac_cmd c;
	अचिन्हित पूर्णांक nfilters = 0;
	अचिन्हित पूर्णांक max_naddr = is_t4(adap->params.chip) ?
				       NUM_MPS_CLS_SRAM_L_INSTANCES :
				       NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
	अचिन्हित पूर्णांक rem = naddr;

	अगर (naddr > max_naddr)
		वापस -EINVAL;

	क्रम (offset = 0; offset < (पूर्णांक)naddr ; /**/) अणु
		अचिन्हित पूर्णांक fw_naddr = (rem < ARRAY_SIZE(c.u.exact)
					 ? rem
					 : ARRAY_SIZE(c.u.exact));
		माप_प्रकार len16 = DIV_ROUND_UP(दुरत्व(काष्ठा fw_vi_mac_cmd,
						     u.exact[fw_naddr]), 16);
		काष्ठा fw_vi_mac_exact *p;
		पूर्णांक i;

		स_रखो(&c, 0, माप(c));
		c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_CMD_EXEC_V(0) |
				     FW_VI_MAC_CMD_VIID_V(viid));
		c.मुक्तmacs_to_len16 =
				cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(0) |
					    FW_CMD_LEN16_V(len16));

		क्रम (i = 0, p = c.u.exact; i < (पूर्णांक)fw_naddr; i++, p++) अणु
			p->valid_to_idx = cpu_to_be16(
				FW_VI_MAC_CMD_VALID_F |
				FW_VI_MAC_CMD_IDX_V(FW_VI_MAC_MAC_BASED_FREE));
			स_नकल(p->macaddr, addr[offset+i], माप(p->macaddr));
		पूर्ण

		ret = t4_wr_mbox_meat(adap, mbox, &c, माप(c), &c, sleep_ok);
		अगर (ret)
			अवरोध;

		क्रम (i = 0, p = c.u.exact; i < fw_naddr; i++, p++) अणु
			u16 index = FW_VI_MAC_CMD_IDX_G(
						be16_to_cpu(p->valid_to_idx));

			अगर (index < max_naddr)
				nfilters++;
		पूर्ण

		offset += fw_naddr;
		rem -= fw_naddr;
	पूर्ण

	अगर (ret == 0)
		ret = nfilters;
	वापस ret;
पूर्ण

/**
 *	t4_change_mac - modअगरies the exact-match filter क्रम a MAC address
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@idx: index of existing filter क्रम old value of MAC address, or -1
 *	@addr: the new MAC address value
 *	@persist: whether a new MAC allocation should be persistent
 *	@smt_idx: the destination to store the new SMT index.
 *
 *	Modअगरies an exact-match filter and sets it to the new MAC address.
 *	Note that in general it is not possible to modअगरy the value of a given
 *	filter so the generic way to modअगरy an address filter is to मुक्त the one
 *	being used by the old address value and allocate a new filter क्रम the
 *	new address value.  @idx can be -1 अगर the address is a new addition.
 *
 *	Returns a negative error number or the index of the filter with the new
 *	MAC value.
 */
पूर्णांक t4_change_mac(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		  पूर्णांक idx, स्थिर u8 *addr, bool persist, u8 *smt_idx)
अणु
	पूर्णांक ret, mode;
	काष्ठा fw_vi_mac_cmd c;
	काष्ठा fw_vi_mac_exact *p = c.u.exact;
	अचिन्हित पूर्णांक max_mac_addr = adap->params.arch.mps_tcam_size;

	अगर (idx < 0)                             /* new allocation */
		idx = persist ? FW_VI_MAC_ADD_PERSIST_MAC : FW_VI_MAC_ADD_MAC;
	mode = smt_idx ? FW_VI_MAC_SMT_AND_MPSTCAM : FW_VI_MAC_MPS_TCAM_ENTRY;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_MAC_CMD_VIID_V(viid));
	c.मुक्तmacs_to_len16 = cpu_to_be32(FW_CMD_LEN16_V(1));
	p->valid_to_idx = cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
				      FW_VI_MAC_CMD_SMAC_RESULT_V(mode) |
				      FW_VI_MAC_CMD_IDX_V(idx));
	स_नकल(p->macaddr, addr, माप(p->macaddr));

	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	अगर (ret == 0) अणु
		ret = FW_VI_MAC_CMD_IDX_G(be16_to_cpu(p->valid_to_idx));
		अगर (ret >= max_mac_addr)
			ret = -ENOMEM;
		अगर (smt_idx) अणु
			अगर (adap->params.viid_smt_extn_support) अणु
				*smt_idx = FW_VI_MAC_CMD_SMTID_G
						    (be32_to_cpu(c.op_to_viid));
			पूर्ण अन्यथा अणु
				/* In T4/T5, SMT contains 256 SMAC entries
				 * organized in 128 rows of 2 entries each.
				 * In T6, SMT contains 256 SMAC entries in
				 * 256 rows.
				 */
				अगर (CHELSIO_CHIP_VERSION(adap->params.chip) <=
								     CHELSIO_T5)
					*smt_idx = (viid & FW_VIID_VIN_M) << 1;
				अन्यथा
					*smt_idx = (viid & FW_VIID_VIN_M);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t4_set_addr_hash - program the MAC inexact-match hash filter
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@ucast: whether the hash filter should also match unicast addresses
 *	@vec: the value to be written to the hash filter
 *	@sleep_ok: call is allowed to sleep
 *
 *	Sets the 64-bit inexact-match hash filter क्रम a भव पूर्णांकerface.
 */
पूर्णांक t4_set_addr_hash(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     bool ucast, u64 vec, bool sleep_ok)
अणु
	काष्ठा fw_vi_mac_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
				   FW_VI_ENABLE_CMD_VIID_V(viid));
	c.मुक्तmacs_to_len16 = cpu_to_be32(FW_VI_MAC_CMD_HASHVECEN_F |
					  FW_VI_MAC_CMD_HASHUNIEN_V(ucast) |
					  FW_CMD_LEN16_V(1));
	c.u.hash.hashvec = cpu_to_be64(vec);
	वापस t4_wr_mbox_meat(adap, mbox, &c, माप(c), शून्य, sleep_ok);
पूर्ण

/**
 *      t4_enable_vi_params - enable/disable a भव पूर्णांकerface
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @viid: the VI id
 *      @rx_en: 1=enable Rx, 0=disable Rx
 *      @tx_en: 1=enable Tx, 0=disable Tx
 *      @dcb_en: 1=enable delivery of Data Center Bridging messages.
 *
 *      Enables/disables a भव पूर्णांकerface.  Note that setting DCB Enable
 *      only makes sense when enabling a Virtual Interface ...
 */
पूर्णांक t4_enable_vi_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			अचिन्हित पूर्णांक viid, bool rx_en, bool tx_en, bool dcb_en)
अणु
	काष्ठा fw_vi_enable_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABLE_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				   FW_VI_ENABLE_CMD_VIID_V(viid));
	c.ien_to_len16 = cpu_to_be32(FW_VI_ENABLE_CMD_IEN_V(rx_en) |
				     FW_VI_ENABLE_CMD_EEN_V(tx_en) |
				     FW_VI_ENABLE_CMD_DCB_INFO_V(dcb_en) |
				     FW_LEN16(c));
	वापस t4_wr_mbox_ns(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_enable_vi - enable/disable a भव पूर्णांकerface
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@rx_en: 1=enable Rx, 0=disable Rx
 *	@tx_en: 1=enable Tx, 0=disable Tx
 *
 *	Enables/disables a भव पूर्णांकerface.
 */
पूर्णांक t4_enable_vi(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		 bool rx_en, bool tx_en)
अणु
	वापस t4_enable_vi_params(adap, mbox, viid, rx_en, tx_en, 0);
पूर्ण

/**
 *	t4_enable_pi_params - enable/disable a Port's Virtual Interface
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @pi: the Port Inक्रमmation काष्ठाure
 *      @rx_en: 1=enable Rx, 0=disable Rx
 *      @tx_en: 1=enable Tx, 0=disable Tx
 *      @dcb_en: 1=enable delivery of Data Center Bridging messages.
 *
 *      Enables/disables a Port's Virtual Interface.  Note that setting DCB
 *	Enable only makes sense when enabling a Virtual Interface ...
 *	If the Virtual Interface enable/disable operation is successful,
 *	we notअगरy the OS-specअगरic code of a potential Link Status change
 *	via the OS Contract API t4_os_link_changed().
 */
पूर्णांक t4_enable_pi_params(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox,
			काष्ठा port_info *pi,
			bool rx_en, bool tx_en, bool dcb_en)
अणु
	पूर्णांक ret = t4_enable_vi_params(adap, mbox, pi->viid,
				      rx_en, tx_en, dcb_en);
	अगर (ret)
		वापस ret;
	t4_os_link_changed(adap, pi->port_id,
			   rx_en && tx_en && pi->link_cfg.link_ok);
	वापस 0;
पूर्ण

/**
 *	t4_identअगरy_port - identअगरy a VI's port by blinking its LED
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@viid: the VI id
 *	@nblinks: how many बार to blink LED at 2.5 Hz
 *
 *	Identअगरies a VI's port by blinking its LED.
 */
पूर्णांक t4_identअगरy_port(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक viid,
		     अचिन्हित पूर्णांक nblinks)
अणु
	काष्ठा fw_vi_enable_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABLE_CMD) |
				   FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				   FW_VI_ENABLE_CMD_VIID_V(viid));
	c.ien_to_len16 = cpu_to_be32(FW_VI_ENABLE_CMD_LED_F | FW_LEN16(c));
	c.blinkdur = cpu_to_be16(nblinks);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_iq_stop - stop an ingress queue and its FLs
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the queues
 *	@vf: the VF owning the queues
 *	@iqtype: the ingress queue type (FW_IQ_TYPE_FL_INT_CAP, etc.)
 *	@iqid: ingress queue id
 *	@fl0id: FL0 queue id or 0xffff अगर no attached FL0
 *	@fl1id: FL1 queue id or 0xffff अगर no attached FL1
 *
 *	Stops an ingress queue and its associated FLs, अगर any.  This causes
 *	any current or future data/messages destined क्रम these queues to be
 *	tossed.
 */
पूर्णांक t4_iq_stop(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
	       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक iqtype, अचिन्हित पूर्णांक iqid,
	       अचिन्हित पूर्णांक fl0id, अचिन्हित पूर्णांक fl1id)
अणु
	काष्ठा fw_iq_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) | FW_CMD_REQUEST_F |
				  FW_CMD_EXEC_F | FW_IQ_CMD_PFN_V(pf) |
				  FW_IQ_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_IQ_CMD_IQSTOP_F | FW_LEN16(c));
	c.type_to_iqandstindex = cpu_to_be32(FW_IQ_CMD_TYPE_V(iqtype));
	c.iqid = cpu_to_be16(iqid);
	c.fl0id = cpu_to_be16(fl0id);
	c.fl1id = cpu_to_be16(fl1id);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_iq_मुक्त - मुक्त an ingress queue and its FLs
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the queues
 *	@vf: the VF owning the queues
 *	@iqtype: the ingress queue type
 *	@iqid: ingress queue id
 *	@fl0id: FL0 queue id or 0xffff अगर no attached FL0
 *	@fl1id: FL1 queue id or 0xffff अगर no attached FL1
 *
 *	Frees an ingress queue and its associated FLs, अगर any.
 */
पूर्णांक t4_iq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
	       अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक iqtype, अचिन्हित पूर्णांक iqid,
	       अचिन्हित पूर्णांक fl0id, अचिन्हित पूर्णांक fl1id)
अणु
	काष्ठा fw_iq_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) | FW_CMD_REQUEST_F |
				  FW_CMD_EXEC_F | FW_IQ_CMD_PFN_V(pf) |
				  FW_IQ_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_IQ_CMD_FREE_F | FW_LEN16(c));
	c.type_to_iqandstindex = cpu_to_be32(FW_IQ_CMD_TYPE_V(iqtype));
	c.iqid = cpu_to_be16(iqid);
	c.fl0id = cpu_to_be16(fl0id);
	c.fl1id = cpu_to_be16(fl1id);
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_eth_eq_मुक्त - मुक्त an Ethernet egress queue
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the queue
 *	@vf: the VF owning the queue
 *	@eqid: egress queue id
 *
 *	Frees an Ethernet egress queue.
 */
पूर्णांक t4_eth_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		   अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid)
अणु
	काष्ठा fw_eq_eth_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_ETH_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				  FW_EQ_ETH_CMD_PFN_V(pf) |
				  FW_EQ_ETH_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_EQ_ETH_CMD_FREE_F | FW_LEN16(c));
	c.eqid_pkd = cpu_to_be32(FW_EQ_ETH_CMD_EQID_V(eqid));
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_ctrl_eq_मुक्त - मुक्त a control egress queue
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the queue
 *	@vf: the VF owning the queue
 *	@eqid: egress queue id
 *
 *	Frees a control egress queue.
 */
पूर्णांक t4_ctrl_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid)
अणु
	काष्ठा fw_eq_ctrl_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_CTRL_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				  FW_EQ_CTRL_CMD_PFN_V(pf) |
				  FW_EQ_CTRL_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_EQ_CTRL_CMD_FREE_F | FW_LEN16(c));
	c.cmpliqid_eqid = cpu_to_be32(FW_EQ_CTRL_CMD_EQID_V(eqid));
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_ofld_eq_मुक्त - मुक्त an offload egress queue
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@pf: the PF owning the queue
 *	@vf: the VF owning the queue
 *	@eqid: egress queue id
 *
 *	Frees a control egress queue.
 */
पूर्णांक t4_ofld_eq_मुक्त(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक pf,
		    अचिन्हित पूर्णांक vf, अचिन्हित पूर्णांक eqid)
अणु
	काष्ठा fw_eq_ofld_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_OFLD_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_EXEC_F |
				  FW_EQ_OFLD_CMD_PFN_V(pf) |
				  FW_EQ_OFLD_CMD_VFN_V(vf));
	c.alloc_to_len16 = cpu_to_be32(FW_EQ_OFLD_CMD_FREE_F | FW_LEN16(c));
	c.eqid_pkd = cpu_to_be32(FW_EQ_OFLD_CMD_EQID_V(eqid));
	वापस t4_wr_mbox(adap, mbox, &c, माप(c), शून्य);
पूर्ण

/**
 *	t4_link_करोwn_rc_str - वापस a string क्रम a Link Down Reason Code
 *	@link_करोwn_rc: Link Down Reason Code
 *
 *	Returns a string representation of the Link Down Reason Code.
 */
अटल स्थिर अक्षर *t4_link_करोwn_rc_str(अचिन्हित अक्षर link_करोwn_rc)
अणु
	अटल स्थिर अक्षर * स्थिर reason[] = अणु
		"Link Down",
		"Remote Fault",
		"Auto-negotiation Failure",
		"Reserved",
		"Insufficient Airflow",
		"Unable To Determine Reason",
		"No RX Signal Detected",
		"Reserved",
	पूर्ण;

	अगर (link_करोwn_rc >= ARRAY_SIZE(reason))
		वापस "Bad Reason Code";

	वापस reason[link_करोwn_rc];
पूर्ण

/* Return the highest speed set in the port capabilities, in Mb/s. */
अटल अचिन्हित पूर्णांक fwcap_to_speed(fw_port_cap32_t caps)
अणु
	#घोषणा TEST_SPEED_RETURN(__caps_speed, __speed) \
		करो अणु \
			अगर (caps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				वापस __speed; \
		पूर्ण जबतक (0)

	TEST_SPEED_RETURN(400G, 400000);
	TEST_SPEED_RETURN(200G, 200000);
	TEST_SPEED_RETURN(100G, 100000);
	TEST_SPEED_RETURN(50G,   50000);
	TEST_SPEED_RETURN(40G,   40000);
	TEST_SPEED_RETURN(25G,   25000);
	TEST_SPEED_RETURN(10G,   10000);
	TEST_SPEED_RETURN(1G,     1000);
	TEST_SPEED_RETURN(100M,    100);

	#अघोषित TEST_SPEED_RETURN

	वापस 0;
पूर्ण

/**
 *	fwcap_to_fwspeed - वापस highest speed in Port Capabilities
 *	@acaps: advertised Port Capabilities
 *
 *	Get the highest speed क्रम the port from the advertised Port
 *	Capabilities.  It will be either the highest speed from the list of
 *	speeds or whatever user has set using ethtool.
 */
अटल fw_port_cap32_t fwcap_to_fwspeed(fw_port_cap32_t acaps)
अणु
	#घोषणा TEST_SPEED_RETURN(__caps_speed) \
		करो अणु \
			अगर (acaps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				वापस FW_PORT_CAP32_SPEED_##__caps_speed; \
		पूर्ण जबतक (0)

	TEST_SPEED_RETURN(400G);
	TEST_SPEED_RETURN(200G);
	TEST_SPEED_RETURN(100G);
	TEST_SPEED_RETURN(50G);
	TEST_SPEED_RETURN(40G);
	TEST_SPEED_RETURN(25G);
	TEST_SPEED_RETURN(10G);
	TEST_SPEED_RETURN(1G);
	TEST_SPEED_RETURN(100M);

	#अघोषित TEST_SPEED_RETURN

	वापस 0;
पूर्ण

/**
 *	lstatus_to_fwcap - translate old lstatus to 32-bit Port Capabilities
 *	@lstatus: old FW_PORT_ACTION_GET_PORT_INFO lstatus value
 *
 *	Translates old FW_PORT_ACTION_GET_PORT_INFO lstatus field पूर्णांकo new
 *	32-bit Port Capabilities value.
 */
अटल fw_port_cap32_t lstatus_to_fwcap(u32 lstatus)
अणु
	fw_port_cap32_t linkattr = 0;

	/* Unक्रमtunately the क्रमmat of the Link Status in the old
	 * 16-bit Port Inक्रमmation message isn't the same as the
	 * 16-bit Port Capabilities bitfield used everywhere अन्यथा ...
	 */
	अगर (lstatus & FW_PORT_CMD_RXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_RX;
	अगर (lstatus & FW_PORT_CMD_TXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_TX;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100M))
		linkattr |= FW_PORT_CAP32_SPEED_100M;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_1G))
		linkattr |= FW_PORT_CAP32_SPEED_1G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_10G))
		linkattr |= FW_PORT_CAP32_SPEED_10G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_25G))
		linkattr |= FW_PORT_CAP32_SPEED_25G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_40G))
		linkattr |= FW_PORT_CAP32_SPEED_40G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100G))
		linkattr |= FW_PORT_CAP32_SPEED_100G;

	वापस linkattr;
पूर्ण

/**
 *	t4_handle_get_port_info - process a FW reply message
 *	@pi: the port info
 *	@rpl: start of the FW message
 *
 *	Processes a GET_PORT_INFO FW reply message.
 */
व्योम t4_handle_get_port_info(काष्ठा port_info *pi, स्थिर __be64 *rpl)
अणु
	स्थिर काष्ठा fw_port_cmd *cmd = (स्थिर व्योम *)rpl;
	fw_port_cap32_t pcaps, acaps, lpacaps, linkattr;
	काष्ठा link_config *lc = &pi->link_cfg;
	काष्ठा adapter *adapter = pi->adapter;
	अचिन्हित पूर्णांक speed, fc, fec, adv_fc;
	क्रमागत fw_port_module_type mod_type;
	पूर्णांक action, link_ok, linkdnrc;
	क्रमागत fw_port_type port_type;

	/* Extract the various fields from the Port Inक्रमmation message.
	 */
	action = FW_PORT_CMD_ACTION_G(be32_to_cpu(cmd->action_to_len16));
	चयन (action) अणु
	हाल FW_PORT_ACTION_GET_PORT_INFO: अणु
		u32 lstatus = be32_to_cpu(cmd->u.info.lstatus_to_modtype);

		link_ok = (lstatus & FW_PORT_CMD_LSTATUS_F) != 0;
		linkdnrc = FW_PORT_CMD_LINKDNRC_G(lstatus);
		port_type = FW_PORT_CMD_PTYPE_G(lstatus);
		mod_type = FW_PORT_CMD_MODTYPE_G(lstatus);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.acap));
		lpacaps = fwcaps16_to_caps32(be16_to_cpu(cmd->u.info.lpacap));
		linkattr = lstatus_to_fwcap(lstatus);
		अवरोध;
	पूर्ण

	हाल FW_PORT_ACTION_GET_PORT_INFO32: अणु
		u32 lstatus32;

		lstatus32 = be32_to_cpu(cmd->u.info32.lstatus32_to_cbllen32);
		link_ok = (lstatus32 & FW_PORT_CMD_LSTATUS32_F) != 0;
		linkdnrc = FW_PORT_CMD_LINKDNRC32_G(lstatus32);
		port_type = FW_PORT_CMD_PORTTYPE32_G(lstatus32);
		mod_type = FW_PORT_CMD_MODTYPE32_G(lstatus32);
		pcaps = be32_to_cpu(cmd->u.info32.pcaps32);
		acaps = be32_to_cpu(cmd->u.info32.acaps32);
		lpacaps = be32_to_cpu(cmd->u.info32.lpacaps32);
		linkattr = be32_to_cpu(cmd->u.info32.linkattr32);
		अवरोध;
	पूर्ण

	शेष:
		dev_err(adapter->pdev_dev, "Handle Port Information: Bad Command/Action %#x\n",
			be32_to_cpu(cmd->action_to_len16));
		वापस;
	पूर्ण

	fec = fwcap_to_cc_fec(acaps);
	adv_fc = fwcap_to_cc_छोड़ो(acaps);
	fc = fwcap_to_cc_छोड़ो(linkattr);
	speed = fwcap_to_speed(linkattr);

	/* Reset state क्रम communicating new Transceiver Module status and
	 * whether the OS-dependent layer wants us to reकरो the current
	 * "sticky" L1 Configure Link Parameters.
	 */
	lc->new_module = false;
	lc->reकरो_l1cfg = false;

	अगर (mod_type != pi->mod_type) अणु
		/* With the newer SFP28 and QSFP28 Transceiver Module Types,
		 * various fundamental Port Capabilities which used to be
		 * immutable can now change radically.  We can now have
		 * Speeds, Auto-Negotiation, Forward Error Correction, etc.
		 * all change based on what Transceiver Module is inserted.
		 * So we need to record the Physical "Port" Capabilities on
		 * every Transceiver Module change.
		 */
		lc->pcaps = pcaps;

		/* When a new Transceiver Module is inserted, the Firmware
		 * will examine its i2c EPROM to determine its type and
		 * general operating parameters including things like Forward
		 * Error Control, etc.  Various IEEE 802.3 standards dictate
		 * how to पूर्णांकerpret these i2c values to determine शेष
		 * "sutomatic" settings.  We record these क्रम future use when
		 * the user explicitly requests these standards-based values.
		 */
		lc->def_acaps = acaps;

		/* Some versions of the early T6 Firmware "cheated" when
		 * handling dअगरferent Transceiver Modules by changing the
		 * underlaying Port Type reported to the Host Drivers.  As
		 * such we need to capture whatever Port Type the Firmware
		 * sends us and record it in हाल it's dअगरferent from what we
		 * were told earlier.  Unक्रमtunately, since Firmware is
		 * क्रमever, we'll need to keep this code here क्रमever, but in
		 * later T6 Firmware it should just be an assignment of the
		 * same value alपढ़ोy recorded.
		 */
		pi->port_type = port_type;

		/* Record new Module Type inक्रमmation.
		 */
		pi->mod_type = mod_type;

		/* Let the OS-dependent layer know अगर we have a new
		 * Transceiver Module inserted.
		 */
		lc->new_module = t4_is_inserted_mod_type(mod_type);

		t4_os_porपंचांगod_changed(adapter, pi->port_id);
	पूर्ण

	अगर (link_ok != lc->link_ok || speed != lc->speed ||
	    fc != lc->fc || adv_fc != lc->advertised_fc ||
	    fec != lc->fec) अणु
		/* something changed */
		अगर (!link_ok && lc->link_ok) अणु
			lc->link_करोwn_rc = linkdnrc;
			dev_warn_ratelimited(adapter->pdev_dev,
					     "Port %d link down, reason: %s\n",
					     pi->tx_chan,
					     t4_link_करोwn_rc_str(linkdnrc));
		पूर्ण
		lc->link_ok = link_ok;
		lc->speed = speed;
		lc->advertised_fc = adv_fc;
		lc->fc = fc;
		lc->fec = fec;

		lc->lpacaps = lpacaps;
		lc->acaps = acaps & ADVERT_MASK;

		/* If we're not physically capable of Auto-Negotiation, note
		 * this as Auto-Negotiation disabled.  Otherwise, we track
		 * what Auto-Negotiation settings we have.  Note parallel
		 * काष्ठाure in t4_link_l1cfg_core() and init_link_config().
		 */
		अगर (!(lc->acaps & FW_PORT_CAP32_ANEG)) अणु
			lc->स्वतःneg = AUTONEG_DISABLE;
		पूर्ण अन्यथा अगर (lc->acaps & FW_PORT_CAP32_ANEG) अणु
			lc->स्वतःneg = AUTONEG_ENABLE;
		पूर्ण अन्यथा अणु
			/* When Autoneg is disabled, user needs to set
			 * single speed.
			 * Similar to cxgb4_ethtool.c: set_link_ksettings
			 */
			lc->acaps = 0;
			lc->speed_caps = fwcap_to_fwspeed(acaps);
			lc->स्वतःneg = AUTONEG_DISABLE;
		पूर्ण

		t4_os_link_changed(adapter, pi->port_id, link_ok);
	पूर्ण

	/* If we have a new Transceiver Module and the OS-dependent code has
	 * told us that it wants us to reकरो whatever "sticky" L1 Configuration
	 * Link Parameters are set, करो that now.
	 */
	अगर (lc->new_module && lc->reकरो_l1cfg) अणु
		काष्ठा link_config old_lc;
		पूर्णांक ret;

		/* Save the current L1 Configuration and restore it अगर an
		 * error occurs.  We probably should fix the l1_cfg*()
		 * routines not to change the link_config when an error
		 * occurs ...
		 */
		old_lc = *lc;
		ret = t4_link_l1cfg_ns(adapter, adapter->mbox, pi->lport, lc);
		अगर (ret) अणु
			*lc = old_lc;
			dev_warn(adapter->pdev_dev,
				 "Attempt to update new Transceiver Module settings failed\n");
		पूर्ण
	पूर्ण
	lc->new_module = false;
	lc->reकरो_l1cfg = false;
पूर्ण

/**
 *	t4_update_port_info - retrieve and update port inक्रमmation अगर changed
 *	@pi: the port_info
 *
 *	We issue a Get Port Inक्रमmation Command to the Firmware and, अगर
 *	successful, we check to see अगर anything is dअगरferent from what we
 *	last recorded and update things accordingly.
 */
पूर्णांक t4_update_port_info(काष्ठा port_info *pi)
अणु
	अचिन्हित पूर्णांक fw_caps = pi->adapter->params.fw_caps_support;
	काष्ठा fw_port_cmd port_cmd;
	पूर्णांक ret;

	स_रखो(&port_cmd, 0, माप(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F | FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->tx_chan));
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_PORT_ACTION_GET_PORT_INFO
				     : FW_PORT_ACTION_GET_PORT_INFO32) |
		FW_LEN16(port_cmd));
	ret = t4_wr_mbox(pi->adapter, pi->adapter->mbox,
			 &port_cmd, माप(port_cmd), &port_cmd);
	अगर (ret)
		वापस ret;

	t4_handle_get_port_info(pi, (__be64 *)&port_cmd);
	वापस 0;
पूर्ण

/**
 *	t4_get_link_params - retrieve basic link parameters क्रम given port
 *	@pi: the port
 *	@link_okp: value वापस poपूर्णांकer क्रम link up/करोwn
 *	@speedp: value वापस poपूर्णांकer क्रम speed (Mb/s)
 *	@mtup: value वापस poपूर्णांकer क्रम mtu
 *
 *	Retrieves basic link parameters क्रम a port: link up/करोwn, speed (Mb/s),
 *	and MTU क्रम a specअगरied port.  A negative error is वापसed on
 *	failure; 0 on success.
 */
पूर्णांक t4_get_link_params(काष्ठा port_info *pi, अचिन्हित पूर्णांक *link_okp,
		       अचिन्हित पूर्णांक *speedp, अचिन्हित पूर्णांक *mtup)
अणु
	अचिन्हित पूर्णांक fw_caps = pi->adapter->params.fw_caps_support;
	अचिन्हित पूर्णांक action, link_ok, mtu;
	काष्ठा fw_port_cmd port_cmd;
	fw_port_cap32_t linkattr;
	पूर्णांक ret;

	स_रखो(&port_cmd, 0, माप(port_cmd));
	port_cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
					    FW_CMD_REQUEST_F | FW_CMD_READ_F |
					    FW_PORT_CMD_PORTID_V(pi->tx_chan));
	action = (fw_caps == FW_CAPS16
		  ? FW_PORT_ACTION_GET_PORT_INFO
		  : FW_PORT_ACTION_GET_PORT_INFO32);
	port_cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(action) |
		FW_LEN16(port_cmd));
	ret = t4_wr_mbox(pi->adapter, pi->adapter->mbox,
			 &port_cmd, माप(port_cmd), &port_cmd);
	अगर (ret)
		वापस ret;

	अगर (action == FW_PORT_ACTION_GET_PORT_INFO) अणु
		u32 lstatus = be32_to_cpu(port_cmd.u.info.lstatus_to_modtype);

		link_ok = !!(lstatus & FW_PORT_CMD_LSTATUS_F);
		linkattr = lstatus_to_fwcap(lstatus);
		mtu = be16_to_cpu(port_cmd.u.info.mtu);
	पूर्ण अन्यथा अणु
		u32 lstatus32 =
			   be32_to_cpu(port_cmd.u.info32.lstatus32_to_cbllen32);

		link_ok = !!(lstatus32 & FW_PORT_CMD_LSTATUS32_F);
		linkattr = be32_to_cpu(port_cmd.u.info32.linkattr32);
		mtu = FW_PORT_CMD_MTU32_G(
			be32_to_cpu(port_cmd.u.info32.auxlinfo32_mtu32));
	पूर्ण

	अगर (link_okp)
		*link_okp = link_ok;
	अगर (speedp)
		*speedp = fwcap_to_speed(linkattr);
	अगर (mtup)
		*mtup = mtu;

	वापस 0;
पूर्ण

/**
 *      t4_handle_fw_rpl - process a FW reply message
 *      @adap: the adapter
 *      @rpl: start of the FW message
 *
 *      Processes a FW message, such as link state change messages.
 */
पूर्णांक t4_handle_fw_rpl(काष्ठा adapter *adap, स्थिर __be64 *rpl)
अणु
	u8 opcode = *(स्थिर u8 *)rpl;

	/* This might be a port command ... this simplअगरies the following
	 * conditionals ...  We can get away with pre-dereferencing
	 * action_to_len16 because it's in the first 16 bytes and all messages
	 * will be at least that दीर्घ.
	 */
	स्थिर काष्ठा fw_port_cmd *p = (स्थिर व्योम *)rpl;
	अचिन्हित पूर्णांक action =
		FW_PORT_CMD_ACTION_G(be32_to_cpu(p->action_to_len16));

	अगर (opcode == FW_PORT_CMD &&
	    (action == FW_PORT_ACTION_GET_PORT_INFO ||
	     action == FW_PORT_ACTION_GET_PORT_INFO32)) अणु
		पूर्णांक i;
		पूर्णांक chan = FW_PORT_CMD_PORTID_G(be32_to_cpu(p->op_to_portid));
		काष्ठा port_info *pi = शून्य;

		क्रम_each_port(adap, i) अणु
			pi = adap2pinfo(adap, i);
			अगर (pi->tx_chan == chan)
				अवरोध;
		पूर्ण

		t4_handle_get_port_info(pi, rpl);
	पूर्ण अन्यथा अणु
		dev_warn(adap->pdev_dev, "Unknown firmware reply %d\n",
			 opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_pci_mode(काष्ठा adapter *adapter, काष्ठा pci_params *p)
अणु
	u16 val;

	अगर (pci_is_pcie(adapter->pdev)) अणु
		pcie_capability_पढ़ो_word(adapter->pdev, PCI_EXP_LNKSTA, &val);
		p->speed = val & PCI_EXP_LNKSTA_CLS;
		p->width = (val & PCI_EXP_LNKSTA_NLW) >> 4;
	पूर्ण
पूर्ण

/**
 *	init_link_config - initialize a link's SW state
 *	@lc: poपूर्णांकer to काष्ठाure holding the link state
 *	@pcaps: link Port Capabilities
 *	@acaps: link current Advertised Port Capabilities
 *
 *	Initializes the SW state मुख्यtained क्रम each link, including the link's
 *	capabilities and शेष speed/flow-control/स्वतःnegotiation settings.
 */
अटल व्योम init_link_config(काष्ठा link_config *lc, fw_port_cap32_t pcaps,
			     fw_port_cap32_t acaps)
अणु
	lc->pcaps = pcaps;
	lc->def_acaps = acaps;
	lc->lpacaps = 0;
	lc->speed_caps = 0;
	lc->speed = 0;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;

	/* For Forward Error Control, we शेष to whatever the Firmware
	 * tells us the Link is currently advertising.
	 */
	lc->requested_fec = FEC_AUTO;
	lc->fec = fwcap_to_cc_fec(lc->def_acaps);

	/* If the Port is capable of Auto-Negtotiation, initialize it as
	 * "enabled" and copy over all of the Physical Port Capabilities
	 * to the Advertised Port Capabilities.  Otherwise mark it as
	 * Auto-Negotiate disabled and select the highest supported speed
	 * क्रम the link.  Note parallel काष्ठाure in t4_link_l1cfg_core()
	 * and t4_handle_get_port_info().
	 */
	अगर (lc->pcaps & FW_PORT_CAP32_ANEG) अणु
		lc->acaps = lc->pcaps & ADVERT_MASK;
		lc->स्वतःneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	पूर्ण अन्यथा अणु
		lc->acaps = 0;
		lc->स्वतःneg = AUTONEG_DISABLE;
		lc->speed_caps = fwcap_to_fwspeed(acaps);
	पूर्ण
पूर्ण

#घोषणा CIM_PF_NOACCESS 0xeeeeeeee

पूर्णांक t4_रुको_dev_पढ़ोy(व्योम __iomem *regs)
अणु
	u32 whoami;

	whoami = पढ़ोl(regs + PL_WHOAMI_A);
	अगर (whoami != 0xffffffff && whoami != CIM_PF_NOACCESS)
		वापस 0;

	msleep(500);
	whoami = पढ़ोl(regs + PL_WHOAMI_A);
	वापस (whoami != 0xffffffff && whoami != CIM_PF_NOACCESS ? 0 : -EIO);
पूर्ण

काष्ठा flash_desc अणु
	u32 venकरोr_and_model_id;
	u32 size_mb;
पूर्ण;

अटल पूर्णांक t4_get_flash_params(काष्ठा adapter *adap)
अणु
	/* Table क्रम non-Numonix supported flash parts.  Numonix parts are left
	 * to the preexisting code.  All flash parts have 64KB sectors.
	 */
	अटल काष्ठा flash_desc supported_flash[] = अणु
		अणु 0x150201, 4 << 20 पूर्ण,       /* Spansion 4MB S25FL032P */
	पूर्ण;

	अचिन्हित पूर्णांक part, manufacturer;
	अचिन्हित पूर्णांक density, size = 0;
	u32 flashid = 0;
	पूर्णांक ret;

	/* Issue a Read ID Command to the Flash part.  We decode supported
	 * Flash parts and their sizes from this.  There's a newer Query
	 * Command which can retrieve detailed geometry inक्रमmation but many
	 * Flash parts करोn't support it.
	 */

	ret = sf1_ग_लिखो(adap, 1, 1, 0, SF_RD_ID);
	अगर (!ret)
		ret = sf1_पढ़ो(adap, 3, 0, 1, &flashid);
	t4_ग_लिखो_reg(adap, SF_OP_A, 0);                    /* unlock SF */
	अगर (ret)
		वापस ret;

	/* Check to see अगर it's one of our non-standard supported Flash parts.
	 */
	क्रम (part = 0; part < ARRAY_SIZE(supported_flash); part++)
		अगर (supported_flash[part].venकरोr_and_model_id == flashid) अणु
			adap->params.sf_size = supported_flash[part].size_mb;
			adap->params.sf_nsec =
				adap->params.sf_size / SF_SEC_SIZE;
			जाओ found;
		पूर्ण

	/* Decode Flash part size.  The code below looks repetitive with
	 * common encodings, but that's not guaranteed in the JEDEC
	 * specअगरication क्रम the Read JEDEC ID command.  The only thing that
	 * we're guaranteed by the JEDEC specअगरication is where the
	 * Manufacturer ID is in the वापसed result.  After that each
	 * Manufacturer ~could~ encode things completely dअगरferently.
	 * Note, all Flash parts must have 64KB sectors.
	 */
	manufacturer = flashid & 0xff;
	चयन (manufacturer) अणु
	हाल 0x20: अणु /* Micron/Numonix */
		/* This Density -> Size decoding table is taken from Micron
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x14: /* 1MB */
			size = 1 << 20;
			अवरोध;
		हाल 0x15: /* 2MB */
			size = 1 << 21;
			अवरोध;
		हाल 0x16: /* 4MB */
			size = 1 << 22;
			अवरोध;
		हाल 0x17: /* 8MB */
			size = 1 << 23;
			अवरोध;
		हाल 0x18: /* 16MB */
			size = 1 << 24;
			अवरोध;
		हाल 0x19: /* 32MB */
			size = 1 << 25;
			अवरोध;
		हाल 0x20: /* 64MB */
			size = 1 << 26;
			अवरोध;
		हाल 0x21: /* 128MB */
			size = 1 << 27;
			अवरोध;
		हाल 0x22: /* 256MB */
			size = 1 << 28;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 0x9d: अणु /* ISSI -- Integrated Silicon Solution, Inc. */
		/* This Density -> Size decoding table is taken from ISSI
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x16: /* 32 MB */
			size = 1 << 25;
			अवरोध;
		हाल 0x17: /* 64MB */
			size = 1 << 26;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 0xc2: अणु /* Macronix */
		/* This Density -> Size decoding table is taken from Macronix
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x17: /* 8MB */
			size = 1 << 23;
			अवरोध;
		हाल 0x18: /* 16MB */
			size = 1 << 24;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 0xef: अणु /* Winbond */
		/* This Density -> Size decoding table is taken from Winbond
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x17: /* 8MB */
			size = 1 << 23;
			अवरोध;
		हाल 0x18: /* 16MB */
			size = 1 << 24;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण

	/* If we didn't recognize the FLASH part, that's no real issue: the
	 * Hardware/Software contract says that Hardware will _*ALWAYS*_
	 * use a FLASH part which is at least 4MB in size and has 64KB
	 * sectors.  The unrecognized FLASH part is likely to be much larger
	 * than 4MB, but that's all we really need.
	 */
	अगर (size == 0) अणु
		dev_warn(adap->pdev_dev, "Unknown Flash Part, ID = %#x, assuming 4MB\n",
			 flashid);
		size = 1 << 22;
	पूर्ण

	/* Store decoded Flash size and fall through पूर्णांकo vetting code. */
	adap->params.sf_size = size;
	adap->params.sf_nsec = size / SF_SEC_SIZE;

found:
	अगर (adap->params.sf_size < FLASH_MIN_SIZE)
		dev_warn(adap->pdev_dev, "WARNING: Flash Part ID %#x, size %#x < %#x\n",
			 flashid, adap->params.sf_size, FLASH_MIN_SIZE);
	वापस 0;
पूर्ण

/**
 *	t4_prep_adapter - prepare SW and HW क्रम operation
 *	@adapter: the adapter
 *
 *	Initialize adapter SW state क्रम the various HW modules, set initial
 *	values क्रम some adapter tunables, take PHYs out of reset, and
 *	initialize the MDIO पूर्णांकerface.
 */
पूर्णांक t4_prep_adapter(काष्ठा adapter *adapter)
अणु
	पूर्णांक ret, ver;
	uपूर्णांक16_t device_id;
	u32 pl_rev;

	get_pci_mode(adapter, &adapter->params.pci);
	pl_rev = REV_G(t4_पढ़ो_reg(adapter, PL_REV_A));

	ret = t4_get_flash_params(adapter);
	अगर (ret < 0) अणु
		dev_err(adapter->pdev_dev, "error %d identifying flash\n", ret);
		वापस ret;
	पूर्ण

	/* Retrieve adapter's device ID
	 */
	pci_पढ़ो_config_word(adapter->pdev, PCI_DEVICE_ID, &device_id);
	ver = device_id >> 12;
	adapter->params.chip = 0;
	चयन (ver) अणु
	हाल CHELSIO_T4:
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T4, pl_rev);
		adapter->params.arch.sge_fl_db = DBPRIO_F;
		adapter->params.arch.mps_tcam_size =
				 NUM_MPS_CLS_SRAM_L_INSTANCES;
		adapter->params.arch.mps_rplc_size = 128;
		adapter->params.arch.nchan = NCHAN;
		adapter->params.arch.pm_stats_cnt = PM_NSTATS;
		adapter->params.arch.vfcount = 128;
		/* Congestion map is क्रम 4 channels so that
		 * MPS can have 4 priority per port.
		 */
		adapter->params.arch.cng_ch_bits_log = 2;
		अवरोध;
	हाल CHELSIO_T5:
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T5, pl_rev);
		adapter->params.arch.sge_fl_db = DBPRIO_F | DBTYPE_F;
		adapter->params.arch.mps_tcam_size =
				 NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
		adapter->params.arch.mps_rplc_size = 128;
		adapter->params.arch.nchan = NCHAN;
		adapter->params.arch.pm_stats_cnt = PM_NSTATS;
		adapter->params.arch.vfcount = 128;
		adapter->params.arch.cng_ch_bits_log = 2;
		अवरोध;
	हाल CHELSIO_T6:
		adapter->params.chip |= CHELSIO_CHIP_CODE(CHELSIO_T6, pl_rev);
		adapter->params.arch.sge_fl_db = 0;
		adapter->params.arch.mps_tcam_size =
				 NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
		adapter->params.arch.mps_rplc_size = 256;
		adapter->params.arch.nchan = 2;
		adapter->params.arch.pm_stats_cnt = T6_PM_NSTATS;
		adapter->params.arch.vfcount = 256;
		/* Congestion map will be क्रम 2 channels so that
		 * MPS can have 8 priority per port.
		 */
		adapter->params.arch.cng_ch_bits_log = 3;
		अवरोध;
	शेष:
		dev_err(adapter->pdev_dev, "Device %d is not supported\n",
			device_id);
		वापस -EINVAL;
	पूर्ण

	adapter->params.cim_la_size = CIMLA_SIZE;
	init_cong_ctrl(adapter->params.a_wnd, adapter->params.b_wnd);

	/*
	 * Default port क्रम debugging in हाल we can't reach FW.
	 */
	adapter->params.nports = 1;
	adapter->params.portvec = 1;
	adapter->params.vpd.cclk = 50000;

	/* Set PCIe completion समयout to 4 seconds. */
	pcie_capability_clear_and_set_word(adapter->pdev, PCI_EXP_DEVCTL2,
					   PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0xd);
	वापस 0;
पूर्ण

/**
 *	t4_shutकरोwn_adapter - shut करोwn adapter, host & wire
 *	@adapter: the adapter
 *
 *	Perक्रमm an emergency shutकरोwn of the adapter and stop it from
 *	continuing any further communication on the ports or DMA to the
 *	host.  This is typically used when the adapter and/or firmware
 *	have crashed and we want to prevent any further accidental
 *	communication with the rest of the world.  This will also क्रमce
 *	the port Link Status to go करोwn -- अगर रेजिस्टर ग_लिखोs work --
 *	which should help our peers figure out that we're करोwn.
 */
पूर्णांक t4_shutकरोwn_adapter(काष्ठा adapter *adapter)
अणु
	पूर्णांक port;

	t4_पूर्णांकr_disable(adapter);
	t4_ग_लिखो_reg(adapter, DBG_GPIO_EN_A, 0);
	क्रम_each_port(adapter, port) अणु
		u32 a_port_cfg = is_t4(adapter->params.chip) ?
				       PORT_REG(port, XGMAC_PORT_CFG_A) :
				       T5_PORT_REG(port, MAC_PORT_CFG_A);

		t4_ग_लिखो_reg(adapter, a_port_cfg,
			     t4_पढ़ो_reg(adapter, a_port_cfg)
			     & ~SIGNAL_DET_V(1));
	पूर्ण
	t4_set_reg_field(adapter, SGE_CONTROL_A, GLOBALENABLE_F, 0);

	वापस 0;
पूर्ण

/**
 *	t4_bar2_sge_qregs - वापस BAR2 SGE Queue रेजिस्टर inक्रमmation
 *	@adapter: the adapter
 *	@qid: the Queue ID
 *	@qtype: the Ingress or Egress type क्रम @qid
 *	@user: true अगर this request is क्रम a user mode queue
 *	@pbar2_qoffset: BAR2 Queue Offset
 *	@pbar2_qid: BAR2 Queue ID or 0 क्रम Queue ID inferred SGE Queues
 *
 *	Returns the BAR2 SGE Queue Registers inक्रमmation associated with the
 *	indicated Absolute Queue ID.  These are passed back in वापस value
 *	poपूर्णांकers.  @qtype should be T4_BAR2_QTYPE_EGRESS क्रम Egress Queue
 *	and T4_BAR2_QTYPE_INGRESS क्रम Ingress Queues.
 *
 *	This may वापस an error which indicates that BAR2 SGE Queue
 *	रेजिस्टरs aren't available.  If an error is not वापसed, then the
 *	following values are वापसed:
 *
 *	  *@pbar2_qoffset: the BAR2 Offset of the @qid Registers
 *	  *@pbar2_qid: the BAR2 SGE Queue ID or 0 of @qid
 *
 *	If the वापसed BAR2 Queue ID is 0, then BAR2 SGE रेजिस्टरs which
 *	require the "Inferred Queue ID" ability may be used.  E.g. the
 *	Write Combining Doorbell Buffer. If the BAR2 Queue ID is not 0,
 *	then these "Inferred Queue ID" रेजिस्टर may not be used.
 */
पूर्णांक t4_bar2_sge_qregs(काष्ठा adapter *adapter,
		      अचिन्हित पूर्णांक qid,
		      क्रमागत t4_bar2_qtype qtype,
		      पूर्णांक user,
		      u64 *pbar2_qoffset,
		      अचिन्हित पूर्णांक *pbar2_qid)
अणु
	अचिन्हित पूर्णांक page_shअगरt, page_size, qpp_shअगरt, qpp_mask;
	u64 bar2_page_offset, bar2_qoffset;
	अचिन्हित पूर्णांक bar2_qid, bar2_qid_offset, bar2_qinferred;

	/* T4 करोesn't support BAR2 SGE Queue रेजिस्टरs क्रम kernel mode queues */
	अगर (!user && is_t4(adapter->params.chip))
		वापस -EINVAL;

	/* Get our SGE Page Size parameters.
	 */
	page_shअगरt = adapter->params.sge.hps + 10;
	page_size = 1 << page_shअगरt;

	/* Get the right Queues per Page parameters क्रम our Queue.
	 */
	qpp_shअगरt = (qtype == T4_BAR2_QTYPE_EGRESS
		     ? adapter->params.sge.eq_qpp
		     : adapter->params.sge.iq_qpp);
	qpp_mask = (1 << qpp_shअगरt) - 1;

	/*  Calculate the basics of the BAR2 SGE Queue रेजिस्टर area:
	 *  o The BAR2 page the Queue रेजिस्टरs will be in.
	 *  o The BAR2 Queue ID.
	 *  o The BAR2 Queue ID Offset पूर्णांकo the BAR2 page.
	 */
	bar2_page_offset = ((u64)(qid >> qpp_shअगरt) << page_shअगरt);
	bar2_qid = qid & qpp_mask;
	bar2_qid_offset = bar2_qid * SGE_UDB_SIZE;

	/* If the BAR2 Queue ID Offset is less than the Page Size, then the
	 * hardware will infer the Absolute Queue ID simply from the ग_लिखोs to
	 * the BAR2 Queue ID Offset within the BAR2 Page (and we need to use a
	 * BAR2 Queue ID of 0 क्रम those ग_लिखोs).  Otherwise, we'll simply
	 * ग_लिखो to the first BAR2 SGE Queue Area within the BAR2 Page with
	 * the BAR2 Queue ID and the hardware will infer the Absolute Queue ID
	 * from the BAR2 Page and BAR2 Queue ID.
	 *
	 * One important censequence of this is that some BAR2 SGE रेजिस्टरs
	 * have a "Queue ID" field and we can ग_लिखो the BAR2 SGE Queue ID
	 * there.  But other रेजिस्टरs synthesize the SGE Queue ID purely
	 * from the ग_लिखोs to the रेजिस्टरs -- the Write Combined Doorbell
	 * Buffer is a good example.  These BAR2 SGE Registers are only
	 * available क्रम those BAR2 SGE Register areas where the SGE Absolute
	 * Queue ID can be inferred from simple ग_लिखोs.
	 */
	bar2_qoffset = bar2_page_offset;
	bar2_qinferred = (bar2_qid_offset < page_size);
	अगर (bar2_qinferred) अणु
		bar2_qoffset += bar2_qid_offset;
		bar2_qid = 0;
	पूर्ण

	*pbar2_qoffset = bar2_qoffset;
	*pbar2_qid = bar2_qid;
	वापस 0;
पूर्ण

/**
 *	t4_init_devlog_params - initialize adapter->params.devlog
 *	@adap: the adapter
 *
 *	Initialize various fields of the adapter's Firmware Device Log
 *	Parameters काष्ठाure.
 */
पूर्णांक t4_init_devlog_params(काष्ठा adapter *adap)
अणु
	काष्ठा devlog_params *dparams = &adap->params.devlog;
	u32 pf_dparams;
	अचिन्हित पूर्णांक devlog_meminfo;
	काष्ठा fw_devlog_cmd devlog_cmd;
	पूर्णांक ret;

	/* If we're dealing with newer firmware, the Device Log Parameters
	 * are stored in a designated रेजिस्टर which allows us to access the
	 * Device Log even अगर we can't talk to the firmware.
	 */
	pf_dparams =
		t4_पढ़ो_reg(adap, PCIE_FW_REG(PCIE_FW_PF_A, PCIE_FW_PF_DEVLOG));
	अगर (pf_dparams) अणु
		अचिन्हित पूर्णांक nentries, nentries128;

		dparams->memtype = PCIE_FW_PF_DEVLOG_MEMTYPE_G(pf_dparams);
		dparams->start = PCIE_FW_PF_DEVLOG_ADDR16_G(pf_dparams) << 4;

		nentries128 = PCIE_FW_PF_DEVLOG_NENTRIES128_G(pf_dparams);
		nentries = (nentries128 + 1) * 128;
		dparams->size = nentries * माप(काष्ठा fw_devlog_e);

		वापस 0;
	पूर्ण

	/* Otherwise, ask the firmware क्रम it's Device Log Parameters.
	 */
	स_रखो(&devlog_cmd, 0, माप(devlog_cmd));
	devlog_cmd.op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_DEVLOG_CMD) |
					     FW_CMD_REQUEST_F | FW_CMD_READ_F);
	devlog_cmd.retval_len16 = cpu_to_be32(FW_LEN16(devlog_cmd));
	ret = t4_wr_mbox(adap, adap->mbox, &devlog_cmd, माप(devlog_cmd),
			 &devlog_cmd);
	अगर (ret)
		वापस ret;

	devlog_meminfo =
		be32_to_cpu(devlog_cmd.memtype_devlog_memaddr16_devlog);
	dparams->memtype = FW_DEVLOG_CMD_MEMTYPE_DEVLOG_G(devlog_meminfo);
	dparams->start = FW_DEVLOG_CMD_MEMADDR16_DEVLOG_G(devlog_meminfo) << 4;
	dparams->size = be32_to_cpu(devlog_cmd.memsize_devlog);

	वापस 0;
पूर्ण

/**
 *	t4_init_sge_params - initialize adap->params.sge
 *	@adapter: the adapter
 *
 *	Initialize various fields of the adapter's SGE Parameters काष्ठाure.
 */
पूर्णांक t4_init_sge_params(काष्ठा adapter *adapter)
अणु
	काष्ठा sge_params *sge_params = &adapter->params.sge;
	u32 hps, qpp;
	अचिन्हित पूर्णांक s_hps, s_qpp;

	/* Extract the SGE Page Size क्रम our PF.
	 */
	hps = t4_पढ़ो_reg(adapter, SGE_HOST_PAGE_SIZE_A);
	s_hps = (HOSTPAGESIZEPF0_S +
		 (HOSTPAGESIZEPF1_S - HOSTPAGESIZEPF0_S) * adapter->pf);
	sge_params->hps = ((hps >> s_hps) & HOSTPAGESIZEPF0_M);

	/* Extract the SGE Egress and Ingess Queues Per Page क्रम our PF.
	 */
	s_qpp = (QUEUESPERPAGEPF0_S +
		(QUEUESPERPAGEPF1_S - QUEUESPERPAGEPF0_S) * adapter->pf);
	qpp = t4_पढ़ो_reg(adapter, SGE_EGRESS_QUEUES_PER_PAGE_PF_A);
	sge_params->eq_qpp = ((qpp >> s_qpp) & QUEUESPERPAGEPF0_M);
	qpp = t4_पढ़ो_reg(adapter, SGE_INGRESS_QUEUES_PER_PAGE_PF_A);
	sge_params->iq_qpp = ((qpp >> s_qpp) & QUEUESPERPAGEPF0_M);

	वापस 0;
पूर्ण

/**
 *      t4_init_tp_params - initialize adap->params.tp
 *      @adap: the adapter
 *      @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 *      Initialize various fields of the adapter's TP Parameters काष्ठाure.
 */
पूर्णांक t4_init_tp_params(काष्ठा adapter *adap, bool sleep_ok)
अणु
	u32 param, val, v;
	पूर्णांक chan, ret;


	v = t4_पढ़ो_reg(adap, TP_TIMER_RESOLUTION_A);
	adap->params.tp.tre = TIMERRESOLUTION_G(v);
	adap->params.tp.dack_re = DELAYEDACKRESOLUTION_G(v);

	/* MODQ_REQ_MAP शेषs to setting queues 0-3 to chan 0-3 */
	क्रम (chan = 0; chan < NCHAN; chan++)
		adap->params.tp.tx_modq[chan] = chan;

	/* Cache the adapter's Compressed Filter Mode/Mask and global Ingress
	 * Configuration.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_FILTER) |
		 FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_FILTER_MODE_MASK));

	/* Read current value */
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
			      &param, &val);
	अगर (ret == 0) अणु
		dev_info(adap->pdev_dev,
			 "Current filter mode/mask 0x%x:0x%x\n",
			 FW_PARAMS_PARAM_FILTER_MODE_G(val),
			 FW_PARAMS_PARAM_FILTER_MASK_G(val));
		adap->params.tp.vlan_pri_map =
			FW_PARAMS_PARAM_FILTER_MODE_G(val);
		adap->params.tp.filter_mask =
			FW_PARAMS_PARAM_FILTER_MASK_G(val);
	पूर्ण अन्यथा अणु
		dev_info(adap->pdev_dev,
			 "Failed to read filter mode/mask via fw api, using indirect-reg-read\n");

		/* Inहाल of older-fw (which करोesn't expose the api
		 * FW_PARAM_DEV_FILTER_MODE_MASK) and newer-driver (which uses
		 * the fw api) combination, fall-back to older method of पढ़ोing
		 * the filter mode from indirect-रेजिस्टर
		 */
		t4_tp_pio_पढ़ो(adap, &adap->params.tp.vlan_pri_map, 1,
			       TP_VLAN_PRI_MAP_A, sleep_ok);

		/* With the older-fw and newer-driver combination we might run
		 * पूर्णांकo an issue when user wants to use hash filter region but
		 * the filter_mask is zero, in this हाल filter_mask validation
		 * is tough. To aव्योम that we set the filter_mask same as filter
		 * mode, which will behave exactly as the older way of ignoring
		 * the filter mask validation.
		 */
		adap->params.tp.filter_mask = adap->params.tp.vlan_pri_map;
	पूर्ण

	t4_tp_pio_पढ़ो(adap, &adap->params.tp.ingress_config, 1,
		       TP_INGRESS_CONFIG_A, sleep_ok);

	/* For T6, cache the adapter's compressed error vector
	 * and passing outer header info क्रम encapsulated packets.
	 */
	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) अणु
		v = t4_पढ़ो_reg(adap, TP_OUT_CONFIG_A);
		adap->params.tp.rx_pkt_encap = (v & CRXPKTENC_F) ? 1 : 0;
	पूर्ण

	/* Now that we have TP_VLAN_PRI_MAP cached, we can calculate the field
	 * shअगरt positions of several elements of the Compressed Filter Tuple
	 * क्रम this adapter which we need frequently ...
	 */
	adap->params.tp.fcoe_shअगरt = t4_filter_field_shअगरt(adap, FCOE_F);
	adap->params.tp.port_shअगरt = t4_filter_field_shअगरt(adap, PORT_F);
	adap->params.tp.vnic_shअगरt = t4_filter_field_shअगरt(adap, VNIC_ID_F);
	adap->params.tp.vlan_shअगरt = t4_filter_field_shअगरt(adap, VLAN_F);
	adap->params.tp.tos_shअगरt = t4_filter_field_shअगरt(adap, TOS_F);
	adap->params.tp.protocol_shअगरt = t4_filter_field_shअगरt(adap,
							       PROTOCOL_F);
	adap->params.tp.ethertype_shअगरt = t4_filter_field_shअगरt(adap,
								ETHERTYPE_F);
	adap->params.tp.macmatch_shअगरt = t4_filter_field_shअगरt(adap,
							       MACMATCH_F);
	adap->params.tp.matchtype_shअगरt = t4_filter_field_shअगरt(adap,
								MPSHITTYPE_F);
	adap->params.tp.frag_shअगरt = t4_filter_field_shअगरt(adap,
							   FRAGMENTATION_F);

	/* If TP_INGRESS_CONFIG.VNID == 0, then TP_VLAN_PRI_MAP.VNIC_ID
	 * represents the presence of an Outer VLAN instead of a VNIC ID.
	 */
	अगर ((adap->params.tp.ingress_config & VNIC_F) == 0)
		adap->params.tp.vnic_shअगरt = -1;

	v = t4_पढ़ो_reg(adap, LE_3_DB_HASH_MASK_GEN_IPV4_T6_A);
	adap->params.tp.hash_filter_mask = v;
	v = t4_पढ़ो_reg(adap, LE_4_DB_HASH_MASK_GEN_IPV4_T6_A);
	adap->params.tp.hash_filter_mask |= ((u64)v << 32);
	वापस 0;
पूर्ण

/**
 *      t4_filter_field_shअगरt - calculate filter field shअगरt
 *      @adap: the adapter
 *      @filter_sel: the desired field (from TP_VLAN_PRI_MAP bits)
 *
 *      Return the shअगरt position of a filter field within the Compressed
 *      Filter Tuple.  The filter field is specअगरied via its selection bit
 *      within TP_VLAN_PRI_MAL (filter mode).  E.g. F_VLAN.
 */
पूर्णांक t4_filter_field_shअगरt(स्थिर काष्ठा adapter *adap, पूर्णांक filter_sel)
अणु
	अचिन्हित पूर्णांक filter_mode = adap->params.tp.vlan_pri_map;
	अचिन्हित पूर्णांक sel;
	पूर्णांक field_shअगरt;

	अगर ((filter_mode & filter_sel) == 0)
		वापस -1;

	क्रम (sel = 1, field_shअगरt = 0; sel < filter_sel; sel <<= 1) अणु
		चयन (filter_mode & sel) अणु
		हाल FCOE_F:
			field_shअगरt += FT_FCOE_W;
			अवरोध;
		हाल PORT_F:
			field_shअगरt += FT_PORT_W;
			अवरोध;
		हाल VNIC_ID_F:
			field_shअगरt += FT_VNIC_ID_W;
			अवरोध;
		हाल VLAN_F:
			field_shअगरt += FT_VLAN_W;
			अवरोध;
		हाल TOS_F:
			field_shअगरt += FT_TOS_W;
			अवरोध;
		हाल PROTOCOL_F:
			field_shअगरt += FT_PROTOCOL_W;
			अवरोध;
		हाल ETHERTYPE_F:
			field_shअगरt += FT_ETHERTYPE_W;
			अवरोध;
		हाल MACMATCH_F:
			field_shअगरt += FT_MACMATCH_W;
			अवरोध;
		हाल MPSHITTYPE_F:
			field_shअगरt += FT_MPSHITTYPE_W;
			अवरोध;
		हाल FRAGMENTATION_F:
			field_shअगरt += FT_FRAGMENTATION_W;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस field_shअगरt;
पूर्ण

पूर्णांक t4_init_rss_mode(काष्ठा adapter *adap, पूर्णांक mbox)
अणु
	पूर्णांक i, ret;
	काष्ठा fw_rss_vi_config_cmd rvc;

	स_रखो(&rvc, 0, माप(rvc));

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *p = adap2pinfo(adap, i);

		rvc.op_to_viid =
			cpu_to_be32(FW_CMD_OP_V(FW_RSS_VI_CONFIG_CMD) |
				    FW_CMD_REQUEST_F | FW_CMD_READ_F |
				    FW_RSS_VI_CONFIG_CMD_VIID_V(p->viid));
		rvc.retval_len16 = cpu_to_be32(FW_LEN16(rvc));
		ret = t4_wr_mbox(adap, mbox, &rvc, माप(rvc), &rvc);
		अगर (ret)
			वापस ret;
		p->rss_mode = be32_to_cpu(rvc.u.basicभव.शेषq_to_udpen);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t4_init_portinfo - allocate a भव पूर्णांकerface and initialize port_info
 *	@pi: the port_info
 *	@mbox: mailbox to use क्रम the FW command
 *	@port: physical port associated with the VI
 *	@pf: the PF owning the VI
 *	@vf: the VF owning the VI
 *	@mac: the MAC address of the VI
 *
 *	Allocates a भव पूर्णांकerface क्रम the given physical port.  If @mac is
 *	not %शून्य it contains the MAC address of the VI as asचिन्हित by FW.
 *	@mac should be large enough to hold an Ethernet address.
 *	Returns < 0 on error.
 */
पूर्णांक t4_init_portinfo(काष्ठा port_info *pi, पूर्णांक mbox,
		     पूर्णांक port, पूर्णांक pf, पूर्णांक vf, u8 mac[])
अणु
	काष्ठा adapter *adapter = pi->adapter;
	अचिन्हित पूर्णांक fw_caps = adapter->params.fw_caps_support;
	काष्ठा fw_port_cmd cmd;
	अचिन्हित पूर्णांक rss_size;
	क्रमागत fw_port_type port_type;
	पूर्णांक mdio_addr;
	fw_port_cap32_t pcaps, acaps;
	u8 vivld = 0, vin = 0;
	पूर्णांक ret;

	/* If we haven't yet determined whether we're talking to Firmware
	 * which knows the new 32-bit Port Capabilities, it's समय to find
	 * out now.  This will also tell new Firmware to send us Port Status
	 * Updates using the new 32-bit Port Capabilities version of the
	 * Port Inक्रमmation message.
	 */
	अगर (fw_caps == FW_CAPS_UNKNOWN) अणु
		u32 param, val;

		param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_PORT_CAPS32));
		val = 1;
		ret = t4_set_params(adapter, mbox, pf, vf, 1, &param, &val);
		fw_caps = (ret == 0 ? FW_CAPS32 : FW_CAPS16);
		adapter->params.fw_caps_support = fw_caps;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) |
				       FW_CMD_REQUEST_F | FW_CMD_READ_F |
				       FW_PORT_CMD_PORTID_V(port));
	cmd.action_to_len16 = cpu_to_be32(
		FW_PORT_CMD_ACTION_V(fw_caps == FW_CAPS16
				     ? FW_PORT_ACTION_GET_PORT_INFO
				     : FW_PORT_ACTION_GET_PORT_INFO32) |
		FW_LEN16(cmd));
	ret = t4_wr_mbox(pi->adapter, mbox, &cmd, माप(cmd), &cmd);
	अगर (ret)
		वापस ret;

	/* Extract the various fields from the Port Inक्रमmation message.
	 */
	अगर (fw_caps == FW_CAPS16) अणु
		u32 lstatus = be32_to_cpu(cmd.u.info.lstatus_to_modtype);

		port_type = FW_PORT_CMD_PTYPE_G(lstatus);
		mdio_addr = ((lstatus & FW_PORT_CMD_MDIOCAP_F)
			     ? FW_PORT_CMD_MDIOADDR_G(lstatus)
			     : -1);
		pcaps = fwcaps16_to_caps32(be16_to_cpu(cmd.u.info.pcap));
		acaps = fwcaps16_to_caps32(be16_to_cpu(cmd.u.info.acap));
	पूर्ण अन्यथा अणु
		u32 lstatus32 = be32_to_cpu(cmd.u.info32.lstatus32_to_cbllen32);

		port_type = FW_PORT_CMD_PORTTYPE32_G(lstatus32);
		mdio_addr = ((lstatus32 & FW_PORT_CMD_MDIOCAP32_F)
			     ? FW_PORT_CMD_MDIOADDR32_G(lstatus32)
			     : -1);
		pcaps = be32_to_cpu(cmd.u.info32.pcaps32);
		acaps = be32_to_cpu(cmd.u.info32.acaps32);
	पूर्ण

	ret = t4_alloc_vi(pi->adapter, mbox, port, pf, vf, 1, mac, &rss_size,
			  &vivld, &vin);
	अगर (ret < 0)
		वापस ret;

	pi->viid = ret;
	pi->tx_chan = port;
	pi->lport = port;
	pi->rss_size = rss_size;
	pi->rx_cchan = t4_get_tp_e2c_map(pi->adapter, port);

	/* If fw supports वापसing the VIN as part of FW_VI_CMD,
	 * save the वापसed values.
	 */
	अगर (adapter->params.viid_smt_extn_support) अणु
		pi->vivld = vivld;
		pi->vin = vin;
	पूर्ण अन्यथा अणु
		/* Retrieve the values from VIID */
		pi->vivld = FW_VIID_VIVLD_G(pi->viid);
		pi->vin =  FW_VIID_VIN_G(pi->viid);
	पूर्ण

	pi->port_type = port_type;
	pi->mdio_addr = mdio_addr;
	pi->mod_type = FW_PORT_MOD_TYPE_NA;

	init_link_config(&pi->link_cfg, pcaps, acaps);
	वापस 0;
पूर्ण

पूर्णांक t4_port_init(काष्ठा adapter *adap, पूर्णांक mbox, पूर्णांक pf, पूर्णांक vf)
अणु
	u8 addr[6];
	पूर्णांक ret, i, j = 0;

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);

		जबतक ((adap->params.portvec & (1 << j)) == 0)
			j++;

		ret = t4_init_portinfo(pi, mbox, j, pf, vf, addr);
		अगर (ret)
			वापस ret;

		स_नकल(adap->port[i]->dev_addr, addr, ETH_ALEN);
		j++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक t4_init_port_mirror(काष्ठा port_info *pi, u8 mbox, u8 port, u8 pf, u8 vf,
			u16 *mirror_viid)
अणु
	पूर्णांक ret;

	ret = t4_alloc_vi(pi->adapter, mbox, port, pf, vf, 1, शून्य, शून्य,
			  शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (mirror_viid)
		*mirror_viid = ret;

	वापस 0;
पूर्ण

/**
 *	t4_पढ़ो_cimq_cfg - पढ़ो CIM queue configuration
 *	@adap: the adapter
 *	@base: holds the queue base addresses in bytes
 *	@size: holds the queue sizes in bytes
 *	@thres: holds the queue full thresholds in bytes
 *
 *	Returns the current configuration of the CIM queues, starting with
 *	the IBQs, then the OBQs.
 */
व्योम t4_पढ़ो_cimq_cfg(काष्ठा adapter *adap, u16 *base, u16 *size, u16 *thres)
अणु
	अचिन्हित पूर्णांक i, v;
	पूर्णांक cim_num_obq = is_t4(adap->params.chip) ?
				CIM_NUM_OBQ : CIM_NUM_OBQ_T5;

	क्रम (i = 0; i < CIM_NUM_IBQ; i++) अणु
		t4_ग_लिखो_reg(adap, CIM_QUEUE_CONFIG_REF_A, IBQSELECT_F |
			     QUENUMSELECT_V(i));
		v = t4_पढ़ो_reg(adap, CIM_QUEUE_CONFIG_CTRL_A);
		/* value is in 256-byte units */
		*base++ = CIMQBASE_G(v) * 256;
		*size++ = CIMQSIZE_G(v) * 256;
		*thres++ = QUEFULLTHRSH_G(v) * 8; /* 8-byte unit */
	पूर्ण
	क्रम (i = 0; i < cim_num_obq; i++) अणु
		t4_ग_लिखो_reg(adap, CIM_QUEUE_CONFIG_REF_A, OBQSELECT_F |
			     QUENUMSELECT_V(i));
		v = t4_पढ़ो_reg(adap, CIM_QUEUE_CONFIG_CTRL_A);
		/* value is in 256-byte units */
		*base++ = CIMQBASE_G(v) * 256;
		*size++ = CIMQSIZE_G(v) * 256;
	पूर्ण
पूर्ण

/**
 *	t4_पढ़ो_cim_ibq - पढ़ो the contents of a CIM inbound queue
 *	@adap: the adapter
 *	@qid: the queue index
 *	@data: where to store the queue contents
 *	@n: capacity of @data in 32-bit words
 *
 *	Reads the contents of the selected CIM queue starting at address 0 up
 *	to the capacity of @data.  @n must be a multiple of 4.  Returns < 0 on
 *	error and the number of 32-bit words actually पढ़ो on success.
 */
पूर्णांक t4_पढ़ो_cim_ibq(काष्ठा adapter *adap, अचिन्हित पूर्णांक qid, u32 *data, माप_प्रकार n)
अणु
	पूर्णांक i, err, attempts;
	अचिन्हित पूर्णांक addr;
	स्थिर अचिन्हित पूर्णांक nwords = CIM_IBQ_SIZE * 4;

	अगर (qid > 5 || (n & 3))
		वापस -EINVAL;

	addr = qid * nwords;
	अगर (n > nwords)
		n = nwords;

	/* It might take 3-10ms beक्रमe the IBQ debug पढ़ो access is allowed.
	 * Wait क्रम 1 Sec with a delay of 1 usec.
	 */
	attempts = 1000000;

	क्रम (i = 0; i < n; i++, addr++) अणु
		t4_ग_लिखो_reg(adap, CIM_IBQ_DBG_CFG_A, IBQDBGADDR_V(addr) |
			     IBQDBGEN_F);
		err = t4_रुको_op_करोne(adap, CIM_IBQ_DBG_CFG_A, IBQDBGBUSY_F, 0,
				      attempts, 1);
		अगर (err)
			वापस err;
		*data++ = t4_पढ़ो_reg(adap, CIM_IBQ_DBG_DATA_A);
	पूर्ण
	t4_ग_लिखो_reg(adap, CIM_IBQ_DBG_CFG_A, 0);
	वापस i;
पूर्ण

/**
 *	t4_पढ़ो_cim_obq - पढ़ो the contents of a CIM outbound queue
 *	@adap: the adapter
 *	@qid: the queue index
 *	@data: where to store the queue contents
 *	@n: capacity of @data in 32-bit words
 *
 *	Reads the contents of the selected CIM queue starting at address 0 up
 *	to the capacity of @data.  @n must be a multiple of 4.  Returns < 0 on
 *	error and the number of 32-bit words actually पढ़ो on success.
 */
पूर्णांक t4_पढ़ो_cim_obq(काष्ठा adapter *adap, अचिन्हित पूर्णांक qid, u32 *data, माप_प्रकार n)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक addr, v, nwords;
	पूर्णांक cim_num_obq = is_t4(adap->params.chip) ?
				CIM_NUM_OBQ : CIM_NUM_OBQ_T5;

	अगर ((qid > (cim_num_obq - 1)) || (n & 3))
		वापस -EINVAL;

	t4_ग_लिखो_reg(adap, CIM_QUEUE_CONFIG_REF_A, OBQSELECT_F |
		     QUENUMSELECT_V(qid));
	v = t4_पढ़ो_reg(adap, CIM_QUEUE_CONFIG_CTRL_A);

	addr = CIMQBASE_G(v) * 64;    /* muliple of 256 -> muliple of 4 */
	nwords = CIMQSIZE_G(v) * 64;  /* same */
	अगर (n > nwords)
		n = nwords;

	क्रम (i = 0; i < n; i++, addr++) अणु
		t4_ग_लिखो_reg(adap, CIM_OBQ_DBG_CFG_A, OBQDBGADDR_V(addr) |
			     OBQDBGEN_F);
		err = t4_रुको_op_करोne(adap, CIM_OBQ_DBG_CFG_A, OBQDBGBUSY_F, 0,
				      2, 1);
		अगर (err)
			वापस err;
		*data++ = t4_पढ़ो_reg(adap, CIM_OBQ_DBG_DATA_A);
	पूर्ण
	t4_ग_लिखो_reg(adap, CIM_OBQ_DBG_CFG_A, 0);
	वापस i;
पूर्ण

/**
 *	t4_cim_पढ़ो - पढ़ो a block from CIM पूर्णांकernal address space
 *	@adap: the adapter
 *	@addr: the start address within the CIM address space
 *	@n: number of words to पढ़ो
 *	@valp: where to store the result
 *
 *	Reads a block of 4-byte words from the CIM पूर्णांकenal address space.
 */
पूर्णांक t4_cim_पढ़ो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक n,
		अचिन्हित पूर्णांक *valp)
अणु
	पूर्णांक ret = 0;

	अगर (t4_पढ़ो_reg(adap, CIM_HOST_ACC_CTRL_A) & HOSTBUSY_F)
		वापस -EBUSY;

	क्रम ( ; !ret && n--; addr += 4) अणु
		t4_ग_लिखो_reg(adap, CIM_HOST_ACC_CTRL_A, addr);
		ret = t4_रुको_op_करोne(adap, CIM_HOST_ACC_CTRL_A, HOSTBUSY_F,
				      0, 5, 2);
		अगर (!ret)
			*valp++ = t4_पढ़ो_reg(adap, CIM_HOST_ACC_DATA_A);
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t4_cim_ग_लिखो - ग_लिखो a block पूर्णांकo CIM पूर्णांकernal address space
 *	@adap: the adapter
 *	@addr: the start address within the CIM address space
 *	@n: number of words to ग_लिखो
 *	@valp: set of values to ग_लिखो
 *
 *	Writes a block of 4-byte words पूर्णांकo the CIM पूर्णांकenal address space.
 */
पूर्णांक t4_cim_ग_लिखो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक n,
		 स्थिर अचिन्हित पूर्णांक *valp)
अणु
	पूर्णांक ret = 0;

	अगर (t4_पढ़ो_reg(adap, CIM_HOST_ACC_CTRL_A) & HOSTBUSY_F)
		वापस -EBUSY;

	क्रम ( ; !ret && n--; addr += 4) अणु
		t4_ग_लिखो_reg(adap, CIM_HOST_ACC_DATA_A, *valp++);
		t4_ग_लिखो_reg(adap, CIM_HOST_ACC_CTRL_A, addr | HOSTWRITE_F);
		ret = t4_रुको_op_करोne(adap, CIM_HOST_ACC_CTRL_A, HOSTBUSY_F,
				      0, 5, 2);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक t4_cim_ग_लिखो1(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
			 अचिन्हित पूर्णांक val)
अणु
	वापस t4_cim_ग_लिखो(adap, addr, 1, &val);
पूर्ण

/**
 *	t4_cim_पढ़ो_la - पढ़ो CIM LA capture buffer
 *	@adap: the adapter
 *	@la_buf: where to store the LA data
 *	@wrptr: the HW ग_लिखो poपूर्णांकer within the capture buffer
 *
 *	Reads the contents of the CIM LA buffer with the most recent entry at
 *	the end	of the वापसed data and with the entry at @wrptr first.
 *	We try to leave the LA in the running state we find it in.
 */
पूर्णांक t4_cim_पढ़ो_la(काष्ठा adapter *adap, u32 *la_buf, अचिन्हित पूर्णांक *wrptr)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक cfg, val, idx;

	ret = t4_cim_पढ़ो(adap, UP_UP_DBG_LA_CFG_A, 1, &cfg);
	अगर (ret)
		वापस ret;

	अगर (cfg & UPDBGLAEN_F) अणु	/* LA is running, मुक्तze it */
		ret = t4_cim_ग_लिखो1(adap, UP_UP_DBG_LA_CFG_A, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = t4_cim_पढ़ो(adap, UP_UP_DBG_LA_CFG_A, 1, &val);
	अगर (ret)
		जाओ restart;

	idx = UPDBGLAWRPTR_G(val);
	अगर (wrptr)
		*wrptr = idx;

	क्रम (i = 0; i < adap->params.cim_la_size; i++) अणु
		ret = t4_cim_ग_लिखो1(adap, UP_UP_DBG_LA_CFG_A,
				    UPDBGLARDPTR_V(idx) | UPDBGLARDEN_F);
		अगर (ret)
			अवरोध;
		ret = t4_cim_पढ़ो(adap, UP_UP_DBG_LA_CFG_A, 1, &val);
		अगर (ret)
			अवरोध;
		अगर (val & UPDBGLARDEN_F) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		ret = t4_cim_पढ़ो(adap, UP_UP_DBG_LA_DATA_A, 1, &la_buf[i]);
		अगर (ret)
			अवरोध;

		/* Bits 0-3 of UpDbgLaRdPtr can be between 0000 to 1001 to
		 * identअगरy the 32-bit portion of the full 312-bit data
		 */
		अगर (is_t6(adap->params.chip) && (idx & 0xf) >= 9)
			idx = (idx & 0xff0) + 0x10;
		अन्यथा
			idx++;
		/* address can't exceed 0xfff */
		idx &= UPDBGLARDPTR_M;
	पूर्ण
restart:
	अगर (cfg & UPDBGLAEN_F) अणु
		पूर्णांक r = t4_cim_ग_लिखो1(adap, UP_UP_DBG_LA_CFG_A,
				      cfg & ~UPDBGLARDEN_F);
		अगर (!ret)
			ret = r;
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t4_tp_पढ़ो_la - पढ़ो TP LA capture buffer
 *	@adap: the adapter
 *	@la_buf: where to store the LA data
 *	@wrptr: the HW ग_लिखो poपूर्णांकer within the capture buffer
 *
 *	Reads the contents of the TP LA buffer with the most recent entry at
 *	the end	of the वापसed data and with the entry at @wrptr first.
 *	We leave the LA in the running state we find it in.
 */
व्योम t4_tp_पढ़ो_la(काष्ठा adapter *adap, u64 *la_buf, अचिन्हित पूर्णांक *wrptr)
अणु
	bool last_incomplete;
	अचिन्हित पूर्णांक i, cfg, val, idx;

	cfg = t4_पढ़ो_reg(adap, TP_DBG_LA_CONFIG_A) & 0xffff;
	अगर (cfg & DBGLAENABLE_F)			/* मुक्तze LA */
		t4_ग_लिखो_reg(adap, TP_DBG_LA_CONFIG_A,
			     adap->params.tp.la_mask | (cfg ^ DBGLAENABLE_F));

	val = t4_पढ़ो_reg(adap, TP_DBG_LA_CONFIG_A);
	idx = DBGLAWPTR_G(val);
	last_incomplete = DBGLAMODE_G(val) >= 2 && (val & DBGLAWHLF_F) == 0;
	अगर (last_incomplete)
		idx = (idx + 1) & DBGLARPTR_M;
	अगर (wrptr)
		*wrptr = idx;

	val &= 0xffff;
	val &= ~DBGLARPTR_V(DBGLARPTR_M);
	val |= adap->params.tp.la_mask;

	क्रम (i = 0; i < TPLA_SIZE; i++) अणु
		t4_ग_लिखो_reg(adap, TP_DBG_LA_CONFIG_A, DBGLARPTR_V(idx) | val);
		la_buf[i] = t4_पढ़ो_reg64(adap, TP_DBG_LA_DATAL_A);
		idx = (idx + 1) & DBGLARPTR_M;
	पूर्ण

	/* Wipe out last entry अगर it isn't valid */
	अगर (last_incomplete)
		la_buf[TPLA_SIZE - 1] = ~0ULL;

	अगर (cfg & DBGLAENABLE_F)                    /* restore running state */
		t4_ग_लिखो_reg(adap, TP_DBG_LA_CONFIG_A,
			     cfg | adap->params.tp.la_mask);
पूर्ण

/* SGE Hung Ingress DMA Warning Threshold समय and Warning Repeat Rate (in
 * seconds).  If we find one of the SGE Ingress DMA State Machines in the same
 * state क्रम more than the Warning Threshold then we'll issue a warning about
 * a potential hang.  We'll repeat the warning as the SGE Ingress DMA Channel
 * appears to be hung every Warning Repeat second till the situation clears.
 * If the situation clears, we'll note that as well.
 */
#घोषणा SGE_IDMA_WARN_THRESH 1
#घोषणा SGE_IDMA_WARN_REPEAT 300

/**
 *	t4_idma_monitor_init - initialize SGE Ingress DMA Monitor
 *	@adapter: the adapter
 *	@idma: the adapter IDMA Monitor state
 *
 *	Initialize the state of an SGE Ingress DMA Monitor.
 */
व्योम t4_idma_monitor_init(काष्ठा adapter *adapter,
			  काष्ठा sge_idma_monitor_state *idma)
अणु
	/* Initialize the state variables क्रम detecting an SGE Ingress DMA
	 * hang.  The SGE has पूर्णांकernal counters which count up on each घड़ी
	 * tick whenever the SGE finds its Ingress DMA State Engines in the
	 * same state they were on the previous घड़ी tick.  The घड़ी used is
	 * the Core Clock so we have a limit on the maximum "time" they can
	 * record; typically a very small number of seconds.  For instance,
	 * with a 600MHz Core Clock, we can only count up to a bit more than
	 * 7s.  So we'll synthesize a larger counter in order to not run the
	 * risk of having the "timers" overflow and give us the flexibility to
	 * मुख्यtain a Hung SGE State Machine of our own which operates across
	 * a दीर्घer समय frame.
	 */
	idma->idma_1s_thresh = core_ticks_per_usec(adapter) * 1000000; /* 1s */
	idma->idma_stalled[0] = 0;
	idma->idma_stalled[1] = 0;
पूर्ण

/**
 *	t4_idma_monitor - monitor SGE Ingress DMA state
 *	@adapter: the adapter
 *	@idma: the adapter IDMA Monitor state
 *	@hz: number of ticks/second
 *	@ticks: number of ticks since the last IDMA Monitor call
 */
व्योम t4_idma_monitor(काष्ठा adapter *adapter,
		     काष्ठा sge_idma_monitor_state *idma,
		     पूर्णांक hz, पूर्णांक ticks)
अणु
	पूर्णांक i, idma_same_state_cnt[2];

	 /* Read the SGE Debug Ingress DMA Same State Count रेजिस्टरs.  These
	  * are counters inside the SGE which count up on each घड़ी when the
	  * SGE finds its Ingress DMA State Engines in the same states they
	  * were in the previous घड़ी.  The counters will peg out at
	  * 0xffffffff without wrapping around so once they pass the 1s
	  * threshold they'll stay above that till the IDMA state changes.
	  */
	t4_ग_लिखो_reg(adapter, SGE_DEBUG_INDEX_A, 13);
	idma_same_state_cnt[0] = t4_पढ़ो_reg(adapter, SGE_DEBUG_DATA_HIGH_A);
	idma_same_state_cnt[1] = t4_पढ़ो_reg(adapter, SGE_DEBUG_DATA_LOW_A);

	क्रम (i = 0; i < 2; i++) अणु
		u32 debug0, debug11;

		/* If the Ingress DMA Same State Counter ("timer") is less
		 * than 1s, then we can reset our synthesized Stall Timer and
		 * जारी.  If we have previously emitted warnings about a
		 * potential stalled Ingress Queue, issue a note indicating
		 * that the Ingress Queue has resumed क्रमward progress.
		 */
		अगर (idma_same_state_cnt[i] < idma->idma_1s_thresh) अणु
			अगर (idma->idma_stalled[i] >= SGE_IDMA_WARN_THRESH * hz)
				dev_warn(adapter->pdev_dev, "SGE idma%d, queue %u, "
					 "resumed after %d seconds\n",
					 i, idma->idma_qid[i],
					 idma->idma_stalled[i] / hz);
			idma->idma_stalled[i] = 0;
			जारी;
		पूर्ण

		/* Synthesize an SGE Ingress DMA Same State Timer in the Hz
		 * करोमुख्य.  The first समय we get here it'll be because we
		 * passed the 1s Threshold; each additional समय it'll be
		 * because the RX Timer Callback is being fired on its regular
		 * schedule.
		 *
		 * If the stall is below our Potential Hung Ingress Queue
		 * Warning Threshold, जारी.
		 */
		अगर (idma->idma_stalled[i] == 0) अणु
			idma->idma_stalled[i] = hz;
			idma->idma_warn[i] = 0;
		पूर्ण अन्यथा अणु
			idma->idma_stalled[i] += ticks;
			idma->idma_warn[i] -= ticks;
		पूर्ण

		अगर (idma->idma_stalled[i] < SGE_IDMA_WARN_THRESH * hz)
			जारी;

		/* We'll issue a warning every SGE_IDMA_WARN_REPEAT seconds.
		 */
		अगर (idma->idma_warn[i] > 0)
			जारी;
		idma->idma_warn[i] = SGE_IDMA_WARN_REPEAT * hz;

		/* Read and save the SGE IDMA State and Queue ID inक्रमmation.
		 * We करो this every समय in हाल it changes across समय ...
		 * can't be too careful ...
		 */
		t4_ग_लिखो_reg(adapter, SGE_DEBUG_INDEX_A, 0);
		debug0 = t4_पढ़ो_reg(adapter, SGE_DEBUG_DATA_LOW_A);
		idma->idma_state[i] = (debug0 >> (i * 9)) & 0x3f;

		t4_ग_लिखो_reg(adapter, SGE_DEBUG_INDEX_A, 11);
		debug11 = t4_पढ़ो_reg(adapter, SGE_DEBUG_DATA_LOW_A);
		idma->idma_qid[i] = (debug11 >> (i * 16)) & 0xffff;

		dev_warn(adapter->pdev_dev, "SGE idma%u, queue %u, potentially stuck in "
			 "state %u for %d seconds (debug0=%#x, debug11=%#x)\n",
			 i, idma->idma_qid[i], idma->idma_state[i],
			 idma->idma_stalled[i] / hz,
			 debug0, debug11);
		t4_sge_decode_idma_state(adapter, idma->idma_state[i]);
	पूर्ण
पूर्ण

/**
 *	t4_load_cfg - करोwnload config file
 *	@adap: the adapter
 *	@cfg_data: the cfg text file to ग_लिखो
 *	@size: text file size
 *
 *	Write the supplied config text file to the card's serial flash.
 */
पूर्णांक t4_load_cfg(काष्ठा adapter *adap, स्थिर u8 *cfg_data, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret, i, n, cfg_addr;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक flash_cfg_start_sec;
	अचिन्हित पूर्णांक sf_sec_size = adap->params.sf_size / adap->params.sf_nsec;

	cfg_addr = t4_flash_cfg_addr(adap);
	अगर (cfg_addr < 0)
		वापस cfg_addr;

	addr = cfg_addr;
	flash_cfg_start_sec = addr / SF_SEC_SIZE;

	अगर (size > FLASH_CFG_MAX_SIZE) अणु
		dev_err(adap->pdev_dev, "cfg file too large, max is %u bytes\n",
			FLASH_CFG_MAX_SIZE);
		वापस -EFBIG;
	पूर्ण

	i = DIV_ROUND_UP(FLASH_CFG_MAX_SIZE,	/* # of sectors spanned */
			 sf_sec_size);
	ret = t4_flash_erase_sectors(adap, flash_cfg_start_sec,
				     flash_cfg_start_sec + i - 1);
	/* If size == 0 then we're simply erasing the FLASH sectors associated
	 * with the on-adapter Firmware Configuration File.
	 */
	अगर (ret || size == 0)
		जाओ out;

	/* this will ग_लिखो to the flash up to SF_PAGE_SIZE at a समय */
	क्रम (i = 0; i < size; i += SF_PAGE_SIZE) अणु
		अगर ((size - i) <  SF_PAGE_SIZE)
			n = size - i;
		अन्यथा
			n = SF_PAGE_SIZE;
		ret = t4_ग_लिखो_flash(adap, addr, n, cfg_data, true);
		अगर (ret)
			जाओ out;

		addr += SF_PAGE_SIZE;
		cfg_data += SF_PAGE_SIZE;
	पूर्ण

out:
	अगर (ret)
		dev_err(adap->pdev_dev, "config file %s failed %d\n",
			(size == 0 ? "clear" : "download"), ret);
	वापस ret;
पूर्ण

/**
 *	t4_set_vf_mac - Set MAC address क्रम the specअगरied VF
 *	@adapter: The adapter
 *	@vf: one of the VFs instantiated by the specअगरied PF
 *	@naddr: the number of MAC addresses
 *	@addr: the MAC address(es) to be set to the specअगरied VF
 */
पूर्णांक t4_set_vf_mac_acl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक vf,
		      अचिन्हित पूर्णांक naddr, u8 *addr)
अणु
	काष्ठा fw_acl_mac_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_ACL_MAC_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F |
				    FW_ACL_MAC_CMD_PFN_V(adapter->pf) |
				    FW_ACL_MAC_CMD_VFN_V(vf));

	/* Note: Do not enable the ACL */
	cmd.en_to_len16 = cpu_to_be32((अचिन्हित पूर्णांक)FW_LEN16(cmd));
	cmd.nmac = naddr;

	चयन (adapter->pf) अणु
	हाल 3:
		स_नकल(cmd.macaddr3, addr, माप(cmd.macaddr3));
		अवरोध;
	हाल 2:
		स_नकल(cmd.macaddr2, addr, माप(cmd.macaddr2));
		अवरोध;
	हाल 1:
		स_नकल(cmd.macaddr1, addr, माप(cmd.macaddr1));
		अवरोध;
	हाल 0:
		स_नकल(cmd.macaddr0, addr, माप(cmd.macaddr0));
		अवरोध;
	पूर्ण

	वापस t4_wr_mbox(adapter, adapter->mbox, &cmd, माप(cmd), &cmd);
पूर्ण

/**
 * t4_पढ़ो_pace_tbl - पढ़ो the pace table
 * @adap: the adapter
 * @pace_vals: holds the वापसed values
 *
 * Returns the values of TP's pace table in microseconds.
 */
व्योम t4_पढ़ो_pace_tbl(काष्ठा adapter *adap, अचिन्हित पूर्णांक pace_vals[NTX_SCHED])
अणु
	अचिन्हित पूर्णांक i, v;

	क्रम (i = 0; i < NTX_SCHED; i++) अणु
		t4_ग_लिखो_reg(adap, TP_PACE_TABLE_A, 0xffff0000 + i);
		v = t4_पढ़ो_reg(adap, TP_PACE_TABLE_A);
		pace_vals[i] = dack_ticks_to_usec(adap, v);
	पूर्ण
पूर्ण

/**
 * t4_get_tx_sched - get the configuration of a Tx HW traffic scheduler
 * @adap: the adapter
 * @sched: the scheduler index
 * @kbps: the byte rate in Kbps
 * @ipg: the पूर्णांकerpacket delay in tenths of nanoseconds
 * @sleep_ok: अगर true we may sleep जबतक aरुकोing command completion
 *
 * Return the current configuration of a HW Tx scheduler.
 */
व्योम t4_get_tx_sched(काष्ठा adapter *adap, अचिन्हित पूर्णांक sched,
		     अचिन्हित पूर्णांक *kbps, अचिन्हित पूर्णांक *ipg, bool sleep_ok)
अणु
	अचिन्हित पूर्णांक v, addr, bpt, cpt;

	अगर (kbps) अणु
		addr = TP_TX_MOD_Q1_Q0_RATE_LIMIT_A - sched / 2;
		t4_tp_पंचांग_pio_पढ़ो(adap, &v, 1, addr, sleep_ok);
		अगर (sched & 1)
			v >>= 16;
		bpt = (v >> 8) & 0xff;
		cpt = v & 0xff;
		अगर (!cpt) अणु
			*kbps = 0;	/* scheduler disabled */
		पूर्ण अन्यथा अणु
			v = (adap->params.vpd.cclk * 1000) / cpt; /* ticks/s */
			*kbps = (v * bpt) / 125;
		पूर्ण
	पूर्ण
	अगर (ipg) अणु
		addr = TP_TX_MOD_Q1_Q0_TIMER_SEPARATOR_A - sched / 2;
		t4_tp_पंचांग_pio_पढ़ो(adap, &v, 1, addr, sleep_ok);
		अगर (sched & 1)
			v >>= 16;
		v &= 0xffff;
		*ipg = (10000 * v) / core_ticks_per_usec(adap);
	पूर्ण
पूर्ण

/* t4_sge_ctxt_rd - पढ़ो an SGE context through FW
 * @adap: the adapter
 * @mbox: mailbox to use क्रम the FW command
 * @cid: the context id
 * @ctype: the context type
 * @data: where to store the context data
 *
 * Issues a FW command through the given mailbox to पढ़ो an SGE context.
 */
पूर्णांक t4_sge_ctxt_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक cid,
		   क्रमागत ctxt_type ctype, u32 *data)
अणु
	काष्ठा fw_ldst_cmd c;
	पूर्णांक ret;

	अगर (ctype == CTXT_FLM)
		ret = FW_LDST_ADDRSPC_SGE_FLMC;
	अन्यथा
		ret = FW_LDST_ADDRSPC_SGE_CONMC;

	स_रखो(&c, 0, माप(c));
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F | FW_CMD_READ_F |
					FW_LDST_CMD_ADDRSPACE_V(ret));
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.idctxt.physid = cpu_to_be32(cid);

	ret = t4_wr_mbox(adap, mbox, &c, माप(c), &c);
	अगर (ret == 0) अणु
		data[0] = be32_to_cpu(c.u.idctxt.ctxt_data0);
		data[1] = be32_to_cpu(c.u.idctxt.ctxt_data1);
		data[2] = be32_to_cpu(c.u.idctxt.ctxt_data2);
		data[3] = be32_to_cpu(c.u.idctxt.ctxt_data3);
		data[4] = be32_to_cpu(c.u.idctxt.ctxt_data4);
		data[5] = be32_to_cpu(c.u.idctxt.ctxt_data5);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * t4_sge_ctxt_rd_bd - पढ़ो an SGE context bypassing FW
 * @adap: the adapter
 * @cid: the context id
 * @ctype: the context type
 * @data: where to store the context data
 *
 * Reads an SGE context directly, bypassing FW.  This is only क्रम
 * debugging when FW is unavailable.
 */
पूर्णांक t4_sge_ctxt_rd_bd(काष्ठा adapter *adap, अचिन्हित पूर्णांक cid,
		      क्रमागत ctxt_type ctype, u32 *data)
अणु
	पूर्णांक i, ret;

	t4_ग_लिखो_reg(adap, SGE_CTXT_CMD_A, CTXTQID_V(cid) | CTXTTYPE_V(ctype));
	ret = t4_रुको_op_करोne(adap, SGE_CTXT_CMD_A, BUSY_F, 0, 3, 1);
	अगर (!ret)
		क्रम (i = SGE_CTXT_DATA0_A; i <= SGE_CTXT_DATA5_A; i += 4)
			*data++ = t4_पढ़ो_reg(adap, i);
	वापस ret;
पूर्ण

पूर्णांक t4_sched_params(काष्ठा adapter *adapter, u8 type, u8 level, u8 mode,
		    u8 rateunit, u8 ratemode, u8 channel, u8 class,
		    u32 minrate, u32 maxrate, u16 weight, u16 pktsize,
		    u16 burstsize)
अणु
	काष्ठा fw_sched_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.op_to_ग_लिखो = cpu_to_be32(FW_CMD_OP_V(FW_SCHED_CMD) |
				      FW_CMD_REQUEST_F |
				      FW_CMD_WRITE_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	cmd.u.params.sc = FW_SCHED_SC_PARAMS;
	cmd.u.params.type = type;
	cmd.u.params.level = level;
	cmd.u.params.mode = mode;
	cmd.u.params.ch = channel;
	cmd.u.params.cl = class;
	cmd.u.params.unit = rateunit;
	cmd.u.params.rate = ratemode;
	cmd.u.params.min = cpu_to_be32(minrate);
	cmd.u.params.max = cpu_to_be32(maxrate);
	cmd.u.params.weight = cpu_to_be16(weight);
	cmd.u.params.pktsize = cpu_to_be16(pktsize);
	cmd.u.params.burstsize = cpu_to_be16(burstsize);

	वापस t4_wr_mbox_meat(adapter, adapter->mbox, &cmd, माप(cmd),
			       शून्य, 1);
पूर्ण

/**
 *	t4_i2c_rd - पढ़ो I2C data from adapter
 *	@adap: the adapter
 *	@mbox: mailbox to use क्रम the FW command
 *	@port: Port number अगर per-port device; <0 अगर not
 *	@devid: per-port device ID or असलolute device ID
 *	@offset: byte offset पूर्णांकo device I2C space
 *	@len: byte length of I2C space data
 *	@buf: buffer in which to वापस I2C data
 *
 *	Reads the I2C data from the indicated device and location.
 */
पूर्णांक t4_i2c_rd(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, पूर्णांक port,
	      अचिन्हित पूर्णांक devid, अचिन्हित पूर्णांक offset,
	      अचिन्हित पूर्णांक len, u8 *buf)
अणु
	काष्ठा fw_ldst_cmd ldst_cmd, ldst_rpl;
	अचिन्हित पूर्णांक i2c_max = माप(ldst_cmd.u.i2c.data);
	पूर्णांक ret = 0;

	अगर (len > I2C_PAGE_SIZE)
		वापस -EINVAL;

	/* Dont allow पढ़ोs that spans multiple pages */
	अगर (offset < I2C_PAGE_SIZE && offset + len > I2C_PAGE_SIZE)
		वापस -EINVAL;

	स_रखो(&ldst_cmd, 0, माप(ldst_cmd));
	ldst_cmd.op_to_addrspace =
		cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
			    FW_CMD_REQUEST_F |
			    FW_CMD_READ_F |
			    FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_I2C));
	ldst_cmd.cycles_to_len16 = cpu_to_be32(FW_LEN16(ldst_cmd));
	ldst_cmd.u.i2c.pid = (port < 0 ? 0xff : port);
	ldst_cmd.u.i2c.did = devid;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक i2c_len = (len < i2c_max) ? len : i2c_max;

		ldst_cmd.u.i2c.boffset = offset;
		ldst_cmd.u.i2c.blen = i2c_len;

		ret = t4_wr_mbox(adap, mbox, &ldst_cmd, माप(ldst_cmd),
				 &ldst_rpl);
		अगर (ret)
			अवरोध;

		स_नकल(buf, ldst_rpl.u.i2c.data, i2c_len);
		offset += i2c_len;
		buf += i2c_len;
		len -= i2c_len;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *      t4_set_vlan_acl - Set a VLAN id क्रम the specअगरied VF
 *      @adap: the adapter
 *      @mbox: mailbox to use क्रम the FW command
 *      @vf: one of the VFs instantiated by the specअगरied PF
 *      @vlan: The vlanid to be set
 */
पूर्णांक t4_set_vlan_acl(काष्ठा adapter *adap, अचिन्हित पूर्णांक mbox, अचिन्हित पूर्णांक vf,
		    u16 vlan)
अणु
	काष्ठा fw_acl_vlan_cmd vlan_cmd;
	अचिन्हित पूर्णांक enable;

	enable = (vlan ? FW_ACL_VLAN_CMD_EN_F : 0);
	स_रखो(&vlan_cmd, 0, माप(vlan_cmd));
	vlan_cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_ACL_VLAN_CMD) |
					 FW_CMD_REQUEST_F |
					 FW_CMD_WRITE_F |
					 FW_CMD_EXEC_F |
					 FW_ACL_VLAN_CMD_PFN_V(adap->pf) |
					 FW_ACL_VLAN_CMD_VFN_V(vf));
	vlan_cmd.en_to_len16 = cpu_to_be32(enable | FW_LEN16(vlan_cmd));
	/* Drop all packets that करोnot match vlan id */
	vlan_cmd.dropnovlan_fm = (enable
				  ? (FW_ACL_VLAN_CMD_DROPNOVLAN_F |
				     FW_ACL_VLAN_CMD_FM_F) : 0);
	अगर (enable != 0) अणु
		vlan_cmd.nvlan = 1;
		vlan_cmd.vlanid[0] = cpu_to_be16(vlan);
	पूर्ण

	वापस t4_wr_mbox(adap, adap->mbox, &vlan_cmd, माप(vlan_cmd), शून्य);
पूर्ण

/**
 *	modअगरy_device_id - Modअगरies the device ID of the Boot BIOS image
 *	@device_id: the device ID to ग_लिखो.
 *	@boot_data: the boot image to modअगरy.
 *
 *	Write the supplied device ID to the boot BIOS image.
 */
अटल व्योम modअगरy_device_id(पूर्णांक device_id, u8 *boot_data)
अणु
	काष्ठा cxgb4_pcir_data *pcir_header;
	काष्ठा legacy_pci_rom_hdr *header;
	u8 *cur_header = boot_data;
	u16 pcir_offset;

	 /* Loop through all chained images and change the device ID's */
	करो अणु
		header = (काष्ठा legacy_pci_rom_hdr *)cur_header;
		pcir_offset = le16_to_cpu(header->pcir_offset);
		pcir_header = (काष्ठा cxgb4_pcir_data *)(cur_header +
			      pcir_offset);

		/**
		 * Only modअगरy the Device ID अगर code type is Legacy or HP.
		 * 0x00: Okay to modअगरy
		 * 0x01: FCODE. Do not modअगरy
		 * 0x03: Okay to modअगरy
		 * 0x04-0xFF: Do not modअगरy
		 */
		अगर (pcir_header->code_type == CXGB4_HDR_CODE1) अणु
			u8 csum = 0;
			पूर्णांक i;

			/**
			 * Modअगरy Device ID to match current adatper
			 */
			pcir_header->device_id = cpu_to_le16(device_id);

			/**
			 * Set checksum temporarily to 0.
			 * We will recalculate it later.
			 */
			header->cksum = 0x0;

			/**
			 * Calculate and update checksum
			 */
			क्रम (i = 0; i < (header->size512 * 512); i++)
				csum += cur_header[i];

			/**
			 * Invert summed value to create the checksum
			 * Writing new checksum value directly to the boot data
			 */
			cur_header[7] = -csum;

		पूर्ण अन्यथा अगर (pcir_header->code_type == CXGB4_HDR_CODE2) अणु
			/**
			 * Modअगरy Device ID to match current adatper
			 */
			pcir_header->device_id = cpu_to_le16(device_id);
		पूर्ण

		/**
		 * Move header poपूर्णांकer up to the next image in the ROM.
		 */
		cur_header += header->size512 * 512;
	पूर्ण जबतक (!(pcir_header->indicator & CXGB4_HDR_INDI));
पूर्ण

/**
 *	t4_load_boot - करोwnload boot flash
 *	@adap: the adapter
 *	@boot_data: the boot image to ग_लिखो
 *	@boot_addr: offset in flash to ग_लिखो boot_data
 *	@size: image size
 *
 *	Write the supplied boot image to the card's serial flash.
 *	The boot image has the following sections: a 28-byte header and the
 *	boot image.
 */
पूर्णांक t4_load_boot(काष्ठा adapter *adap, u8 *boot_data,
		 अचिन्हित पूर्णांक boot_addr, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक sf_sec_size = adap->params.sf_size / adap->params.sf_nsec;
	अचिन्हित पूर्णांक boot_sector = (boot_addr * 1024);
	काष्ठा cxgb4_pci_exp_rom_header *header;
	काष्ठा cxgb4_pcir_data *pcir_header;
	पूर्णांक pcir_offset;
	अचिन्हित पूर्णांक i;
	u16 device_id;
	पूर्णांक ret, addr;

	/**
	 * Make sure the boot image करोes not encroach on the firmware region
	 */
	अगर ((boot_sector + size) >> 16 > FLASH_FW_START_SEC) अणु
		dev_err(adap->pdev_dev, "boot image encroaching on firmware region\n");
		वापस -EFBIG;
	पूर्ण

	/* Get boot header */
	header = (काष्ठा cxgb4_pci_exp_rom_header *)boot_data;
	pcir_offset = le16_to_cpu(header->pcir_offset);
	/* PCIR Data Structure */
	pcir_header = (काष्ठा cxgb4_pcir_data *)&boot_data[pcir_offset];

	/**
	 * Perक्रमm some primitive sanity testing to aव्योम accidentally
	 * writing garbage over the boot sectors.  We ought to check क्रम
	 * more but it's not worth it क्रम now ...
	 */
	अगर (size < BOOT_MIN_SIZE || size > BOOT_MAX_SIZE) अणु
		dev_err(adap->pdev_dev, "boot image too small/large\n");
		वापस -EFBIG;
	पूर्ण

	अगर (le16_to_cpu(header->signature) != BOOT_SIGNATURE) अणु
		dev_err(adap->pdev_dev, "Boot image missing signature\n");
		वापस -EINVAL;
	पूर्ण

	/* Check PCI header signature */
	अगर (le32_to_cpu(pcir_header->signature) != PCIR_SIGNATURE) अणु
		dev_err(adap->pdev_dev, "PCI header missing signature\n");
		वापस -EINVAL;
	पूर्ण

	/* Check Venकरोr ID matches Chelsio ID*/
	अगर (le16_to_cpu(pcir_header->venकरोr_id) != PCI_VENDOR_ID_CHELSIO) अणु
		dev_err(adap->pdev_dev, "Vendor ID missing signature\n");
		वापस -EINVAL;
	पूर्ण

	/**
	 * The boot sector is comprised of the Expansion-ROM boot, iSCSI boot,
	 * and Boot configuration data sections. These 3 boot sections span
	 * sectors 0 to 7 in flash and live right beक्रमe the FW image location.
	 */
	i = DIV_ROUND_UP(size ? size : FLASH_FW_START,  sf_sec_size);
	ret = t4_flash_erase_sectors(adap, boot_sector >> 16,
				     (boot_sector >> 16) + i - 1);

	/**
	 * If size == 0 then we're simply erasing the FLASH sectors associated
	 * with the on-adapter option ROM file
	 */
	अगर (ret || size == 0)
		जाओ out;
	/* Retrieve adapter's device ID */
	pci_पढ़ो_config_word(adap->pdev, PCI_DEVICE_ID, &device_id);
       /* Want to deal with PF 0 so I strip off PF 4 indicator */
	device_id = device_id & 0xf0ff;

	 /* Check PCIE Device ID */
	अगर (le16_to_cpu(pcir_header->device_id) != device_id) अणु
		/**
		 * Change the device ID in the Boot BIOS image to match
		 * the Device ID of the current adapter.
		 */
		modअगरy_device_id(device_id, boot_data);
	पूर्ण

	/**
	 * Skip over the first SF_PAGE_SIZE worth of data and ग_लिखो it after
	 * we finish copying the rest of the boot image. This will ensure
	 * that the BIOS boot header will only be written अगर the boot image
	 * was written in full.
	 */
	addr = boot_sector;
	क्रम (size -= SF_PAGE_SIZE; size; size -= SF_PAGE_SIZE) अणु
		addr += SF_PAGE_SIZE;
		boot_data += SF_PAGE_SIZE;
		ret = t4_ग_लिखो_flash(adap, addr, SF_PAGE_SIZE, boot_data,
				     false);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = t4_ग_लिखो_flash(adap, boot_sector, SF_PAGE_SIZE,
			     (स्थिर u8 *)header, false);

out:
	अगर (ret)
		dev_err(adap->pdev_dev, "boot image load failed, error %d\n",
			ret);
	वापस ret;
पूर्ण

/**
 *	t4_flash_bootcfg_addr - वापस the address of the flash
 *	optionrom configuration
 *	@adapter: the adapter
 *
 *	Return the address within the flash where the OptionROM Configuration
 *	is stored, or an error अगर the device FLASH is too small to contain
 *	a OptionROM Configuration.
 */
अटल पूर्णांक t4_flash_bootcfg_addr(काष्ठा adapter *adapter)
अणु
	/**
	 * If the device FLASH isn't large enough to hold a Firmware
	 * Configuration File, वापस an error.
	 */
	अगर (adapter->params.sf_size <
	    FLASH_BOOTCFG_START + FLASH_BOOTCFG_MAX_SIZE)
		वापस -ENOSPC;

	वापस FLASH_BOOTCFG_START;
पूर्ण

पूर्णांक t4_load_bootcfg(काष्ठा adapter *adap, स्थिर u8 *cfg_data, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक sf_sec_size = adap->params.sf_size / adap->params.sf_nsec;
	काष्ठा cxgb4_bootcfg_data *header;
	अचिन्हित पूर्णांक flash_cfg_start_sec;
	अचिन्हित पूर्णांक addr, npad;
	पूर्णांक ret, i, n, cfg_addr;

	cfg_addr = t4_flash_bootcfg_addr(adap);
	अगर (cfg_addr < 0)
		वापस cfg_addr;

	addr = cfg_addr;
	flash_cfg_start_sec = addr / SF_SEC_SIZE;

	अगर (size > FLASH_BOOTCFG_MAX_SIZE) अणु
		dev_err(adap->pdev_dev, "bootcfg file too large, max is %u bytes\n",
			FLASH_BOOTCFG_MAX_SIZE);
		वापस -EFBIG;
	पूर्ण

	header = (काष्ठा cxgb4_bootcfg_data *)cfg_data;
	अगर (le16_to_cpu(header->signature) != BOOT_CFG_SIG) अणु
		dev_err(adap->pdev_dev, "Wrong bootcfg signature\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	i = DIV_ROUND_UP(FLASH_BOOTCFG_MAX_SIZE,
			 sf_sec_size);
	ret = t4_flash_erase_sectors(adap, flash_cfg_start_sec,
				     flash_cfg_start_sec + i - 1);

	/**
	 * If size == 0 then we're simply erasing the FLASH sectors associated
	 * with the on-adapter OptionROM Configuration File.
	 */
	अगर (ret || size == 0)
		जाओ out;

	/* this will ग_लिखो to the flash up to SF_PAGE_SIZE at a समय */
	क्रम (i = 0; i < size; i += SF_PAGE_SIZE) अणु
		n = min_t(u32, size - i, SF_PAGE_SIZE);

		ret = t4_ग_लिखो_flash(adap, addr, n, cfg_data, false);
		अगर (ret)
			जाओ out;

		addr += SF_PAGE_SIZE;
		cfg_data += SF_PAGE_SIZE;
	पूर्ण

	npad = ((size + 4 - 1) & ~3) - size;
	क्रम (i = 0; i < npad; i++) अणु
		u8 data = 0;

		ret = t4_ग_लिखो_flash(adap, cfg_addr + size + i, 1, &data,
				     false);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	अगर (ret)
		dev_err(adap->pdev_dev, "boot config data %s failed %d\n",
			(size == 0 ? "clear" : "download"), ret);
	वापस ret;
पूर्ण
