<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * I3C HCI v2.0 Command Descriptor Handling
 *
 * Note: The I3C HCI v2.0 spec is still in flux. The code here will change.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/i3c/master.h>

#समावेश "hci.h"
#समावेश "cmd.h"
#समावेश "xfer_mode_rate.h"


/*
 * Unअगरied Data Transfer Command
 */

#घोषणा CMD_0_ATTR_U			FIELD_PREP(CMD_0_ATTR, 0x4)

#घोषणा CMD_U3_HDR_TSP_ML_CTRL(v)	FIELD_PREP(W3_MASK(107, 104), v)
#घोषणा CMD_U3_IDB4(v)			FIELD_PREP(W3_MASK(103,  96), v)
#घोषणा CMD_U3_HDR_CMD(v)		FIELD_PREP(W3_MASK(103,  96), v)
#घोषणा CMD_U2_IDB3(v)			FIELD_PREP(W2_MASK( 95,  88), v)
#घोषणा CMD_U2_HDR_BT(v)		FIELD_PREP(W2_MASK( 95,  88), v)
#घोषणा CMD_U2_IDB2(v)			FIELD_PREP(W2_MASK( 87,  80), v)
#घोषणा CMD_U2_BT_CMD2(v)		FIELD_PREP(W2_MASK( 87,  80), v)
#घोषणा CMD_U2_IDB1(v)			FIELD_PREP(W2_MASK( 79,  72), v)
#घोषणा CMD_U2_BT_CMD1(v)		FIELD_PREP(W2_MASK( 79,  72), v)
#घोषणा CMD_U2_IDB0(v)			FIELD_PREP(W2_MASK( 71,  64), v)
#घोषणा CMD_U2_BT_CMD0(v)		FIELD_PREP(W2_MASK( 71,  64), v)
#घोषणा CMD_U1_ERR_HANDLING(v)		FIELD_PREP(W1_MASK( 63,  62), v)
#घोषणा CMD_U1_ADD_FUNC(v)		FIELD_PREP(W1_MASK( 61,  56), v)
#घोषणा CMD_U1_COMBO_XFER			   W1_BIT_( 55)
#घोषणा CMD_U1_DATA_LENGTH(v)		FIELD_PREP(W1_MASK( 53,  32), v)
#घोषणा CMD_U0_TOC				   W0_BIT_( 31)
#घोषणा CMD_U0_ROC				   W0_BIT_( 30)
#घोषणा CMD_U0_MAY_YIELD			   W0_BIT_( 29)
#घोषणा CMD_U0_NACK_RCNT(v)		FIELD_PREP(W0_MASK( 28,  27), v)
#घोषणा CMD_U0_IDB_COUNT(v)		FIELD_PREP(W0_MASK( 26,  24), v)
#घोषणा CMD_U0_MODE_INDEX(v)		FIELD_PREP(W0_MASK( 22,  18), v)
#घोषणा CMD_U0_XFER_RATE(v)		FIELD_PREP(W0_MASK( 17,  15), v)
#घोषणा CMD_U0_DEV_ADDRESS(v)		FIELD_PREP(W0_MASK( 14,   8), v)
#घोषणा CMD_U0_RnW				   W0_BIT_(  7)
#घोषणा CMD_U0_TID(v)			FIELD_PREP(W0_MASK(  6,   3), v)

/*
 * Address Assignment Command
 */

#घोषणा CMD_0_ATTR_A			FIELD_PREP(CMD_0_ATTR, 0x2)

#घोषणा CMD_A1_DATA_LENGTH(v)		FIELD_PREP(W1_MASK( 53,  32), v)
#घोषणा CMD_A0_TOC				   W0_BIT_( 31)
#घोषणा CMD_A0_ROC				   W0_BIT_( 30)
#घोषणा CMD_A0_XFER_RATE(v)		FIELD_PREP(W0_MASK( 17,  15), v)
#घोषणा CMD_A0_ASSIGN_ADDRESS(v)	FIELD_PREP(W0_MASK( 14,   8), v)
#घोषणा CMD_A0_TID(v)			FIELD_PREP(W0_MASK(  6,   3), v)


अटल अचिन्हित पूर्णांक get_i3c_rate_idx(काष्ठा i3c_hci *hci)
अणु
	काष्ठा i3c_bus *bus = i3c_master_get_bus(&hci->master);

	अगर (bus->scl_rate.i3c >= 12000000)
		वापस XFERRATE_I3C_SDR0;
	अगर (bus->scl_rate.i3c > 8000000)
		वापस XFERRATE_I3C_SDR1;
	अगर (bus->scl_rate.i3c > 6000000)
		वापस XFERRATE_I3C_SDR2;
	अगर (bus->scl_rate.i3c > 4000000)
		वापस XFERRATE_I3C_SDR3;
	अगर (bus->scl_rate.i3c > 2000000)
		वापस XFERRATE_I3C_SDR4;
	वापस XFERRATE_I3C_SDR_FM_FMP;
पूर्ण

अटल अचिन्हित पूर्णांक get_i2c_rate_idx(काष्ठा i3c_hci *hci)
अणु
	काष्ठा i3c_bus *bus = i3c_master_get_bus(&hci->master);

	अगर (bus->scl_rate.i2c >= 1000000)
		वापस XFERRATE_I2C_FMP;
	वापस XFERRATE_I2C_FM;
पूर्ण

अटल व्योम hci_cmd_v2_prep_निजी_xfer(काष्ठा i3c_hci *hci,
					 काष्ठा hci_xfer *xfer,
					 u8 addr, अचिन्हित पूर्णांक mode,
					 अचिन्हित पूर्णांक rate)
अणु
	u8 *data = xfer->data;
	अचिन्हित पूर्णांक data_len = xfer->data_len;
	bool rnw = xfer->rnw;

	xfer->cmd_tid = hci_get_tid();

	अगर (!rnw && data_len <= 5) अणु
		xfer->cmd_desc[0] =
			CMD_0_ATTR_U |
			CMD_U0_TID(xfer->cmd_tid) |
			CMD_U0_DEV_ADDRESS(addr) |
			CMD_U0_XFER_RATE(rate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(data_len);
		xfer->cmd_desc[1] =
			CMD_U1_DATA_LENGTH(0);
		xfer->cmd_desc[2] = 0;
		xfer->cmd_desc[3] = 0;
		चयन (data_len) अणु
		हाल 5:
			xfer->cmd_desc[3] |= CMD_U3_IDB4(data[4]);
			fallthrough;
		हाल 4:
			xfer->cmd_desc[2] |= CMD_U2_IDB3(data[3]);
			fallthrough;
		हाल 3:
			xfer->cmd_desc[2] |= CMD_U2_IDB2(data[2]);
			fallthrough;
		हाल 2:
			xfer->cmd_desc[2] |= CMD_U2_IDB1(data[1]);
			fallthrough;
		हाल 1:
			xfer->cmd_desc[2] |= CMD_U2_IDB0(data[0]);
			fallthrough;
		हाल 0:
			अवरोध;
		पूर्ण
		/* we consumed all the data with the cmd descriptor */
		xfer->data = शून्य;
	पूर्ण अन्यथा अणु
		xfer->cmd_desc[0] =
			CMD_0_ATTR_U |
			CMD_U0_TID(xfer->cmd_tid) |
			(rnw ? CMD_U0_RnW : 0) |
			CMD_U0_DEV_ADDRESS(addr) |
			CMD_U0_XFER_RATE(rate) |
			CMD_U0_MODE_INDEX(mode);
		xfer->cmd_desc[1] =
			CMD_U1_DATA_LENGTH(data_len);
		xfer->cmd_desc[2] = 0;
		xfer->cmd_desc[3] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hci_cmd_v2_prep_ccc(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer,
			       u8 ccc_addr, u8 ccc_cmd, bool raw)
अणु
	अचिन्हित पूर्णांक mode = XFERMODE_IDX_I3C_SDR;
	अचिन्हित पूर्णांक rate = get_i3c_rate_idx(hci);
	u8 *data = xfer->data;
	अचिन्हित पूर्णांक data_len = xfer->data_len;
	bool rnw = xfer->rnw;

	अगर (raw && ccc_addr != I3C_BROADCAST_ADDR) अणु
		hci_cmd_v2_prep_निजी_xfer(hci, xfer, ccc_addr, mode, rate);
		वापस 0;
	पूर्ण

	xfer->cmd_tid = hci_get_tid();

	अगर (!rnw && data_len <= 4) अणु
		xfer->cmd_desc[0] =
			CMD_0_ATTR_U |
			CMD_U0_TID(xfer->cmd_tid) |
			CMD_U0_DEV_ADDRESS(ccc_addr) |
			CMD_U0_XFER_RATE(rate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(data_len + (!raw ? 0 : 1));
		xfer->cmd_desc[1] =
			CMD_U1_DATA_LENGTH(0);
		xfer->cmd_desc[2] =
			CMD_U2_IDB0(ccc_cmd);
		xfer->cmd_desc[3] = 0;
		चयन (data_len) अणु
		हाल 4:
			xfer->cmd_desc[3] |= CMD_U3_IDB4(data[3]);
			fallthrough;
		हाल 3:
			xfer->cmd_desc[2] |= CMD_U2_IDB3(data[2]);
			fallthrough;
		हाल 2:
			xfer->cmd_desc[2] |= CMD_U2_IDB2(data[1]);
			fallthrough;
		हाल 1:
			xfer->cmd_desc[2] |= CMD_U2_IDB1(data[0]);
			fallthrough;
		हाल 0:
			अवरोध;
		पूर्ण
		/* we consumed all the data with the cmd descriptor */
		xfer->data = शून्य;
	पूर्ण अन्यथा अणु
		xfer->cmd_desc[0] =
			CMD_0_ATTR_U |
			CMD_U0_TID(xfer->cmd_tid) |
			(rnw ? CMD_U0_RnW : 0) |
			CMD_U0_DEV_ADDRESS(ccc_addr) |
			CMD_U0_XFER_RATE(rate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(!raw ? 0 : 1);
		xfer->cmd_desc[1] =
			CMD_U1_DATA_LENGTH(data_len);
		xfer->cmd_desc[2] =
			CMD_U2_IDB0(ccc_cmd);
		xfer->cmd_desc[3] = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hci_cmd_v2_prep_i3c_xfer(काष्ठा i3c_hci *hci,
				     काष्ठा i3c_dev_desc *dev,
				     काष्ठा hci_xfer *xfer)
अणु
	अचिन्हित पूर्णांक mode = XFERMODE_IDX_I3C_SDR;
	अचिन्हित पूर्णांक rate = get_i3c_rate_idx(hci);
	u8 addr = dev->info.dyn_addr;

	hci_cmd_v2_prep_निजी_xfer(hci, xfer, addr, mode, rate);
पूर्ण

अटल व्योम hci_cmd_v2_prep_i2c_xfer(काष्ठा i3c_hci *hci,
				     काष्ठा i2c_dev_desc *dev,
				     काष्ठा hci_xfer *xfer)
अणु
	अचिन्हित पूर्णांक mode = XFERMODE_IDX_I2C;
	अचिन्हित पूर्णांक rate = get_i2c_rate_idx(hci);
	u8 addr = dev->addr;

	hci_cmd_v2_prep_निजी_xfer(hci, xfer, addr, mode, rate);
पूर्ण

अटल पूर्णांक hci_cmd_v2_daa(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_xfer *xfer;
	पूर्णांक ret;
	u8 next_addr = 0;
	u32 device_id[2];
	u64 pid;
	अचिन्हित पूर्णांक dcr, bcr;
	DECLARE_COMPLETION_ONSTACK(करोne);

	xfer = hci_alloc_xfer(2);
	अगर (!xfer)
		वापस -ENOMEM;

	xfer[0].data = &device_id;
	xfer[0].data_len = 8;
	xfer[0].rnw = true;
	xfer[0].cmd_desc[1] = CMD_A1_DATA_LENGTH(8);
	xfer[1].completion = &करोne;

	क्रम (;;) अणु
		ret = i3c_master_get_मुक्त_addr(&hci->master, next_addr);
		अगर (ret < 0)
			अवरोध;
		next_addr = ret;
		DBG("next_addr = 0x%02x", next_addr);
		xfer[0].cmd_tid = hci_get_tid();
		xfer[0].cmd_desc[0] =
			CMD_0_ATTR_A |
			CMD_A0_TID(xfer[0].cmd_tid) |
			CMD_A0_ROC;
		xfer[1].cmd_tid = hci_get_tid();
		xfer[1].cmd_desc[0] =
			CMD_0_ATTR_A |
			CMD_A0_TID(xfer[1].cmd_tid) |
			CMD_A0_ASSIGN_ADDRESS(next_addr) |
			CMD_A0_ROC |
			CMD_A0_TOC;
		hci->io->queue_xfer(hci, xfer, 2);
		अगर (!रुको_क्रम_completion_समयout(&करोne, HZ) &&
		    hci->io->dequeue_xfer(hci, xfer, 2)) अणु
			ret = -ETIME;
			अवरोध;
		पूर्ण
		अगर (RESP_STATUS(xfer[0].response) != RESP_SUCCESS) अणु
			ret = 0;  /* no more devices to be asचिन्हित */
			अवरोध;
		पूर्ण
		अगर (RESP_STATUS(xfer[1].response) != RESP_SUCCESS) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		pid = FIELD_GET(W1_MASK(47, 32), device_id[1]);
		pid = (pid << 32) | device_id[0];
		bcr = FIELD_GET(W1_MASK(55, 48), device_id[1]);
		dcr = FIELD_GET(W1_MASK(63, 56), device_id[1]);
		DBG("assigned address %#x to device PID=0x%llx DCR=%#x BCR=%#x",
		    next_addr, pid, dcr, bcr);
		/*
		 * TODO: Extend the subप्रणाली layer to allow क्रम रेजिस्टरing
		 * new device and provide BCR/DCR/PID at the same समय.
		 */
		ret = i3c_master_add_i3c_dev_locked(&hci->master, next_addr);
		अगर (ret)
			अवरोध;
	पूर्ण

	hci_मुक्त_xfer(xfer, 2);
	वापस ret;
पूर्ण

स्थिर काष्ठा hci_cmd_ops mipi_i3c_hci_cmd_v2 = अणु
	.prep_ccc		= hci_cmd_v2_prep_ccc,
	.prep_i3c_xfer		= hci_cmd_v2_prep_i3c_xfer,
	.prep_i2c_xfer		= hci_cmd_v2_prep_i2c_xfer,
	.perक्रमm_daa		= hci_cmd_v2_daa,
पूर्ण;
