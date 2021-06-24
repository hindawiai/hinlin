<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/idr.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/rtsx_pci.h>
#समावेश <linux/mmc/card.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "rtsx_pcr.h"
#समावेश "rts5261.h"
#समावेश "rts5228.h"

अटल bool msi_en = true;
module_param(msi_en, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(msi_en, "Enable MSI");

अटल DEFINE_IDR(rtsx_pci_idr);
अटल DEFINE_SPINLOCK(rtsx_pci_lock);

अटल काष्ठा mfd_cell rtsx_pcr_cells[] = अणु
	[RTSX_SD_CARD] = अणु
		.name = DRV_NAME_RTSX_PCI_SDMMC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id rtsx_pci_ids[] = अणु
	अणु PCI_DEVICE(0x10EC, 0x5209), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5229), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5289), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5227), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x522A), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5249), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5287), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5286), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x524A), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x525A), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5260), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5261), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(0x10EC, 0x5228), PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtsx_pci_ids);

अटल पूर्णांक rtsx_comm_set_ltr_latency(काष्ठा rtsx_pcr *pcr, u32 latency)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MSGTXDATA0,
				MASK_8_BIT_DEF, (u8) (latency & 0xFF));
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MSGTXDATA1,
				MASK_8_BIT_DEF, (u8)((latency >> 8) & 0xFF));
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MSGTXDATA2,
				MASK_8_BIT_DEF, (u8)((latency >> 16) & 0xFF));
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, MSGTXDATA3,
				MASK_8_BIT_DEF, (u8)((latency >> 24) & 0xFF));
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, LTR_CTL, LTR_TX_EN_MASK |
		LTR_LATENCY_MODE_MASK, LTR_TX_EN_1 | LTR_LATENCY_MODE_SW);

	वापस 0;
पूर्ण

पूर्णांक rtsx_set_ltr_latency(काष्ठा rtsx_pcr *pcr, u32 latency)
अणु
	वापस rtsx_comm_set_ltr_latency(pcr, latency);
पूर्ण

अटल व्योम rtsx_comm_set_aspm(काष्ठा rtsx_pcr *pcr, bool enable)
अणु
	अगर (pcr->aspm_enabled == enable)
		वापस;

	अगर (pcr->aspm_mode == ASPM_MODE_CFG) अणु
		pcie_capability_clear_and_set_word(pcr->pci, PCI_EXP_LNKCTL,
						PCI_EXP_LNKCTL_ASPMC,
						enable ? pcr->aspm_en : 0);
	पूर्ण अन्यथा अगर (pcr->aspm_mode == ASPM_MODE_REG) अणु
		अगर (pcr->aspm_en & 0x02)
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, FORCE_ASPM_CTL0 |
				FORCE_ASPM_CTL1, enable ? 0 : FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1);
		अन्यथा
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, FORCE_ASPM_CTL0 |
				FORCE_ASPM_CTL1, FORCE_ASPM_CTL0 | FORCE_ASPM_CTL1);
	पूर्ण

	अगर (!enable && (pcr->aspm_en & 0x02))
		mdelay(10);

	pcr->aspm_enabled = enable;
पूर्ण

अटल व्योम rtsx_disable_aspm(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->set_aspm)
		pcr->ops->set_aspm(pcr, false);
	अन्यथा
		rtsx_comm_set_aspm(pcr, false);
पूर्ण

पूर्णांक rtsx_set_l1off_sub(काष्ठा rtsx_pcr *pcr, u8 val)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, L1SUB_CONFIG3, 0xFF, val);

	वापस 0;
पूर्ण

अटल व्योम rtsx_set_l1off_sub_cfg_d0(काष्ठा rtsx_pcr *pcr, पूर्णांक active)
अणु
	अगर (pcr->ops->set_l1off_cfg_sub_d0)
		pcr->ops->set_l1off_cfg_sub_d0(pcr, active);
पूर्ण

अटल व्योम rtsx_comm_pm_full_on(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	rtsx_disable_aspm(pcr);

	/* Fixes DMA transfer timout issue after disabling ASPM on RTS5260 */
	msleep(1);

	अगर (option->ltr_enabled)
		rtsx_set_ltr_latency(pcr, option->ltr_active_latency);

	अगर (rtsx_check_dev_flag(pcr, LTR_L1SS_PWR_GATE_EN))
		rtsx_set_l1off_sub_cfg_d0(pcr, 1);
पूर्ण

अटल व्योम rtsx_pm_full_on(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_comm_pm_full_on(pcr);
पूर्ण

व्योम rtsx_pci_start_run(काष्ठा rtsx_pcr *pcr)
अणु
	/* If pci device हटाओd, करोn't queue idle work any more */
	अगर (pcr->हटाओ_pci)
		वापस;

	अगर (pcr->rtd3_en)
		अगर (pcr->is_runसमय_suspended) अणु
			pm_runसमय_get(&(pcr->pci->dev));
			pcr->is_runसमय_suspended = false;
		पूर्ण

	अगर (pcr->state != PDEV_STAT_RUN) अणु
		pcr->state = PDEV_STAT_RUN;
		अगर (pcr->ops->enable_स्वतः_blink)
			pcr->ops->enable_स्वतः_blink(pcr);
		rtsx_pm_full_on(pcr);
	पूर्ण

	mod_delayed_work(प्रणाली_wq, &pcr->idle_work, msecs_to_jअगरfies(200));
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_start_run);

पूर्णांक rtsx_pci_ग_लिखो_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u16 addr, u8 mask, u8 data)
अणु
	पूर्णांक i;
	u32 val = HAIMR_WRITE_START;

	val |= (u32)(addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	rtsx_pci_ग_लिखोl(pcr, RTSX_HAIMR, val);

	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		val = rtsx_pci_पढ़ोl(pcr, RTSX_HAIMR);
		अगर ((val & HAIMR_TRANS_END) == 0) अणु
			अगर (data != (u8)val)
				वापस -EIO;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_ग_लिखो_रेजिस्टर);

पूर्णांक rtsx_pci_पढ़ो_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u16 addr, u8 *data)
अणु
	u32 val = HAIMR_READ_START;
	पूर्णांक i;

	val |= (u32)(addr & 0x3FFF) << 16;
	rtsx_pci_ग_लिखोl(pcr, RTSX_HAIMR, val);

	क्रम (i = 0; i < MAX_RW_REG_CNT; i++) अणु
		val = rtsx_pci_पढ़ोl(pcr, RTSX_HAIMR);
		अगर ((val & HAIMR_TRANS_END) == 0)
			अवरोध;
	पूर्ण

	अगर (i >= MAX_RW_REG_CNT)
		वापस -ETIMEDOUT;

	अगर (data)
		*data = (u8)(val & 0xFF);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_पढ़ो_रेजिस्टर);

पूर्णांक __rtsx_pci_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val)
अणु
	पूर्णांक err, i, finished = 0;
	u8 पंचांगp;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYDATA0, 0xFF, (u8)val);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYDATA1, 0xFF, (u8)(val >> 8));
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYADDR, 0xFF, addr);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYRWCTL, 0xFF, 0x81);

	क्रम (i = 0; i < 100000; i++) अणु
		err = rtsx_pci_पढ़ो_रेजिस्टर(pcr, PHYRWCTL, &पंचांगp);
		अगर (err < 0)
			वापस err;

		अगर (!(पंचांगp & 0x80)) अणु
			finished = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!finished)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक rtsx_pci_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val)
अणु
	अगर (pcr->ops->ग_लिखो_phy)
		वापस pcr->ops->ग_लिखो_phy(pcr, addr, val);

	वापस __rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, addr, val);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_ग_लिखो_phy_रेजिस्टर);

पूर्णांक __rtsx_pci_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val)
अणु
	पूर्णांक err, i, finished = 0;
	u16 data;
	u8 पंचांगp, val1, val2;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYADDR, 0xFF, addr);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PHYRWCTL, 0xFF, 0x80);

	क्रम (i = 0; i < 100000; i++) अणु
		err = rtsx_pci_पढ़ो_रेजिस्टर(pcr, PHYRWCTL, &पंचांगp);
		अगर (err < 0)
			वापस err;

		अगर (!(पंचांगp & 0x80)) अणु
			finished = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!finished)
		वापस -ETIMEDOUT;

	rtsx_pci_पढ़ो_रेजिस्टर(pcr, PHYDATA0, &val1);
	rtsx_pci_पढ़ो_रेजिस्टर(pcr, PHYDATA1, &val2);
	data = val1 | (val2 << 8);

	अगर (val)
		*val = data;

	वापस 0;
पूर्ण

पूर्णांक rtsx_pci_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val)
अणु
	अगर (pcr->ops->पढ़ो_phy)
		वापस pcr->ops->पढ़ो_phy(pcr, addr, val);

	वापस __rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, addr, val);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_पढ़ो_phy_रेजिस्टर);

व्योम rtsx_pci_stop_cmd(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->stop_cmd)
		वापस pcr->ops->stop_cmd(pcr);

	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBCTLR, STOP_CMD);
	rtsx_pci_ग_लिखोl(pcr, RTSX_HDBCTLR, STOP_DMA);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, DMACTL, 0x80, 0x80);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RBCTL, 0x80, 0x80);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_stop_cmd);

व्योम rtsx_pci_add_cmd(काष्ठा rtsx_pcr *pcr,
		u8 cmd_type, u16 reg_addr, u8 mask, u8 data)
अणु
	अचिन्हित दीर्घ flags;
	u32 val = 0;
	u32 *ptr = (u32 *)(pcr->host_cmds_ptr);

	val |= (u32)(cmd_type & 0x03) << 30;
	val |= (u32)(reg_addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	spin_lock_irqsave(&pcr->lock, flags);
	ptr += pcr->ci;
	अगर (pcr->ci < (HOST_CMDS_BUF_LEN / 4)) अणु
		put_unaligned_le32(val, ptr);
		ptr++;
		pcr->ci++;
	पूर्ण
	spin_unlock_irqrestore(&pcr->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_add_cmd);

व्योम rtsx_pci_send_cmd_no_रुको(काष्ठा rtsx_pcr *pcr)
अणु
	u32 val = 1 << 31;

	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBAR, pcr->host_cmds_addr);

	val |= (u32)(pcr->ci * 4) & 0x00FFFFFF;
	/* Hardware Auto Response */
	val |= 0x40000000;
	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBCTLR, val);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_send_cmd_no_रुको);

पूर्णांक rtsx_pci_send_cmd(काष्ठा rtsx_pcr *pcr, पूर्णांक समयout)
अणु
	काष्ठा completion trans_करोne;
	u32 val = 1 << 31;
	दीर्घ समयleft;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&pcr->lock, flags);

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	pcr->करोne = &trans_करोne;
	pcr->trans_result = TRANS_NOT_READY;
	init_completion(&trans_करोne);

	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBAR, pcr->host_cmds_addr);

	val |= (u32)(pcr->ci * 4) & 0x00FFFFFF;
	/* Hardware Auto Response */
	val |= 0x40000000;
	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBCTLR, val);

	spin_unlock_irqrestore(&pcr->lock, flags);

	/* Wait क्रम TRANS_OK_INT */
	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&trans_करोne, msecs_to_jअगरfies(समयout));
	अगर (समयleft <= 0) अणु
		pcr_dbg(pcr, "Timeout (%s %d)\n", __func__, __LINE__);
		err = -ETIMEDOUT;
		जाओ finish_send_cmd;
	पूर्ण

	spin_lock_irqsave(&pcr->lock, flags);
	अगर (pcr->trans_result == TRANS_RESULT_FAIL)
		err = -EINVAL;
	अन्यथा अगर (pcr->trans_result == TRANS_RESULT_OK)
		err = 0;
	अन्यथा अगर (pcr->trans_result == TRANS_NO_DEVICE)
		err = -ENODEV;
	spin_unlock_irqrestore(&pcr->lock, flags);

finish_send_cmd:
	spin_lock_irqsave(&pcr->lock, flags);
	pcr->करोne = शून्य;
	spin_unlock_irqrestore(&pcr->lock, flags);

	अगर ((err < 0) && (err != -ENODEV))
		rtsx_pci_stop_cmd(pcr);

	अगर (pcr->finish_me)
		complete(pcr->finish_me);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_send_cmd);

अटल व्योम rtsx_pci_add_sg_tbl(काष्ठा rtsx_pcr *pcr,
		dma_addr_t addr, अचिन्हित पूर्णांक len, पूर्णांक end)
अणु
	u64 *ptr = (u64 *)(pcr->host_sg_tbl_ptr) + pcr->sgi;
	u64 val;
	u8 option = RTSX_SG_VALID | RTSX_SG_TRANS_DATA;

	pcr_dbg(pcr, "DMA addr: 0x%x, Len: 0x%x\n", (अचिन्हित पूर्णांक)addr, len);

	अगर (end)
		option |= RTSX_SG_END;

	अगर ((PCI_PID(pcr) == PID_5261) || (PCI_PID(pcr) == PID_5228)) अणु
		अगर (len > 0xFFFF)
			val = ((u64)addr << 32) | (((u64)len & 0xFFFF) << 16)
				| (((u64)len >> 16) << 6) | option;
		अन्यथा
			val = ((u64)addr << 32) | ((u64)len << 16) | option;
	पूर्ण अन्यथा अणु
		val = ((u64)addr << 32) | ((u64)len << 12) | option;
	पूर्ण
	put_unaligned_le64(val, ptr);
	pcr->sgi++;
पूर्ण

पूर्णांक rtsx_pci_transfer_data(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो, पूर्णांक समयout)
अणु
	पूर्णांक err = 0, count;

	pcr_dbg(pcr, "--> %s: num_sg = %d\n", __func__, num_sg);
	count = rtsx_pci_dma_map_sg(pcr, sglist, num_sg, पढ़ो);
	अगर (count < 1)
		वापस -EINVAL;
	pcr_dbg(pcr, "DMA mapping count: %d\n", count);

	err = rtsx_pci_dma_transfer(pcr, sglist, count, पढ़ो, समयout);

	rtsx_pci_dma_unmap_sg(pcr, sglist, num_sg, पढ़ो);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_transfer_data);

पूर्णांक rtsx_pci_dma_map_sg(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो)
अणु
	क्रमागत dma_data_direction dir = पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	अगर (pcr->हटाओ_pci)
		वापस -EINVAL;

	अगर ((sglist == शून्य) || (num_sg <= 0))
		वापस -EINVAL;

	वापस dma_map_sg(&(pcr->pci->dev), sglist, num_sg, dir);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_dma_map_sg);

व्योम rtsx_pci_dma_unmap_sg(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो)
अणु
	क्रमागत dma_data_direction dir = पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	dma_unmap_sg(&(pcr->pci->dev), sglist, num_sg, dir);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_dma_unmap_sg);

पूर्णांक rtsx_pci_dma_transfer(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक count, bool पढ़ो, पूर्णांक समयout)
अणु
	काष्ठा completion trans_करोne;
	काष्ठा scatterlist *sg;
	dma_addr_t addr;
	दीर्घ समयleft;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;
	पूर्णांक i, err = 0;
	u32 val;
	u8 dir = पढ़ो ? DEVICE_TO_HOST : HOST_TO_DEVICE;

	अगर (pcr->हटाओ_pci)
		वापस -ENODEV;

	अगर ((sglist == शून्य) || (count < 1))
		वापस -EINVAL;

	val = ((u32)(dir & 0x01) << 29) | TRIG_DMA | ADMA_MODE;
	pcr->sgi = 0;
	क्रम_each_sg(sglist, sg, count, i) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
		rtsx_pci_add_sg_tbl(pcr, addr, len, i == count - 1);
	पूर्ण

	spin_lock_irqsave(&pcr->lock, flags);

	pcr->करोne = &trans_करोne;
	pcr->trans_result = TRANS_NOT_READY;
	init_completion(&trans_करोne);
	rtsx_pci_ग_लिखोl(pcr, RTSX_HDBAR, pcr->host_sg_tbl_addr);
	rtsx_pci_ग_लिखोl(pcr, RTSX_HDBCTLR, val);

	spin_unlock_irqrestore(&pcr->lock, flags);

	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&trans_करोne, msecs_to_jअगरfies(समयout));
	अगर (समयleft <= 0) अणु
		pcr_dbg(pcr, "Timeout (%s %d)\n", __func__, __LINE__);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&pcr->lock, flags);
	अगर (pcr->trans_result == TRANS_RESULT_FAIL) अणु
		err = -EILSEQ;
		अगर (pcr->dma_error_count < RTS_MAX_TIMES_FREQ_REDUCTION)
			pcr->dma_error_count++;
	पूर्ण

	अन्यथा अगर (pcr->trans_result == TRANS_NO_DEVICE)
		err = -ENODEV;
	spin_unlock_irqrestore(&pcr->lock, flags);

out:
	spin_lock_irqsave(&pcr->lock, flags);
	pcr->करोne = शून्य;
	spin_unlock_irqrestore(&pcr->lock, flags);

	अगर ((err < 0) && (err != -ENODEV))
		rtsx_pci_stop_cmd(pcr);

	अगर (pcr->finish_me)
		complete(pcr->finish_me);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_dma_transfer);

पूर्णांक rtsx_pci_पढ़ो_ppbuf(काष्ठा rtsx_pcr *pcr, u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक err;
	पूर्णांक i, j;
	u16 reg;
	u8 *ptr;

	अगर (buf_len > 512)
		buf_len = 512;

	ptr = buf;
	reg = PPBUF_BASE2;
	क्रम (i = 0; i < buf_len / 256; i++) अणु
		rtsx_pci_init_cmd(pcr);

		क्रम (j = 0; j < 256; j++)
			rtsx_pci_add_cmd(pcr, READ_REG_CMD, reg++, 0, 0);

		err = rtsx_pci_send_cmd(pcr, 250);
		अगर (err < 0)
			वापस err;

		स_नकल(ptr, rtsx_pci_get_cmd_data(pcr), 256);
		ptr += 256;
	पूर्ण

	अगर (buf_len % 256) अणु
		rtsx_pci_init_cmd(pcr);

		क्रम (j = 0; j < buf_len % 256; j++)
			rtsx_pci_add_cmd(pcr, READ_REG_CMD, reg++, 0, 0);

		err = rtsx_pci_send_cmd(pcr, 250);
		अगर (err < 0)
			वापस err;
	पूर्ण

	स_नकल(ptr, rtsx_pci_get_cmd_data(pcr), buf_len % 256);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_पढ़ो_ppbuf);

पूर्णांक rtsx_pci_ग_लिखो_ppbuf(काष्ठा rtsx_pcr *pcr, u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक err;
	पूर्णांक i, j;
	u16 reg;
	u8 *ptr;

	अगर (buf_len > 512)
		buf_len = 512;

	ptr = buf;
	reg = PPBUF_BASE2;
	क्रम (i = 0; i < buf_len / 256; i++) अणु
		rtsx_pci_init_cmd(pcr);

		क्रम (j = 0; j < 256; j++) अणु
			rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
					reg++, 0xFF, *ptr);
			ptr++;
		पूर्ण

		err = rtsx_pci_send_cmd(pcr, 250);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (buf_len % 256) अणु
		rtsx_pci_init_cmd(pcr);

		क्रम (j = 0; j < buf_len % 256; j++) अणु
			rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
					reg++, 0xFF, *ptr);
			ptr++;
		पूर्ण

		err = rtsx_pci_send_cmd(pcr, 250);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_ग_लिखो_ppbuf);

अटल पूर्णांक rtsx_pci_set_pull_ctl(काष्ठा rtsx_pcr *pcr, स्थिर u32 *tbl)
अणु
	rtsx_pci_init_cmd(pcr);

	जबतक (*tbl & 0xFFFF0000) अणु
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
				(u16)(*tbl >> 16), 0xFF, (u8)(*tbl));
		tbl++;
	पूर्ण

	वापस rtsx_pci_send_cmd(pcr, 100);
पूर्ण

पूर्णांक rtsx_pci_card_pull_ctl_enable(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	स्थिर u32 *tbl;

	अगर (card == RTSX_SD_CARD)
		tbl = pcr->sd_pull_ctl_enable_tbl;
	अन्यथा अगर (card == RTSX_MS_CARD)
		tbl = pcr->ms_pull_ctl_enable_tbl;
	अन्यथा
		वापस -EINVAL;

	वापस rtsx_pci_set_pull_ctl(pcr, tbl);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_pull_ctl_enable);

पूर्णांक rtsx_pci_card_pull_ctl_disable(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	स्थिर u32 *tbl;

	अगर (card == RTSX_SD_CARD)
		tbl = pcr->sd_pull_ctl_disable_tbl;
	अन्यथा अगर (card == RTSX_MS_CARD)
		tbl = pcr->ms_pull_ctl_disable_tbl;
	अन्यथा
		वापस -EINVAL;

	वापस rtsx_pci_set_pull_ctl(pcr, tbl);
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_pull_ctl_disable);

अटल व्योम rtsx_pci_enable_bus_पूर्णांक(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_hw_param *hw_param = &pcr->hw_param;

	pcr->bier = TRANS_OK_INT_EN | TRANS_FAIL_INT_EN | SD_INT_EN
		| hw_param->पूर्णांकerrupt_en;

	अगर (pcr->num_slots > 1)
		pcr->bier |= MS_INT_EN;

	/* Enable Bus Interrupt */
	rtsx_pci_ग_लिखोl(pcr, RTSX_BIER, pcr->bier);

	pcr_dbg(pcr, "RTSX_BIER: 0x%08x\n", pcr->bier);
पूर्ण

अटल अंतरभूत u8 द्विगुन_ssc_depth(u8 depth)
अणु
	वापस ((depth > 1) ? (depth - 1) : depth);
पूर्ण

अटल u8 revise_ssc_depth(u8 ssc_depth, u8 भाग)
अणु
	अगर (भाग > CLK_DIV_1) अणु
		अगर (ssc_depth > (भाग - 1))
			ssc_depth -= (भाग - 1);
		अन्यथा
			ssc_depth = SSC_DEPTH_4M;
	पूर्ण

	वापस ssc_depth;
पूर्ण

पूर्णांक rtsx_pci_चयन_घड़ी(काष्ठा rtsx_pcr *pcr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk)
अणु
	पूर्णांक err, clk;
	u8 n, clk_भागider, mcu_cnt, भाग;
	अटल स्थिर u8 depth[] = अणु
		[RTSX_SSC_DEPTH_4M] = SSC_DEPTH_4M,
		[RTSX_SSC_DEPTH_2M] = SSC_DEPTH_2M,
		[RTSX_SSC_DEPTH_1M] = SSC_DEPTH_1M,
		[RTSX_SSC_DEPTH_500K] = SSC_DEPTH_500K,
		[RTSX_SSC_DEPTH_250K] = SSC_DEPTH_250K,
	पूर्ण;

	अगर (PCI_PID(pcr) == PID_5261)
		वापस rts5261_pci_चयन_घड़ी(pcr, card_घड़ी,
				ssc_depth, initial_mode, द्विगुन_clk, vpclk);
	अगर (PCI_PID(pcr) == PID_5228)
		वापस rts5228_pci_चयन_घड़ी(pcr, card_घड़ी,
				ssc_depth, initial_mode, द्विगुन_clk, vpclk);

	अगर (initial_mode) अणु
		/* We use 250k(around) here, in initial stage */
		clk_भागider = SD_CLK_DIVIDE_128;
		card_घड़ी = 30000000;
	पूर्ण अन्यथा अणु
		clk_भागider = SD_CLK_DIVIDE_0;
	पूर्ण
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, clk_भागider);
	अगर (err < 0)
		वापस err;

	/* Reduce card घड़ी by 20MHz each समय a DMA transfer error occurs */
	अगर (card_घड़ी == UHS_SDR104_MAX_DTR &&
	    pcr->dma_error_count &&
	    PCI_PID(pcr) == RTS5227_DEVICE_ID)
		card_घड़ी = UHS_SDR104_MAX_DTR -
			(pcr->dma_error_count * 20000000);

	card_घड़ी /= 1000000;
	pcr_dbg(pcr, "Switch card clock to %dMHz\n", card_घड़ी);

	clk = card_घड़ी;
	अगर (!initial_mode && द्विगुन_clk)
		clk = card_घड़ी * 2;
	pcr_dbg(pcr, "Internal SSC clock: %dMHz (cur_clock = %d)\n",
		clk, pcr->cur_घड़ी);

	अगर (clk == pcr->cur_घड़ी)
		वापस 0;

	अगर (pcr->ops->conv_clk_and_भाग_n)
		n = (u8)pcr->ops->conv_clk_and_भाग_n(clk, CLK_TO_DIV_N);
	अन्यथा
		n = (u8)(clk - 2);
	अगर ((clk <= 2) || (n > MAX_DIV_N_PCR))
		वापस -EINVAL;

	mcu_cnt = (u8)(125/clk + 3);
	अगर (mcu_cnt > 15)
		mcu_cnt = 15;

	/* Make sure that the SSC घड़ी भाग_n is not less than MIN_DIV_N_PCR */
	भाग = CLK_DIV_1;
	जबतक ((n < MIN_DIV_N_PCR) && (भाग < CLK_DIV_8)) अणु
		अगर (pcr->ops->conv_clk_and_भाग_n) अणु
			पूर्णांक dbl_clk = pcr->ops->conv_clk_and_भाग_n(n,
					DIV_N_TO_CLK) * 2;
			n = (u8)pcr->ops->conv_clk_and_भाग_n(dbl_clk,
					CLK_TO_DIV_N);
		पूर्ण अन्यथा अणु
			n = (n + 2) * 2 - 2;
		पूर्ण
		भाग++;
	पूर्ण
	pcr_dbg(pcr, "n = %d, div = %d\n", n, भाग);

	ssc_depth = depth[ssc_depth];
	अगर (द्विगुन_clk)
		ssc_depth = द्विगुन_ssc_depth(ssc_depth);

	ssc_depth = revise_ssc_depth(ssc_depth, भाग);
	pcr_dbg(pcr, "ssc_depth = %d\n", ssc_depth);

	rtsx_pci_init_cmd(pcr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_CTL,
			CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_DIV,
			0xFF, (भाग << 4) | mcu_cnt);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2,
			SSC_DEPTH_MASK, ssc_depth);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	अगर (vpclk) अणु
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, 0);
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, PHASE_NOT_RESET);
	पूर्ण

	err = rtsx_pci_send_cmd(pcr, 2000);
	अगर (err < 0)
		वापस err;

	/* Wait SSC घड़ी stable */
	udelay(SSC_CLOCK_STABLE_WAIT);
	err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CLK_CTL, CLK_LOW_FREQ, 0);
	अगर (err < 0)
		वापस err;

	pcr->cur_घड़ी = clk;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_चयन_घड़ी);

पूर्णांक rtsx_pci_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	अगर (pcr->ops->card_घातer_on)
		वापस pcr->ops->card_घातer_on(pcr, card);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_घातer_on);

पूर्णांक rtsx_pci_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	अगर (pcr->ops->card_घातer_off)
		वापस pcr->ops->card_घातer_off(pcr, card);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_घातer_off);

पूर्णांक rtsx_pci_card_exclusive_check(काष्ठा rtsx_pcr *pcr, पूर्णांक card)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cd_mask[] = अणु
		[RTSX_SD_CARD] = SD_EXIST,
		[RTSX_MS_CARD] = MS_EXIST
	पूर्ण;

	अगर (!(pcr->flags & PCR_MS_PMOS)) अणु
		/* When using single PMOS, accessing card is not permitted
		 * अगर the existing card is not the designated one.
		 */
		अगर (pcr->card_exist & (~cd_mask[card]))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_exclusive_check);

पूर्णांक rtsx_pci_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage)
अणु
	अगर (pcr->ops->चयन_output_voltage)
		वापस pcr->ops->चयन_output_voltage(pcr, voltage);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_चयन_output_voltage);

अचिन्हित पूर्णांक rtsx_pci_card_exist(काष्ठा rtsx_pcr *pcr)
अणु
	अचिन्हित पूर्णांक val;

	val = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	अगर (pcr->ops->cd_deglitch)
		val = pcr->ops->cd_deglitch(pcr);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_card_exist);

व्योम rtsx_pci_complete_unfinished_transfer(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा completion finish;

	pcr->finish_me = &finish;
	init_completion(&finish);

	अगर (pcr->करोne)
		complete(pcr->करोne);

	अगर (!pcr->हटाओ_pci)
		rtsx_pci_stop_cmd(pcr);

	रुको_क्रम_completion_पूर्णांकerruptible_समयout(&finish,
			msecs_to_jअगरfies(2));
	pcr->finish_me = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rtsx_pci_complete_unfinished_transfer);

अटल व्योम rtsx_pci_card_detect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा rtsx_pcr *pcr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक card_detect = 0, card_inserted, card_हटाओd;
	u32 irq_status;

	dwork = to_delayed_work(work);
	pcr = container_of(dwork, काष्ठा rtsx_pcr, carddet_work);

	pcr_dbg(pcr, "--> %s\n", __func__);

	mutex_lock(&pcr->pcr_mutex);
	spin_lock_irqsave(&pcr->lock, flags);

	irq_status = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	pcr_dbg(pcr, "irq_status: 0x%08x\n", irq_status);

	irq_status &= CARD_EXIST;
	card_inserted = pcr->card_inserted & irq_status;
	card_हटाओd = pcr->card_हटाओd;
	pcr->card_inserted = 0;
	pcr->card_हटाओd = 0;

	spin_unlock_irqrestore(&pcr->lock, flags);

	अगर (card_inserted || card_हटाओd) अणु
		pcr_dbg(pcr, "card_inserted: 0x%x, card_removed: 0x%x\n",
			card_inserted, card_हटाओd);

		अगर (pcr->ops->cd_deglitch)
			card_inserted = pcr->ops->cd_deglitch(pcr);

		card_detect = card_inserted | card_हटाओd;

		pcr->card_exist |= card_inserted;
		pcr->card_exist &= ~card_हटाओd;
	पूर्ण

	mutex_unlock(&pcr->pcr_mutex);

	अगर ((card_detect & SD_EXIST) && pcr->slots[RTSX_SD_CARD].card_event)
		pcr->slots[RTSX_SD_CARD].card_event(
				pcr->slots[RTSX_SD_CARD].p_dev);
	अगर ((card_detect & MS_EXIST) && pcr->slots[RTSX_MS_CARD].card_event)
		pcr->slots[RTSX_MS_CARD].card_event(
				pcr->slots[RTSX_MS_CARD].p_dev);
पूर्ण

अटल व्योम rtsx_pci_process_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->process_ocp) अणु
		pcr->ops->process_ocp(pcr);
	पूर्ण अन्यथा अणु
		अगर (!pcr->option.ocp_en)
			वापस;
		rtsx_pci_get_ocpstat(pcr, &pcr->ocp_stat);
		अगर (pcr->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) अणु
			rtsx_pci_card_घातer_off(pcr, RTSX_SD_CARD);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, 0);
			rtsx_pci_clear_ocpstat(pcr);
			pcr->ocp_stat = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rtsx_pci_process_ocp_पूर्णांकerrupt(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->option.ocp_en)
		rtsx_pci_process_ocp(pcr);

	वापस 0;
पूर्ण

अटल irqवापस_t rtsx_pci_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rtsx_pcr *pcr = dev_id;
	u32 पूर्णांक_reg;

	अगर (!pcr)
		वापस IRQ_NONE;

	spin_lock(&pcr->lock);

	पूर्णांक_reg = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR);
	/* Clear पूर्णांकerrupt flag */
	rtsx_pci_ग_लिखोl(pcr, RTSX_BIPR, पूर्णांक_reg);
	अगर ((पूर्णांक_reg & pcr->bier) == 0) अणु
		spin_unlock(&pcr->lock);
		वापस IRQ_NONE;
	पूर्ण
	अगर (पूर्णांक_reg == 0xFFFFFFFF) अणु
		spin_unlock(&pcr->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	पूर्णांक_reg &= (pcr->bier | 0x7FFFFF);

	अगर (पूर्णांक_reg & SD_OC_INT)
		rtsx_pci_process_ocp_पूर्णांकerrupt(pcr);

	अगर (पूर्णांक_reg & SD_INT) अणु
		अगर (पूर्णांक_reg & SD_EXIST) अणु
			pcr->card_inserted |= SD_EXIST;
		पूर्ण अन्यथा अणु
			pcr->card_हटाओd |= SD_EXIST;
			pcr->card_inserted &= ~SD_EXIST;
			अगर (PCI_PID(pcr) == PID_5261) अणु
				rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_STATUS,
					RTS5261_EXPRESS_LINK_FAIL_MASK, 0);
				pcr->extra_caps |= EXTRA_CAPS_SD_EXPRESS;
			पूर्ण
		पूर्ण
		pcr->dma_error_count = 0;
	पूर्ण

	अगर (पूर्णांक_reg & MS_INT) अणु
		अगर (पूर्णांक_reg & MS_EXIST) अणु
			pcr->card_inserted |= MS_EXIST;
		पूर्ण अन्यथा अणु
			pcr->card_हटाओd |= MS_EXIST;
			pcr->card_inserted &= ~MS_EXIST;
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_reg & (NEED_COMPLETE_INT | DELINK_INT)) अणु
		अगर (पूर्णांक_reg & (TRANS_FAIL_INT | DELINK_INT)) अणु
			pcr->trans_result = TRANS_RESULT_FAIL;
			अगर (pcr->करोne)
				complete(pcr->करोne);
		पूर्ण अन्यथा अगर (पूर्णांक_reg & TRANS_OK_INT) अणु
			pcr->trans_result = TRANS_RESULT_OK;
			अगर (pcr->करोne)
				complete(pcr->करोne);
		पूर्ण
	पूर्ण

	अगर ((pcr->card_inserted || pcr->card_हटाओd) && !(पूर्णांक_reg & SD_OC_INT))
		schedule_delayed_work(&pcr->carddet_work,
				msecs_to_jअगरfies(200));

	spin_unlock(&pcr->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rtsx_pci_acquire_irq(काष्ठा rtsx_pcr *pcr)
अणु
	pcr_dbg(pcr, "%s: pcr->msi_en = %d, pci->irq = %d\n",
			__func__, pcr->msi_en, pcr->pci->irq);

	अगर (request_irq(pcr->pci->irq, rtsx_pci_isr,
			pcr->msi_en ? 0 : IRQF_SHARED,
			DRV_NAME_RTSX_PCI, pcr)) अणु
		dev_err(&(pcr->pci->dev),
			"rtsx_sdmmc: unable to grab IRQ %d, disabling device\n",
			pcr->pci->irq);
		वापस -1;
	पूर्ण

	pcr->irq = pcr->pci->irq;
	pci_पूर्णांकx(pcr->pci, !pcr->msi_en);

	वापस 0;
पूर्ण

अटल व्योम rtsx_enable_aspm(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->set_aspm)
		pcr->ops->set_aspm(pcr, true);
	अन्यथा
		rtsx_comm_set_aspm(pcr, true);
पूर्ण

अटल व्योम rtsx_comm_pm_घातer_saving(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा rtsx_cr_option *option = &pcr->option;

	अगर (option->ltr_enabled) अणु
		u32 latency = option->ltr_l1off_latency;

		अगर (rtsx_check_dev_flag(pcr, L1_SNOOZE_TEST_EN))
			mdelay(option->l1_snooze_delay);

		rtsx_set_ltr_latency(pcr, latency);
	पूर्ण

	अगर (rtsx_check_dev_flag(pcr, LTR_L1SS_PWR_GATE_EN))
		rtsx_set_l1off_sub_cfg_d0(pcr, 0);

	rtsx_enable_aspm(pcr);
पूर्ण

अटल व्योम rtsx_pm_घातer_saving(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_comm_pm_घातer_saving(pcr);
पूर्ण

अटल व्योम rtsx_pci_rtd3_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा rtsx_pcr *pcr = container_of(dwork, काष्ठा rtsx_pcr, rtd3_work);

	pcr_dbg(pcr, "--> %s\n", __func__);
	अगर (!pcr->is_runसमय_suspended)
		pm_runसमय_put(&(pcr->pci->dev));
पूर्ण

अटल व्योम rtsx_pci_idle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा rtsx_pcr *pcr = container_of(dwork, काष्ठा rtsx_pcr, idle_work);

	pcr_dbg(pcr, "--> %s\n", __func__);

	mutex_lock(&pcr->pcr_mutex);

	pcr->state = PDEV_STAT_IDLE;

	अगर (pcr->ops->disable_स्वतः_blink)
		pcr->ops->disable_स्वतः_blink(pcr);
	अगर (pcr->ops->turn_off_led)
		pcr->ops->turn_off_led(pcr);

	rtsx_pm_घातer_saving(pcr);

	mutex_unlock(&pcr->pcr_mutex);

	अगर (pcr->rtd3_en)
		mod_delayed_work(प्रणाली_wq, &pcr->rtd3_work, msecs_to_jअगरfies(10000));
पूर्ण

अटल व्योम rtsx_base_क्रमce_घातer_करोwn(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	/* Set relink_समय to 0 */
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 1, MASK_8_BIT_DEF, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 2, MASK_8_BIT_DEF, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, AUTOLOAD_CFG_BASE + 3,
			RELINK_TIME_MASK, 0);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, pcr->reg_pm_ctrl3,
			D3_DELINK_MODE_EN, D3_DELINK_MODE_EN);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, ALL_POWER_DOWN, ALL_POWER_DOWN);
पूर्ण

अटल व्योम __maybe_unused rtsx_pci_घातer_off(काष्ठा rtsx_pcr *pcr, u8 pm_state)
अणु
	अगर (pcr->ops->turn_off_led)
		pcr->ops->turn_off_led(pcr);

	rtsx_pci_ग_लिखोl(pcr, RTSX_BIER, 0);
	pcr->bier = 0;

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PETXCFG, 0x08, 0x08);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, HOST_SLEEP_STATE, 0x03, pm_state);

	अगर (pcr->ops->क्रमce_घातer_करोwn)
		pcr->ops->क्रमce_घातer_करोwn(pcr, pm_state);
	अन्यथा
		rtsx_base_क्रमce_घातer_करोwn(pcr, pm_state);
पूर्ण

व्योम rtsx_pci_enable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 val = SD_OCP_INT_EN | SD_DETECT_EN;

	अगर (pcr->ops->enable_ocp) अणु
		pcr->ops->enable_ocp(pcr);
	पूर्ण अन्यथा अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, OC_POWER_DOWN, 0);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, 0xFF, val);
	पूर्ण

पूर्ण

व्योम rtsx_pci_disable_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	u8 mask = SD_OCP_INT_EN | SD_DETECT_EN;

	अगर (pcr->ops->disable_ocp) अणु
		pcr->ops->disable_ocp(pcr);
	पूर्ण अन्यथा अणु
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, OC_POWER_DOWN,
				OC_POWER_DOWN);
	पूर्ण
पूर्ण

व्योम rtsx_pci_init_ocp(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->init_ocp) अणु
		pcr->ops->init_ocp(pcr);
	पूर्ण अन्यथा अणु
		काष्ठा rtsx_cr_option *option = &(pcr->option);

		अगर (option->ocp_en) अणु
			u8 val = option->sd_800mA_ocp_thd;

			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, OC_POWER_DOWN, 0);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPPARA1,
				SD_OCP_TIME_MASK, SD_OCP_TIME_800);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPPARA2,
				SD_OCP_THD_MASK, val);
			rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPGLITCH,
				SD_OCP_GLITCH_MASK, pcr->hw_param.ocp_glitch);
			rtsx_pci_enable_ocp(pcr);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक rtsx_pci_get_ocpstat(काष्ठा rtsx_pcr *pcr, u8 *val)
अणु
	अगर (pcr->ops->get_ocpstat)
		वापस pcr->ops->get_ocpstat(pcr, val);
	अन्यथा
		वापस rtsx_pci_पढ़ो_रेजिस्टर(pcr, REG_OCPSTAT, val);
पूर्ण

व्योम rtsx_pci_clear_ocpstat(काष्ठा rtsx_pcr *pcr)
अणु
	अगर (pcr->ops->clear_ocpstat) अणु
		pcr->ops->clear_ocpstat(pcr);
	पूर्ण अन्यथा अणु
		u8 mask = SD_OCP_INT_CLR | SD_OC_CLR;
		u8 val = SD_OCP_INT_CLR | SD_OC_CLR;

		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, val);
		udelay(100);
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_OCPCTL, mask, 0);
	पूर्ण
पूर्ण

व्योम rtsx_pci_enable_oobs_polling(काष्ठा rtsx_pcr *pcr)
अणु
	u16 val;

	अगर ((PCI_PID(pcr) != PID_525A) && (PCI_PID(pcr) != PID_5260)) अणु
		rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, 0x01, &val);
		val |= 1<<9;
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x01, val);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_OOBS_OFF_TIMER, 0xFF, 0x32);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_OOBS_ON_TIMER, 0xFF, 0x05);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_VCM_ON_TIMER, 0xFF, 0x83);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_OOBS_POLLING, 0xFF, 0xDE);

पूर्ण

व्योम rtsx_pci_disable_oobs_polling(काष्ठा rtsx_pcr *pcr)
अणु
	u16 val;

	अगर ((PCI_PID(pcr) != PID_525A) && (PCI_PID(pcr) != PID_5260)) अणु
		rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, 0x01, &val);
		val &= ~(1<<9);
		rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, 0x01, val);
	पूर्ण
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_VCM_ON_TIMER, 0xFF, 0x03);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, REG_CFG_OOBS_POLLING, 0xFF, 0x00);

पूर्ण

पूर्णांक rtsx_sd_घातer_off_card3v3(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_CLK_EN, SD_CLK_EN |
		MS_CLK_EN | SD40_CLK_EN, 0);
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, SD_OUTPUT_EN, 0);
	rtsx_pci_card_घातer_off(pcr, RTSX_SD_CARD);

	msleep(50);

	rtsx_pci_card_pull_ctl_disable(pcr, RTSX_SD_CARD);

	वापस 0;
पूर्ण

पूर्णांक rtsx_ms_घातer_off_card3v3(काष्ठा rtsx_pcr *pcr)
अणु
	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_CLK_EN, SD_CLK_EN |
		MS_CLK_EN | SD40_CLK_EN, 0);

	rtsx_pci_card_pull_ctl_disable(pcr, RTSX_MS_CARD);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, CARD_OE, MS_OUTPUT_EN, 0);
	rtsx_pci_card_घातer_off(pcr, RTSX_MS_CARD);

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_init_hw(काष्ठा rtsx_pcr *pcr)
अणु
	काष्ठा pci_dev *pdev = pcr->pci;
	पूर्णांक err;

	अगर (PCI_PID(pcr) == PID_5228)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5228_LDO1_CFG1, RTS5228_LDO1_SR_TIME_MASK,
				RTS5228_LDO1_SR_0_5);

	rtsx_pci_ग_लिखोl(pcr, RTSX_HCBAR, pcr->host_cmds_addr);

	rtsx_pci_enable_bus_पूर्णांक(pcr);

	/* Power on SSC */
	अगर (PCI_PID(pcr) == PID_5261) अणु
		/* Gating real mcu घड़ी */
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_FW_CFG1,
			RTS5261_MCU_CLOCK_GATING, 0);
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, RTS5261_REG_FPDCTL,
			SSC_POWER_DOWN, 0);
	पूर्ण अन्यथा अणु
		err = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, FPDCTL, SSC_POWER_DOWN, 0);
	पूर्ण
	अगर (err < 0)
		वापस err;

	/* Wait SSC घातer stable */
	udelay(200);

	rtsx_disable_aspm(pcr);
	अगर (pcr->ops->optimize_phy) अणु
		err = pcr->ops->optimize_phy(pcr);
		अगर (err < 0)
			वापस err;
	पूर्ण

	rtsx_pci_init_cmd(pcr);

	/* Set mcu_cnt to 7 to ensure data can be sampled properly */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CLK_DIV, 0x07, 0x07);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, HOST_SLEEP_STATE, 0x03, 0x00);
	/* Disable card घड़ी */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_CLK_EN, 0x1E, 0);
	/* Reset delink mode */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CHANGE_LINK_STATE, 0x0A, 0);
	/* Card driving select */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CARD_DRIVE_SEL,
			0xFF, pcr->card_drive_sel);
	/* Enable SSC Clock */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL1,
			0xFF, SSC_8X_EN | SSC_SEL_4M);
	अगर (PCI_PID(pcr) == PID_5261)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2, 0xFF,
			RTS5261_SSC_DEPTH_2M);
	अन्यथा अगर (PCI_PID(pcr) == PID_5228)
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2, 0xFF,
			RTS5228_SSC_DEPTH_2M);
	अन्यथा
		rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SSC_CTL2, 0xFF, 0x12);

	/* Disable cd_pwr_save */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, CHANGE_LINK_STATE, 0x16, 0x10);
	/* Clear Link Ready Interrupt */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, IRQSTAT0,
			LINK_RDY_INT, LINK_RDY_INT);
	/* Enlarge the estimation winकरोw of PERST# glitch
	 * to reduce the chance of invalid card पूर्णांकerrupt
	 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PERST_GLITCH_WIDTH, 0xFF, 0x80);
	/* Update RC oscillator to 400k
	 * bit[0] F_HIGH: क्रम RC oscillator, Rst_value is 1'b1
	 *                1: 2M  0: 400k
	 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, RCCTL, 0x01, 0x00);
	/* Set पूर्णांकerrupt ग_लिखो clear
	 * bit 1: U_elbi_अगर_rd_clr_en
	 *	1: Enable ELBI पूर्णांकerrupt[31:22] & [7:0] flag पढ़ो clear
	 *	0: ELBI पूर्णांकerrupt flag[31:22] & [7:0] only can be ग_लिखो clear
	 */
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, NFTS_TX_CTRL, 0x02, 0);

	err = rtsx_pci_send_cmd(pcr, 100);
	अगर (err < 0)
		वापस err;

	चयन (PCI_PID(pcr)) अणु
	हाल PID_5250:
	हाल PID_524A:
	हाल PID_525A:
	हाल PID_5260:
	हाल PID_5261:
	हाल PID_5228:
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, PM_CLK_FORCE_CTL, 1, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*init ocp*/
	rtsx_pci_init_ocp(pcr);

	/* Enable clk_request_n to enable घड़ी घातer management */
	pcie_capability_clear_and_set_word(pcr->pci, PCI_EXP_LNKCTL,
					0, PCI_EXP_LNKCTL_CLKREQ_EN);
	/* Enter L1 when host tx idle */
	pci_ग_लिखो_config_byte(pdev, 0x70F, 0x5B);

	अगर (pcr->ops->extra_init_hw) अणु
		err = pcr->ops->extra_init_hw(pcr);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pcr->aspm_mode == ASPM_MODE_REG)
		rtsx_pci_ग_लिखो_रेजिस्टर(pcr, ASPM_FORCE_CTL, 0x30, 0x30);

	/* No CD पूर्णांकerrupt अगर probing driver with card inserted.
	 * So we need to initialize pcr->card_exist here.
	 */
	अगर (pcr->ops->cd_deglitch)
		pcr->card_exist = pcr->ops->cd_deglitch(pcr);
	अन्यथा
		pcr->card_exist = rtsx_pci_पढ़ोl(pcr, RTSX_BIPR) & CARD_EXIST;

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_init_chip(काष्ठा rtsx_pcr *pcr)
अणु
	पूर्णांक err;
	u16 cfg_val;
	u8 val;

	spin_lock_init(&pcr->lock);
	mutex_init(&pcr->pcr_mutex);

	चयन (PCI_PID(pcr)) अणु
	शेष:
	हाल 0x5209:
		rts5209_init_params(pcr);
		अवरोध;

	हाल 0x5229:
		rts5229_init_params(pcr);
		अवरोध;

	हाल 0x5289:
		rtl8411_init_params(pcr);
		अवरोध;

	हाल 0x5227:
		rts5227_init_params(pcr);
		अवरोध;

	हाल 0x522A:
		rts522a_init_params(pcr);
		अवरोध;

	हाल 0x5249:
		rts5249_init_params(pcr);
		अवरोध;

	हाल 0x524A:
		rts524a_init_params(pcr);
		अवरोध;

	हाल 0x525A:
		rts525a_init_params(pcr);
		अवरोध;

	हाल 0x5287:
		rtl8411b_init_params(pcr);
		अवरोध;

	हाल 0x5286:
		rtl8402_init_params(pcr);
		अवरोध;

	हाल 0x5260:
		rts5260_init_params(pcr);
		अवरोध;

	हाल 0x5261:
		rts5261_init_params(pcr);
		अवरोध;

	हाल 0x5228:
		rts5228_init_params(pcr);
		अवरोध;
	पूर्ण

	pcr_dbg(pcr, "PID: 0x%04x, IC version: 0x%02x\n",
			PCI_PID(pcr), pcr->ic_version);

	pcr->slots = kसुस्मृति(pcr->num_slots, माप(काष्ठा rtsx_slot),
			GFP_KERNEL);
	अगर (!pcr->slots)
		वापस -ENOMEM;

	अगर (pcr->aspm_mode == ASPM_MODE_CFG) अणु
		pcie_capability_पढ़ो_word(pcr->pci, PCI_EXP_LNKCTL, &cfg_val);
		अगर (cfg_val & PCI_EXP_LNKCTL_ASPM_L1)
			pcr->aspm_enabled = true;
		अन्यथा
			pcr->aspm_enabled = false;

	पूर्ण अन्यथा अगर (pcr->aspm_mode == ASPM_MODE_REG) अणु
		rtsx_pci_पढ़ो_रेजिस्टर(pcr, ASPM_FORCE_CTL, &val);
		अगर (val & FORCE_ASPM_CTL0 && val & FORCE_ASPM_CTL1)
			pcr->aspm_enabled = false;
		अन्यथा
			pcr->aspm_enabled = true;
	पूर्ण

	अगर (pcr->ops->fetch_venकरोr_settings)
		pcr->ops->fetch_venकरोr_settings(pcr);

	pcr_dbg(pcr, "pcr->aspm_en = 0x%x\n", pcr->aspm_en);
	pcr_dbg(pcr, "pcr->sd30_drive_sel_1v8 = 0x%x\n",
			pcr->sd30_drive_sel_1v8);
	pcr_dbg(pcr, "pcr->sd30_drive_sel_3v3 = 0x%x\n",
			pcr->sd30_drive_sel_3v3);
	pcr_dbg(pcr, "pcr->card_drive_sel = 0x%x\n",
			pcr->card_drive_sel);
	pcr_dbg(pcr, "pcr->flags = 0x%x\n", pcr->flags);

	pcr->state = PDEV_STAT_IDLE;
	err = rtsx_pci_init_hw(pcr);
	अगर (err < 0) अणु
		kमुक्त(pcr->slots);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_probe(काष्ठा pci_dev *pcidev,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा rtsx_pcr *pcr;
	काष्ठा pcr_handle *handle;
	u32 base, len;
	पूर्णांक ret, i, bar = 0;

	dev_dbg(&(pcidev->dev),
		": Realtek PCI-E Card Reader found at %s [%04x:%04x] (rev %x)\n",
		pci_name(pcidev), (पूर्णांक)pcidev->venकरोr, (पूर्णांक)pcidev->device,
		(पूर्णांक)pcidev->revision);

	ret = pci_set_dma_mask(pcidev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		वापस ret;

	ret = pci_enable_device(pcidev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(pcidev, DRV_NAME_RTSX_PCI);
	अगर (ret)
		जाओ disable;

	pcr = kzalloc(माप(*pcr), GFP_KERNEL);
	अगर (!pcr) अणु
		ret = -ENOMEM;
		जाओ release_pci;
	पूर्ण

	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (!handle) अणु
		ret = -ENOMEM;
		जाओ मुक्त_pcr;
	पूर्ण
	handle->pcr = pcr;

	idr_preload(GFP_KERNEL);
	spin_lock(&rtsx_pci_lock);
	ret = idr_alloc(&rtsx_pci_idr, pcr, 0, 0, GFP_NOWAIT);
	अगर (ret >= 0)
		pcr->id = ret;
	spin_unlock(&rtsx_pci_lock);
	idr_preload_end();
	अगर (ret < 0)
		जाओ मुक्त_handle;

	pcr->pci = pcidev;
	dev_set_drvdata(&pcidev->dev, handle);

	अगर (CHK_PCI_PID(pcr, 0x525A))
		bar = 1;
	len = pci_resource_len(pcidev, bar);
	base = pci_resource_start(pcidev, bar);
	pcr->remap_addr = ioremap(base, len);
	अगर (!pcr->remap_addr) अणु
		ret = -ENOMEM;
		जाओ मुक्त_handle;
	पूर्ण

	pcr->rtsx_resv_buf = dma_alloc_coherent(&(pcidev->dev),
			RTSX_RESV_BUF_LEN, &(pcr->rtsx_resv_buf_addr),
			GFP_KERNEL);
	अगर (pcr->rtsx_resv_buf == शून्य) अणु
		ret = -ENXIO;
		जाओ unmap;
	पूर्ण
	pcr->host_cmds_ptr = pcr->rtsx_resv_buf;
	pcr->host_cmds_addr = pcr->rtsx_resv_buf_addr;
	pcr->host_sg_tbl_ptr = pcr->rtsx_resv_buf + HOST_CMDS_BUF_LEN;
	pcr->host_sg_tbl_addr = pcr->rtsx_resv_buf_addr + HOST_CMDS_BUF_LEN;
	pcr->card_inserted = 0;
	pcr->card_हटाओd = 0;
	INIT_DELAYED_WORK(&pcr->carddet_work, rtsx_pci_card_detect);
	INIT_DELAYED_WORK(&pcr->idle_work, rtsx_pci_idle_work);

	pcr->msi_en = msi_en;
	अगर (pcr->msi_en) अणु
		ret = pci_enable_msi(pcidev);
		अगर (ret)
			pcr->msi_en = false;
	पूर्ण

	ret = rtsx_pci_acquire_irq(pcr);
	अगर (ret < 0)
		जाओ disable_msi;

	pci_set_master(pcidev);
	synchronize_irq(pcr->irq);

	ret = rtsx_pci_init_chip(pcr);
	अगर (ret < 0)
		जाओ disable_irq;

	क्रम (i = 0; i < ARRAY_SIZE(rtsx_pcr_cells); i++) अणु
		rtsx_pcr_cells[i].platक्रमm_data = handle;
		rtsx_pcr_cells[i].pdata_size = माप(*handle);
	पूर्ण

	अगर (pcr->rtd3_en) अणु
		INIT_DELAYED_WORK(&pcr->rtd3_work, rtsx_pci_rtd3_work);
		pm_runसमय_allow(&pcidev->dev);
		pm_runसमय_enable(&pcidev->dev);
		pcr->is_runसमय_suspended = false;
	पूर्ण


	ret = mfd_add_devices(&pcidev->dev, pcr->id, rtsx_pcr_cells,
			ARRAY_SIZE(rtsx_pcr_cells), शून्य, 0, शून्य);
	अगर (ret < 0)
		जाओ मुक्त_slots;

	schedule_delayed_work(&pcr->idle_work, msecs_to_jअगरfies(200));

	वापस 0;

मुक्त_slots:
	kमुक्त(pcr->slots);
disable_irq:
	मुक्त_irq(pcr->irq, (व्योम *)pcr);
disable_msi:
	अगर (pcr->msi_en)
		pci_disable_msi(pcr->pci);
	dma_मुक्त_coherent(&(pcr->pci->dev), RTSX_RESV_BUF_LEN,
			pcr->rtsx_resv_buf, pcr->rtsx_resv_buf_addr);
unmap:
	iounmap(pcr->remap_addr);
मुक्त_handle:
	kमुक्त(handle);
मुक्त_pcr:
	kमुक्त(pcr);
release_pci:
	pci_release_regions(pcidev);
disable:
	pci_disable_device(pcidev);

	वापस ret;
पूर्ण

अटल व्योम rtsx_pci_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा pcr_handle *handle = pci_get_drvdata(pcidev);
	काष्ठा rtsx_pcr *pcr = handle->pcr;

	अगर (pcr->rtd3_en)
		pm_runसमय_get_noresume(&pcr->pci->dev);

	pcr->हटाओ_pci = true;

	/* Disable पूर्णांकerrupts at the pcr level */
	spin_lock_irq(&pcr->lock);
	rtsx_pci_ग_लिखोl(pcr, RTSX_BIER, 0);
	pcr->bier = 0;
	spin_unlock_irq(&pcr->lock);

	cancel_delayed_work_sync(&pcr->carddet_work);
	cancel_delayed_work_sync(&pcr->idle_work);
	अगर (pcr->rtd3_en)
		cancel_delayed_work_sync(&pcr->rtd3_work);

	mfd_हटाओ_devices(&pcidev->dev);

	dma_मुक्त_coherent(&(pcr->pci->dev), RTSX_RESV_BUF_LEN,
			pcr->rtsx_resv_buf, pcr->rtsx_resv_buf_addr);
	मुक्त_irq(pcr->irq, (व्योम *)pcr);
	अगर (pcr->msi_en)
		pci_disable_msi(pcr->pci);
	iounmap(pcr->remap_addr);

	pci_release_regions(pcidev);
	pci_disable_device(pcidev);

	spin_lock(&rtsx_pci_lock);
	idr_हटाओ(&rtsx_pci_idr, pcr->id);
	spin_unlock(&rtsx_pci_lock);

	अगर (pcr->rtd3_en) अणु
		pm_runसमय_disable(&pcr->pci->dev);
		pm_runसमय_put_noidle(&pcr->pci->dev);
	पूर्ण

	kमुक्त(pcr->slots);
	kमुक्त(pcr);
	kमुक्त(handle);

	dev_dbg(&(pcidev->dev),
		": Realtek PCI-E Card Reader at %s [%04x:%04x] has been removed\n",
		pci_name(pcidev), (पूर्णांक)pcidev->venकरोr, (पूर्णांक)pcidev->device);
पूर्ण

अटल पूर्णांक __maybe_unused rtsx_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pcidev = to_pci_dev(dev_d);
	काष्ठा pcr_handle *handle;
	काष्ठा rtsx_pcr *pcr;

	dev_dbg(&(pcidev->dev), "--> %s\n", __func__);

	handle = pci_get_drvdata(pcidev);
	pcr = handle->pcr;

	cancel_delayed_work(&pcr->carddet_work);
	cancel_delayed_work(&pcr->idle_work);

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_घातer_off(pcr, HOST_ENTER_S3);

	device_wakeup_disable(dev_d);

	mutex_unlock(&pcr->pcr_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtsx_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pcidev = to_pci_dev(dev_d);
	काष्ठा pcr_handle *handle;
	काष्ठा rtsx_pcr *pcr;
	पूर्णांक ret = 0;

	dev_dbg(&(pcidev->dev), "--> %s\n", __func__);

	handle = pci_get_drvdata(pcidev);
	pcr = handle->pcr;

	mutex_lock(&pcr->pcr_mutex);

	ret = rtsx_pci_ग_लिखो_रेजिस्टर(pcr, HOST_SLEEP_STATE, 0x03, 0x00);
	अगर (ret)
		जाओ out;

	ret = rtsx_pci_init_hw(pcr);
	अगर (ret)
		जाओ out;

	schedule_delayed_work(&pcr->idle_work, msecs_to_jअगरfies(200));

out:
	mutex_unlock(&pcr->pcr_mutex);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम rtsx_pci_shutकरोwn(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा pcr_handle *handle;
	काष्ठा rtsx_pcr *pcr;

	dev_dbg(&(pcidev->dev), "--> %s\n", __func__);

	handle = pci_get_drvdata(pcidev);
	pcr = handle->pcr;
	rtsx_pci_घातer_off(pcr, HOST_ENTER_S1);

	pci_disable_device(pcidev);
	मुक्त_irq(pcr->irq, (व्योम *)pcr);
	अगर (pcr->msi_en)
		pci_disable_msi(pcr->pci);
पूर्ण

अटल पूर्णांक rtsx_pci_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pcidev = to_pci_dev(device);
	काष्ठा pcr_handle *handle;
	काष्ठा rtsx_pcr *pcr;

	handle = pci_get_drvdata(pcidev);
	pcr = handle->pcr;
	dev_dbg(&(pcidev->dev), "--> %s\n", __func__);

	cancel_delayed_work(&pcr->carddet_work);
	cancel_delayed_work(&pcr->rtd3_work);
	cancel_delayed_work(&pcr->idle_work);

	mutex_lock(&pcr->pcr_mutex);
	rtsx_pci_घातer_off(pcr, HOST_ENTER_S3);

	मुक्त_irq(pcr->irq, (व्योम *)pcr);

	mutex_unlock(&pcr->pcr_mutex);

	pcr->is_runसमय_suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rtsx_pci_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pcidev = to_pci_dev(device);
	काष्ठा pcr_handle *handle;
	काष्ठा rtsx_pcr *pcr;

	handle = pci_get_drvdata(pcidev);
	pcr = handle->pcr;
	dev_dbg(&(pcidev->dev), "--> %s\n", __func__);

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_ग_लिखो_रेजिस्टर(pcr, HOST_SLEEP_STATE, 0x03, 0x00);
	rtsx_pci_acquire_irq(pcr);
	synchronize_irq(pcr->irq);

	अगर (pcr->ops->fetch_venकरोr_settings)
		pcr->ops->fetch_venकरोr_settings(pcr);

	rtsx_pci_init_hw(pcr);

	अगर (pcr->slots[RTSX_SD_CARD].p_dev != शून्य) अणु
		pcr->slots[RTSX_SD_CARD].card_event(
				pcr->slots[RTSX_SD_CARD].p_dev);
	पूर्ण

	schedule_delayed_work(&pcr->idle_work, msecs_to_jअगरfies(200));

	mutex_unlock(&pcr->pcr_mutex);
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_PM */

#घोषणा rtsx_pci_shutकरोwn शून्य
#घोषणा rtsx_pci_runसमय_suspend शून्य
#घोषणा rtsx_pic_runसमय_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops rtsx_pci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rtsx_pci_suspend, rtsx_pci_resume)
	SET_RUNTIME_PM_OPS(rtsx_pci_runसमय_suspend, rtsx_pci_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा pci_driver rtsx_pci_driver = अणु
	.name = DRV_NAME_RTSX_PCI,
	.id_table = rtsx_pci_ids,
	.probe = rtsx_pci_probe,
	.हटाओ = rtsx_pci_हटाओ,
	.driver.pm = &rtsx_pci_pm_ops,
	.shutकरोwn = rtsx_pci_shutकरोwn,
पूर्ण;
module_pci_driver(rtsx_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wei WANG <wei_wang@realsil.com.cn>");
MODULE_DESCRIPTION("Realtek PCI-E Card Reader Driver");
