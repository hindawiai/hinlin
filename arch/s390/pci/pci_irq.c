<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/airq.h>

अटल क्रमागत अणुFLOATING, सूचीECTEDपूर्ण irq_delivery;

#घोषणा	SIC_IRQ_MODE_ALL		0
#घोषणा	SIC_IRQ_MODE_SINGLE		1
#घोषणा	SIC_IRQ_MODE_सूचीECT		4
#घोषणा	SIC_IRQ_MODE_D_ALL		16
#घोषणा	SIC_IRQ_MODE_D_SINGLE		17
#घोषणा	SIC_IRQ_MODE_SET_CPU		18

/*
 * summary bit vector
 * FLOATING - summary bit per function
 * सूचीECTED - summary bit per cpu (only used in fallback path)
 */
अटल काष्ठा airq_iv *zpci_sbv;

/*
 * पूर्णांकerrupt bit vectors
 * FLOATING - पूर्णांकerrupt bit vector per function
 * सूचीECTED - पूर्णांकerrupt bit vector per cpu
 */
अटल काष्ठा airq_iv **zpci_ibv;

/* Modअगरy PCI: Register adapter पूर्णांकerruptions */
अटल पूर्णांक zpci_set_airq(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_REG_INT);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 status;

	fib.fmt0.isc = PCI_ISC;
	fib.fmt0.sum = 1;	/* enable summary notअगरications */
	fib.fmt0.noi = airq_iv_end(zdev->aibv);
	fib.fmt0.aibv = (अचिन्हित दीर्घ) zdev->aibv->vector;
	fib.fmt0.aibvo = 0;	/* each zdev has its own पूर्णांकerrupt vector */
	fib.fmt0.aisb = (अचिन्हित दीर्घ) zpci_sbv->vector + (zdev->aisb/64)*8;
	fib.fmt0.aisbo = zdev->aisb & 63;

	वापस zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Unरेजिस्टर adapter पूर्णांकerruptions */
अटल पूर्णांक zpci_clear_airq(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_DEREG_INT);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 cc, status;

	cc = zpci_mod_fc(req, &fib, &status);
	अगर (cc == 3 || (cc == 1 && status == 24))
		/* Function alपढ़ोy gone or IRQs alपढ़ोy deरेजिस्टरed. */
		cc = 0;

	वापस cc ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Register CPU directed पूर्णांकerruptions */
अटल पूर्णांक zpci_set_directed_irq(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_REG_INT_D);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 status;

	fib.fmt = 1;
	fib.fmt1.noi = zdev->msi_nr_irqs;
	fib.fmt1.dibvo = zdev->msi_first_bit;

	वापस zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Unरेजिस्टर CPU directed पूर्णांकerruptions */
अटल पूर्णांक zpci_clear_directed_irq(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_DEREG_INT_D);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 cc, status;

	fib.fmt = 1;
	cc = zpci_mod_fc(req, &fib, &status);
	अगर (cc == 3 || (cc == 1 && status == 24))
		/* Function alपढ़ोy gone or IRQs alपढ़ोy deरेजिस्टरed. */
		cc = 0;

	वापस cc ? -EIO : 0;
पूर्ण

अटल पूर्णांक zpci_set_irq_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest,
				 bool क्रमce)
अणु
	काष्ठा msi_desc *entry = irq_get_msi_desc(data->irq);
	काष्ठा msi_msg msg = entry->msg;
	पूर्णांक cpu_addr = smp_cpu_get_cpu_address(cpumask_first(dest));

	msg.address_lo &= 0xff0000ff;
	msg.address_lo |= (cpu_addr << 8);
	pci_ग_लिखो_msi_msg(data->irq, &msg);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip zpci_irq_chip = अणु
	.name = "PCI-MSI",
	.irq_unmask = pci_msi_unmask_irq,
	.irq_mask = pci_msi_mask_irq,
पूर्ण;

अटल व्योम zpci_handle_cpu_local_irq(bool rescan)
अणु
	काष्ठा airq_iv *dibv = zpci_ibv[smp_processor_id()];
	अचिन्हित दीर्घ bit;
	पूर्णांक irqs_on = 0;

	क्रम (bit = 0;;) अणु
		/* Scan the directed IRQ bit vector */
		bit = airq_iv_scan(dibv, bit, airq_iv_end(dibv));
		अगर (bit == -1UL) अणु
			अगर (!rescan || irqs_on++)
				/* End of second scan with पूर्णांकerrupts on. */
				अवरोध;
			/* First scan complete, reenable पूर्णांकerrupts. */
			अगर (zpci_set_irq_ctrl(SIC_IRQ_MODE_D_SINGLE, PCI_ISC))
				अवरोध;
			bit = 0;
			जारी;
		पूर्ण
		inc_irq_stat(IRQIO_MSI);
		generic_handle_irq(airq_iv_get_data(dibv, bit));
	पूर्ण
पूर्ण

काष्ठा cpu_irq_data अणु
	call_single_data_t csd;
	atomic_t scheduled;
पूर्ण;
अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा cpu_irq_data, irq_data);

अटल व्योम zpci_handle_remote_irq(व्योम *data)
अणु
	atomic_t *scheduled = data;

	करो अणु
		zpci_handle_cpu_local_irq(false);
	पूर्ण जबतक (atomic_dec_वापस(scheduled));
पूर्ण

अटल व्योम zpci_handle_fallback_irq(व्योम)
अणु
	काष्ठा cpu_irq_data *cpu_data;
	अचिन्हित दीर्घ cpu;
	पूर्णांक irqs_on = 0;

	क्रम (cpu = 0;;) अणु
		cpu = airq_iv_scan(zpci_sbv, cpu, airq_iv_end(zpci_sbv));
		अगर (cpu == -1UL) अणु
			अगर (irqs_on++)
				/* End of second scan with पूर्णांकerrupts on. */
				अवरोध;
			/* First scan complete, reenable पूर्णांकerrupts. */
			अगर (zpci_set_irq_ctrl(SIC_IRQ_MODE_SINGLE, PCI_ISC))
				अवरोध;
			cpu = 0;
			जारी;
		पूर्ण
		cpu_data = &per_cpu(irq_data, cpu);
		अगर (atomic_inc_वापस(&cpu_data->scheduled) > 1)
			जारी;

		INIT_CSD(&cpu_data->csd, zpci_handle_remote_irq, &cpu_data->scheduled);
		smp_call_function_single_async(cpu, &cpu_data->csd);
	पूर्ण
पूर्ण

अटल व्योम zpci_directed_irq_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	अगर (भग्नing) अणु
		inc_irq_stat(IRQIO_PCF);
		zpci_handle_fallback_irq();
	पूर्ण अन्यथा अणु
		inc_irq_stat(IRQIO_PCD);
		zpci_handle_cpu_local_irq(true);
	पूर्ण
पूर्ण

अटल व्योम zpci_भग्नing_irq_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	अचिन्हित दीर्घ si, ai;
	काष्ठा airq_iv *aibv;
	पूर्णांक irqs_on = 0;

	inc_irq_stat(IRQIO_PCF);
	क्रम (si = 0;;) अणु
		/* Scan adapter summary indicator bit vector */
		si = airq_iv_scan(zpci_sbv, si, airq_iv_end(zpci_sbv));
		अगर (si == -1UL) अणु
			अगर (irqs_on++)
				/* End of second scan with पूर्णांकerrupts on. */
				अवरोध;
			/* First scan complete, reenable पूर्णांकerrupts. */
			अगर (zpci_set_irq_ctrl(SIC_IRQ_MODE_SINGLE, PCI_ISC))
				अवरोध;
			si = 0;
			जारी;
		पूर्ण

		/* Scan the adapter पूर्णांकerrupt vector क्रम this device. */
		aibv = zpci_ibv[si];
		क्रम (ai = 0;;) अणु
			ai = airq_iv_scan(aibv, ai, airq_iv_end(aibv));
			अगर (ai == -1UL)
				अवरोध;
			inc_irq_stat(IRQIO_MSI);
			airq_iv_lock(aibv, ai);
			generic_handle_irq(airq_iv_get_data(aibv, ai));
			airq_iv_unlock(aibv, ai);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक arch_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	अचिन्हित पूर्णांक hwirq, msi_vecs, cpu;
	अचिन्हित दीर्घ bit;
	काष्ठा msi_desc *msi;
	काष्ठा msi_msg msg;
	पूर्णांक cpu_addr;
	पूर्णांक rc, irq;

	zdev->aisb = -1UL;
	zdev->msi_first_bit = -1U;
	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;
	msi_vecs = min_t(अचिन्हित पूर्णांक, nvec, zdev->max_msi);

	अगर (irq_delivery == सूचीECTED) अणु
		/* Allocate cpu vector bits */
		bit = airq_iv_alloc(zpci_ibv[0], msi_vecs);
		अगर (bit == -1UL)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		/* Allocate adapter summary indicator bit */
		bit = airq_iv_alloc_bit(zpci_sbv);
		अगर (bit == -1UL)
			वापस -EIO;
		zdev->aisb = bit;

		/* Create adapter पूर्णांकerrupt vector */
		zdev->aibv = airq_iv_create(msi_vecs, AIRQ_IV_DATA | AIRQ_IV_BITLOCK);
		अगर (!zdev->aibv)
			वापस -ENOMEM;

		/* Wire up लघुcut poपूर्णांकer */
		zpci_ibv[bit] = zdev->aibv;
		/* Each function has its own पूर्णांकerrupt vector */
		bit = 0;
	पूर्ण

	/* Request MSI पूर्णांकerrupts */
	hwirq = bit;
	क्रम_each_pci_msi_entry(msi, pdev) अणु
		rc = -EIO;
		अगर (hwirq - bit >= msi_vecs)
			अवरोध;
		irq = __irq_alloc_descs(-1, 0, 1, 0, THIS_MODULE,
				(irq_delivery == सूचीECTED) ?
				msi->affinity : शून्य);
		अगर (irq < 0)
			वापस -ENOMEM;
		rc = irq_set_msi_desc(irq, msi);
		अगर (rc)
			वापस rc;
		irq_set_chip_and_handler(irq, &zpci_irq_chip,
					 handle_percpu_irq);
		msg.data = hwirq - bit;
		अगर (irq_delivery == सूचीECTED) अणु
			अगर (msi->affinity)
				cpu = cpumask_first(&msi->affinity->mask);
			अन्यथा
				cpu = 0;
			cpu_addr = smp_cpu_get_cpu_address(cpu);

			msg.address_lo = zdev->msi_addr & 0xff0000ff;
			msg.address_lo |= (cpu_addr << 8);

			क्रम_each_possible_cpu(cpu) अणु
				airq_iv_set_data(zpci_ibv[cpu], hwirq, irq);
			पूर्ण
		पूर्ण अन्यथा अणु
			msg.address_lo = zdev->msi_addr & 0xffffffff;
			airq_iv_set_data(zdev->aibv, hwirq, irq);
		पूर्ण
		msg.address_hi = zdev->msi_addr >> 32;
		pci_ग_लिखो_msi_msg(irq, &msg);
		hwirq++;
	पूर्ण

	zdev->msi_first_bit = bit;
	zdev->msi_nr_irqs = msi_vecs;

	अगर (irq_delivery == सूचीECTED)
		rc = zpci_set_directed_irq(zdev);
	अन्यथा
		rc = zpci_set_airq(zdev);
	अगर (rc)
		वापस rc;

	वापस (msi_vecs == nvec) ? 0 : msi_vecs;
पूर्ण

व्योम arch_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	काष्ठा msi_desc *msi;
	पूर्णांक rc;

	/* Disable पूर्णांकerrupts */
	अगर (irq_delivery == सूचीECTED)
		rc = zpci_clear_directed_irq(zdev);
	अन्यथा
		rc = zpci_clear_airq(zdev);
	अगर (rc)
		वापस;

	/* Release MSI पूर्णांकerrupts */
	क्रम_each_pci_msi_entry(msi, pdev) अणु
		अगर (!msi->irq)
			जारी;
		अगर (msi->msi_attrib.is_msix)
			__pci_msix_desc_mask_irq(msi, 1);
		अन्यथा
			__pci_msi_desc_mask_irq(msi, 1, 1);
		irq_set_msi_desc(msi->irq, शून्य);
		irq_मुक्त_desc(msi->irq);
		msi->msg.address_lo = 0;
		msi->msg.address_hi = 0;
		msi->msg.data = 0;
		msi->irq = 0;
	पूर्ण

	अगर (zdev->aisb != -1UL) अणु
		zpci_ibv[zdev->aisb] = शून्य;
		airq_iv_मुक्त_bit(zpci_sbv, zdev->aisb);
		zdev->aisb = -1UL;
	पूर्ण
	अगर (zdev->aibv) अणु
		airq_iv_release(zdev->aibv);
		zdev->aibv = शून्य;
	पूर्ण

	अगर ((irq_delivery == सूचीECTED) && zdev->msi_first_bit != -1U)
		airq_iv_मुक्त(zpci_ibv[0], zdev->msi_first_bit, zdev->msi_nr_irqs);
पूर्ण

अटल काष्ठा airq_काष्ठा zpci_airq = अणु
	.handler = zpci_भग्नing_irq_handler,
	.isc = PCI_ISC,
पूर्ण;

अटल व्योम __init cpu_enable_directed_irq(व्योम *unused)
अणु
	जोड़ zpci_sic_iib iib = अणुअणु0पूर्णपूर्ण;

	iib.cdiib.dibv_addr = (u64) zpci_ibv[smp_processor_id()]->vector;

	__zpci_set_irq_ctrl(SIC_IRQ_MODE_SET_CPU, 0, &iib);
	zpci_set_irq_ctrl(SIC_IRQ_MODE_D_SINGLE, PCI_ISC);
पूर्ण

अटल पूर्णांक __init zpci_directed_irq_init(व्योम)
अणु
	जोड़ zpci_sic_iib iib = अणुअणु0पूर्णपूर्ण;
	अचिन्हित पूर्णांक cpu;

	zpci_sbv = airq_iv_create(num_possible_cpus(), 0);
	अगर (!zpci_sbv)
		वापस -ENOMEM;

	iib.diib.isc = PCI_ISC;
	iib.diib.nr_cpus = num_possible_cpus();
	iib.diib.disb_addr = (u64) zpci_sbv->vector;
	__zpci_set_irq_ctrl(SIC_IRQ_MODE_सूचीECT, 0, &iib);

	zpci_ibv = kसुस्मृति(num_possible_cpus(), माप(*zpci_ibv),
			   GFP_KERNEL);
	अगर (!zpci_ibv)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		/*
		 * Per CPU IRQ vectors look the same but bit-allocation
		 * is only करोne on the first vector.
		 */
		zpci_ibv[cpu] = airq_iv_create(cache_line_size() * BITS_PER_BYTE,
					       AIRQ_IV_DATA |
					       AIRQ_IV_CACHELINE |
					       (!cpu ? AIRQ_IV_ALLOC : 0));
		अगर (!zpci_ibv[cpu])
			वापस -ENOMEM;
	पूर्ण
	on_each_cpu(cpu_enable_directed_irq, शून्य, 1);

	zpci_irq_chip.irq_set_affinity = zpci_set_irq_affinity;

	वापस 0;
पूर्ण

अटल पूर्णांक __init zpci_भग्नing_irq_init(व्योम)
अणु
	zpci_ibv = kसुस्मृति(ZPCI_NR_DEVICES, माप(*zpci_ibv), GFP_KERNEL);
	अगर (!zpci_ibv)
		वापस -ENOMEM;

	zpci_sbv = airq_iv_create(ZPCI_NR_DEVICES, AIRQ_IV_ALLOC);
	अगर (!zpci_sbv)
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	kमुक्त(zpci_ibv);
	वापस -ENOMEM;
पूर्ण

पूर्णांक __init zpci_irq_init(व्योम)
अणु
	पूर्णांक rc;

	irq_delivery = sclp.has_dirq ? सूचीECTED : FLOATING;
	अगर (s390_pci_क्रमce_भग्नing)
		irq_delivery = FLOATING;

	अगर (irq_delivery == सूचीECTED)
		zpci_airq.handler = zpci_directed_irq_handler;

	rc = रेजिस्टर_adapter_पूर्णांकerrupt(&zpci_airq);
	अगर (rc)
		जाओ out;
	/* Set summary to 1 to be called every समय क्रम the ISC. */
	*zpci_airq.lsi_ptr = 1;

	चयन (irq_delivery) अणु
	हाल FLOATING:
		rc = zpci_भग्नing_irq_init();
		अवरोध;
	हाल सूचीECTED:
		rc = zpci_directed_irq_init();
		अवरोध;
	पूर्ण

	अगर (rc)
		जाओ out_airq;

	/*
	 * Enable भग्नing IRQs (with suppression after one IRQ). When using
	 * directed IRQs this enables the fallback path.
	 */
	zpci_set_irq_ctrl(SIC_IRQ_MODE_SINGLE, PCI_ISC);

	वापस 0;
out_airq:
	unरेजिस्टर_adapter_पूर्णांकerrupt(&zpci_airq);
out:
	वापस rc;
पूर्ण

व्योम __init zpci_irq_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	अगर (irq_delivery == सूचीECTED) अणु
		क्रम_each_possible_cpu(cpu) अणु
			airq_iv_release(zpci_ibv[cpu]);
		पूर्ण
	पूर्ण
	kमुक्त(zpci_ibv);
	अगर (zpci_sbv)
		airq_iv_release(zpci_sbv);
	unरेजिस्टर_adapter_पूर्णांकerrupt(&zpci_airq);
पूर्ण
