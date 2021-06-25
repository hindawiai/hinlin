<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * Host side endpoपूर्णांक driver to implement Non-Transparent Bridge functionality
 *
 * Copyright (C) 2020 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/ntb.h>

#घोषणा NTB_EPF_COMMAND		0x0
#घोषणा CMD_CONFIGURE_DOORBELL	1
#घोषणा CMD_TEARDOWN_DOORBELL	2
#घोषणा CMD_CONFIGURE_MW	3
#घोषणा CMD_TEARDOWN_MW		4
#घोषणा CMD_LINK_UP		5
#घोषणा CMD_LINK_DOWN		6

#घोषणा NTB_EPF_ARGUMENT	0x4
#घोषणा MSIX_ENABLE		BIT(16)

#घोषणा NTB_EPF_CMD_STATUS	0x8
#घोषणा COMMAND_STATUS_OK	1
#घोषणा COMMAND_STATUS_ERROR	2

#घोषणा NTB_EPF_LINK_STATUS	0x0A
#घोषणा LINK_STATUS_UP		BIT(0)

#घोषणा NTB_EPF_TOPOLOGY	0x0C
#घोषणा NTB_EPF_LOWER_ADDR	0x10
#घोषणा NTB_EPF_UPPER_ADDR	0x14
#घोषणा NTB_EPF_LOWER_SIZE	0x18
#घोषणा NTB_EPF_UPPER_SIZE	0x1C
#घोषणा NTB_EPF_MW_COUNT	0x20
#घोषणा NTB_EPF_MW1_OFFSET	0x24
#घोषणा NTB_EPF_SPAD_OFFSET	0x28
#घोषणा NTB_EPF_SPAD_COUNT	0x2C
#घोषणा NTB_EPF_DB_ENTRY_SIZE	0x30
#घोषणा NTB_EPF_DB_DATA(n)	(0x34 + (n) * 4)
#घोषणा NTB_EPF_DB_OFFSET(n)	(0xB4 + (n) * 4)

#घोषणा NTB_EPF_MIN_DB_COUNT	3
#घोषणा NTB_EPF_MAX_DB_COUNT	31
#घोषणा NTB_EPF_MW_OFFSET	2

#घोषणा NTB_EPF_COMMAND_TIMEOUT	1000 /* 1 Sec */

क्रमागत pci_barno अणु
	BAR_0,
	BAR_1,
	BAR_2,
	BAR_3,
	BAR_4,
	BAR_5,
पूर्ण;

काष्ठा ntb_epf_dev अणु
	काष्ठा ntb_dev ntb;
	काष्ठा device *dev;
	/* Mutex to protect providing commands to NTB EPF */
	काष्ठा mutex cmd_lock;

	क्रमागत pci_barno ctrl_reg_bar;
	क्रमागत pci_barno peer_spad_reg_bar;
	क्रमागत pci_barno db_reg_bar;

	अचिन्हित पूर्णांक mw_count;
	अचिन्हित पूर्णांक spad_count;
	अचिन्हित पूर्णांक db_count;

	व्योम __iomem *ctrl_reg;
	व्योम __iomem *db_reg;
	व्योम __iomem *peer_spad_reg;

	अचिन्हित पूर्णांक self_spad;
	अचिन्हित पूर्णांक peer_spad;

	पूर्णांक db_val;
	u64 db_valid_mask;
पूर्ण;

#घोषणा ntb_ndev(__ntb) container_of(__ntb, काष्ठा ntb_epf_dev, ntb)

काष्ठा ntb_epf_data अणु
	/* BAR that contains both control region and self spad region */
	क्रमागत pci_barno ctrl_reg_bar;
	/* BAR that contains peer spad region */
	क्रमागत pci_barno peer_spad_reg_bar;
	/* BAR that contains Doorbell region and Memory winकरोw '1' */
	क्रमागत pci_barno db_reg_bar;
पूर्ण;

अटल पूर्णांक ntb_epf_send_command(काष्ठा ntb_epf_dev *ndev, u32 command,
				u32 argument)
अणु
	kसमय_प्रकार समयout;
	bool समयकरोut;
	पूर्णांक ret = 0;
	u32 status;

	mutex_lock(&ndev->cmd_lock);
	ग_लिखोl(argument, ndev->ctrl_reg + NTB_EPF_ARGUMENT);
	ग_लिखोl(command, ndev->ctrl_reg + NTB_EPF_COMMAND);

	समयout = kसमय_add_ms(kसमय_get(), NTB_EPF_COMMAND_TIMEOUT);
	जबतक (1) अणु
		समयकरोut = kसमय_after(kसमय_get(), समयout);
		status = पढ़ोw(ndev->ctrl_reg + NTB_EPF_CMD_STATUS);

		अगर (status == COMMAND_STATUS_ERROR) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (status == COMMAND_STATUS_OK)
			अवरोध;

		अगर (WARN_ON(समयकरोut)) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		usleep_range(5, 10);
	पूर्ण

	ग_लिखोw(0, ndev->ctrl_reg + NTB_EPF_CMD_STATUS);
	mutex_unlock(&ndev->cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ntb_epf_mw_to_bar(काष्ठा ntb_epf_dev *ndev, पूर्णांक idx)
अणु
	काष्ठा device *dev = ndev->dev;

	अगर (idx < 0 || idx > ndev->mw_count) अणु
		dev_err(dev, "Unsupported Memory Window index %d\n", idx);
		वापस -EINVAL;
	पूर्ण

	वापस idx + 2;
पूर्ण

अटल पूर्णांक ntb_epf_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;

	अगर (pidx != NTB_DEF_PEER_IDX) अणु
		dev_err(dev, "Unsupported Peer ID %d\n", pidx);
		वापस -EINVAL;
	पूर्ण

	वापस ndev->mw_count;
पूर्ण

अटल पूर्णांक ntb_epf_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				resource_माप_प्रकार *addr_align,
				resource_माप_प्रकार *size_align,
				resource_माप_प्रकार *size_max)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX) अणु
		dev_err(dev, "Unsupported Peer ID %d\n", pidx);
		वापस -EINVAL;
	पूर्ण

	bar = ntb_epf_mw_to_bar(ndev, idx);
	अगर (bar < 0)
		वापस bar;

	अगर (addr_align)
		*addr_align = SZ_4K;

	अगर (size_align)
		*size_align = 1;

	अगर (size_max)
		*size_max = pci_resource_len(ndev->ntb.pdev, bar);

	वापस 0;
पूर्ण

अटल u64 ntb_epf_link_is_up(काष्ठा ntb_dev *ntb,
			      क्रमागत ntb_speed *speed,
			      क्रमागत ntb_width *width)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 status;

	status = पढ़ोw(ndev->ctrl_reg + NTB_EPF_LINK_STATUS);

	वापस status & LINK_STATUS_UP;
पूर्ण

अटल u32 ntb_epf_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक idx)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	u32 offset;

	अगर (idx < 0 || idx >= ndev->spad_count) अणु
		dev_err(dev, "READ: Invalid ScratchPad Index %d\n", idx);
		वापस 0;
	पूर्ण

	offset = पढ़ोl(ndev->ctrl_reg + NTB_EPF_SPAD_OFFSET);
	offset += (idx << 2);

	वापस पढ़ोl(ndev->ctrl_reg + offset);
पूर्ण

अटल पूर्णांक ntb_epf_spad_ग_लिखो(काष्ठा ntb_dev *ntb,
			      पूर्णांक idx, u32 val)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	u32 offset;

	अगर (idx < 0 || idx >= ndev->spad_count) अणु
		dev_err(dev, "WRITE: Invalid ScratchPad Index %d\n", idx);
		वापस -EINVAL;
	पूर्ण

	offset = पढ़ोl(ndev->ctrl_reg + NTB_EPF_SPAD_OFFSET);
	offset += (idx << 2);
	ग_लिखोl(val, ndev->ctrl_reg + offset);

	वापस 0;
पूर्ण

अटल u32 ntb_epf_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	u32 offset;

	अगर (pidx != NTB_DEF_PEER_IDX) अणु
		dev_err(dev, "Unsupported Peer ID %d\n", pidx);
		वापस -EINVAL;
	पूर्ण

	अगर (idx < 0 || idx >= ndev->spad_count) अणु
		dev_err(dev, "WRITE: Invalid Peer ScratchPad Index %d\n", idx);
		वापस -EINVAL;
	पूर्ण

	offset = (idx << 2);
	वापस पढ़ोl(ndev->peer_spad_reg + offset);
पूर्ण

अटल पूर्णांक ntb_epf_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
				   पूर्णांक idx, u32 val)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	u32 offset;

	अगर (pidx != NTB_DEF_PEER_IDX) अणु
		dev_err(dev, "Unsupported Peer ID %d\n", pidx);
		वापस -EINVAL;
	पूर्ण

	अगर (idx < 0 || idx >= ndev->spad_count) अणु
		dev_err(dev, "WRITE: Invalid Peer ScratchPad Index %d\n", idx);
		वापस -EINVAL;
	पूर्ण

	offset = (idx << 2);
	ग_लिखोl(val, ndev->peer_spad_reg + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_link_enable(काष्ठा ntb_dev *ntb,
			       क्रमागत ntb_speed max_speed,
			       क्रमागत ntb_width max_width)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	पूर्णांक ret;

	ret = ntb_epf_send_command(ndev, CMD_LINK_UP, 0);
	अगर (ret) अणु
		dev_err(dev, "Fail to enable link\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	पूर्णांक ret;

	ret = ntb_epf_send_command(ndev, CMD_LINK_DOWN, 0);
	अगर (ret) अणु
		dev_err(dev, "Fail to disable link\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t ntb_epf_vec_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा ntb_epf_dev *ndev = dev;
	पूर्णांक irq_no;

	irq_no = irq - pci_irq_vector(ndev->ntb.pdev, 0);
	ndev->db_val = irq_no + 1;

	अगर (irq_no == 0)
		ntb_link_event(&ndev->ntb);
	अन्यथा
		ntb_db_event(&ndev->ntb, irq_no);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ntb_epf_init_isr(काष्ठा ntb_epf_dev *ndev, पूर्णांक msi_min, पूर्णांक msi_max)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	काष्ठा device *dev = ndev->dev;
	u32 argument = MSIX_ENABLE;
	पूर्णांक irq;
	पूर्णांक ret;
	पूर्णांक i;

	irq = pci_alloc_irq_vectors(pdev, msi_min, msi_max, PCI_IRQ_MSIX);
	अगर (irq < 0) अणु
		dev_dbg(dev, "Failed to get MSIX interrupts\n");
		irq = pci_alloc_irq_vectors(pdev, msi_min, msi_max,
					    PCI_IRQ_MSI);
		अगर (irq < 0) अणु
			dev_err(dev, "Failed to get MSI interrupts\n");
			वापस irq;
		पूर्ण
		argument &= ~MSIX_ENABLE;
	पूर्ण

	क्रम (i = 0; i < irq; i++) अणु
		ret = request_irq(pci_irq_vector(pdev, i), ntb_epf_vec_isr,
				  0, "ntb_epf", ndev);
		अगर (ret) अणु
			dev_err(dev, "Failed to request irq\n");
			जाओ err_request_irq;
		पूर्ण
	पूर्ण

	ndev->db_count = irq - 1;

	ret = ntb_epf_send_command(ndev, CMD_CONFIGURE_DOORBELL,
				   argument | irq);
	अगर (ret) अणु
		dev_err(dev, "Failed to configure doorbell\n");
		जाओ err_configure_db;
	पूर्ण

	वापस 0;

err_configure_db:
	क्रम (i = 0; i < ndev->db_count + 1; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), ndev);

err_request_irq:
	pci_मुक्त_irq_vectors(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक ntb_epf_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->mw_count;
पूर्ण

अटल पूर्णांक ntb_epf_spad_count(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->spad_count;
पूर्ण

अटल u64 ntb_epf_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	वापस ntb_ndev(ntb)->db_valid_mask;
पूर्ण

अटल पूर्णांक ntb_epf_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
				dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	resource_माप_प्रकार mw_size;
	पूर्णांक bar;

	अगर (pidx != NTB_DEF_PEER_IDX) अणु
		dev_err(dev, "Unsupported Peer ID %d\n", pidx);
		वापस -EINVAL;
	पूर्ण

	bar = idx + NTB_EPF_MW_OFFSET;

	mw_size = pci_resource_len(ntb->pdev, bar);

	अगर (size > mw_size) अणु
		dev_err(dev, "Size:%pa is greater than the MW size %pa\n",
			&size, &mw_size);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(lower_32_bits(addr), ndev->ctrl_reg + NTB_EPF_LOWER_ADDR);
	ग_लिखोl(upper_32_bits(addr), ndev->ctrl_reg + NTB_EPF_UPPER_ADDR);
	ग_लिखोl(lower_32_bits(size), ndev->ctrl_reg + NTB_EPF_LOWER_SIZE);
	ग_लिखोl(upper_32_bits(size), ndev->ctrl_reg + NTB_EPF_UPPER_SIZE);
	ntb_epf_send_command(ndev, CMD_CONFIGURE_MW, idx);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_mw_clear_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	काष्ठा device *dev = ndev->dev;
	पूर्णांक ret = 0;

	ntb_epf_send_command(ndev, CMD_TEARDOWN_MW, idx);
	अगर (ret)
		dev_err(dev, "Failed to teardown memory window\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ntb_epf_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक idx,
				    phys_addr_t *base, resource_माप_प्रकार *size)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 offset = 0;
	पूर्णांक bar;

	अगर (idx == 0)
		offset = पढ़ोl(ndev->ctrl_reg + NTB_EPF_MW1_OFFSET);

	bar = idx + NTB_EPF_MW_OFFSET;

	अगर (base)
		*base = pci_resource_start(ndev->ntb.pdev, bar) + offset;

	अगर (size)
		*size = pci_resource_len(ndev->ntb.pdev, bar) - offset;

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);
	u32 पूर्णांकerrupt_num = ffs(db_bits) + 1;
	काष्ठा device *dev = ndev->dev;
	u32 db_entry_size;
	u32 db_offset;
	u32 db_data;

	अगर (पूर्णांकerrupt_num > ndev->db_count) अणु
		dev_err(dev, "DB interrupt %d greater than Max Supported %d\n",
			पूर्णांकerrupt_num, ndev->db_count);
		वापस -EINVAL;
	पूर्ण

	db_entry_size = पढ़ोl(ndev->ctrl_reg + NTB_EPF_DB_ENTRY_SIZE);

	db_data = पढ़ोl(ndev->ctrl_reg + NTB_EPF_DB_DATA(पूर्णांकerrupt_num));
	db_offset = पढ़ोl(ndev->ctrl_reg + NTB_EPF_DB_OFFSET(पूर्णांकerrupt_num));
	ग_लिखोl(db_data, ndev->db_reg + (db_entry_size * पूर्णांकerrupt_num) +
	       db_offset);

	वापस 0;
पूर्ण

अटल u64 ntb_epf_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);

	वापस ndev->db_val;
पूर्ण

अटल पूर्णांक ntb_epf_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा ntb_epf_dev *ndev = ntb_ndev(ntb);

	ndev->db_val = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ntb_dev_ops ntb_epf_ops = अणु
	.mw_count		= ntb_epf_mw_count,
	.spad_count		= ntb_epf_spad_count,
	.peer_mw_count		= ntb_epf_peer_mw_count,
	.db_valid_mask		= ntb_epf_db_valid_mask,
	.db_set_mask		= ntb_epf_db_set_mask,
	.mw_set_trans		= ntb_epf_mw_set_trans,
	.mw_clear_trans		= ntb_epf_mw_clear_trans,
	.peer_mw_get_addr	= ntb_epf_peer_mw_get_addr,
	.link_enable		= ntb_epf_link_enable,
	.spad_पढ़ो		= ntb_epf_spad_पढ़ो,
	.spad_ग_लिखो		= ntb_epf_spad_ग_लिखो,
	.peer_spad_पढ़ो		= ntb_epf_peer_spad_पढ़ो,
	.peer_spad_ग_लिखो	= ntb_epf_peer_spad_ग_लिखो,
	.peer_db_set		= ntb_epf_peer_db_set,
	.db_पढ़ो		= ntb_epf_db_पढ़ो,
	.mw_get_align		= ntb_epf_mw_get_align,
	.link_is_up		= ntb_epf_link_is_up,
	.db_clear_mask		= ntb_epf_db_clear_mask,
	.db_clear		= ntb_epf_db_clear,
	.link_disable		= ntb_epf_link_disable,
पूर्ण;

अटल अंतरभूत व्योम ntb_epf_init_काष्ठा(काष्ठा ntb_epf_dev *ndev,
				       काष्ठा pci_dev *pdev)
अणु
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &ntb_epf_ops;
पूर्ण

अटल पूर्णांक ntb_epf_init_dev(काष्ठा ntb_epf_dev *ndev)
अणु
	काष्ठा device *dev = ndev->dev;
	पूर्णांक ret;

	/* One Link पूर्णांकerrupt and rest करोorbell पूर्णांकerrupt */
	ret = ntb_epf_init_isr(ndev, NTB_EPF_MIN_DB_COUNT + 1,
			       NTB_EPF_MAX_DB_COUNT + 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to init ISR\n");
		वापस ret;
	पूर्ण

	ndev->db_valid_mask = BIT_ULL(ndev->db_count) - 1;
	ndev->mw_count = पढ़ोl(ndev->ctrl_reg + NTB_EPF_MW_COUNT);
	ndev->spad_count = पढ़ोl(ndev->ctrl_reg + NTB_EPF_SPAD_COUNT);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_epf_init_pci(काष्ठा ntb_epf_dev *ndev,
			    काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = ndev->dev;
	पूर्णांक ret;

	pci_set_drvdata(pdev, ndev);

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable PCI device\n");
		जाओ err_pci_enable;
	पूर्ण

	ret = pci_request_regions(pdev, "ntb");
	अगर (ret) अणु
		dev_err(dev, "Cannot obtain PCI resources\n");
		जाओ err_pci_regions;
	पूर्ण

	pci_set_master(pdev);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(dev, "Cannot set DMA mask\n");
			जाओ err_dma_mask;
		पूर्ण
		dev_warn(&pdev->dev, "Cannot DMA highmem\n");
	पूर्ण

	ndev->ctrl_reg = pci_iomap(pdev, ndev->ctrl_reg_bar, 0);
	अगर (!ndev->ctrl_reg) अणु
		ret = -EIO;
		जाओ err_dma_mask;
	पूर्ण

	ndev->peer_spad_reg = pci_iomap(pdev, ndev->peer_spad_reg_bar, 0);
	अगर (!ndev->peer_spad_reg) अणु
		ret = -EIO;
		जाओ err_dma_mask;
	पूर्ण

	ndev->db_reg = pci_iomap(pdev, ndev->db_reg_bar, 0);
	अगर (!ndev->db_reg) अणु
		ret = -EIO;
		जाओ err_dma_mask;
	पूर्ण

	वापस 0;

err_dma_mask:
	pci_clear_master(pdev);

err_pci_regions:
	pci_disable_device(pdev);

err_pci_enable:
	pci_set_drvdata(pdev, शून्य);

	वापस ret;
पूर्ण

अटल व्योम ntb_epf_deinit_pci(काष्ठा ntb_epf_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;

	pci_iounmap(pdev, ndev->ctrl_reg);
	pci_iounmap(pdev, ndev->peer_spad_reg);
	pci_iounmap(pdev, ndev->db_reg);

	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल व्योम ntb_epf_cleanup_isr(काष्ठा ntb_epf_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	पूर्णांक i;

	ntb_epf_send_command(ndev, CMD_TEARDOWN_DOORBELL, ndev->db_count + 1);

	क्रम (i = 0; i < ndev->db_count + 1; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), ndev);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक ntb_epf_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	क्रमागत pci_barno peer_spad_reg_bar = BAR_1;
	क्रमागत pci_barno ctrl_reg_bar = BAR_0;
	क्रमागत pci_barno db_reg_bar = BAR_2;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ntb_epf_data *data;
	काष्ठा ntb_epf_dev *ndev;
	पूर्णांक ret;

	अगर (pci_is_bridge(pdev))
		वापस -ENODEV;

	ndev = devm_kzalloc(dev, माप(*ndev), GFP_KERNEL);
	अगर (!ndev)
		वापस -ENOMEM;

	data = (काष्ठा ntb_epf_data *)id->driver_data;
	अगर (data) अणु
		अगर (data->peer_spad_reg_bar)
			peer_spad_reg_bar = data->peer_spad_reg_bar;
		अगर (data->ctrl_reg_bar)
			ctrl_reg_bar = data->ctrl_reg_bar;
		अगर (data->db_reg_bar)
			db_reg_bar = data->db_reg_bar;
	पूर्ण

	ndev->peer_spad_reg_bar = peer_spad_reg_bar;
	ndev->ctrl_reg_bar = ctrl_reg_bar;
	ndev->db_reg_bar = db_reg_bar;
	ndev->dev = dev;

	ntb_epf_init_काष्ठा(ndev, pdev);
	mutex_init(&ndev->cmd_lock);

	ret = ntb_epf_init_pci(ndev, pdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to init PCI\n");
		वापस ret;
	पूर्ण

	ret = ntb_epf_init_dev(ndev);
	अगर (ret) अणु
		dev_err(dev, "Failed to init device\n");
		जाओ err_init_dev;
	पूर्ण

	ret = ntb_रेजिस्टर_device(&ndev->ntb);
	अगर (ret) अणु
		dev_err(dev, "Failed to register NTB device\n");
		जाओ err_रेजिस्टर_dev;
	पूर्ण

	वापस 0;

err_रेजिस्टर_dev:
	ntb_epf_cleanup_isr(ndev);

err_init_dev:
	ntb_epf_deinit_pci(ndev);

	वापस ret;
पूर्ण

अटल व्योम ntb_epf_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ntb_epf_dev *ndev = pci_get_drvdata(pdev);

	ntb_unरेजिस्टर_device(&ndev->ntb);
	ntb_epf_cleanup_isr(ndev);
	ntb_epf_deinit_pci(ndev);
पूर्ण

अटल स्थिर काष्ठा ntb_epf_data j721e_data = अणु
	.ctrl_reg_bar = BAR_0,
	.peer_spad_reg_bar = BAR_1,
	.db_reg_bar = BAR_2,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ntb_epf_pci_tbl[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_J721E),
		.class = PCI_CLASS_MEMORY_RAM << 8, .class_mask = 0xffff00,
		.driver_data = (kernel_uदीर्घ_t)&j721e_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ntb_epf_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= ntb_epf_pci_tbl,
	.probe		= ntb_epf_pci_probe,
	.हटाओ		= ntb_epf_pci_हटाओ,
पूर्ण;
module_pci_driver(ntb_epf_pci_driver);

MODULE_DESCRIPTION("PCI ENDPOINT NTB HOST DRIVER");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
