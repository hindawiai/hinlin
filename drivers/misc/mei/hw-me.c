<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/pci.h>

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>

#समावेश "mei_dev.h"
#समावेश "hbm.h"

#समावेश "hw-me.h"
#समावेश "hw-me-regs.h"

#समावेश "mei-trace.h"

/**
 * mei_me_reg_पढ़ो - Reads 32bit data from the mei device
 *
 * @hw: the me hardware काष्ठाure
 * @offset: offset from which to पढ़ो the data
 *
 * Return: रेजिस्टर value (u32)
 */
अटल अंतरभूत u32 mei_me_reg_पढ़ो(स्थिर काष्ठा mei_me_hw *hw,
			       अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो32(hw->mem_addr + offset);
पूर्ण


/**
 * mei_me_reg_ग_लिखो - Writes 32bit data to the mei device
 *
 * @hw: the me hardware काष्ठाure
 * @offset: offset from which to ग_लिखो the data
 * @value: रेजिस्टर value to ग_लिखो (u32)
 */
अटल अंतरभूत व्योम mei_me_reg_ग_लिखो(स्थिर काष्ठा mei_me_hw *hw,
				 अचिन्हित दीर्घ offset, u32 value)
अणु
	ioग_लिखो32(value, hw->mem_addr + offset);
पूर्ण

/**
 * mei_me_mecbrw_पढ़ो - Reads 32bit data from ME circular buffer
 *  पढ़ो winकरोw रेजिस्टर
 *
 * @dev: the device काष्ठाure
 *
 * Return: ME_CB_RW रेजिस्टर value (u32)
 */
अटल अंतरभूत u32 mei_me_mecbrw_पढ़ो(स्थिर काष्ठा mei_device *dev)
अणु
	वापस mei_me_reg_पढ़ो(to_me_hw(dev), ME_CB_RW);
पूर्ण

/**
 * mei_me_hcbww_ग_लिखो - ग_लिखो 32bit data to the host circular buffer
 *
 * @dev: the device काष्ठाure
 * @data: 32bit data to be written to the host circular buffer
 */
अटल अंतरभूत व्योम mei_me_hcbww_ग_लिखो(काष्ठा mei_device *dev, u32 data)
अणु
	mei_me_reg_ग_लिखो(to_me_hw(dev), H_CB_WW, data);
पूर्ण

/**
 * mei_me_mecsr_पढ़ो - Reads 32bit data from the ME CSR
 *
 * @dev: the device काष्ठाure
 *
 * Return: ME_CSR_HA रेजिस्टर value (u32)
 */
अटल अंतरभूत u32 mei_me_mecsr_पढ़ो(स्थिर काष्ठा mei_device *dev)
अणु
	u32 reg;

	reg = mei_me_reg_पढ़ो(to_me_hw(dev), ME_CSR_HA);
	trace_mei_reg_पढ़ो(dev->dev, "ME_CSR_HA", ME_CSR_HA, reg);

	वापस reg;
पूर्ण

/**
 * mei_hcsr_पढ़ो - Reads 32bit data from the host CSR
 *
 * @dev: the device काष्ठाure
 *
 * Return: H_CSR रेजिस्टर value (u32)
 */
अटल अंतरभूत u32 mei_hcsr_पढ़ो(स्थिर काष्ठा mei_device *dev)
अणु
	u32 reg;

	reg = mei_me_reg_पढ़ो(to_me_hw(dev), H_CSR);
	trace_mei_reg_पढ़ो(dev->dev, "H_CSR", H_CSR, reg);

	वापस reg;
पूर्ण

/**
 * mei_hcsr_ग_लिखो - ग_लिखोs H_CSR रेजिस्टर to the mei device
 *
 * @dev: the device काष्ठाure
 * @reg: new रेजिस्टर value
 */
अटल अंतरभूत व्योम mei_hcsr_ग_लिखो(काष्ठा mei_device *dev, u32 reg)
अणु
	trace_mei_reg_ग_लिखो(dev->dev, "H_CSR", H_CSR, reg);
	mei_me_reg_ग_लिखो(to_me_hw(dev), H_CSR, reg);
पूर्ण

/**
 * mei_hcsr_set - ग_लिखोs H_CSR रेजिस्टर to the mei device,
 * and ignores the H_IS bit क्रम it is ग_लिखो-one-to-zero.
 *
 * @dev: the device काष्ठाure
 * @reg: new रेजिस्टर value
 */
अटल अंतरभूत व्योम mei_hcsr_set(काष्ठा mei_device *dev, u32 reg)
अणु
	reg &= ~H_CSR_IS_MASK;
	mei_hcsr_ग_लिखो(dev, reg);
पूर्ण

/**
 * mei_hcsr_set_hig - set host पूर्णांकerrupt (set H_IG)
 *
 * @dev: the device काष्ठाure
 */
अटल अंतरभूत व्योम mei_hcsr_set_hig(काष्ठा mei_device *dev)
अणु
	u32 hcsr;

	hcsr = mei_hcsr_पढ़ो(dev) | H_IG;
	mei_hcsr_set(dev, hcsr);
पूर्ण

/**
 * mei_me_d0i3c_पढ़ो - Reads 32bit data from the D0I3C रेजिस्टर
 *
 * @dev: the device काष्ठाure
 *
 * Return: H_D0I3C रेजिस्टर value (u32)
 */
अटल अंतरभूत u32 mei_me_d0i3c_पढ़ो(स्थिर काष्ठा mei_device *dev)
अणु
	u32 reg;

	reg = mei_me_reg_पढ़ो(to_me_hw(dev), H_D0I3C);
	trace_mei_reg_पढ़ो(dev->dev, "H_D0I3C", H_D0I3C, reg);

	वापस reg;
पूर्ण

/**
 * mei_me_d0i3c_ग_लिखो - ग_लिखोs H_D0I3C रेजिस्टर to device
 *
 * @dev: the device काष्ठाure
 * @reg: new रेजिस्टर value
 */
अटल अंतरभूत व्योम mei_me_d0i3c_ग_लिखो(काष्ठा mei_device *dev, u32 reg)
अणु
	trace_mei_reg_ग_लिखो(dev->dev, "H_D0I3C", H_D0I3C, reg);
	mei_me_reg_ग_लिखो(to_me_hw(dev), H_D0I3C, reg);
पूर्ण

/**
 * mei_me_trc_status - पढ़ो trc status रेजिस्टर
 *
 * @dev: mei device
 * @trc: trc status रेजिस्टर value
 *
 * Return: 0 on success, error otherwise
 */
अटल पूर्णांक mei_me_trc_status(काष्ठा mei_device *dev, u32 *trc)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (!hw->cfg->hw_trc_supported)
		वापस -EOPNOTSUPP;

	*trc = mei_me_reg_पढ़ो(hw, ME_TRC);
	trace_mei_reg_पढ़ो(dev->dev, "ME_TRC", ME_TRC, *trc);

	वापस 0;
पूर्ण

/**
 * mei_me_fw_status - पढ़ो fw status रेजिस्टर from pci config space
 *
 * @dev: mei device
 * @fw_status: fw status रेजिस्टर values
 *
 * Return: 0 on success, error otherwise
 */
अटल पूर्णांक mei_me_fw_status(काष्ठा mei_device *dev,
			    काष्ठा mei_fw_status *fw_status)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	स्थिर काष्ठा mei_fw_status *fw_src = &hw->cfg->fw_status;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!fw_status || !hw->पढ़ो_fws)
		वापस -EINVAL;

	fw_status->count = fw_src->count;
	क्रम (i = 0; i < fw_src->count && i < MEI_FW_STATUS_MAX; i++) अणु
		ret = hw->पढ़ो_fws(dev, fw_src->status[i],
				   &fw_status->status[i]);
		trace_mei_pci_cfg_पढ़ो(dev->dev, "PCI_CFG_HFS_X",
				       fw_src->status[i],
				       fw_status->status[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_me_hw_config - configure hw dependent settings
 *
 * @dev: mei device
 *
 * Return:
 *  * -EINVAL when पढ़ो_fws is not set
 *  * 0 on success
 *
 */
अटल पूर्णांक mei_me_hw_config(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	u32 hcsr, reg;

	अगर (WARN_ON(!hw->पढ़ो_fws))
		वापस -EINVAL;

	/* Doesn't change in runसमय */
	hcsr = mei_hcsr_पढ़ो(dev);
	hw->hbuf_depth = (hcsr & H_CBD) >> 24;

	reg = 0;
	hw->पढ़ो_fws(dev, PCI_CFG_HFS_1, &reg);
	trace_mei_pci_cfg_पढ़ो(dev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, reg);
	hw->d0i3_supported =
		((reg & PCI_CFG_HFS_1_D0I3_MSK) == PCI_CFG_HFS_1_D0I3_MSK);

	hw->pg_state = MEI_PG_OFF;
	अगर (hw->d0i3_supported) अणु
		reg = mei_me_d0i3c_पढ़ो(dev);
		अगर (reg & H_D0I3C_I3)
			hw->pg_state = MEI_PG_ON;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_me_pg_state  - translate पूर्णांकernal pg state
 *   to the mei घातer gating state
 *
 * @dev:  mei device
 *
 * Return: MEI_PG_OFF अगर aliveness is on and MEI_PG_ON otherwise
 */
अटल अंतरभूत क्रमागत mei_pg_state mei_me_pg_state(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	वापस hw->pg_state;
पूर्ण

अटल अंतरभूत u32 me_पूर्णांकr_src(u32 hcsr)
अणु
	वापस hcsr & H_CSR_IS_MASK;
पूर्ण

/**
 * me_पूर्णांकr_disable - disables mei device पूर्णांकerrupts
 *      using supplied hcsr रेजिस्टर value.
 *
 * @dev: the device काष्ठाure
 * @hcsr: supplied hcsr रेजिस्टर value
 */
अटल अंतरभूत व्योम me_पूर्णांकr_disable(काष्ठा mei_device *dev, u32 hcsr)
अणु
	hcsr &= ~H_CSR_IE_MASK;
	mei_hcsr_set(dev, hcsr);
पूर्ण

/**
 * me_पूर्णांकr_clear - clear and stop पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 * @hcsr: supplied hcsr रेजिस्टर value
 */
अटल अंतरभूत व्योम me_पूर्णांकr_clear(काष्ठा mei_device *dev, u32 hcsr)
अणु
	अगर (me_पूर्णांकr_src(hcsr))
		mei_hcsr_ग_लिखो(dev, hcsr);
पूर्ण

/**
 * mei_me_पूर्णांकr_clear - clear and stop पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_पूर्णांकr_clear(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	me_पूर्णांकr_clear(dev, hcsr);
पूर्ण
/**
 * mei_me_पूर्णांकr_enable - enables mei device पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_पूर्णांकr_enable(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	hcsr |= H_CSR_IE_MASK;
	mei_hcsr_set(dev, hcsr);
पूर्ण

/**
 * mei_me_पूर्णांकr_disable - disables mei device पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_पूर्णांकr_disable(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	me_पूर्णांकr_disable(dev, hcsr);
पूर्ण

/**
 * mei_me_synchronize_irq - रुको क्रम pending IRQ handlers
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_synchronize_irq(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	synchronize_irq(hw->irq);
पूर्ण

/**
 * mei_me_hw_reset_release - release device from the reset
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_hw_reset_release(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	hcsr |= H_IG;
	hcsr &= ~H_RST;
	mei_hcsr_set(dev, hcsr);
पूर्ण

/**
 * mei_me_host_set_पढ़ोy - enable device
 *
 * @dev: mei device
 */
अटल व्योम mei_me_host_set_पढ़ोy(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	hcsr |= H_CSR_IE_MASK | H_IG | H_RDY;
	mei_hcsr_set(dev, hcsr);
पूर्ण

/**
 * mei_me_host_is_पढ़ोy - check whether the host has turned पढ़ोy
 *
 * @dev: mei device
 * Return: bool
 */
अटल bool mei_me_host_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	u32 hcsr = mei_hcsr_पढ़ो(dev);

	वापस (hcsr & H_RDY) == H_RDY;
पूर्ण

/**
 * mei_me_hw_is_पढ़ोy - check whether the me(hw) has turned पढ़ोy
 *
 * @dev: mei device
 * Return: bool
 */
अटल bool mei_me_hw_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	u32 mecsr = mei_me_mecsr_पढ़ो(dev);

	वापस (mecsr & ME_RDY_HRA) == ME_RDY_HRA;
पूर्ण

/**
 * mei_me_hw_is_resetting - check whether the me(hw) is in reset
 *
 * @dev: mei device
 * Return: bool
 */
अटल bool mei_me_hw_is_resetting(काष्ठा mei_device *dev)
अणु
	u32 mecsr = mei_me_mecsr_पढ़ो(dev);

	वापस (mecsr & ME_RST_HRA) == ME_RST_HRA;
पूर्ण

/**
 * mei_me_hw_पढ़ोy_रुको - रुको until the me(hw) has turned पढ़ोy
 *  or समयout is reached
 *
 * @dev: mei device
 * Return: 0 on success, error otherwise
 */
अटल पूर्णांक mei_me_hw_पढ़ोy_रुको(काष्ठा mei_device *dev)
अणु
	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_hw_पढ़ोy,
			dev->recvd_hw_पढ़ोy,
			mei_secs_to_jअगरfies(MEI_HW_READY_TIMEOUT));
	mutex_lock(&dev->device_lock);
	अगर (!dev->recvd_hw_पढ़ोy) अणु
		dev_err(dev->dev, "wait hw ready failed\n");
		वापस -ETIME;
	पूर्ण

	mei_me_hw_reset_release(dev);
	dev->recvd_hw_पढ़ोy = false;
	वापस 0;
पूर्ण

/**
 * mei_me_hw_start - hw start routine
 *
 * @dev: mei device
 * Return: 0 on success, error otherwise
 */
अटल पूर्णांक mei_me_hw_start(काष्ठा mei_device *dev)
अणु
	पूर्णांक ret = mei_me_hw_पढ़ोy_रुको(dev);

	अगर (ret)
		वापस ret;
	dev_dbg(dev->dev, "hw is ready\n");

	mei_me_host_set_पढ़ोy(dev);
	वापस ret;
पूर्ण


/**
 * mei_hbuf_filled_slots - माला_लो number of device filled buffer slots
 *
 * @dev: the device काष्ठाure
 *
 * Return: number of filled slots
 */
अटल अचिन्हित अक्षर mei_hbuf_filled_slots(काष्ठा mei_device *dev)
अणु
	u32 hcsr;
	अक्षर पढ़ो_ptr, ग_लिखो_ptr;

	hcsr = mei_hcsr_पढ़ो(dev);

	पढ़ो_ptr = (अक्षर) ((hcsr & H_CBRP) >> 8);
	ग_लिखो_ptr = (अक्षर) ((hcsr & H_CBWP) >> 16);

	वापस (अचिन्हित अक्षर) (ग_लिखो_ptr - पढ़ो_ptr);
पूर्ण

/**
 * mei_me_hbuf_is_empty - checks अगर host buffer is empty.
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर empty, false - otherwise.
 */
अटल bool mei_me_hbuf_is_empty(काष्ठा mei_device *dev)
अणु
	वापस mei_hbuf_filled_slots(dev) == 0;
पूर्ण

/**
 * mei_me_hbuf_empty_slots - counts ग_लिखो empty slots.
 *
 * @dev: the device काष्ठाure
 *
 * Return: -EOVERFLOW अगर overflow, otherwise empty slots count
 */
अटल पूर्णांक mei_me_hbuf_empty_slots(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	अचिन्हित अक्षर filled_slots, empty_slots;

	filled_slots = mei_hbuf_filled_slots(dev);
	empty_slots = hw->hbuf_depth - filled_slots;

	/* check क्रम overflow */
	अगर (filled_slots > hw->hbuf_depth)
		वापस -EOVERFLOW;

	वापस empty_slots;
पूर्ण

/**
 * mei_me_hbuf_depth - वापसs depth of the hw buffer.
 *
 * @dev: the device काष्ठाure
 *
 * Return: size of hw buffer in slots
 */
अटल u32 mei_me_hbuf_depth(स्थिर काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	वापस hw->hbuf_depth;
पूर्ण

/**
 * mei_me_hbuf_ग_लिखो - ग_लिखोs a message to host hw buffer.
 *
 * @dev: the device काष्ठाure
 * @hdr: header of message
 * @hdr_len: header length in bytes: must be multiplication of a slot (4bytes)
 * @data: payload
 * @data_len: payload length in bytes
 *
 * Return: 0 अगर success, < 0 - otherwise.
 */
अटल पूर्णांक mei_me_hbuf_ग_लिखो(काष्ठा mei_device *dev,
			     स्थिर व्योम *hdr, माप_प्रकार hdr_len,
			     स्थिर व्योम *data, माप_प्रकार data_len)
अणु
	अचिन्हित दीर्घ rem;
	अचिन्हित दीर्घ i;
	स्थिर u32 *reg_buf;
	u32 dw_cnt;
	पूर्णांक empty_slots;

	अगर (WARN_ON(!hdr || !data || hdr_len & 0x3))
		वापस -EINVAL;

	dev_dbg(dev->dev, MEI_HDR_FMT, MEI_HDR_PRM((काष्ठा mei_msg_hdr *)hdr));

	empty_slots = mei_hbuf_empty_slots(dev);
	dev_dbg(dev->dev, "empty slots = %hu.\n", empty_slots);

	अगर (empty_slots < 0)
		वापस -EOVERFLOW;

	dw_cnt = mei_data2slots(hdr_len + data_len);
	अगर (dw_cnt > (u32)empty_slots)
		वापस -EMSGSIZE;

	reg_buf = hdr;
	क्रम (i = 0; i < hdr_len / MEI_SLOT_SIZE; i++)
		mei_me_hcbww_ग_लिखो(dev, reg_buf[i]);

	reg_buf = data;
	क्रम (i = 0; i < data_len / MEI_SLOT_SIZE; i++)
		mei_me_hcbww_ग_लिखो(dev, reg_buf[i]);

	rem = data_len & 0x3;
	अगर (rem > 0) अणु
		u32 reg = 0;

		स_नकल(&reg, (स्थिर u8 *)data + data_len - rem, rem);
		mei_me_hcbww_ग_लिखो(dev, reg);
	पूर्ण

	mei_hcsr_set_hig(dev);
	अगर (!mei_me_hw_is_पढ़ोy(dev))
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * mei_me_count_full_पढ़ो_slots - counts पढ़ो full slots.
 *
 * @dev: the device काष्ठाure
 *
 * Return: -EOVERFLOW अगर overflow, otherwise filled slots count
 */
अटल पूर्णांक mei_me_count_full_पढ़ो_slots(काष्ठा mei_device *dev)
अणु
	u32 me_csr;
	अक्षर पढ़ो_ptr, ग_लिखो_ptr;
	अचिन्हित अक्षर buffer_depth, filled_slots;

	me_csr = mei_me_mecsr_पढ़ो(dev);
	buffer_depth = (अचिन्हित अक्षर)((me_csr & ME_CBD_HRA) >> 24);
	पढ़ो_ptr = (अक्षर) ((me_csr & ME_CBRP_HRA) >> 8);
	ग_लिखो_ptr = (अक्षर) ((me_csr & ME_CBWP_HRA) >> 16);
	filled_slots = (अचिन्हित अक्षर) (ग_लिखो_ptr - पढ़ो_ptr);

	/* check क्रम overflow */
	अगर (filled_slots > buffer_depth)
		वापस -EOVERFLOW;

	dev_dbg(dev->dev, "filled_slots =%08x\n", filled_slots);
	वापस (पूर्णांक)filled_slots;
पूर्ण

/**
 * mei_me_पढ़ो_slots - पढ़ोs a message from mei device.
 *
 * @dev: the device काष्ठाure
 * @buffer: message buffer will be written
 * @buffer_length: message size will be पढ़ो
 *
 * Return: always 0
 */
अटल पूर्णांक mei_me_पढ़ो_slots(काष्ठा mei_device *dev, अचिन्हित अक्षर *buffer,
			     अचिन्हित दीर्घ buffer_length)
अणु
	u32 *reg_buf = (u32 *)buffer;

	क्रम (; buffer_length >= MEI_SLOT_SIZE; buffer_length -= MEI_SLOT_SIZE)
		*reg_buf++ = mei_me_mecbrw_पढ़ो(dev);

	अगर (buffer_length > 0) अणु
		u32 reg = mei_me_mecbrw_पढ़ो(dev);

		स_नकल(reg_buf, &reg, buffer_length);
	पूर्ण

	mei_hcsr_set_hig(dev);
	वापस 0;
पूर्ण

/**
 * mei_me_pg_set - ग_लिखो pg enter रेजिस्टर
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_pg_set(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	u32 reg;

	reg = mei_me_reg_पढ़ो(hw, H_HPG_CSR);
	trace_mei_reg_पढ़ो(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);

	reg |= H_HPG_CSR_PGI;

	trace_mei_reg_ग_लिखो(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);
	mei_me_reg_ग_लिखो(hw, H_HPG_CSR, reg);
पूर्ण

/**
 * mei_me_pg_unset - ग_लिखो pg निकास रेजिस्टर
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_pg_unset(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	u32 reg;

	reg = mei_me_reg_पढ़ो(hw, H_HPG_CSR);
	trace_mei_reg_पढ़ो(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);

	WARN(!(reg & H_HPG_CSR_PGI), "PGI is not set\n");

	reg |= H_HPG_CSR_PGIHEXR;

	trace_mei_reg_ग_लिखो(dev->dev, "H_HPG_CSR", H_HPG_CSR, reg);
	mei_me_reg_ग_लिखो(hw, H_HPG_CSR, reg);
पूर्ण

/**
 * mei_me_pg_legacy_enter_sync - perक्रमm legacy pg entry procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_pg_legacy_enter_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	अचिन्हित दीर्घ समयout = mei_secs_to_jअगरfies(MEI_PGI_TIMEOUT);
	पूर्णांक ret;

	dev->pg_event = MEI_PG_EVENT_WAIT;

	ret = mei_hbm_pg(dev, MEI_PG_ISOLATION_ENTRY_REQ_CMD);
	अगर (ret)
		वापस ret;

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_RECEIVED, समयout);
	mutex_lock(&dev->device_lock);

	अगर (dev->pg_event == MEI_PG_EVENT_RECEIVED) अणु
		mei_me_pg_set(dev);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -ETIME;
	पूर्ण

	dev->pg_event = MEI_PG_EVENT_IDLE;
	hw->pg_state = MEI_PG_ON;

	वापस ret;
पूर्ण

/**
 * mei_me_pg_legacy_निकास_sync - perक्रमm legacy pg निकास procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_pg_legacy_निकास_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	अचिन्हित दीर्घ समयout = mei_secs_to_jअगरfies(MEI_PGI_TIMEOUT);
	पूर्णांक ret;

	अगर (dev->pg_event == MEI_PG_EVENT_RECEIVED)
		जाओ reply;

	dev->pg_event = MEI_PG_EVENT_WAIT;

	mei_me_pg_unset(dev);

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_RECEIVED, समयout);
	mutex_lock(&dev->device_lock);

reply:
	अगर (dev->pg_event != MEI_PG_EVENT_RECEIVED) अणु
		ret = -ETIME;
		जाओ out;
	पूर्ण

	dev->pg_event = MEI_PG_EVENT_INTR_WAIT;
	ret = mei_hbm_pg(dev, MEI_PG_ISOLATION_EXIT_RES_CMD);
	अगर (ret)
		वापस ret;

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED, समयout);
	mutex_lock(&dev->device_lock);

	अगर (dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED)
		ret = 0;
	अन्यथा
		ret = -ETIME;

out:
	dev->pg_event = MEI_PG_EVENT_IDLE;
	hw->pg_state = MEI_PG_OFF;

	वापस ret;
पूर्ण

/**
 * mei_me_pg_in_transition - is device now in pg transition
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर in pg transition, false otherwise
 */
अटल bool mei_me_pg_in_transition(काष्ठा mei_device *dev)
अणु
	वापस dev->pg_event >= MEI_PG_EVENT_WAIT &&
	       dev->pg_event <= MEI_PG_EVENT_INTR_WAIT;
पूर्ण

/**
 * mei_me_pg_is_enabled - detect अगर PG is supported by HW
 *
 * @dev: the device काष्ठाure
 *
 * Return: true is pg supported, false otherwise
 */
अटल bool mei_me_pg_is_enabled(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	u32 reg = mei_me_mecsr_पढ़ो(dev);

	अगर (hw->d0i3_supported)
		वापस true;

	अगर ((reg & ME_PGIC_HRA) == 0)
		जाओ notsupported;

	अगर (!dev->hbm_f_pg_supported)
		जाओ notsupported;

	वापस true;

notsupported:
	dev_dbg(dev->dev, "pg: not supported: d0i3 = %d HGP = %d hbm version %d.%d ?= %d.%d\n",
		hw->d0i3_supported,
		!!(reg & ME_PGIC_HRA),
		dev->version.major_version,
		dev->version.minor_version,
		HBM_MAJOR_VERSION_PGI,
		HBM_MINOR_VERSION_PGI);

	वापस false;
पूर्ण

/**
 * mei_me_d0i3_set - ग_लिखो d0i3 रेजिस्टर bit on mei device.
 *
 * @dev: the device काष्ठाure
 * @पूर्णांकr: ask क्रम पूर्णांकerrupt
 *
 * Return: D0I3C रेजिस्टर value
 */
अटल u32 mei_me_d0i3_set(काष्ठा mei_device *dev, bool पूर्णांकr)
अणु
	u32 reg = mei_me_d0i3c_पढ़ो(dev);

	reg |= H_D0I3C_I3;
	अगर (पूर्णांकr)
		reg |= H_D0I3C_IR;
	अन्यथा
		reg &= ~H_D0I3C_IR;
	mei_me_d0i3c_ग_लिखो(dev, reg);
	/* पढ़ो it to ensure HW consistency */
	reg = mei_me_d0i3c_पढ़ो(dev);
	वापस reg;
पूर्ण

/**
 * mei_me_d0i3_unset - clean d0i3 रेजिस्टर bit on mei device.
 *
 * @dev: the device काष्ठाure
 *
 * Return: D0I3C रेजिस्टर value
 */
अटल u32 mei_me_d0i3_unset(काष्ठा mei_device *dev)
अणु
	u32 reg = mei_me_d0i3c_पढ़ो(dev);

	reg &= ~H_D0I3C_I3;
	reg |= H_D0I3C_IR;
	mei_me_d0i3c_ग_लिखो(dev, reg);
	/* पढ़ो it to ensure HW consistency */
	reg = mei_me_d0i3c_पढ़ो(dev);
	वापस reg;
पूर्ण

/**
 * mei_me_d0i3_enter_sync - perक्रमm d0i3 entry procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_d0i3_enter_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	अचिन्हित दीर्घ d0i3_समयout = mei_secs_to_jअगरfies(MEI_D0I3_TIMEOUT);
	अचिन्हित दीर्घ pgi_समयout = mei_secs_to_jअगरfies(MEI_PGI_TIMEOUT);
	पूर्णांक ret;
	u32 reg;

	reg = mei_me_d0i3c_पढ़ो(dev);
	अगर (reg & H_D0I3C_I3) अणु
		/* we are in d0i3, nothing to करो */
		dev_dbg(dev->dev, "d0i3 set not needed\n");
		ret = 0;
		जाओ on;
	पूर्ण

	/* PGI entry procedure */
	dev->pg_event = MEI_PG_EVENT_WAIT;

	ret = mei_hbm_pg(dev, MEI_PG_ISOLATION_ENTRY_REQ_CMD);
	अगर (ret)
		/* FIXME: should we reset here? */
		जाओ out;

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_RECEIVED, pgi_समयout);
	mutex_lock(&dev->device_lock);

	अगर (dev->pg_event != MEI_PG_EVENT_RECEIVED) अणु
		ret = -ETIME;
		जाओ out;
	पूर्ण
	/* end PGI entry procedure */

	dev->pg_event = MEI_PG_EVENT_INTR_WAIT;

	reg = mei_me_d0i3_set(dev, true);
	अगर (!(reg & H_D0I3C_CIP)) अणु
		dev_dbg(dev->dev, "d0i3 enter wait not needed\n");
		ret = 0;
		जाओ on;
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED, d0i3_समयout);
	mutex_lock(&dev->device_lock);

	अगर (dev->pg_event != MEI_PG_EVENT_INTR_RECEIVED) अणु
		reg = mei_me_d0i3c_पढ़ो(dev);
		अगर (!(reg & H_D0I3C_I3)) अणु
			ret = -ETIME;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
on:
	hw->pg_state = MEI_PG_ON;
out:
	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_dbg(dev->dev, "d0i3 enter ret = %d\n", ret);
	वापस ret;
पूर्ण

/**
 * mei_me_d0i3_enter - perक्रमm d0i3 entry procedure
 *   no hbm PG handshake
 *   no रुकोing क्रम confirmation; runs with पूर्णांकerrupts
 *   disabled
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_d0i3_enter(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	u32 reg;

	reg = mei_me_d0i3c_पढ़ो(dev);
	अगर (reg & H_D0I3C_I3) अणु
		/* we are in d0i3, nothing to करो */
		dev_dbg(dev->dev, "already d0i3 : set not needed\n");
		जाओ on;
	पूर्ण

	mei_me_d0i3_set(dev, false);
on:
	hw->pg_state = MEI_PG_ON;
	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_dbg(dev->dev, "d0i3 enter\n");
	वापस 0;
पूर्ण

/**
 * mei_me_d0i3_निकास_sync - perक्रमm d0i3 निकास procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_d0i3_निकास_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	अचिन्हित दीर्घ समयout = mei_secs_to_jअगरfies(MEI_D0I3_TIMEOUT);
	पूर्णांक ret;
	u32 reg;

	dev->pg_event = MEI_PG_EVENT_INTR_WAIT;

	reg = mei_me_d0i3c_पढ़ो(dev);
	अगर (!(reg & H_D0I3C_I3)) अणु
		/* we are not in d0i3, nothing to करो */
		dev_dbg(dev->dev, "d0i3 exit not needed\n");
		ret = 0;
		जाओ off;
	पूर्ण

	reg = mei_me_d0i3_unset(dev);
	अगर (!(reg & H_D0I3C_CIP)) अणु
		dev_dbg(dev->dev, "d0i3 exit wait not needed\n");
		ret = 0;
		जाओ off;
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_pg,
		dev->pg_event == MEI_PG_EVENT_INTR_RECEIVED, समयout);
	mutex_lock(&dev->device_lock);

	अगर (dev->pg_event != MEI_PG_EVENT_INTR_RECEIVED) अणु
		reg = mei_me_d0i3c_पढ़ो(dev);
		अगर (reg & H_D0I3C_I3) अणु
			ret = -ETIME;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
off:
	hw->pg_state = MEI_PG_OFF;
out:
	dev->pg_event = MEI_PG_EVENT_IDLE;

	dev_dbg(dev->dev, "d0i3 exit ret = %d\n", ret);
	वापस ret;
पूर्ण

/**
 * mei_me_pg_legacy_पूर्णांकr - perक्रमm legacy pg processing
 *			   in पूर्णांकerrupt thपढ़ो handler
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_me_pg_legacy_पूर्णांकr(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (dev->pg_event != MEI_PG_EVENT_INTR_WAIT)
		वापस;

	dev->pg_event = MEI_PG_EVENT_INTR_RECEIVED;
	hw->pg_state = MEI_PG_OFF;
	अगर (रुकोqueue_active(&dev->रुको_pg))
		wake_up(&dev->रुको_pg);
पूर्ण

/**
 * mei_me_d0i3_पूर्णांकr - perक्रमm d0i3 processing in पूर्णांकerrupt thपढ़ो handler
 *
 * @dev: the device काष्ठाure
 * @पूर्णांकr_source: पूर्णांकerrupt source
 */
अटल व्योम mei_me_d0i3_पूर्णांकr(काष्ठा mei_device *dev, u32 पूर्णांकr_source)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (dev->pg_event == MEI_PG_EVENT_INTR_WAIT &&
	    (पूर्णांकr_source & H_D0I3C_IS)) अणु
		dev->pg_event = MEI_PG_EVENT_INTR_RECEIVED;
		अगर (hw->pg_state == MEI_PG_ON) अणु
			hw->pg_state = MEI_PG_OFF;
			अगर (dev->hbm_state != MEI_HBM_IDLE) अणु
				/*
				 * क्रमce H_RDY because it could be
				 * wiped off during PG
				 */
				dev_dbg(dev->dev, "d0i3 set host ready\n");
				mei_me_host_set_पढ़ोy(dev);
			पूर्ण
		पूर्ण अन्यथा अणु
			hw->pg_state = MEI_PG_ON;
		पूर्ण

		wake_up(&dev->रुको_pg);
	पूर्ण

	अगर (hw->pg_state == MEI_PG_ON && (पूर्णांकr_source & H_IS)) अणु
		/*
		 * HW sent some data and we are in D0i3, so
		 * we got here because of HW initiated निकास from D0i3.
		 * Start runसमय pm resume sequence to निकास low घातer state.
		 */
		dev_dbg(dev->dev, "d0i3 want resume\n");
		mei_hbm_pg_resume(dev);
	पूर्ण
पूर्ण

/**
 * mei_me_pg_पूर्णांकr - perक्रमm pg processing in पूर्णांकerrupt thपढ़ो handler
 *
 * @dev: the device काष्ठाure
 * @पूर्णांकr_source: पूर्णांकerrupt source
 */
अटल व्योम mei_me_pg_पूर्णांकr(काष्ठा mei_device *dev, u32 पूर्णांकr_source)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (hw->d0i3_supported)
		mei_me_d0i3_पूर्णांकr(dev, पूर्णांकr_source);
	अन्यथा
		mei_me_pg_legacy_पूर्णांकr(dev);
पूर्ण

/**
 * mei_me_pg_enter_sync - perक्रमm runसमय pm entry procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
पूर्णांक mei_me_pg_enter_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (hw->d0i3_supported)
		वापस mei_me_d0i3_enter_sync(dev);
	अन्यथा
		वापस mei_me_pg_legacy_enter_sync(dev);
पूर्ण

/**
 * mei_me_pg_निकास_sync - perक्रमm runसमय pm निकास procedure
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
पूर्णांक mei_me_pg_निकास_sync(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);

	अगर (hw->d0i3_supported)
		वापस mei_me_d0i3_निकास_sync(dev);
	अन्यथा
		वापस mei_me_pg_legacy_निकास_sync(dev);
पूर्ण

/**
 * mei_me_hw_reset - resets fw via mei csr रेजिस्टर.
 *
 * @dev: the device काष्ठाure
 * @पूर्णांकr_enable: अगर पूर्णांकerrupt should be enabled after reset.
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_me_hw_reset(काष्ठा mei_device *dev, bool पूर्णांकr_enable)
अणु
	काष्ठा mei_me_hw *hw = to_me_hw(dev);
	पूर्णांक ret;
	u32 hcsr;

	अगर (पूर्णांकr_enable) अणु
		mei_me_पूर्णांकr_enable(dev);
		अगर (hw->d0i3_supported) अणु
			ret = mei_me_d0i3_निकास_sync(dev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	pm_runसमय_set_active(dev->dev);

	hcsr = mei_hcsr_पढ़ो(dev);
	/* H_RST may be found lit beक्रमe reset is started,
	 * क्रम example अगर preceding reset flow hasn't completed.
	 * In that हाल निश्चितing H_RST will be ignored, thereक्रमe
	 * we need to clean H_RST bit to start a successful reset sequence.
	 */
	अगर ((hcsr & H_RST) == H_RST) अणु
		dev_warn(dev->dev, "H_RST is set = 0x%08X", hcsr);
		hcsr &= ~H_RST;
		mei_hcsr_set(dev, hcsr);
		hcsr = mei_hcsr_पढ़ो(dev);
	पूर्ण

	hcsr |= H_RST | H_IG | H_CSR_IS_MASK;

	अगर (!पूर्णांकr_enable)
		hcsr &= ~H_CSR_IE_MASK;

	dev->recvd_hw_पढ़ोy = false;
	mei_hcsr_ग_लिखो(dev, hcsr);

	/*
	 * Host पढ़ोs the H_CSR once to ensure that the
	 * posted ग_लिखो to H_CSR completes.
	 */
	hcsr = mei_hcsr_पढ़ो(dev);

	अगर ((hcsr & H_RST) == 0)
		dev_warn(dev->dev, "H_RST is not set = 0x%08X", hcsr);

	अगर ((hcsr & H_RDY) == H_RDY)
		dev_warn(dev->dev, "H_RDY is not cleared 0x%08X", hcsr);

	अगर (!पूर्णांकr_enable) अणु
		mei_me_hw_reset_release(dev);
		अगर (hw->d0i3_supported) अणु
			ret = mei_me_d0i3_enter(dev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mei_me_irq_quick_handler - The ISR of the MEI device
 *
 * @irq: The irq number
 * @dev_id: poपूर्णांकer to the device काष्ठाure
 *
 * Return: irqवापस_t
 */
irqवापस_t mei_me_irq_quick_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mei_device *dev = (काष्ठा mei_device *)dev_id;
	u32 hcsr;

	hcsr = mei_hcsr_पढ़ो(dev);
	अगर (!me_पूर्णांकr_src(hcsr))
		वापस IRQ_NONE;

	dev_dbg(dev->dev, "interrupt source 0x%08X\n", me_पूर्णांकr_src(hcsr));

	/* disable पूर्णांकerrupts on device */
	me_पूर्णांकr_disable(dev, hcsr);
	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * mei_me_irq_thपढ़ो_handler - function called after ISR to handle the पूर्णांकerrupt
 * processing.
 *
 * @irq: The irq number
 * @dev_id: poपूर्णांकer to the device काष्ठाure
 *
 * Return: irqवापस_t
 *
 */
irqवापस_t mei_me_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mei_device *dev = (काष्ठा mei_device *) dev_id;
	काष्ठा list_head cmpl_list;
	s32 slots;
	u32 hcsr;
	पूर्णांक rets = 0;

	dev_dbg(dev->dev, "function called after ISR to handle the interrupt processing.\n");
	/* initialize our complete list */
	mutex_lock(&dev->device_lock);

	hcsr = mei_hcsr_पढ़ो(dev);
	me_पूर्णांकr_clear(dev, hcsr);

	INIT_LIST_HEAD(&cmpl_list);

	/* check अगर ME wants a reset */
	अगर (!mei_hw_is_पढ़ोy(dev) && dev->dev_state != MEI_DEV_RESETTING) अणु
		dev_warn(dev->dev, "FW not ready: resetting.\n");
		schedule_work(&dev->reset_work);
		जाओ end;
	पूर्ण

	अगर (mei_me_hw_is_resetting(dev))
		mei_hcsr_set_hig(dev);

	mei_me_pg_पूर्णांकr(dev, me_पूर्णांकr_src(hcsr));

	/*  check अगर we need to start the dev */
	अगर (!mei_host_is_पढ़ोy(dev)) अणु
		अगर (mei_hw_is_पढ़ोy(dev)) अणु
			dev_dbg(dev->dev, "we need to start the dev.\n");
			dev->recvd_hw_पढ़ोy = true;
			wake_up(&dev->रुको_hw_पढ़ोy);
		पूर्ण अन्यथा अणु
			dev_dbg(dev->dev, "Spurious Interrupt\n");
		पूर्ण
		जाओ end;
	पूर्ण
	/* check slots available क्रम पढ़ोing */
	slots = mei_count_full_पढ़ो_slots(dev);
	जबतक (slots > 0) अणु
		dev_dbg(dev->dev, "slots to read = %08x\n", slots);
		rets = mei_irq_पढ़ो_handler(dev, &cmpl_list, &slots);
		/* There is a race between ME ग_लिखो and पूर्णांकerrupt delivery:
		 * Not all data is always available immediately after the
		 * पूर्णांकerrupt, so try to पढ़ो again on the next पूर्णांकerrupt.
		 */
		अगर (rets == -ENODATA)
			अवरोध;

		अगर (rets &&
		    (dev->dev_state != MEI_DEV_RESETTING &&
		     dev->dev_state != MEI_DEV_POWER_DOWN)) अणु
			dev_err(dev->dev, "mei_irq_read_handler ret = %d.\n",
						rets);
			schedule_work(&dev->reset_work);
			जाओ end;
		पूर्ण
	पूर्ण

	dev->hbuf_is_पढ़ोy = mei_hbuf_is_पढ़ोy(dev);

	/*
	 * During PG handshake only allowed ग_लिखो is the replay to the
	 * PG निकास message, so block calling ग_लिखो function
	 * अगर the pg event is in PG handshake
	 */
	अगर (dev->pg_event != MEI_PG_EVENT_WAIT &&
	    dev->pg_event != MEI_PG_EVENT_RECEIVED) अणु
		rets = mei_irq_ग_लिखो_handler(dev, &cmpl_list);
		dev->hbuf_is_पढ़ोy = mei_hbuf_is_पढ़ोy(dev);
	पूर्ण

	mei_irq_compl_handler(dev, &cmpl_list);

end:
	dev_dbg(dev->dev, "interrupt thread end ret = %d\n", rets);
	mei_me_पूर्णांकr_enable(dev);
	mutex_unlock(&dev->device_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा mei_hw_ops mei_me_hw_ops = अणु

	.trc_status = mei_me_trc_status,
	.fw_status = mei_me_fw_status,
	.pg_state  = mei_me_pg_state,

	.host_is_पढ़ोy = mei_me_host_is_पढ़ोy,

	.hw_is_पढ़ोy = mei_me_hw_is_पढ़ोy,
	.hw_reset = mei_me_hw_reset,
	.hw_config = mei_me_hw_config,
	.hw_start = mei_me_hw_start,

	.pg_in_transition = mei_me_pg_in_transition,
	.pg_is_enabled = mei_me_pg_is_enabled,

	.पूर्णांकr_clear = mei_me_पूर्णांकr_clear,
	.पूर्णांकr_enable = mei_me_पूर्णांकr_enable,
	.पूर्णांकr_disable = mei_me_पूर्णांकr_disable,
	.synchronize_irq = mei_me_synchronize_irq,

	.hbuf_मुक्त_slots = mei_me_hbuf_empty_slots,
	.hbuf_is_पढ़ोy = mei_me_hbuf_is_empty,
	.hbuf_depth = mei_me_hbuf_depth,

	.ग_लिखो = mei_me_hbuf_ग_लिखो,

	.rdbuf_full_slots = mei_me_count_full_पढ़ो_slots,
	.पढ़ो_hdr = mei_me_mecbrw_पढ़ो,
	.पढ़ो = mei_me_पढ़ो_slots
पूर्ण;

/**
 * mei_me_fw_type_nm() - check क्रम nm sku
 *
 * Read ME FW Status रेजिस्टर to check क्रम the Node Manager (NM) Firmware.
 * The NM FW is only संकेतed in PCI function 0.
 * __Note__: Deprecated by PCH8 and newer.
 *
 * @pdev: pci device
 *
 * Return: true in हाल of NM firmware
 */
अटल bool mei_me_fw_type_nm(स्थिर काष्ठा pci_dev *pdev)
अणु
	u32 reg;
	अचिन्हित पूर्णांक devfn;

	devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	pci_bus_पढ़ो_config_dword(pdev->bus, devfn, PCI_CFG_HFS_2, &reg);
	trace_mei_pci_cfg_पढ़ो(&pdev->dev, "PCI_CFG_HFS_2", PCI_CFG_HFS_2, reg);
	/* make sure that bit 9 (NM) is up and bit 10 (DM) is करोwn */
	वापस (reg & 0x600) == 0x200;
पूर्ण

#घोषणा MEI_CFG_FW_NM                           \
	.quirk_probe = mei_me_fw_type_nm

/**
 * mei_me_fw_sku_sps_4() - check क्रम sps 4.0 sku
 *
 * Read ME FW Status रेजिस्टर to check क्रम SPS Firmware.
 * The SPS FW is only संकेतed in the PCI function 0.
 * __Note__: Deprecated by SPS 5.0 and newer.
 *
 * @pdev: pci device
 *
 * Return: true in हाल of SPS firmware
 */
अटल bool mei_me_fw_type_sps_4(स्थिर काष्ठा pci_dev *pdev)
अणु
	u32 reg;
	अचिन्हित पूर्णांक devfn;

	devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	pci_bus_पढ़ो_config_dword(pdev->bus, devfn, PCI_CFG_HFS_1, &reg);
	trace_mei_pci_cfg_पढ़ो(&pdev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, reg);
	वापस (reg & PCI_CFG_HFS_1_OPMODE_MSK) == PCI_CFG_HFS_1_OPMODE_SPS;
पूर्ण

#घोषणा MEI_CFG_FW_SPS_4                          \
	.quirk_probe = mei_me_fw_type_sps_4

/**
 * mei_me_fw_sku_sps() - check क्रम sps sku
 *
 * Read ME FW Status रेजिस्टर to check क्रम SPS Firmware.
 * The SPS FW is only संकेतed in pci function 0
 *
 * @pdev: pci device
 *
 * Return: true in हाल of SPS firmware
 */
अटल bool mei_me_fw_type_sps(स्थिर काष्ठा pci_dev *pdev)
अणु
	u32 reg;
	u32 fw_type;
	अचिन्हित पूर्णांक devfn;

	devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	pci_bus_पढ़ो_config_dword(pdev->bus, devfn, PCI_CFG_HFS_3, &reg);
	trace_mei_pci_cfg_पढ़ो(&pdev->dev, "PCI_CFG_HFS_3", PCI_CFG_HFS_3, reg);
	fw_type = (reg & PCI_CFG_HFS_3_FW_SKU_MSK);

	dev_dbg(&pdev->dev, "fw type is %d\n", fw_type);

	वापस fw_type == PCI_CFG_HFS_3_FW_SKU_SPS;
पूर्ण

#घोषणा MEI_CFG_KIND_ITOUCH                     \
	.kind = "itouch"

#घोषणा MEI_CFG_FW_SPS                          \
	.quirk_probe = mei_me_fw_type_sps

#घोषणा MEI_CFG_FW_VER_SUPP                     \
	.fw_ver_supported = 1

#घोषणा MEI_CFG_ICH_HFS                      \
	.fw_status.count = 0

#घोषणा MEI_CFG_ICH10_HFS                        \
	.fw_status.count = 1,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1

#घोषणा MEI_CFG_PCH_HFS                         \
	.fw_status.count = 2,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1,   \
	.fw_status.status[1] = PCI_CFG_HFS_2

#घोषणा MEI_CFG_PCH8_HFS                        \
	.fw_status.count = 6,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1,   \
	.fw_status.status[1] = PCI_CFG_HFS_2,   \
	.fw_status.status[2] = PCI_CFG_HFS_3,   \
	.fw_status.status[3] = PCI_CFG_HFS_4,   \
	.fw_status.status[4] = PCI_CFG_HFS_5,   \
	.fw_status.status[5] = PCI_CFG_HFS_6

#घोषणा MEI_CFG_DMA_128 \
	.dma_size[DMA_DSCR_HOST] = SZ_128K, \
	.dma_size[DMA_DSCR_DEVICE] = SZ_128K, \
	.dma_size[DMA_DSCR_CTRL] = PAGE_SIZE

#घोषणा MEI_CFG_TRC \
	.hw_trc_supported = 1

/* ICH Legacy devices */
अटल स्थिर काष्ठा mei_cfg mei_me_ich_cfg = अणु
	MEI_CFG_ICH_HFS,
पूर्ण;

/* ICH devices */
अटल स्थिर काष्ठा mei_cfg mei_me_ich10_cfg = अणु
	MEI_CFG_ICH10_HFS,
पूर्ण;

/* PCH6 devices */
अटल स्थिर काष्ठा mei_cfg mei_me_pch6_cfg = अणु
	MEI_CFG_PCH_HFS,
पूर्ण;

/* PCH7 devices */
अटल स्थिर काष्ठा mei_cfg mei_me_pch7_cfg = अणु
	MEI_CFG_PCH_HFS,
	MEI_CFG_FW_VER_SUPP,
पूर्ण;

/* PCH Cougar Poपूर्णांक and Patsburg with quirk क्रम Node Manager exclusion */
अटल स्थिर काष्ठा mei_cfg mei_me_pch_cpt_pbg_cfg = अणु
	MEI_CFG_PCH_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_FW_NM,
पूर्ण;

/* PCH8 Lynx Poपूर्णांक and newer devices */
अटल स्थिर काष्ठा mei_cfg mei_me_pch8_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
पूर्ण;

/* PCH8 Lynx Poपूर्णांक and newer devices - iTouch */
अटल स्थिर काष्ठा mei_cfg mei_me_pch8_itouch_cfg = अणु
	MEI_CFG_KIND_ITOUCH,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
पूर्ण;

/* PCH8 Lynx Poपूर्णांक with quirk क्रम SPS Firmware exclusion */
अटल स्थिर काष्ठा mei_cfg mei_me_pch8_sps_4_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_FW_SPS_4,
पूर्ण;

/* LBG with quirk क्रम SPS (4.0) Firmware exclusion */
अटल स्थिर काष्ठा mei_cfg mei_me_pch12_sps_4_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_FW_SPS_4,
पूर्ण;

/* Cannon Lake and newer devices */
अटल स्थिर काष्ठा mei_cfg mei_me_pch12_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_DMA_128,
पूर्ण;

/* Cannon Lake with quirk क्रम SPS 5.0 and newer Firmware exclusion */
अटल स्थिर काष्ठा mei_cfg mei_me_pch12_sps_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_FW_SPS,
पूर्ण;

/* Cannon Lake itouch with quirk क्रम SPS 5.0 and newer Firmware exclusion
 * w/o DMA support.
 */
अटल स्थिर काष्ठा mei_cfg mei_me_pch12_itouch_sps_cfg = अणु
	MEI_CFG_KIND_ITOUCH,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_FW_SPS,
पूर्ण;

/* Tiger Lake and newer devices */
अटल स्थिर काष्ठा mei_cfg mei_me_pch15_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_TRC,
पूर्ण;

/* Tiger Lake with quirk क्रम SPS 5.0 and newer Firmware exclusion */
अटल स्थिर काष्ठा mei_cfg mei_me_pch15_sps_cfg = अणु
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VER_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_TRC,
	MEI_CFG_FW_SPS,
पूर्ण;

/*
 * mei_cfg_list - A list of platक्रमm platक्रमm specअगरic configurations.
 * Note: has to be synchronized with  क्रमागत mei_cfg_idx.
 */
अटल स्थिर काष्ठा mei_cfg *स्थिर mei_cfg_list[] = अणु
	[MEI_ME_UNDEF_CFG] = शून्य,
	[MEI_ME_ICH_CFG] = &mei_me_ich_cfg,
	[MEI_ME_ICH10_CFG] = &mei_me_ich10_cfg,
	[MEI_ME_PCH6_CFG] = &mei_me_pch6_cfg,
	[MEI_ME_PCH7_CFG] = &mei_me_pch7_cfg,
	[MEI_ME_PCH_CPT_PBG_CFG] = &mei_me_pch_cpt_pbg_cfg,
	[MEI_ME_PCH8_CFG] = &mei_me_pch8_cfg,
	[MEI_ME_PCH8_ITOUCH_CFG] = &mei_me_pch8_itouch_cfg,
	[MEI_ME_PCH8_SPS_4_CFG] = &mei_me_pch8_sps_4_cfg,
	[MEI_ME_PCH12_CFG] = &mei_me_pch12_cfg,
	[MEI_ME_PCH12_SPS_4_CFG] = &mei_me_pch12_sps_4_cfg,
	[MEI_ME_PCH12_SPS_CFG] = &mei_me_pch12_sps_cfg,
	[MEI_ME_PCH12_SPS_ITOUCH_CFG] = &mei_me_pch12_itouch_sps_cfg,
	[MEI_ME_PCH15_CFG] = &mei_me_pch15_cfg,
	[MEI_ME_PCH15_SPS_CFG] = &mei_me_pch15_sps_cfg,
पूर्ण;

स्थिर काष्ठा mei_cfg *mei_me_get_cfg(kernel_uदीर्घ_t idx)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(mei_cfg_list) != MEI_ME_NUM_CFG);

	अगर (idx >= MEI_ME_NUM_CFG)
		वापस शून्य;

	वापस mei_cfg_list[idx];
पूर्ण;

/**
 * mei_me_dev_init - allocates and initializes the mei device काष्ठाure
 *
 * @parent: device associated with physical device (pci/platक्रमm)
 * @cfg: per device generation config
 *
 * Return: The mei_device poपूर्णांकer on success, शून्य on failure.
 */
काष्ठा mei_device *mei_me_dev_init(काष्ठा device *parent,
				   स्थिर काष्ठा mei_cfg *cfg)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_me_hw *hw;
	पूर्णांक i;

	dev = devm_kzalloc(parent, माप(*dev) + माप(*hw), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	hw = to_me_hw(dev);

	क्रम (i = 0; i < DMA_DSCR_NUM; i++)
		dev->dr_dscr[i].size = cfg->dma_size[i];

	mei_device_init(dev, parent, &mei_me_hw_ops);
	hw->cfg = cfg;

	dev->fw_f_fw_ver_supported = cfg->fw_ver_supported;

	dev->kind = cfg->kind;

	वापस dev;
पूर्ण

