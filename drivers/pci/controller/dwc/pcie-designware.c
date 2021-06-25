<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Synopsys DesignWare PCIe host controller driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		https://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/types.h>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

/*
 * These पूर्णांकerfaces resemble the pci_find_*capability() पूर्णांकerfaces, but these
 * are क्रम configuring host controllers, which are bridges *to* PCI devices but
 * are not PCI devices themselves.
 */
अटल u8 __dw_pcie_find_next_cap(काष्ठा dw_pcie *pci, u8 cap_ptr,
				  u8 cap)
अणु
	u8 cap_id, next_cap_ptr;
	u16 reg;

	अगर (!cap_ptr)
		वापस 0;

	reg = dw_pcie_पढ़ोw_dbi(pci, cap_ptr);
	cap_id = (reg & 0x00ff);

	अगर (cap_id > PCI_CAP_ID_MAX)
		वापस 0;

	अगर (cap_id == cap)
		वापस cap_ptr;

	next_cap_ptr = (reg & 0xff00) >> 8;
	वापस __dw_pcie_find_next_cap(pci, next_cap_ptr, cap);
पूर्ण

u8 dw_pcie_find_capability(काष्ठा dw_pcie *pci, u8 cap)
अणु
	u8 next_cap_ptr;
	u16 reg;

	reg = dw_pcie_पढ़ोw_dbi(pci, PCI_CAPABILITY_LIST);
	next_cap_ptr = (reg & 0x00ff);

	वापस __dw_pcie_find_next_cap(pci, next_cap_ptr, cap);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_find_capability);

अटल u16 dw_pcie_find_next_ext_capability(काष्ठा dw_pcie *pci, u16 start,
					    u8 cap)
अणु
	u32 header;
	पूर्णांक ttl;
	पूर्णांक pos = PCI_CFG_SPACE_SIZE;

	/* minimum 8 bytes per capability */
	ttl = (PCI_CFG_SPACE_EXP_SIZE - PCI_CFG_SPACE_SIZE) / 8;

	अगर (start)
		pos = start;

	header = dw_pcie_पढ़ोl_dbi(pci, pos);
	/*
	 * If we have no capabilities, this is indicated by cap ID,
	 * cap version and next poपूर्णांकer all being 0.
	 */
	अगर (header == 0)
		वापस 0;

	जबतक (ttl-- > 0) अणु
		अगर (PCI_EXT_CAP_ID(header) == cap && pos != start)
			वापस pos;

		pos = PCI_EXT_CAP_NEXT(header);
		अगर (pos < PCI_CFG_SPACE_SIZE)
			अवरोध;

		header = dw_pcie_पढ़ोl_dbi(pci, pos);
	पूर्ण

	वापस 0;
पूर्ण

u16 dw_pcie_find_ext_capability(काष्ठा dw_pcie *pci, u8 cap)
अणु
	वापस dw_pcie_find_next_ext_capability(pci, 0, cap);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_find_ext_capability);

पूर्णांक dw_pcie_पढ़ो(व्योम __iomem *addr, पूर्णांक size, u32 *val)
अणु
	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size)) अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	अगर (size == 4) अणु
		*val = पढ़ोl(addr);
	पूर्ण अन्यथा अगर (size == 2) अणु
		*val = पढ़ोw(addr);
	पूर्ण अन्यथा अगर (size == 1) अणु
		*val = पढ़ोb(addr);
	पूर्ण अन्यथा अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_पढ़ो);

पूर्णांक dw_pcie_ग_लिखो(व्योम __iomem *addr, पूर्णांक size, u32 val)
अणु
	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (size == 4)
		ग_लिखोl(val, addr);
	अन्यथा अगर (size == 2)
		ग_लिखोw(val, addr);
	अन्यथा अगर (size == 1)
		ग_लिखोb(val, addr);
	अन्यथा
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ग_लिखो);

u32 dw_pcie_पढ़ो_dbi(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (pci->ops && pci->ops->पढ़ो_dbi)
		वापस pci->ops->पढ़ो_dbi(pci, pci->dbi_base, reg, size);

	ret = dw_pcie_पढ़ो(pci->dbi_base + reg, size, &val);
	अगर (ret)
		dev_err(pci->dev, "Read DBI address failed\n");

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_पढ़ो_dbi);

व्योम dw_pcie_ग_लिखो_dbi(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size, u32 val)
अणु
	पूर्णांक ret;

	अगर (pci->ops && pci->ops->ग_लिखो_dbi) अणु
		pci->ops->ग_लिखो_dbi(pci, pci->dbi_base, reg, size, val);
		वापस;
	पूर्ण

	ret = dw_pcie_ग_लिखो(pci->dbi_base + reg, size, val);
	अगर (ret)
		dev_err(pci->dev, "Write DBI address failed\n");
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ग_लिखो_dbi);

व्योम dw_pcie_ग_लिखो_dbi2(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size, u32 val)
अणु
	पूर्णांक ret;

	अगर (pci->ops && pci->ops->ग_लिखो_dbi2) अणु
		pci->ops->ग_लिखो_dbi2(pci, pci->dbi_base2, reg, size, val);
		वापस;
	पूर्ण

	ret = dw_pcie_ग_लिखो(pci->dbi_base2 + reg, size, val);
	अगर (ret)
		dev_err(pci->dev, "write DBI address failed\n");
पूर्ण

अटल u32 dw_pcie_पढ़ोl_atu(काष्ठा dw_pcie *pci, u32 reg)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (pci->ops && pci->ops->पढ़ो_dbi)
		वापस pci->ops->पढ़ो_dbi(pci, pci->atu_base, reg, 4);

	ret = dw_pcie_पढ़ो(pci->atu_base + reg, 4, &val);
	अगर (ret)
		dev_err(pci->dev, "Read ATU address failed\n");

	वापस val;
पूर्ण

अटल व्योम dw_pcie_ग_लिखोl_atu(काष्ठा dw_pcie *pci, u32 reg, u32 val)
अणु
	पूर्णांक ret;

	अगर (pci->ops && pci->ops->ग_लिखो_dbi) अणु
		pci->ops->ग_लिखो_dbi(pci, pci->atu_base, reg, 4, val);
		वापस;
	पूर्ण

	ret = dw_pcie_ग_लिखो(pci->atu_base + reg, 4, val);
	अगर (ret)
		dev_err(pci->dev, "Write ATU address failed\n");
पूर्ण

अटल u32 dw_pcie_पढ़ोl_ob_unroll(काष्ठा dw_pcie *pci, u32 index, u32 reg)
अणु
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);

	वापस dw_pcie_पढ़ोl_atu(pci, offset + reg);
पूर्ण

अटल व्योम dw_pcie_ग_लिखोl_ob_unroll(काष्ठा dw_pcie *pci, u32 index, u32 reg,
				     u32 val)
अणु
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);

	dw_pcie_ग_लिखोl_atu(pci, offset + reg, val);
पूर्ण

अटल अंतरभूत u32 dw_pcie_enable_ecrc(u32 val)
अणु
	/*
	 * DesignWare core version 4.90A has a design issue where the 'TD'
	 * bit in the Control रेजिस्टर-1 of the ATU outbound region acts
	 * like an override क्रम the ECRC setting, i.e., the presence of TLP
	 * Digest (ECRC) in the outgoing TLPs is solely determined by this
	 * bit. This is contrary to the PCIe spec which says that the
	 * enablement of the ECRC is solely determined by the AER
	 * रेजिस्टरs.
	 *
	 * Because of this, even when the ECRC is enabled through AER
	 * रेजिस्टरs, the transactions going through ATU won't have TLP
	 * Digest as there is no way the PCI core AER code could program
	 * the TD bit which is specअगरic to the DesignWare core.
	 *
	 * The best way to handle this scenario is to program the TD bit
	 * always. It affects only the traffic from root port to करोwnstream
	 * devices.
	 *
	 * At this poपूर्णांक,
	 * When ECRC is enabled in AER रेजिस्टरs, everything works normally
	 * When ECRC is NOT enabled in AER रेजिस्टरs, then,
	 * on Root Port:- TLP Digest (DWord size) माला_लो appended to each packet
	 *                even through it is not required. Since करोwnstream
	 *                TLPs are mostly क्रम configuration accesses and BAR
	 *                accesses, they are not in critical path and won't
	 *                have much negative effect on the perक्रमmance.
	 * on End Poपूर्णांक:- TLP Digest is received क्रम some/all the packets coming
	 *                from the root port. TLP Digest is ignored because,
	 *                as per the PCIe Spec r5.0 v1.0 section 2.2.3
	 *                "TLP Digest Rules", when an endpoपूर्णांक receives TLP
	 *                Digest when its ECRC check functionality is disabled
	 *                in AER रेजिस्टरs, received TLP Digest is just ignored.
	 * Since there is no issue or error reported either side, best way to
	 * handle the scenario is to program TD bit by शेष.
	 */

	वापस val | PCIE_ATU_TD;
पूर्ण

अटल व्योम dw_pcie_prog_outbound_atu_unroll(काष्ठा dw_pcie *pci, u8 func_no,
					     पूर्णांक index, पूर्णांक type,
					     u64 cpu_addr, u64 pci_addr,
					     u64 size)
अणु
	u32 retries, val;
	u64 limit_addr = cpu_addr + size - 1;

	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_BASE,
				 lower_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_BASE,
				 upper_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_LIMIT,
				 lower_32_bits(limit_addr));
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_LIMIT,
				 upper_32_bits(limit_addr));
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
				 lower_32_bits(pci_addr));
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
				 upper_32_bits(pci_addr));
	val = type | PCIE_ATU_FUNC_NUM(func_no);
	val = upper_32_bits(size - 1) ?
		val | PCIE_ATU_INCREASE_REGION_SIZE : val;
	अगर (pci->version == 0x490A)
		val = dw_pcie_enable_ecrc(val);
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1, val);
	dw_pcie_ग_लिखोl_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
				 PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect beक्रमe any subsequent config
	 * and I/O accesses.
	 */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) अणु
		val = dw_pcie_पढ़ोl_ob_unroll(pci, index,
					      PCIE_ATU_UNR_REGION_CTRL2);
		अगर (val & PCIE_ATU_ENABLE)
			वापस;

		mdelay(LINK_WAIT_IATU);
	पूर्ण
	dev_err(pci->dev, "Outbound iATU is not being enabled\n");
पूर्ण

अटल व्योम __dw_pcie_prog_outbound_atu(काष्ठा dw_pcie *pci, u8 func_no,
					पूर्णांक index, पूर्णांक type, u64 cpu_addr,
					u64 pci_addr, u64 size)
अणु
	u32 retries, val;

	अगर (pci->ops && pci->ops->cpu_addr_fixup)
		cpu_addr = pci->ops->cpu_addr_fixup(pci, cpu_addr);

	अगर (pci->iatu_unroll_enabled) अणु
		dw_pcie_prog_outbound_atu_unroll(pci, func_no, index, type,
						 cpu_addr, pci_addr, size);
		वापस;
	पूर्ण

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT,
			   PCIE_ATU_REGION_OUTBOUND | index);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LOWER_BASE,
			   lower_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_UPPER_BASE,
			   upper_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LIMIT,
			   lower_32_bits(cpu_addr + size - 1));
	अगर (pci->version >= 0x460A)
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_UPPER_LIMIT,
				   upper_32_bits(cpu_addr + size - 1));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LOWER_TARGET,
			   lower_32_bits(pci_addr));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_UPPER_TARGET,
			   upper_32_bits(pci_addr));
	val = type | PCIE_ATU_FUNC_NUM(func_no);
	val = ((upper_32_bits(size - 1)) && (pci->version >= 0x460A)) ?
		val | PCIE_ATU_INCREASE_REGION_SIZE : val;
	अगर (pci->version == 0x490A)
		val = dw_pcie_enable_ecrc(val);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_CR1, val);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect beक्रमe any subsequent config
	 * and I/O accesses.
	 */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_CR2);
		अगर (val & PCIE_ATU_ENABLE)
			वापस;

		mdelay(LINK_WAIT_IATU);
	पूर्ण
	dev_err(pci->dev, "Outbound iATU is not being enabled\n");
पूर्ण

व्योम dw_pcie_prog_outbound_atu(काष्ठा dw_pcie *pci, पूर्णांक index, पूर्णांक type,
			       u64 cpu_addr, u64 pci_addr, u64 size)
अणु
	__dw_pcie_prog_outbound_atu(pci, 0, index, type,
				    cpu_addr, pci_addr, size);
पूर्ण

व्योम dw_pcie_prog_ep_outbound_atu(काष्ठा dw_pcie *pci, u8 func_no, पूर्णांक index,
				  पूर्णांक type, u64 cpu_addr, u64 pci_addr,
				  u64 size)
अणु
	__dw_pcie_prog_outbound_atu(pci, func_no, index, type,
				    cpu_addr, pci_addr, size);
पूर्ण

अटल u32 dw_pcie_पढ़ोl_ib_unroll(काष्ठा dw_pcie *pci, u32 index, u32 reg)
अणु
	u32 offset = PCIE_GET_ATU_INB_UNR_REG_OFFSET(index);

	वापस dw_pcie_पढ़ोl_atu(pci, offset + reg);
पूर्ण

अटल व्योम dw_pcie_ग_लिखोl_ib_unroll(काष्ठा dw_pcie *pci, u32 index, u32 reg,
				     u32 val)
अणु
	u32 offset = PCIE_GET_ATU_INB_UNR_REG_OFFSET(index);

	dw_pcie_ग_लिखोl_atu(pci, offset + reg, val);
पूर्ण

अटल पूर्णांक dw_pcie_prog_inbound_atu_unroll(काष्ठा dw_pcie *pci, u8 func_no,
					   पूर्णांक index, पूर्णांक bar, u64 cpu_addr,
					   क्रमागत dw_pcie_as_type as_type)
अणु
	पूर्णांक type;
	u32 retries, val;

	dw_pcie_ग_लिखोl_ib_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
				 lower_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_ib_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
				 upper_32_bits(cpu_addr));

	चयन (as_type) अणु
	हाल DW_PCIE_AS_MEM:
		type = PCIE_ATU_TYPE_MEM;
		अवरोध;
	हाल DW_PCIE_AS_IO:
		type = PCIE_ATU_TYPE_IO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dw_pcie_ग_लिखोl_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1, type |
				 PCIE_ATU_FUNC_NUM(func_no));
	dw_pcie_ग_लिखोl_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
				 PCIE_ATU_FUNC_NUM_MATCH_EN |
				 PCIE_ATU_ENABLE |
				 PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

	/*
	 * Make sure ATU enable takes effect beक्रमe any subsequent config
	 * and I/O accesses.
	 */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) अणु
		val = dw_pcie_पढ़ोl_ib_unroll(pci, index,
					      PCIE_ATU_UNR_REGION_CTRL2);
		अगर (val & PCIE_ATU_ENABLE)
			वापस 0;

		mdelay(LINK_WAIT_IATU);
	पूर्ण
	dev_err(pci->dev, "Inbound iATU is not being enabled\n");

	वापस -EBUSY;
पूर्ण

पूर्णांक dw_pcie_prog_inbound_atu(काष्ठा dw_pcie *pci, u8 func_no, पूर्णांक index,
			     पूर्णांक bar, u64 cpu_addr,
			     क्रमागत dw_pcie_as_type as_type)
अणु
	पूर्णांक type;
	u32 retries, val;

	अगर (pci->iatu_unroll_enabled)
		वापस dw_pcie_prog_inbound_atu_unroll(pci, func_no, index, bar,
						       cpu_addr, as_type);

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_INBOUND |
			   index);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LOWER_TARGET, lower_32_bits(cpu_addr));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_UPPER_TARGET, upper_32_bits(cpu_addr));

	चयन (as_type) अणु
	हाल DW_PCIE_AS_MEM:
		type = PCIE_ATU_TYPE_MEM;
		अवरोध;
	हाल DW_PCIE_AS_IO:
		type = PCIE_ATU_TYPE_IO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_CR1, type |
			   PCIE_ATU_FUNC_NUM(func_no));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE |
			   PCIE_ATU_FUNC_NUM_MATCH_EN |
			   PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

	/*
	 * Make sure ATU enable takes effect beक्रमe any subsequent config
	 * and I/O accesses.
	 */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_CR2);
		अगर (val & PCIE_ATU_ENABLE)
			वापस 0;

		mdelay(LINK_WAIT_IATU);
	पूर्ण
	dev_err(pci->dev, "Inbound iATU is not being enabled\n");

	वापस -EBUSY;
पूर्ण

व्योम dw_pcie_disable_atu(काष्ठा dw_pcie *pci, पूर्णांक index,
			 क्रमागत dw_pcie_region_type type)
अणु
	पूर्णांक region;

	चयन (type) अणु
	हाल DW_PCIE_REGION_INBOUND:
		region = PCIE_ATU_REGION_INBOUND;
		अवरोध;
	हाल DW_PCIE_REGION_OUTBOUND:
		region = PCIE_ATU_REGION_OUTBOUND;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT, region | index);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_CR2, ~(u32)PCIE_ATU_ENABLE);
पूर्ण

पूर्णांक dw_pcie_रुको_क्रम_link(काष्ठा dw_pcie *pci)
अणु
	पूर्णांक retries;

	/* Check अगर the link is up or not */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) अणु
		अगर (dw_pcie_link_up(pci)) अणु
			dev_info(pci->dev, "Link up\n");
			वापस 0;
		पूर्ण
		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	पूर्ण

	dev_info(pci->dev, "Phy link never came up\n");

	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_रुको_क्रम_link);

पूर्णांक dw_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	u32 val;

	अगर (pci->ops && pci->ops->link_up)
		वापस pci->ops->link_up(pci);

	val = पढ़ोl(pci->dbi_base + PCIE_PORT_DEBUG1);
	वापस ((val & PCIE_PORT_DEBUG1_LINK_UP) &&
		(!(val & PCIE_PORT_DEBUG1_LINK_IN_TRAINING)));
पूर्ण

व्योम dw_pcie_upconfig_setup(काष्ठा dw_pcie *pci)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_MULTI_LANE_CTRL);
	val |= PORT_MLTI_UPCFG_SUPPORT;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PORT_MULTI_LANE_CTRL, val);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_upconfig_setup);

अटल व्योम dw_pcie_link_set_max_speed(काष्ठा dw_pcie *pci, u32 link_gen)
अणु
	u32 cap, ctrl2, link_speed;
	u8 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);

	cap = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_LNKCAP);
	ctrl2 = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_LNKCTL2);
	ctrl2 &= ~PCI_EXP_LNKCTL2_TLS;

	चयन (pcie_link_speed[link_gen]) अणु
	हाल PCIE_SPEED_2_5GT:
		link_speed = PCI_EXP_LNKCTL2_TLS_2_5GT;
		अवरोध;
	हाल PCIE_SPEED_5_0GT:
		link_speed = PCI_EXP_LNKCTL2_TLS_5_0GT;
		अवरोध;
	हाल PCIE_SPEED_8_0GT:
		link_speed = PCI_EXP_LNKCTL2_TLS_8_0GT;
		अवरोध;
	हाल PCIE_SPEED_16_0GT:
		link_speed = PCI_EXP_LNKCTL2_TLS_16_0GT;
		अवरोध;
	शेष:
		/* Use hardware capability */
		link_speed = FIELD_GET(PCI_EXP_LNKCAP_SLS, cap);
		ctrl2 &= ~PCI_EXP_LNKCTL2_HASD;
		अवरोध;
	पूर्ण

	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_LNKCTL2, ctrl2 | link_speed);

	cap &= ~((u32)PCI_EXP_LNKCAP_SLS);
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_LNKCAP, cap | link_speed);

पूर्ण

अटल u8 dw_pcie_iatu_unroll_enabled(काष्ठा dw_pcie *pci)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_VIEWPORT);
	अगर (val == 0xffffffff)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम dw_pcie_iatu_detect_regions_unroll(काष्ठा dw_pcie *pci)
अणु
	पूर्णांक max_region, i, ob = 0, ib = 0;
	u32 val;

	max_region = min((पूर्णांक)pci->atu_size / 512, 256);

	क्रम (i = 0; i < max_region; i++) अणु
		dw_pcie_ग_लिखोl_ob_unroll(pci, i, PCIE_ATU_UNR_LOWER_TARGET,
					0x11110000);

		val = dw_pcie_पढ़ोl_ob_unroll(pci, i, PCIE_ATU_UNR_LOWER_TARGET);
		अगर (val == 0x11110000)
			ob++;
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < max_region; i++) अणु
		dw_pcie_ग_लिखोl_ib_unroll(pci, i, PCIE_ATU_UNR_LOWER_TARGET,
					0x11110000);

		val = dw_pcie_पढ़ोl_ib_unroll(pci, i, PCIE_ATU_UNR_LOWER_TARGET);
		अगर (val == 0x11110000)
			ib++;
		अन्यथा
			अवरोध;
	पूर्ण
	pci->num_ib_winकरोws = ib;
	pci->num_ob_winकरोws = ob;
पूर्ण

अटल व्योम dw_pcie_iatu_detect_regions(काष्ठा dw_pcie *pci)
अणु
	पूर्णांक max_region, i, ob = 0, ib = 0;
	u32 val;

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT, 0xFF);
	max_region = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_VIEWPORT) + 1;

	क्रम (i = 0; i < max_region; i++) अणु
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_OUTBOUND | i);
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LOWER_TARGET, 0x11110000);
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_LOWER_TARGET);
		अगर (val == 0x11110000)
			ob++;
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < max_region; i++) अणु
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_INBOUND | i);
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_ATU_LOWER_TARGET, 0x11110000);
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_ATU_LOWER_TARGET);
		अगर (val == 0x11110000)
			ib++;
		अन्यथा
			अवरोध;
	पूर्ण

	pci->num_ib_winकरोws = ib;
	pci->num_ob_winकरोws = ob;
पूर्ण

व्योम dw_pcie_iatu_detect(काष्ठा dw_pcie *pci)
अणु
	काष्ठा device *dev = pci->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (pci->version >= 0x480A || (!pci->version &&
				       dw_pcie_iatu_unroll_enabled(pci))) अणु
		pci->iatu_unroll_enabled = true;
		अगर (!pci->atu_base) अणु
			काष्ठा resource *res =
				platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "atu");
			अगर (res)
				pci->atu_size = resource_size(res);
			pci->atu_base = devm_ioremap_resource(dev, res);
			अगर (IS_ERR(pci->atu_base))
				pci->atu_base = pci->dbi_base + DEFAULT_DBI_ATU_OFFSET;
		पूर्ण

		अगर (!pci->atu_size)
			/* Pick a minimal शेष, enough क्रम 8 in and 8 out winकरोws */
			pci->atu_size = SZ_4K;

		dw_pcie_iatu_detect_regions_unroll(pci);
	पूर्ण अन्यथा
		dw_pcie_iatu_detect_regions(pci);

	dev_info(pci->dev, "iATU unroll: %s\n", pci->iatu_unroll_enabled ?
		"enabled" : "disabled");

	dev_info(pci->dev, "Detected iATU regions: %u outbound, %u inbound",
		 pci->num_ob_winकरोws, pci->num_ib_winकरोws);
पूर्ण

व्योम dw_pcie_setup(काष्ठा dw_pcie *pci)
अणु
	u32 val;
	काष्ठा device *dev = pci->dev;
	काष्ठा device_node *np = dev->of_node;

	अगर (pci->link_gen > 0)
		dw_pcie_link_set_max_speed(pci, pci->link_gen);

	/* Configure Gen1 N_FTS */
	अगर (pci->n_fts[0]) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_AFR);
		val &= ~(PORT_AFR_N_FTS_MASK | PORT_AFR_CC_N_FTS_MASK);
		val |= PORT_AFR_N_FTS(pci->n_fts[0]);
		val |= PORT_AFR_CC_N_FTS(pci->n_fts[0]);
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_PORT_AFR, val);
	पूर्ण

	/* Configure Gen2+ N_FTS */
	अगर (pci->n_fts[1]) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
		val &= ~PORT_LOGIC_N_FTS_MASK;
		val |= pci->n_fts[pci->link_gen - 1];
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
	पूर्ण

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val &= ~PORT_LINK_FAST_LINK_MODE;
	val |= PORT_LINK_DLL_LINK_EN;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	of_property_पढ़ो_u32(np, "num-lanes", &pci->num_lanes);
	अगर (!pci->num_lanes) अणु
		dev_dbg(pci->dev, "Using h/w default number of lanes\n");
		वापस;
	पूर्ण

	/* Set the number of lanes */
	val &= ~PORT_LINK_FAST_LINK_MODE;
	val &= ~PORT_LINK_MODE_MASK;
	चयन (pci->num_lanes) अणु
	हाल 1:
		val |= PORT_LINK_MODE_1_LANES;
		अवरोध;
	हाल 2:
		val |= PORT_LINK_MODE_2_LANES;
		अवरोध;
	हाल 4:
		val |= PORT_LINK_MODE_4_LANES;
		अवरोध;
	हाल 8:
		val |= PORT_LINK_MODE_8_LANES;
		अवरोध;
	शेष:
		dev_err(pci->dev, "num-lanes %u: invalid value\n", pci->num_lanes);
		वापस;
	पूर्ण
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	/* Set link width speed control रेजिस्टर */
	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
	val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
	चयन (pci->num_lanes) अणु
	हाल 1:
		val |= PORT_LOGIC_LINK_WIDTH_1_LANES;
		अवरोध;
	हाल 2:
		val |= PORT_LOGIC_LINK_WIDTH_2_LANES;
		अवरोध;
	हाल 4:
		val |= PORT_LOGIC_LINK_WIDTH_4_LANES;
		अवरोध;
	हाल 8:
		val |= PORT_LOGIC_LINK_WIDTH_8_LANES;
		अवरोध;
	पूर्ण
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);

	अगर (of_property_पढ़ो_bool(np, "snps,enable-cdm-check")) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS);
		val |= PCIE_PL_CHK_REG_CHK_REG_CONTINUOUS |
		       PCIE_PL_CHK_REG_CHK_REG_START;
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS, val);
	पूर्ण
पूर्ण
