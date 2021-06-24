<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005-2009, 2010 Cavium Networks
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-npi-defs.h>
#समावेश <यंत्र/octeon/cvmx-pci-defs.h>
#समावेश <यंत्र/octeon/cvmx-npei-defs.h>
#समावेश <यंत्र/octeon/cvmx-sli-defs.h>
#समावेश <यंत्र/octeon/cvmx-pexp-defs.h>
#समावेश <यंत्र/octeon/pci-octeon.h>

/*
 * Each bit in msi_मुक्त_irq_biपंचांगask represents a MSI पूर्णांकerrupt that is
 * in use.
 */
अटल u64 msi_मुक्त_irq_biपंचांगask[4];

/*
 * Each bit in msi_multiple_irq_biपंचांगask tells that the device using
 * this bit in msi_मुक्त_irq_biपंचांगask is also using the next bit. This
 * is used so we can disable all of the MSI पूर्णांकerrupts when a device
 * uses multiple.
 */
अटल u64 msi_multiple_irq_biपंचांगask[4];

/*
 * This lock controls updates to msi_मुक्त_irq_biपंचांगask and
 * msi_multiple_irq_biपंचांगask.
 */
अटल DEFINE_SPINLOCK(msi_मुक्त_irq_biपंचांगask_lock);

/*
 * Number of MSI IRQs used. This variable is set up in
 * the module init समय.
 */
अटल पूर्णांक msi_irq_size;

/**
 * Called when a driver request MSI पूर्णांकerrupts instead of the
 * legacy INT A-D. This routine will allocate multiple पूर्णांकerrupts
 * क्रम MSI devices that support them. A device can override this by
 * programming the MSI control bits [6:4] beक्रमe calling
 * pci_enable_msi().
 *
 * @dev:    Device requesting MSI पूर्णांकerrupts
 * @desc:   MSI descriptor
 *
 * Returns 0 on success.
 */
पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *desc)
अणु
	काष्ठा msi_msg msg;
	u16 control;
	पूर्णांक configured_निजी_bits;
	पूर्णांक request_निजी_bits;
	पूर्णांक irq = 0;
	पूर्णांक irq_step;
	u64 search_mask;
	पूर्णांक index;

	/*
	 * Read the MSI config to figure out how many IRQs this device
	 * wants.  Most devices only want 1, which will give
	 * configured_निजी_bits and request_निजी_bits equal 0.
	 */
	pci_पढ़ो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);

	/*
	 * If the number of निजी bits has been configured then use
	 * that value instead of the requested number. This gives the
	 * driver the chance to override the number of पूर्णांकerrupts
	 * beक्रमe calling pci_enable_msi().
	 */
	configured_निजी_bits = (control & PCI_MSI_FLAGS_QSIZE) >> 4;
	अगर (configured_निजी_bits == 0) अणु
		/* Nothing is configured, so use the hardware requested size */
		request_निजी_bits = (control & PCI_MSI_FLAGS_QMASK) >> 1;
	पूर्ण अन्यथा अणु
		/*
		 * Use the number of configured bits, assuming the
		 * driver wanted to override the hardware request
		 * value.
		 */
		request_निजी_bits = configured_निजी_bits;
	पूर्ण

	/*
	 * The PCI 2.3 spec mandates that there are at most 32
	 * पूर्णांकerrupts. If this device asks क्रम more, only give it one.
	 */
	अगर (request_निजी_bits > 5)
		request_निजी_bits = 0;

try_only_one:
	/*
	 * The IRQs have to be aligned on a घातer of two based on the
	 * number being requested.
	 */
	irq_step = 1 << request_निजी_bits;

	/* Mask with one bit क्रम each IRQ */
	search_mask = (1 << irq_step) - 1;

	/*
	 * We're going to search msi_मुक्त_irq_biपंचांगask_lock क्रम zero
	 * bits. This represents an MSI पूर्णांकerrupt number that isn't in
	 * use.
	 */
	spin_lock(&msi_मुक्त_irq_biपंचांगask_lock);
	क्रम (index = 0; index < msi_irq_size/64; index++) अणु
		क्रम (irq = 0; irq < 64; irq += irq_step) अणु
			अगर ((msi_मुक्त_irq_biपंचांगask[index] & (search_mask << irq)) == 0) अणु
				msi_मुक्त_irq_biपंचांगask[index] |= search_mask << irq;
				msi_multiple_irq_biपंचांगask[index] |= (search_mask >> 1) << irq;
				जाओ msi_irq_allocated;
			पूर्ण
		पूर्ण
	पूर्ण
msi_irq_allocated:
	spin_unlock(&msi_मुक्त_irq_biपंचांगask_lock);

	/* Make sure the search क्रम available पूर्णांकerrupts didn't fail */
	अगर (irq >= 64) अणु
		अगर (request_निजी_bits) अणु
			pr_err("arch_setup_msi_irq: Unable to find %d free interrupts, trying just one",
			       1 << request_निजी_bits);
			request_निजी_bits = 0;
			जाओ try_only_one;
		पूर्ण अन्यथा
			panic("arch_setup_msi_irq: Unable to find a free MSI interrupt");
	पूर्ण

	/* MSI पूर्णांकerrupts start at logical IRQ OCTEON_IRQ_MSI_BIT0 */
	irq += index*64;
	irq += OCTEON_IRQ_MSI_BIT0;

	चयन (octeon_dma_bar_type) अणु
	हाल OCTEON_DMA_BAR_TYPE_SMALL:
		/* When not using big bar, Bar 0 is based at 128MB */
		msg.address_lo =
			((128ul << 20) + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = ((128ul << 20) + CVMX_PCI_MSI_RCV) >> 32;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_BIG:
		/* When using big bar, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_PCI_MSI_RCV) >> 32;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_PCIE:
		/* When using PCIe, Bar 0 is based at 0 */
		/* FIXME CVMX_NPEI_MSI_RCV* other than 0? */
		msg.address_lo = (0 + CVMX_NPEI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_NPEI_PCIE_MSI_RCV) >> 32;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_PCIE2:
		/* When using PCIe2, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_SLI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_SLI_PCIE_MSI_RCV) >> 32;
		अवरोध;
	शेष:
		panic("arch_setup_msi_irq: Invalid octeon_dma_bar_type");
	पूर्ण
	msg.data = irq - OCTEON_IRQ_MSI_BIT0;

	/* Update the number of IRQs the device has available to it */
	control &= ~PCI_MSI_FLAGS_QSIZE;
	control |= request_निजी_bits << 4;
	pci_ग_लिखो_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, control);

	irq_set_msi_desc(irq, desc);
	pci_ग_लिखो_msi_msg(irq, &msg);
	वापस 0;
पूर्ण

पूर्णांक arch_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक ret;

	/*
	 * MSI-X is not supported.
	 */
	अगर (type == PCI_CAP_ID_MSIX)
		वापस -EINVAL;

	/*
	 * If an architecture wants to support multiple MSI, it needs to
	 * override arch_setup_msi_irqs()
	 */
	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;

	क्रम_each_pci_msi_entry(entry, dev) अणु
		ret = arch_setup_msi_irq(dev, entry);
		अगर (ret < 0)
			वापस ret;
		अगर (ret > 0)
			वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Called when a device no दीर्घer needs its MSI पूर्णांकerrupts. All
 * MSI पूर्णांकerrupts क्रम the device are मुक्तd.
 *
 * @irq:    The devices first irq number. There may be multple in sequence.
 */
व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक number_irqs;
	u64 biपंचांगask;
	पूर्णांक index = 0;
	पूर्णांक irq0;

	अगर ((irq < OCTEON_IRQ_MSI_BIT0)
		|| (irq > msi_irq_size + OCTEON_IRQ_MSI_BIT0))
		panic("arch_teardown_msi_irq: Attempted to teardown illegal "
		      "MSI interrupt (%d)", irq);

	irq -= OCTEON_IRQ_MSI_BIT0;
	index = irq / 64;
	irq0 = irq % 64;

	/*
	 * Count the number of IRQs we need to मुक्त by looking at the
	 * msi_multiple_irq_biपंचांगask. Each bit set means that the next
	 * IRQ is also owned by this device.
	 */
	number_irqs = 0;
	जबतक ((irq0 + number_irqs < 64) &&
	       (msi_multiple_irq_biपंचांगask[index]
		& (1ull << (irq0 + number_irqs))))
		number_irqs++;
	number_irqs++;
	/* Mask with one bit क्रम each IRQ */
	biपंचांगask = (1 << number_irqs) - 1;
	/* Shअगरt the mask to the correct bit location */
	biपंचांगask <<= irq0;
	अगर ((msi_मुक्त_irq_biपंचांगask[index] & biपंचांगask) != biपंचांगask)
		panic("arch_teardown_msi_irq: Attempted to teardown MSI "
		      "interrupt (%d) not in use", irq);

	/* Checks are करोne, update the in use biपंचांगask */
	spin_lock(&msi_मुक्त_irq_biपंचांगask_lock);
	msi_मुक्त_irq_biपंचांगask[index] &= ~biपंचांगask;
	msi_multiple_irq_biपंचांगask[index] &= ~biपंचांगask;
	spin_unlock(&msi_मुक्त_irq_biपंचांगask_lock);
पूर्ण

अटल DEFINE_RAW_SPINLOCK(octeon_irq_msi_lock);

अटल u64 msi_rcv_reg[4];
अटल u64 mis_ena_reg[4];

अटल व्योम octeon_irq_msi_enable_pcie(काष्ठा irq_data *data)
अणु
	u64 en;
	अचिन्हित दीर्घ flags;
	पूर्णांक msi_number = data->irq - OCTEON_IRQ_MSI_BIT0;
	पूर्णांक irq_index = msi_number >> 6;
	पूर्णांक irq_bit = msi_number & 0x3f;

	raw_spin_lock_irqsave(&octeon_irq_msi_lock, flags);
	en = cvmx_पढ़ो_csr(mis_ena_reg[irq_index]);
	en |= 1ull << irq_bit;
	cvmx_ग_लिखो_csr(mis_ena_reg[irq_index], en);
	cvmx_पढ़ो_csr(mis_ena_reg[irq_index]);
	raw_spin_unlock_irqrestore(&octeon_irq_msi_lock, flags);
पूर्ण

अटल व्योम octeon_irq_msi_disable_pcie(काष्ठा irq_data *data)
अणु
	u64 en;
	अचिन्हित दीर्घ flags;
	पूर्णांक msi_number = data->irq - OCTEON_IRQ_MSI_BIT0;
	पूर्णांक irq_index = msi_number >> 6;
	पूर्णांक irq_bit = msi_number & 0x3f;

	raw_spin_lock_irqsave(&octeon_irq_msi_lock, flags);
	en = cvmx_पढ़ो_csr(mis_ena_reg[irq_index]);
	en &= ~(1ull << irq_bit);
	cvmx_ग_लिखो_csr(mis_ena_reg[irq_index], en);
	cvmx_पढ़ो_csr(mis_ena_reg[irq_index]);
	raw_spin_unlock_irqrestore(&octeon_irq_msi_lock, flags);
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_msi_pcie = अणु
	.name = "MSI",
	.irq_enable = octeon_irq_msi_enable_pcie,
	.irq_disable = octeon_irq_msi_disable_pcie,
पूर्ण;

अटल व्योम octeon_irq_msi_enable_pci(काष्ठा irq_data *data)
अणु
	/*
	 * Octeon PCI करोesn't have the ability to mask/unmask MSI
	 * पूर्णांकerrupts inभागidually. Instead of masking/unmasking them
	 * in groups of 16, we simple assume MSI devices are well
	 * behaved. MSI पूर्णांकerrupts are always enable and the ACK is
	 * assumed to be enough
	 */
पूर्ण

अटल व्योम octeon_irq_msi_disable_pci(काष्ठा irq_data *data)
अणु
	/* See comment in enable */
पूर्ण

अटल काष्ठा irq_chip octeon_irq_chip_msi_pci = अणु
	.name = "MSI",
	.irq_enable = octeon_irq_msi_enable_pci,
	.irq_disable = octeon_irq_msi_disable_pci,
पूर्ण;

/*
 * Called by the पूर्णांकerrupt handling code when an MSI पूर्णांकerrupt
 * occurs.
 */
अटल irqवापस_t __octeon_msi_करो_पूर्णांकerrupt(पूर्णांक index, u64 msi_bits)
अणु
	पूर्णांक irq;
	पूर्णांक bit;

	bit = fls64(msi_bits);
	अगर (bit) अणु
		bit--;
		/* Acknowledge it first. */
		cvmx_ग_लिखो_csr(msi_rcv_reg[index], 1ull << bit);

		irq = bit + OCTEON_IRQ_MSI_BIT0 + 64 * index;
		करो_IRQ(irq);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

#घोषणा OCTEON_MSI_INT_HANDLER_X(x)					\
अटल irqवापस_t octeon_msi_पूर्णांकerrupt##x(पूर्णांक cpl, व्योम *dev_id)	\
अणु									\
	u64 msi_bits = cvmx_पढ़ो_csr(msi_rcv_reg[(x)]);			\
	वापस __octeon_msi_करो_पूर्णांकerrupt((x), msi_bits);		\
पूर्ण

/*
 * Create octeon_msi_पूर्णांकerruptअणु0-3पूर्ण function body
 */
OCTEON_MSI_INT_HANDLER_X(0);
OCTEON_MSI_INT_HANDLER_X(1);
OCTEON_MSI_INT_HANDLER_X(2);
OCTEON_MSI_INT_HANDLER_X(3);

/*
 * Initializes the MSI पूर्णांकerrupt handling code
 */
पूर्णांक __init octeon_msi_initialize(व्योम)
अणु
	पूर्णांक irq;
	काष्ठा irq_chip *msi;

	अगर (octeon_dma_bar_type == OCTEON_DMA_BAR_TYPE_INVALID) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (octeon_dma_bar_type == OCTEON_DMA_BAR_TYPE_PCIE) अणु
		msi_rcv_reg[0] = CVMX_PEXP_NPEI_MSI_RCV0;
		msi_rcv_reg[1] = CVMX_PEXP_NPEI_MSI_RCV1;
		msi_rcv_reg[2] = CVMX_PEXP_NPEI_MSI_RCV2;
		msi_rcv_reg[3] = CVMX_PEXP_NPEI_MSI_RCV3;
		mis_ena_reg[0] = CVMX_PEXP_NPEI_MSI_ENB0;
		mis_ena_reg[1] = CVMX_PEXP_NPEI_MSI_ENB1;
		mis_ena_reg[2] = CVMX_PEXP_NPEI_MSI_ENB2;
		mis_ena_reg[3] = CVMX_PEXP_NPEI_MSI_ENB3;
		msi = &octeon_irq_chip_msi_pcie;
	पूर्ण अन्यथा अणु
		msi_rcv_reg[0] = CVMX_NPI_NPI_MSI_RCV;
#घोषणा INVALID_GENERATE_ADE 0x8700000000000000ULL;
		msi_rcv_reg[1] = INVALID_GENERATE_ADE;
		msi_rcv_reg[2] = INVALID_GENERATE_ADE;
		msi_rcv_reg[3] = INVALID_GENERATE_ADE;
		mis_ena_reg[0] = INVALID_GENERATE_ADE;
		mis_ena_reg[1] = INVALID_GENERATE_ADE;
		mis_ena_reg[2] = INVALID_GENERATE_ADE;
		mis_ena_reg[3] = INVALID_GENERATE_ADE;
		msi = &octeon_irq_chip_msi_pci;
	पूर्ण

	क्रम (irq = OCTEON_IRQ_MSI_BIT0; irq <= OCTEON_IRQ_MSI_LAST; irq++)
		irq_set_chip_and_handler(irq, msi, handle_simple_irq);

	अगर (octeon_has_feature(OCTEON_FEATURE_PCIE)) अणु
		अगर (request_irq(OCTEON_IRQ_PCI_MSI0, octeon_msi_पूर्णांकerrupt0,
				0, "MSI[0:63]", octeon_msi_पूर्णांकerrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI0) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI1, octeon_msi_पूर्णांकerrupt1,
				0, "MSI[64:127]", octeon_msi_पूर्णांकerrupt1))
			panic("request_irq(OCTEON_IRQ_PCI_MSI1) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI2, octeon_msi_पूर्णांकerrupt2,
				0, "MSI[127:191]", octeon_msi_पूर्णांकerrupt2))
			panic("request_irq(OCTEON_IRQ_PCI_MSI2) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI3, octeon_msi_पूर्णांकerrupt3,
				0, "MSI[192:255]", octeon_msi_पूर्णांकerrupt3))
			panic("request_irq(OCTEON_IRQ_PCI_MSI3) failed");

		msi_irq_size = 256;
	पूर्ण अन्यथा अगर (octeon_is_pci_host()) अणु
		अगर (request_irq(OCTEON_IRQ_PCI_MSI0, octeon_msi_पूर्णांकerrupt0,
				0, "MSI[0:15]", octeon_msi_पूर्णांकerrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI0) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI1, octeon_msi_पूर्णांकerrupt0,
				0, "MSI[16:31]", octeon_msi_पूर्णांकerrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI1) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI2, octeon_msi_पूर्णांकerrupt0,
				0, "MSI[32:47]", octeon_msi_पूर्णांकerrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI2) failed");

		अगर (request_irq(OCTEON_IRQ_PCI_MSI3, octeon_msi_पूर्णांकerrupt0,
				0, "MSI[48:63]", octeon_msi_पूर्णांकerrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI3) failed");
		msi_irq_size = 64;
	पूर्ण
	वापस 0;
पूर्ण
subsys_initcall(octeon_msi_initialize);
