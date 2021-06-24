<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * I3C HCI v1.0/v1.1 Command Descriptor Handling
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/i3c/master.h>

#समावेश "hci.h"
#समावेश "cmd.h"
#समावेश "dat.h"
#समावेश "dct.h"


/*
 * Address Assignment Command
 */

#घोषणा CMD_0_ATTR_A			FIELD_PREP(CMD_0_ATTR, 0x2)

#घोषणा CMD_A0_TOC				   W0_BIT_(31)
#घोषणा CMD_A0_ROC				   W0_BIT_(30)
#घोषणा CMD_A0_DEV_COUNT(v)		FIELD_PREP(W0_MASK(29, 26), v)
#घोषणा CMD_A0_DEV_INDEX(v)		FIELD_PREP(W0_MASK(20, 16), v)
#घोषणा CMD_A0_CMD(v)			FIELD_PREP(W0_MASK(14,  7), v)
#घोषणा CMD_A0_TID(v)			FIELD_PREP(W0_MASK( 6,  3), v)

/*
 * Immediate Data Transfer Command
 */

#घोषणा CMD_0_ATTR_I			FIELD_PREP(CMD_0_ATTR, 0x1)

#घोषणा CMD_I1_DATA_BYTE_4(v)		FIELD_PREP(W1_MASK(63, 56), v)
#घोषणा CMD_I1_DATA_BYTE_3(v)		FIELD_PREP(W1_MASK(55, 48), v)
#घोषणा CMD_I1_DATA_BYTE_2(v)		FIELD_PREP(W1_MASK(47, 40), v)
#घोषणा CMD_I1_DATA_BYTE_1(v)		FIELD_PREP(W1_MASK(39, 32), v)
#घोषणा CMD_I1_DEF_BYTE(v)		FIELD_PREP(W1_MASK(39, 32), v)
#घोषणा CMD_I0_TOC				   W0_BIT_(31)
#घोषणा CMD_I0_ROC				   W0_BIT_(30)
#घोषणा CMD_I0_RNW				   W0_BIT_(29)
#घोषणा CMD_I0_MODE(v)			FIELD_PREP(W0_MASK(28, 26), v)
#घोषणा CMD_I0_DTT(v)			FIELD_PREP(W0_MASK(25, 23), v)
#घोषणा CMD_I0_DEV_INDEX(v)		FIELD_PREP(W0_MASK(20, 16), v)
#घोषणा CMD_I0_CP				   W0_BIT_(15)
#घोषणा CMD_I0_CMD(v)			FIELD_PREP(W0_MASK(14,  7), v)
#घोषणा CMD_I0_TID(v)			FIELD_PREP(W0_MASK( 6,  3), v)

/*
 * Regular Data Transfer Command
 */

#घोषणा CMD_0_ATTR_R			FIELD_PREP(CMD_0_ATTR, 0x0)

#घोषणा CMD_R1_DATA_LENGTH(v)		FIELD_PREP(W1_MASK(63, 48), v)
#घोषणा CMD_R1_DEF_BYTE(v)		FIELD_PREP(W1_MASK(39, 32), v)
#घोषणा CMD_R0_TOC				   W0_BIT_(31)
#घोषणा CMD_R0_ROC				   W0_BIT_(30)
#घोषणा CMD_R0_RNW				   W0_BIT_(29)
#घोषणा CMD_R0_MODE(v)			FIELD_PREP(W0_MASK(28, 26), v)
#घोषणा CMD_R0_DBP				   W0_BIT_(25)
#घोषणा CMD_R0_DEV_INDEX(v)		FIELD_PREP(W0_MASK(20, 16), v)
#घोषणा CMD_R0_CP				   W0_BIT_(15)
#घोषणा CMD_R0_CMD(v)			FIELD_PREP(W0_MASK(14,  7), v)
#घोषणा CMD_R0_TID(v)			FIELD_PREP(W0_MASK( 6,  3), v)

/*
 * Combo Transfer (Write + Write/Read) Command
 */

#घोषणा CMD_0_ATTR_C			FIELD_PREP(CMD_0_ATTR, 0x3)

#घोषणा CMD_C1_DATA_LENGTH(v)		FIELD_PREP(W1_MASK(63, 48), v)
#घोषणा CMD_C1_OFFSET(v)		FIELD_PREP(W1_MASK(47, 32), v)
#घोषणा CMD_C0_TOC				   W0_BIT_(31)
#घोषणा CMD_C0_ROC				   W0_BIT_(30)
#घोषणा CMD_C0_RNW				   W0_BIT_(29)
#घोषणा CMD_C0_MODE(v)			FIELD_PREP(W0_MASK(28, 26), v)
#घोषणा CMD_C0_16_BIT_SUBOFFSET			   W0_BIT_(25)
#घोषणा CMD_C0_FIRST_PHASE_MODE			   W0_BIT_(24)
#घोषणा CMD_C0_DATA_LENGTH_POSITION(v)	FIELD_PREP(W0_MASK(23, 22), v)
#घोषणा CMD_C0_DEV_INDEX(v)		FIELD_PREP(W0_MASK(20, 16), v)
#घोषणा CMD_C0_CP				   W0_BIT_(15)
#घोषणा CMD_C0_CMD(v)			FIELD_PREP(W0_MASK(14,  7), v)
#घोषणा CMD_C0_TID(v)			FIELD_PREP(W0_MASK( 6,  3), v)

/*
 * Internal Control Command
 */

#घोषणा CMD_0_ATTR_M			FIELD_PREP(CMD_0_ATTR, 0x7)

#घोषणा CMD_M1_VENDOR_SPECIFIC			   W1_MASK(63, 32)
#घोषणा CMD_M0_MIPI_RESERVED			   W0_MASK(31, 12)
#घोषणा CMD_M0_MIPI_CMD				   W0_MASK(11,  8)
#घोषणा CMD_M0_VENDOR_INFO_PRESENT		   W0_BIT_( 7)
#घोषणा CMD_M0_TID(v)			FIELD_PREP(W0_MASK( 6,  3), v)


/* Data Transfer Speed and Mode */
क्रमागत hci_cmd_mode अणु
	MODE_I3C_SDR0		= 0x0,
	MODE_I3C_SDR1		= 0x1,
	MODE_I3C_SDR2		= 0x2,
	MODE_I3C_SDR3		= 0x3,
	MODE_I3C_SDR4		= 0x4,
	MODE_I3C_HDR_TSx	= 0x5,
	MODE_I3C_HDR_DDR	= 0x6,
	MODE_I3C_HDR_BT		= 0x7,
	MODE_I3C_Fm_FmP		= 0x8,
	MODE_I2C_Fm		= 0x0,
	MODE_I2C_FmP		= 0x1,
	MODE_I2C_UD1		= 0x2,
	MODE_I2C_UD2		= 0x3,
	MODE_I2C_UD3		= 0x4,
पूर्ण;

अटल क्रमागत hci_cmd_mode get_i3c_mode(काष्ठा i3c_hci *hci)
अणु
	काष्ठा i3c_bus *bus = i3c_master_get_bus(&hci->master);

	अगर (bus->scl_rate.i3c >= 12500000)
		वापस MODE_I3C_SDR0;
	अगर (bus->scl_rate.i3c > 8000000)
		वापस MODE_I3C_SDR1;
	अगर (bus->scl_rate.i3c > 6000000)
		वापस MODE_I3C_SDR2;
	अगर (bus->scl_rate.i3c > 4000000)
		वापस MODE_I3C_SDR3;
	अगर (bus->scl_rate.i3c > 2000000)
		वापस MODE_I3C_SDR4;
	वापस MODE_I3C_Fm_FmP;
पूर्ण

अटल क्रमागत hci_cmd_mode get_i2c_mode(काष्ठा i3c_hci *hci)
अणु
	काष्ठा i3c_bus *bus = i3c_master_get_bus(&hci->master);

	अगर (bus->scl_rate.i2c >= 1000000)
		वापस MODE_I2C_FmP;
	वापस MODE_I2C_Fm;
पूर्ण

अटल व्योम fill_data_bytes(काष्ठा hci_xfer *xfer, u8 *data,
			    अचिन्हित पूर्णांक data_len)
अणु
	xfer->cmd_desc[1] = 0;
	चयन (data_len) अणु
	हाल 4:
		xfer->cmd_desc[1] |= CMD_I1_DATA_BYTE_4(data[3]);
		fallthrough;
	हाल 3:
		xfer->cmd_desc[1] |= CMD_I1_DATA_BYTE_3(data[2]);
		fallthrough;
	हाल 2:
		xfer->cmd_desc[1] |= CMD_I1_DATA_BYTE_2(data[1]);
		fallthrough;
	हाल 1:
		xfer->cmd_desc[1] |= CMD_I1_DATA_BYTE_1(data[0]);
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण
	/* we consumed all the data with the cmd descriptor */
	xfer->data = शून्य;
पूर्ण

अटल पूर्णांक hci_cmd_v1_prep_ccc(काष्ठा i3c_hci *hci,
			       काष्ठा hci_xfer *xfer,
			       u8 ccc_addr, u8 ccc_cmd, bool raw)
अणु
	अचिन्हित पूर्णांक dat_idx = 0;
	क्रमागत hci_cmd_mode mode = get_i3c_mode(hci);
	u8 *data = xfer->data;
	अचिन्हित पूर्णांक data_len = xfer->data_len;
	bool rnw = xfer->rnw;
	पूर्णांक ret;

	/* this should never happen */
	अगर (WARN_ON(raw))
		वापस -EINVAL;

	अगर (ccc_addr != I3C_BROADCAST_ADDR) अणु
		ret = mipi_i3c_hci_dat_v1.get_index(hci, ccc_addr);
		अगर (ret < 0)
			वापस ret;
		dat_idx = ret;
	पूर्ण

	xfer->cmd_tid = hci_get_tid();

	अगर (!rnw && data_len <= 4) अणु
		/* we use an Immediate Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_I |
			CMD_I0_TID(xfer->cmd_tid) |
			CMD_I0_CMD(ccc_cmd) | CMD_I0_CP |
			CMD_I0_DEV_INDEX(dat_idx) |
			CMD_I0_DTT(data_len) |
			CMD_I0_MODE(mode);
		fill_data_bytes(xfer, data, data_len);
	पूर्ण अन्यथा अणु
		/* we use a Regular Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_R |
			CMD_R0_TID(xfer->cmd_tid) |
			CMD_R0_CMD(ccc_cmd) | CMD_R0_CP |
			CMD_R0_DEV_INDEX(dat_idx) |
			CMD_R0_MODE(mode) |
			(rnw ? CMD_R0_RNW : 0);
		xfer->cmd_desc[1] =
			CMD_R1_DATA_LENGTH(data_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hci_cmd_v1_prep_i3c_xfer(काष्ठा i3c_hci *hci,
				     काष्ठा i3c_dev_desc *dev,
				     काष्ठा hci_xfer *xfer)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	अचिन्हित पूर्णांक dat_idx = dev_data->dat_idx;
	क्रमागत hci_cmd_mode mode = get_i3c_mode(hci);
	u8 *data = xfer->data;
	अचिन्हित पूर्णांक data_len = xfer->data_len;
	bool rnw = xfer->rnw;

	xfer->cmd_tid = hci_get_tid();

	अगर (!rnw && data_len <= 4) अणु
		/* we use an Immediate Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_I |
			CMD_I0_TID(xfer->cmd_tid) |
			CMD_I0_DEV_INDEX(dat_idx) |
			CMD_I0_DTT(data_len) |
			CMD_I0_MODE(mode);
		fill_data_bytes(xfer, data, data_len);
	पूर्ण अन्यथा अणु
		/* we use a Regular Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_R |
			CMD_R0_TID(xfer->cmd_tid) |
			CMD_R0_DEV_INDEX(dat_idx) |
			CMD_R0_MODE(mode) |
			(rnw ? CMD_R0_RNW : 0);
		xfer->cmd_desc[1] =
			CMD_R1_DATA_LENGTH(data_len);
	पूर्ण
पूर्ण

अटल व्योम hci_cmd_v1_prep_i2c_xfer(काष्ठा i3c_hci *hci,
				     काष्ठा i2c_dev_desc *dev,
				     काष्ठा hci_xfer *xfer)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i2c_dev_get_master_data(dev);
	अचिन्हित पूर्णांक dat_idx = dev_data->dat_idx;
	क्रमागत hci_cmd_mode mode = get_i2c_mode(hci);
	u8 *data = xfer->data;
	अचिन्हित पूर्णांक data_len = xfer->data_len;
	bool rnw = xfer->rnw;

	xfer->cmd_tid = hci_get_tid();

	अगर (!rnw && data_len <= 4) अणु
		/* we use an Immediate Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_I |
			CMD_I0_TID(xfer->cmd_tid) |
			CMD_I0_DEV_INDEX(dat_idx) |
			CMD_I0_DTT(data_len) |
			CMD_I0_MODE(mode);
		fill_data_bytes(xfer, data, data_len);
	पूर्ण अन्यथा अणु
		/* we use a Regular Data Transfer Command */
		xfer->cmd_desc[0] =
			CMD_0_ATTR_R |
			CMD_R0_TID(xfer->cmd_tid) |
			CMD_R0_DEV_INDEX(dat_idx) |
			CMD_R0_MODE(mode) |
			(rnw ? CMD_R0_RNW : 0);
		xfer->cmd_desc[1] =
			CMD_R1_DATA_LENGTH(data_len);
	पूर्ण
पूर्ण

अटल पूर्णांक hci_cmd_v1_daa(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_xfer *xfer;
	पूर्णांक ret, dat_idx = -1;
	u8 next_addr = 0;
	u64 pid;
	अचिन्हित पूर्णांक dcr, bcr;
	DECLARE_COMPLETION_ONSTACK(करोne);

	xfer = hci_alloc_xfer(2);
	अगर (!xfer)
		वापस -ENOMEM;

	/*
	 * Simple क्रम now: we allocate a temporary DAT entry, करो a single
	 * DAA, रेजिस्टर the device which will allocate its own DAT entry
	 * via the core callback, then मुक्त the temporary DAT entry.
	 * Loop until there is no more devices to assign an address to.
	 * Yes, there is room क्रम improvements.
	 */
	क्रम (;;) अणु
		ret = mipi_i3c_hci_dat_v1.alloc_entry(hci);
		अगर (ret < 0)
			अवरोध;
		dat_idx = ret;
		ret = i3c_master_get_मुक्त_addr(&hci->master, next_addr);
		अगर (ret < 0)
			अवरोध;
		next_addr = ret;

		DBG("next_addr = 0x%02x, DAA using DAT %d", next_addr, dat_idx);
		mipi_i3c_hci_dat_v1.set_dynamic_addr(hci, dat_idx, next_addr);
		mipi_i3c_hci_dct_index_reset(hci);

		xfer->cmd_tid = hci_get_tid();
		xfer->cmd_desc[0] =
			CMD_0_ATTR_A |
			CMD_A0_TID(xfer->cmd_tid) |
			CMD_A0_CMD(I3C_CCC_ENTDAA) |
			CMD_A0_DEV_INDEX(dat_idx) |
			CMD_A0_DEV_COUNT(1) |
			CMD_A0_ROC | CMD_A0_TOC;
		xfer->cmd_desc[1] = 0;
		hci->io->queue_xfer(hci, xfer, 1);
		अगर (!रुको_क्रम_completion_समयout(&करोne, HZ) &&
		    hci->io->dequeue_xfer(hci, xfer, 1)) अणु
			ret = -ETIME;
			अवरोध;
		पूर्ण
		अगर (RESP_STATUS(xfer[0].response) == RESP_ERR_NACK &&
		    RESP_STATUS(xfer[0].response) == 1) अणु
			ret = 0;  /* no more devices to be asचिन्हित */
			अवरोध;
		पूर्ण
		अगर (RESP_STATUS(xfer[0].response) != RESP_SUCCESS) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		i3c_hci_dct_get_val(hci, 0, &pid, &dcr, &bcr);
		DBG("assigned address %#x to device PID=0x%llx DCR=%#x BCR=%#x",
		    next_addr, pid, dcr, bcr);

		mipi_i3c_hci_dat_v1.मुक्त_entry(hci, dat_idx);
		dat_idx = -1;

		/*
		 * TODO: Extend the subप्रणाली layer to allow क्रम रेजिस्टरing
		 * new device and provide BCR/DCR/PID at the same समय.
		 */
		ret = i3c_master_add_i3c_dev_locked(&hci->master, next_addr);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (dat_idx >= 0)
		mipi_i3c_hci_dat_v1.मुक्त_entry(hci, dat_idx);
	hci_मुक्त_xfer(xfer, 1);
	वापस ret;
पूर्ण

स्थिर काष्ठा hci_cmd_ops mipi_i3c_hci_cmd_v1 = अणु
	.prep_ccc		= hci_cmd_v1_prep_ccc,
	.prep_i3c_xfer		= hci_cmd_v1_prep_i3c_xfer,
	.prep_i2c_xfer		= hci_cmd_v1_prep_i2c_xfer,
	.perक्रमm_daa		= hci_cmd_v1_daa,
पूर्ण;
