<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Core driver code with मुख्य पूर्णांकerface to the I3C subप्रणाली.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hci.h"
#समावेश "ext_caps.h"
#समावेश "cmd.h"
#समावेश "dat.h"


/*
 * Host Controller Capabilities and Operation Registers
 */

#घोषणा reg_पढ़ो(r)		पढ़ोl(hci->base_regs + (r))
#घोषणा reg_ग_लिखो(r, v)		ग_लिखोl(v, hci->base_regs + (r))
#घोषणा reg_set(r, v)		reg_ग_लिखो(r, reg_पढ़ो(r) | (v))
#घोषणा reg_clear(r, v)		reg_ग_लिखो(r, reg_पढ़ो(r) & ~(v))

#घोषणा HCI_VERSION			0x00	/* HCI Version (in BCD) */

#घोषणा HC_CONTROL			0x04
#घोषणा HC_CONTROL_BUS_ENABLE		BIT(31)
#घोषणा HC_CONTROL_RESUME		BIT(30)
#घोषणा HC_CONTROL_ABORT		BIT(29)
#घोषणा HC_CONTROL_HALT_ON_CMD_TIMEOUT	BIT(12)
#घोषणा HC_CONTROL_HOT_JOIN_CTRL	BIT(8)	/* Hot-Join ACK/NACK Control */
#घोषणा HC_CONTROL_I2C_TARGET_PRESENT	BIT(7)
#घोषणा HC_CONTROL_PIO_MODE		BIT(6)	/* DMA/PIO Mode Selector */
#घोषणा HC_CONTROL_DATA_BIG_ENDIAN	BIT(4)
#घोषणा HC_CONTROL_IBA_INCLUDE		BIT(0)	/* Include I3C Broadcast Address */

#घोषणा MASTER_DEVICE_ADDR		0x08	/* Master Device Address */
#घोषणा MASTER_DYNAMIC_ADDR_VALID	BIT(31)	/* Dynamic Address is Valid */
#घोषणा MASTER_DYNAMIC_ADDR(v)		FIELD_PREP(GENMASK(22, 16), v)

#घोषणा HC_CAPABILITIES			0x0c
#घोषणा HC_CAP_SG_DC_EN			BIT(30)
#घोषणा HC_CAP_SG_IBI_EN		BIT(29)
#घोषणा HC_CAP_SG_CR_EN			BIT(28)
#घोषणा HC_CAP_MAX_DATA_LENGTH		GENMASK(24, 22)
#घोषणा HC_CAP_CMD_SIZE			GENMASK(21, 20)
#घोषणा HC_CAP_सूचीECT_COMMANDS_EN	BIT(18)
#घोषणा HC_CAP_MULTI_LANE_EN		BIT(15)
#घोषणा HC_CAP_CMD_CCC_DEFBYTE		BIT(10)
#घोषणा HC_CAP_HDR_BT_EN		BIT(8)
#घोषणा HC_CAP_HDR_TS_EN		BIT(7)
#घोषणा HC_CAP_HDR_DDR_EN		BIT(6)
#घोषणा HC_CAP_NON_CURRENT_MASTER_CAP	BIT(5)	/* master hanकरोff capable */
#घोषणा HC_CAP_DATA_BYTE_CFG_EN		BIT(4)	/* endian selection possible */
#घोषणा HC_CAP_AUTO_COMMAND		BIT(3)
#घोषणा HC_CAP_COMBO_COMMAND		BIT(2)

#घोषणा RESET_CONTROL			0x10
#घोषणा BUS_RESET			BIT(31)
#घोषणा BUS_RESET_TYPE			GENMASK(30, 29)
#घोषणा IBI_QUEUE_RST			BIT(5)
#घोषणा RX_FIFO_RST			BIT(4)
#घोषणा TX_FIFO_RST			BIT(3)
#घोषणा RESP_QUEUE_RST			BIT(2)
#घोषणा CMD_QUEUE_RST			BIT(1)
#घोषणा SOFT_RST			BIT(0)	/* Core Reset */

#घोषणा PRESENT_STATE			0x14
#घोषणा STATE_CURRENT_MASTER		BIT(2)

#घोषणा INTR_STATUS			0x20
#घोषणा INTR_STATUS_ENABLE		0x24
#घोषणा INTR_SIGNAL_ENABLE		0x28
#घोषणा INTR_FORCE			0x2c
#घोषणा INTR_HC_CMD_SEQ_UFLOW_STAT	BIT(12)	/* Cmd Sequence Underflow */
#घोषणा INTR_HC_RESET_CANCEL		BIT(11)	/* HC Cancelled Reset */
#घोषणा INTR_HC_INTERNAL_ERR		BIT(10)	/* HC Internal Error */
#घोषणा INTR_HC_PIO			BIT(8)	/* cascaded PIO पूर्णांकerrupt */
#घोषणा INTR_HC_RINGS			GENMASK(7, 0)

#घोषणा DAT_SECTION			0x30	/* Device Address Table */
#घोषणा DAT_ENTRY_SIZE			GENMASK(31, 28)
#घोषणा DAT_TABLE_SIZE			GENMASK(18, 12)
#घोषणा DAT_TABLE_OFFSET		GENMASK(11, 0)

#घोषणा DCT_SECTION			0x34	/* Device Characteristics Table */
#घोषणा DCT_ENTRY_SIZE			GENMASK(31, 28)
#घोषणा DCT_TABLE_INDEX			GENMASK(23, 19)
#घोषणा DCT_TABLE_SIZE			GENMASK(18, 12)
#घोषणा DCT_TABLE_OFFSET		GENMASK(11, 0)

#घोषणा RING_HEADERS_SECTION		0x38
#घोषणा RING_HEADERS_OFFSET		GENMASK(15, 0)

#घोषणा PIO_SECTION			0x3c
#घोषणा PIO_REGS_OFFSET			GENMASK(15, 0)	/* PIO Offset */

#घोषणा EXT_CAPS_SECTION		0x40
#घोषणा EXT_CAPS_OFFSET			GENMASK(15, 0)

#घोषणा IBI_NOTIFY_CTRL			0x58	/* IBI Notअगरy Control */
#घोषणा IBI_NOTIFY_SIR_REJECTED		BIT(3)	/* Rejected Target Interrupt Request */
#घोषणा IBI_NOTIFY_MR_REJECTED		BIT(1)	/* Rejected Master Request Control */
#घोषणा IBI_NOTIFY_HJ_REJECTED		BIT(0)	/* Rejected Hot-Join Control */

#घोषणा DEV_CTX_BASE_LO			0x60
#घोषणा DEV_CTX_BASE_HI			0x64


अटल अंतरभूत काष्ठा i3c_hci *to_i3c_hci(काष्ठा i3c_master_controller *m)
अणु
	वापस container_of(m, काष्ठा i3c_hci, master);
पूर्ण

अटल पूर्णांक i3c_hci_bus_init(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_device_info info;
	पूर्णांक ret;

	DBG("");

	अगर (hci->cmd == &mipi_i3c_hci_cmd_v1) अणु
		ret = mipi_i3c_hci_dat_v1.init(hci);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = i3c_master_get_मुक्त_addr(m, 0);
	अगर (ret < 0)
		वापस ret;
	reg_ग_लिखो(MASTER_DEVICE_ADDR,
		  MASTER_DYNAMIC_ADDR(ret) | MASTER_DYNAMIC_ADDR_VALID);
	स_रखो(&info, 0, माप(info));
	info.dyn_addr = ret;
	ret = i3c_master_set_info(m, &info);
	अगर (ret)
		वापस ret;

	ret = hci->io->init(hci);
	अगर (ret)
		वापस ret;

	reg_set(HC_CONTROL, HC_CONTROL_BUS_ENABLE);
	DBG("HC_CONTROL = %#x", reg_पढ़ो(HC_CONTROL));

	वापस 0;
पूर्ण

अटल व्योम i3c_hci_bus_cleanup(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा i3c_hci *hci = to_i3c_hci(m);

	DBG("");

	reg_clear(HC_CONTROL, HC_CONTROL_BUS_ENABLE);
	hci->io->cleanup(hci);
	अगर (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.cleanup(hci);
पूर्ण

व्योम mipi_i3c_hci_resume(काष्ठा i3c_hci *hci)
अणु
	/* the HC_CONTROL_RESUME bit is R/W1C so just पढ़ो and ग_लिखो back */
	reg_ग_लिखो(HC_CONTROL, reg_पढ़ो(HC_CONTROL));
पूर्ण

/* located here rather than pio.c because needed bits are in core reg space */
व्योम mipi_i3c_hci_pio_reset(काष्ठा i3c_hci *hci)
अणु
	reg_ग_लिखो(RESET_CONTROL, RX_FIFO_RST | TX_FIFO_RST | RESP_QUEUE_RST);
पूर्ण

/* located here rather than dct.c because needed bits are in core reg space */
व्योम mipi_i3c_hci_dct_index_reset(काष्ठा i3c_hci *hci)
अणु
	reg_ग_लिखो(DCT_SECTION, FIELD_PREP(DCT_TABLE_INDEX, 0));
पूर्ण

अटल पूर्णांक i3c_hci_send_ccc_cmd(काष्ठा i3c_master_controller *m,
				काष्ठा i3c_ccc_cmd *ccc)
अणु
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा hci_xfer *xfer;
	bool raw = !!(hci->quirks & HCI_QUIRK_RAW_CCC);
	bool prefixed = raw && !!(ccc->id & I3C_CCC_सूचीECT);
	अचिन्हित पूर्णांक nxfers = ccc->ndests + prefixed;
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक i, last, ret = 0;

	DBG("cmd=%#x rnw=%d ndests=%d data[0].len=%d",
	    ccc->id, ccc->rnw, ccc->ndests, ccc->dests[0].payload.len);

	xfer = hci_alloc_xfer(nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	अगर (prefixed) अणु
		xfer->data = शून्य;
		xfer->data_len = 0;
		xfer->rnw = false;
		hci->cmd->prep_ccc(hci, xfer, I3C_BROADCAST_ADDR,
				   ccc->id, true);
		xfer++;
	पूर्ण

	क्रम (i = 0; i < nxfers - prefixed; i++) अणु
		xfer[i].data = ccc->dests[i].payload.data;
		xfer[i].data_len = ccc->dests[i].payload.len;
		xfer[i].rnw = ccc->rnw;
		ret = hci->cmd->prep_ccc(hci, &xfer[i], ccc->dests[i].addr,
					 ccc->id, raw);
		अगर (ret)
			जाओ out;
		xfer[i].cmd_desc[0] |= CMD_0_ROC;
	पूर्ण
	last = i - 1;
	xfer[last].cmd_desc[0] |= CMD_0_TOC;
	xfer[last].completion = &करोne;

	अगर (prefixed)
		xfer--;

	ret = hci->io->queue_xfer(hci, xfer, nxfers);
	अगर (ret)
		जाओ out;
	अगर (!रुको_क्रम_completion_समयout(&करोne, HZ) &&
	    hci->io->dequeue_xfer(hci, xfer, nxfers)) अणु
		ret = -ETIME;
		जाओ out;
	पूर्ण
	क्रम (i = prefixed; i < nxfers; i++) अणु
		अगर (ccc->rnw)
			ccc->dests[i - prefixed].payload.len =
				RESP_DATA_LENGTH(xfer[i].response);
		अगर (RESP_STATUS(xfer[i].response) != RESP_SUCCESS) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ccc->rnw)
		DBG("got: %*ph",
		    ccc->dests[0].payload.len, ccc->dests[0].payload.data);

out:
	hci_मुक्त_xfer(xfer, nxfers);
	वापस ret;
पूर्ण

अटल पूर्णांक i3c_hci_daa(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा i3c_hci *hci = to_i3c_hci(m);

	DBG("");

	वापस hci->cmd->perक्रमm_daa(hci);
पूर्ण

अटल पूर्णांक i3c_hci_priv_xfers(काष्ठा i3c_dev_desc *dev,
			      काष्ठा i3c_priv_xfer *i3c_xfers,
			      पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा hci_xfer *xfer;
	DECLARE_COMPLETION_ONSTACK(करोne);
	अचिन्हित पूर्णांक size_limit;
	पूर्णांक i, last, ret = 0;

	DBG("nxfers = %d", nxfers);

	xfer = hci_alloc_xfer(nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	size_limit = 1U << (16 + FIELD_GET(HC_CAP_MAX_DATA_LENGTH, hci->caps));

	क्रम (i = 0; i < nxfers; i++) अणु
		xfer[i].data_len = i3c_xfers[i].len;
		ret = -EFBIG;
		अगर (xfer[i].data_len >= size_limit)
			जाओ out;
		xfer[i].rnw = i3c_xfers[i].rnw;
		अगर (i3c_xfers[i].rnw) अणु
			xfer[i].data = i3c_xfers[i].data.in;
		पूर्ण अन्यथा अणु
			/* silence the स्थिर qualअगरier warning with a cast */
			xfer[i].data = (व्योम *) i3c_xfers[i].data.out;
		पूर्ण
		hci->cmd->prep_i3c_xfer(hci, dev, &xfer[i]);
		xfer[i].cmd_desc[0] |= CMD_0_ROC;
	पूर्ण
	last = i - 1;
	xfer[last].cmd_desc[0] |= CMD_0_TOC;
	xfer[last].completion = &करोne;

	ret = hci->io->queue_xfer(hci, xfer, nxfers);
	अगर (ret)
		जाओ out;
	अगर (!रुको_क्रम_completion_समयout(&करोne, HZ) &&
	    hci->io->dequeue_xfer(hci, xfer, nxfers)) अणु
		ret = -ETIME;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (i3c_xfers[i].rnw)
			i3c_xfers[i].len = RESP_DATA_LENGTH(xfer[i].response);
		अगर (RESP_STATUS(xfer[i].response) != RESP_SUCCESS) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	hci_मुक्त_xfer(xfer, nxfers);
	वापस ret;
पूर्ण

अटल पूर्णांक i3c_hci_i2c_xfers(काष्ठा i2c_dev_desc *dev,
			     स्थिर काष्ठा i2c_msg *i2c_xfers, पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा hci_xfer *xfer;
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक i, last, ret = 0;

	DBG("nxfers = %d", nxfers);

	xfer = hci_alloc_xfer(nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	क्रम (i = 0; i < nxfers; i++) अणु
		xfer[i].data = i2c_xfers[i].buf;
		xfer[i].data_len = i2c_xfers[i].len;
		xfer[i].rnw = i2c_xfers[i].flags & I2C_M_RD;
		hci->cmd->prep_i2c_xfer(hci, dev, &xfer[i]);
		xfer[i].cmd_desc[0] |= CMD_0_ROC;
	पूर्ण
	last = i - 1;
	xfer[last].cmd_desc[0] |= CMD_0_TOC;
	xfer[last].completion = &करोne;

	ret = hci->io->queue_xfer(hci, xfer, nxfers);
	अगर (ret)
		जाओ out;
	अगर (!रुको_क्रम_completion_समयout(&करोne, HZ) &&
	    hci->io->dequeue_xfer(hci, xfer, nxfers)) अणु
		ret = -ETIME;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (RESP_STATUS(xfer[i].response) != RESP_SUCCESS) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	hci_मुक्त_xfer(xfer, nxfers);
	वापस ret;
पूर्ण

अटल पूर्णांक i3c_hci_attach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data;
	पूर्णांक ret;

	DBG("");

	dev_data = kzalloc(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data)
		वापस -ENOMEM;
	अगर (hci->cmd == &mipi_i3c_hci_cmd_v1) अणु
		ret = mipi_i3c_hci_dat_v1.alloc_entry(hci);
		अगर (ret < 0) अणु
			kमुक्त(dev_data);
			वापस ret;
		पूर्ण
		mipi_i3c_hci_dat_v1.set_dynamic_addr(hci, ret, dev->info.dyn_addr);
		dev_data->dat_idx = ret;
	पूर्ण
	i3c_dev_set_master_data(dev, dev_data);
	वापस 0;
पूर्ण

अटल पूर्णांक i3c_hci_reattach_i3c_dev(काष्ठा i3c_dev_desc *dev, u8 old_dyn_addr)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);

	DBG("");

	अगर (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.set_dynamic_addr(hci, dev_data->dat_idx,
					     dev->info.dyn_addr);
	वापस 0;
पूर्ण

अटल व्योम i3c_hci_detach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);

	DBG("");

	i3c_dev_set_master_data(dev, शून्य);
	अगर (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.मुक्त_entry(hci, dev_data->dat_idx);
	kमुक्त(dev_data);
पूर्ण

अटल पूर्णांक i3c_hci_attach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data;
	पूर्णांक ret;

	DBG("");

	अगर (hci->cmd != &mipi_i3c_hci_cmd_v1)
		वापस 0;
	dev_data = kzalloc(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data)
		वापस -ENOMEM;
	ret = mipi_i3c_hci_dat_v1.alloc_entry(hci);
	अगर (ret < 0) अणु
		kमुक्त(dev_data);
		वापस ret;
	पूर्ण
	mipi_i3c_hci_dat_v1.set_अटल_addr(hci, ret, dev->addr);
	mipi_i3c_hci_dat_v1.set_flags(hci, ret, DAT_0_I2C_DEVICE, 0);
	dev_data->dat_idx = ret;
	i2c_dev_set_master_data(dev, dev_data);
	वापस 0;
पूर्ण

अटल व्योम i3c_hci_detach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i2c_dev_get_master_data(dev);

	DBG("");

	अगर (dev_data) अणु
		i2c_dev_set_master_data(dev, शून्य);
		अगर (hci->cmd == &mipi_i3c_hci_cmd_v1)
			mipi_i3c_hci_dat_v1.मुक्त_entry(hci, dev_data->dat_idx);
		kमुक्त(dev_data);
	पूर्ण
पूर्ण

अटल पूर्णांक i3c_hci_request_ibi(काष्ठा i3c_dev_desc *dev,
			       स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	अचिन्हित पूर्णांक dat_idx = dev_data->dat_idx;

	अगर (req->max_payload_len != 0)
		mipi_i3c_hci_dat_v1.set_flags(hci, dat_idx, DAT_0_IBI_PAYLOAD, 0);
	अन्यथा
		mipi_i3c_hci_dat_v1.clear_flags(hci, dat_idx, DAT_0_IBI_PAYLOAD, 0);
	वापस hci->io->request_ibi(hci, dev, req);
पूर्ण

अटल व्योम i3c_hci_मुक्त_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);

	hci->io->मुक्त_ibi(hci, dev);
पूर्ण

अटल पूर्णांक i3c_hci_enable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);

	mipi_i3c_hci_dat_v1.clear_flags(hci, dev_data->dat_idx, DAT_0_SIR_REJECT, 0);
	वापस i3c_master_enec_locked(m, dev->info.dyn_addr, I3C_CCC_EVENT_SIR);
पूर्ण

अटल पूर्णांक i3c_hci_disable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);

	mipi_i3c_hci_dat_v1.set_flags(hci, dev_data->dat_idx, DAT_0_SIR_REJECT, 0);
	वापस i3c_master_disec_locked(m, dev->info.dyn_addr, I3C_CCC_EVENT_SIR);
पूर्ण

अटल व्योम i3c_hci_recycle_ibi_slot(काष्ठा i3c_dev_desc *dev,
				     काष्ठा i3c_ibi_slot *slot)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा i3c_hci *hci = to_i3c_hci(m);

	hci->io->recycle_ibi_slot(hci, dev, slot);
पूर्ण

अटल स्थिर काष्ठा i3c_master_controller_ops i3c_hci_ops = अणु
	.bus_init		= i3c_hci_bus_init,
	.bus_cleanup		= i3c_hci_bus_cleanup,
	.करो_daa			= i3c_hci_daa,
	.send_ccc_cmd		= i3c_hci_send_ccc_cmd,
	.priv_xfers		= i3c_hci_priv_xfers,
	.i2c_xfers		= i3c_hci_i2c_xfers,
	.attach_i3c_dev		= i3c_hci_attach_i3c_dev,
	.reattach_i3c_dev	= i3c_hci_reattach_i3c_dev,
	.detach_i3c_dev		= i3c_hci_detach_i3c_dev,
	.attach_i2c_dev		= i3c_hci_attach_i2c_dev,
	.detach_i2c_dev		= i3c_hci_detach_i2c_dev,
	.request_ibi		= i3c_hci_request_ibi,
	.मुक्त_ibi		= i3c_hci_मुक्त_ibi,
	.enable_ibi		= i3c_hci_enable_ibi,
	.disable_ibi		= i3c_hci_disable_ibi,
	.recycle_ibi_slot	= i3c_hci_recycle_ibi_slot,
पूर्ण;

अटल irqवापस_t i3c_hci_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i3c_hci *hci = dev_id;
	irqवापस_t result = IRQ_NONE;
	u32 val;

	val = reg_पढ़ो(INTR_STATUS);
	DBG("INTR_STATUS = %#x", val);

	अगर (val) अणु
		reg_ग_लिखो(INTR_STATUS, val);
	पूर्ण अन्यथा अणु
		/* v1.0 करोes not have PIO cascaded notअगरication bits */
		val |= INTR_HC_PIO;
	पूर्ण

	अगर (val & INTR_HC_RESET_CANCEL) अणु
		DBG("cancelled reset");
		val &= ~INTR_HC_RESET_CANCEL;
	पूर्ण
	अगर (val & INTR_HC_INTERNAL_ERR) अणु
		dev_err(&hci->master.dev, "Host Controller Internal Error\n");
		val &= ~INTR_HC_INTERNAL_ERR;
	पूर्ण
	अगर (val & INTR_HC_PIO) अणु
		hci->io->irq_handler(hci, 0);
		val &= ~INTR_HC_PIO;
	पूर्ण
	अगर (val & INTR_HC_RINGS) अणु
		hci->io->irq_handler(hci, val & INTR_HC_RINGS);
		val &= ~INTR_HC_RINGS;
	पूर्ण
	अगर (val)
		dev_err(&hci->master.dev, "unexpected INTR_STATUS %#x\n", val);
	अन्यथा
		result = IRQ_HANDLED;

	वापस result;
पूर्ण

अटल पूर्णांक i3c_hci_init(काष्ठा i3c_hci *hci)
अणु
	u32 regval, offset;
	पूर्णांक ret;

	/* Validate HCI hardware version */
	regval = reg_पढ़ो(HCI_VERSION);
	hci->version_major = (regval >> 8) & 0xf;
	hci->version_minor = (regval >> 4) & 0xf;
	hci->revision = regval & 0xf;
	dev_notice(&hci->master.dev, "MIPI I3C HCI v%u.%u r%02u\n",
		   hci->version_major, hci->version_minor, hci->revision);
	/* known versions */
	चयन (regval & ~0xf) अणु
	हाल 0x100:	/* version 1.0 */
	हाल 0x110:	/* version 1.1 */
	हाल 0x200:	/* version 2.0 */
		अवरोध;
	शेष:
		dev_err(&hci->master.dev, "unsupported HCI version\n");
		वापस -EPROTONOSUPPORT;
	पूर्ण

	hci->caps = reg_पढ़ो(HC_CAPABILITIES);
	DBG("caps = %#x", hci->caps);

	regval = reg_पढ़ो(DAT_SECTION);
	offset = FIELD_GET(DAT_TABLE_OFFSET, regval);
	hci->DAT_regs = offset ? hci->base_regs + offset : शून्य;
	hci->DAT_entries = FIELD_GET(DAT_TABLE_SIZE, regval);
	hci->DAT_entry_size = FIELD_GET(DAT_ENTRY_SIZE, regval);
	dev_info(&hci->master.dev, "DAT: %u %u-bytes entries at offset %#x\n",
		 hci->DAT_entries, hci->DAT_entry_size * 4, offset);

	regval = reg_पढ़ो(DCT_SECTION);
	offset = FIELD_GET(DCT_TABLE_OFFSET, regval);
	hci->DCT_regs = offset ? hci->base_regs + offset : शून्य;
	hci->DCT_entries = FIELD_GET(DCT_TABLE_SIZE, regval);
	hci->DCT_entry_size = FIELD_GET(DCT_ENTRY_SIZE, regval);
	dev_info(&hci->master.dev, "DCT: %u %u-bytes entries at offset %#x\n",
		 hci->DCT_entries, hci->DCT_entry_size * 4, offset);

	regval = reg_पढ़ो(RING_HEADERS_SECTION);
	offset = FIELD_GET(RING_HEADERS_OFFSET, regval);
	hci->RHS_regs = offset ? hci->base_regs + offset : शून्य;
	dev_info(&hci->master.dev, "Ring Headers at offset %#x\n", offset);

	regval = reg_पढ़ो(PIO_SECTION);
	offset = FIELD_GET(PIO_REGS_OFFSET, regval);
	hci->PIO_regs = offset ? hci->base_regs + offset : शून्य;
	dev_info(&hci->master.dev, "PIO section at offset %#x\n", offset);

	regval = reg_पढ़ो(EXT_CAPS_SECTION);
	offset = FIELD_GET(EXT_CAPS_OFFSET, regval);
	hci->EXTCAPS_regs = offset ? hci->base_regs + offset : शून्य;
	dev_info(&hci->master.dev, "Extended Caps at offset %#x\n", offset);

	ret = i3c_hci_parse_ext_caps(hci);
	अगर (ret)
		वापस ret;

	/*
	 * Now let's reset the hardware.
	 * SOFT_RST must be clear beक्रमe we ग_लिखो to it.
	 * Then we must रुको until it clears again.
	 */
	ret = पढ़ोx_poll_समयout(reg_पढ़ो, RESET_CONTROL, regval,
				 !(regval & SOFT_RST), 1, 10000);
	अगर (ret)
		वापस -ENXIO;
	reg_ग_लिखो(RESET_CONTROL, SOFT_RST);
	ret = पढ़ोx_poll_समयout(reg_पढ़ो, RESET_CONTROL, regval,
				 !(regval & SOFT_RST), 1, 10000);
	अगर (ret)
		वापस -ENXIO;

	/* Disable all पूर्णांकerrupts and allow all संकेत updates */
	reg_ग_लिखो(INTR_SIGNAL_ENABLE, 0x0);
	reg_ग_लिखो(INTR_STATUS_ENABLE, 0xffffffff);

	/* Make sure our data ordering fits the host's */
	regval = reg_पढ़ो(HC_CONTROL);
	अगर (IS_ENABLED(CONFIG_BIG_ENDIAN)) अणु
		अगर (!(regval & HC_CONTROL_DATA_BIG_ENDIAN)) अणु
			regval |= HC_CONTROL_DATA_BIG_ENDIAN;
			reg_ग_लिखो(HC_CONTROL, regval);
			regval = reg_पढ़ो(HC_CONTROL);
			अगर (!(regval & HC_CONTROL_DATA_BIG_ENDIAN)) अणु
				dev_err(&hci->master.dev, "cannot set BE mode\n");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (regval & HC_CONTROL_DATA_BIG_ENDIAN) अणु
			regval &= ~HC_CONTROL_DATA_BIG_ENDIAN;
			reg_ग_लिखो(HC_CONTROL, regval);
			regval = reg_पढ़ो(HC_CONTROL);
			अगर (regval & HC_CONTROL_DATA_BIG_ENDIAN) अणु
				dev_err(&hci->master.dev, "cannot clear BE mode\n");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Select our command descriptor model */
	चयन (FIELD_GET(HC_CAP_CMD_SIZE, hci->caps)) अणु
	हाल 0:
		hci->cmd = &mipi_i3c_hci_cmd_v1;
		अवरोध;
	हाल 1:
		hci->cmd = &mipi_i3c_hci_cmd_v2;
		अवरोध;
	शेष:
		dev_err(&hci->master.dev, "wrong CMD_SIZE capability value\n");
		वापस -EINVAL;
	पूर्ण

	/* Try activating DMA operations first */
	अगर (hci->RHS_regs) अणु
		reg_clear(HC_CONTROL, HC_CONTROL_PIO_MODE);
		अगर (reg_पढ़ो(HC_CONTROL) & HC_CONTROL_PIO_MODE) अणु
			dev_err(&hci->master.dev, "PIO mode is stuck\n");
			ret = -EIO;
		पूर्ण अन्यथा अणु
			hci->io = &mipi_i3c_hci_dma;
			dev_info(&hci->master.dev, "Using DMA\n");
		पूर्ण
	पूर्ण

	/* If no DMA, try PIO */
	अगर (!hci->io && hci->PIO_regs) अणु
		reg_set(HC_CONTROL, HC_CONTROL_PIO_MODE);
		अगर (!(reg_पढ़ो(HC_CONTROL) & HC_CONTROL_PIO_MODE)) अणु
			dev_err(&hci->master.dev, "DMA mode is stuck\n");
			ret = -EIO;
		पूर्ण अन्यथा अणु
			hci->io = &mipi_i3c_hci_pio;
			dev_info(&hci->master.dev, "Using PIO\n");
		पूर्ण
	पूर्ण

	अगर (!hci->io) अणु
		dev_err(&hci->master.dev, "neither DMA nor PIO can be used\n");
		अगर (!ret)
			ret = -EINVAL;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i3c_hci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i3c_hci *hci;
	पूर्णांक irq, ret;

	hci = devm_kzalloc(&pdev->dev, माप(*hci), GFP_KERNEL);
	अगर (!hci)
		वापस -ENOMEM;
	hci->base_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hci->base_regs))
		वापस PTR_ERR(hci->base_regs);

	platक्रमm_set_drvdata(pdev, hci);
	/* temporary क्रम dev_prपूर्णांकk's, to be replaced in i3c_master_रेजिस्टर */
	hci->master.dev.init_name = dev_name(&pdev->dev);

	ret = i3c_hci_init(hci);
	अगर (ret)
		वापस ret;

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq, i3c_hci_irq_handler,
			       0, शून्य, hci);
	अगर (ret)
		वापस ret;

	ret = i3c_master_रेजिस्टर(&hci->master, &pdev->dev,
				  &i3c_hci_ops, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक i3c_hci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i3c_hci *hci = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = i3c_master_unरेजिस्टर(&hci->master);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id i3c_hci_of_match[] = अणु
	अणु .compatible = "mipi-i3c-hci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i3c_hci_of_match);

अटल काष्ठा platक्रमm_driver i3c_hci_driver = अणु
	.probe = i3c_hci_probe,
	.हटाओ = i3c_hci_हटाओ,
	.driver = अणु
		.name = "mipi-i3c-hci",
		.of_match_table = of_match_ptr(i3c_hci_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(i3c_hci_driver);

MODULE_AUTHOR("Nicolas Pitre <npitre@baylibre.com>");
MODULE_DESCRIPTION("MIPI I3C HCI driver");
MODULE_LICENSE("Dual BSD/GPL");
