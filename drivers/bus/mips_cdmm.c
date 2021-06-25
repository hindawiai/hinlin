<शैली गुरु>
/*
 * Bus driver क्रम MIPS Common Device Memory Map (CDMM).
 *
 * Copyright (C) 2014-2015 Imagination Technologies Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/err.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cdmm.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/mipsregs.h>

/* Access control and status रेजिस्टर fields */
#घोषणा CDMM_ACSR_DEVTYPE_SHIFT	24
#घोषणा CDMM_ACSR_DEVTYPE	(255ul << CDMM_ACSR_DEVTYPE_SHIFT)
#घोषणा CDMM_ACSR_DEVSIZE_SHIFT	16
#घोषणा CDMM_ACSR_DEVSIZE	(31ul << CDMM_ACSR_DEVSIZE_SHIFT)
#घोषणा CDMM_ACSR_DEVREV_SHIFT	12
#घोषणा CDMM_ACSR_DEVREV	(15ul << CDMM_ACSR_DEVREV_SHIFT)
#घोषणा CDMM_ACSR_UW		(1ul << 3)
#घोषणा CDMM_ACSR_UR		(1ul << 2)
#घोषणा CDMM_ACSR_SW		(1ul << 1)
#घोषणा CDMM_ACSR_SR		(1ul << 0)

/* Each block of device रेजिस्टरs is 64 bytes */
#घोषणा CDMM_DRB_SIZE		64

#घोषणा to_mips_cdmm_driver(d)	container_of(d, काष्ठा mips_cdmm_driver, drv)

/* Default physical base address */
अटल phys_addr_t mips_cdmm_शेष_base;

/* Bus operations */

अटल स्थिर काष्ठा mips_cdmm_device_id *
mips_cdmm_lookup(स्थिर काष्ठा mips_cdmm_device_id *table,
		 काष्ठा mips_cdmm_device *dev)
अणु
	पूर्णांक ret = 0;

	क्रम (; table->type; ++table) अणु
		ret = (dev->type == table->type);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret ? table : शून्य;
पूर्ण

अटल पूर्णांक mips_cdmm_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	काष्ठा mips_cdmm_driver *cdrv = to_mips_cdmm_driver(drv);

	वापस mips_cdmm_lookup(cdrv->id_table, cdev) != शून्य;
पूर्ण

अटल पूर्णांक mips_cdmm_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	पूर्णांक retval = 0;

	retval = add_uevent_var(env, "CDMM_CPU=%u", cdev->cpu);
	अगर (retval)
		वापस retval;

	retval = add_uevent_var(env, "CDMM_TYPE=0x%02x", cdev->type);
	अगर (retval)
		वापस retval;

	retval = add_uevent_var(env, "CDMM_REV=%u", cdev->rev);
	अगर (retval)
		वापस retval;

	retval = add_uevent_var(env, "MODALIAS=mipscdmm:t%02X", cdev->type);
	वापस retval;
पूर्ण

/* Device attributes */

#घोषणा CDMM_ATTR(name, fmt, arg...)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *_dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा mips_cdmm_device *dev = to_mips_cdmm_device(_dev);	\
	वापस प्र_लिखो(buf, fmt, arg);					\
पूर्ण									\
अटल DEVICE_ATTR_RO(name);

CDMM_ATTR(cpu, "%u\n", dev->cpu);
CDMM_ATTR(type, "0x%02x\n", dev->type);
CDMM_ATTR(revision, "%u\n", dev->rev);
CDMM_ATTR(modalias, "mipscdmm:t%02X\n", dev->type);
CDMM_ATTR(resource, "\t%016llx\t%016llx\t%016lx\n",
	  (अचिन्हित दीर्घ दीर्घ)dev->res.start,
	  (अचिन्हित दीर्घ दीर्घ)dev->res.end,
	  dev->res.flags);

अटल काष्ठा attribute *mips_cdmm_dev_attrs[] = अणु
	&dev_attr_cpu.attr,
	&dev_attr_type.attr,
	&dev_attr_revision.attr,
	&dev_attr_modalias.attr,
	&dev_attr_resource.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mips_cdmm_dev);

काष्ठा bus_type mips_cdmm_bustype = अणु
	.name		= "cdmm",
	.dev_groups	= mips_cdmm_dev_groups,
	.match		= mips_cdmm_match,
	.uevent		= mips_cdmm_uevent,
पूर्ण;
EXPORT_SYMBOL_GPL(mips_cdmm_bustype);

/*
 * Standard driver callback helpers.
 *
 * All the CDMM driver callbacks need to be executed on the appropriate CPU from
 * workqueues. For the standard driver callbacks we need a work function
 * (mips_cdmm_अणुव्योम,पूर्णांकपूर्ण_work()) to करो the actual call from the right CPU, and a
 * wrapper function (generated with BUILD_PERCPU_HELPER) to arrange क्रम the work
 * function to be called on that CPU.
 */

/**
 * काष्ठा mips_cdmm_work_dev - Data क्रम per-device call work.
 * @fn:		CDMM driver callback function to call क्रम the device.
 * @dev:	CDMM device to pass to @fn.
 */
काष्ठा mips_cdmm_work_dev अणु
	व्योम			*fn;
	काष्ठा mips_cdmm_device *dev;
पूर्ण;

/**
 * mips_cdmm_व्योम_work() - Call a व्योम वापसing CDMM driver callback.
 * @data:	काष्ठा mips_cdmm_work_dev poपूर्णांकer.
 *
 * A work_on_cpu() callback function to call an arbitrary CDMM driver callback
 * function which करोesn't वापस a value.
 */
अटल दीर्घ mips_cdmm_व्योम_work(व्योम *data)
अणु
	काष्ठा mips_cdmm_work_dev *work = data;
	व्योम (*fn)(काष्ठा mips_cdmm_device *) = work->fn;

	fn(work->dev);
	वापस 0;
पूर्ण

/**
 * mips_cdmm_पूर्णांक_work() - Call an पूर्णांक वापसing CDMM driver callback.
 * @data:	काष्ठा mips_cdmm_work_dev poपूर्णांकer.
 *
 * A work_on_cpu() callback function to call an arbitrary CDMM driver callback
 * function which वापसs an पूर्णांक.
 */
अटल दीर्घ mips_cdmm_पूर्णांक_work(व्योम *data)
अणु
	काष्ठा mips_cdmm_work_dev *work = data;
	पूर्णांक (*fn)(काष्ठा mips_cdmm_device *) = work->fn;

	वापस fn(work->dev);
पूर्ण

#घोषणा _BUILD_RET_व्योम
#घोषणा _BUILD_RET_पूर्णांक	वापस

/**
 * BUILD_PERCPU_HELPER() - Helper to call a CDMM driver callback on right CPU.
 * @_ret:	Return type (व्योम or पूर्णांक).
 * @_name:	Name of CDMM driver callback function.
 *
 * Generates a specअगरic device callback function to call a CDMM driver callback
 * function on the appropriate CPU क्रम the device, and अगर applicable वापस the
 * result.
 */
#घोषणा BUILD_PERCPU_HELPER(_ret, _name)				\
अटल _ret mips_cdmm_##_name(काष्ठा device *dev)			\
अणु									\
	काष्ठा mips_cdmm_device *cdev = to_mips_cdmm_device(dev);	\
	काष्ठा mips_cdmm_driver *cdrv = to_mips_cdmm_driver(dev->driver); \
	काष्ठा mips_cdmm_work_dev work = अणु				\
		.fn	= cdrv->_name,					\
		.dev	= cdev,						\
	पूर्ण;								\
									\
	_BUILD_RET_##_ret work_on_cpu(cdev->cpu,			\
				      mips_cdmm_##_ret##_work, &work);	\
पूर्ण

/* Driver callback functions */
BUILD_PERCPU_HELPER(पूर्णांक, probe)     /* पूर्णांक mips_cdmm_probe(काष्ठा device) */
BUILD_PERCPU_HELPER(पूर्णांक, हटाओ)    /* पूर्णांक mips_cdmm_हटाओ(काष्ठा device) */
BUILD_PERCPU_HELPER(व्योम, shutकरोwn) /* व्योम mips_cdmm_shutकरोwn(काष्ठा device) */


/* Driver registration */

/**
 * mips_cdmm_driver_रेजिस्टर() - Register a CDMM driver.
 * @drv:	CDMM driver inक्रमmation.
 *
 * Register a CDMM driver with the CDMM subप्रणाली. The driver will be inक्रमmed
 * of matching devices which are discovered.
 *
 * Returns:	0 on success.
 */
पूर्णांक mips_cdmm_driver_रेजिस्टर(काष्ठा mips_cdmm_driver *drv)
अणु
	drv->drv.bus = &mips_cdmm_bustype;

	अगर (drv->probe)
		drv->drv.probe = mips_cdmm_probe;
	अगर (drv->हटाओ)
		drv->drv.हटाओ = mips_cdmm_हटाओ;
	अगर (drv->shutकरोwn)
		drv->drv.shutकरोwn = mips_cdmm_shutकरोwn;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(mips_cdmm_driver_रेजिस्टर);

/**
 * mips_cdmm_driver_unरेजिस्टर() - Unरेजिस्टर a CDMM driver.
 * @drv:	CDMM driver inक्रमmation.
 *
 * Unरेजिस्टर a CDMM driver from the CDMM subप्रणाली.
 */
व्योम mips_cdmm_driver_unरेजिस्टर(काष्ठा mips_cdmm_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(mips_cdmm_driver_unरेजिस्टर);


/* CDMM initialisation and bus discovery */

/**
 * काष्ठा mips_cdmm_bus - Info about CDMM bus.
 * @phys:		Physical address at which it is mapped.
 * @regs:		Virtual address where रेजिस्टरs can be accessed.
 * @drbs:		Total number of DRBs.
 * @drbs_reserved:	Number of DRBs reserved.
 * @discovered:		Whether the devices on the bus have been discovered yet.
 * @offline:		Whether the CDMM bus is going offline (or very early
 *			coming back online), in which हाल it should be
 *			reconfigured each समय.
 */
काष्ठा mips_cdmm_bus अणु
	phys_addr_t	 phys;
	व्योम __iomem	*regs;
	अचिन्हित पूर्णांक	 drbs;
	अचिन्हित पूर्णांक	 drbs_reserved;
	bool		 discovered;
	bool		 offline;
पूर्ण;

अटल काष्ठा mips_cdmm_bus mips_cdmm_boot_bus;
अटल DEFINE_PER_CPU(काष्ठा mips_cdmm_bus *, mips_cdmm_buses);
अटल atomic_t mips_cdmm_next_id = ATOMIC_INIT(-1);

/**
 * mips_cdmm_get_bus() - Get the per-CPU CDMM bus inक्रमmation.
 *
 * Get inक्रमmation about the per-CPU CDMM bus, अगर the bus is present.
 *
 * The caller must prevent migration to another CPU, either by disabling
 * pre-emption or by running from a pinned kernel thपढ़ो.
 *
 * Returns:	Poपूर्णांकer to CDMM bus inक्रमmation क्रम the current CPU.
 *		May वापस ERR_PTR(-त्रुटि_सं) in हाल of error, so check with
 *		IS_ERR().
 */
अटल काष्ठा mips_cdmm_bus *mips_cdmm_get_bus(व्योम)
अणु
	काष्ठा mips_cdmm_bus *bus, **bus_p;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu;

	अगर (!cpu_has_cdmm)
		वापस ERR_PTR(-ENODEV);

	cpu = smp_processor_id();
	/* Aव्योम early use of per-cpu primitives beक्रमe initialised */
	अगर (cpu == 0)
		वापस &mips_cdmm_boot_bus;

	/* Get bus poपूर्णांकer */
	bus_p = per_cpu_ptr(&mips_cdmm_buses, cpu);
	local_irq_save(flags);
	bus = *bus_p;
	/* Attempt allocation अगर शून्य */
	अगर (unlikely(!bus)) अणु
		bus = kzalloc(माप(*bus), GFP_ATOMIC);
		अगर (unlikely(!bus))
			bus = ERR_PTR(-ENOMEM);
		अन्यथा
			*bus_p = bus;
	पूर्ण
	local_irq_restore(flags);
	वापस bus;
पूर्ण

/**
 * mips_cdmm_cur_base() - Find current physical base address of CDMM region.
 *
 * Returns:	Physical base address of CDMM region according to cdmmbase CP0
 *		रेजिस्टर, or 0 अगर the CDMM region is disabled.
 */
अटल phys_addr_t mips_cdmm_cur_base(व्योम)
अणु
	अचिन्हित दीर्घ cdmmbase = पढ़ो_c0_cdmmbase();

	अगर (!(cdmmbase & MIPS_CDMMBASE_EN))
		वापस 0;

	वापस (cdmmbase >> MIPS_CDMMBASE_ADDR_SHIFT)
		<< MIPS_CDMMBASE_ADDR_START;
पूर्ण

/**
 * mips_cdmm_phys_base() - Choose a physical base address क्रम CDMM region.
 *
 * Picking a suitable physical address at which to map the CDMM region is
 * platक्रमm specअगरic, so this weak function can be overridden by platक्रमm
 * code to pick a suitable value अगर none is configured by the bootloader.
 * By शेष this method tries to find a CDMM-specअगरic node in the प्रणाली
 * dtb. Note that this won't work क्रम early serial console.
 */
phys_addr_t __weak mips_cdmm_phys_base(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक err;

	np = of_find_compatible_node(शून्य, शून्य, "mti,mips-cdmm");
	अगर (np) अणु
		err = of_address_to_resource(np, 0, &res);
		अगर (!err)
			वापस res.start;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mips_cdmm_setup() - Ensure the CDMM bus is initialised and usable.
 * @bus:	Poपूर्णांकer to bus inक्रमmation क्रम current CPU.
 *		IS_ERR(bus) is checked, so no need क्रम caller to check.
 *
 * The caller must prevent migration to another CPU, either by disabling
 * pre-emption or by running from a pinned kernel thपढ़ो.
 *
 * Returns	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक mips_cdmm_setup(काष्ठा mips_cdmm_bus *bus)
अणु
	अचिन्हित दीर्घ cdmmbase, flags;
	पूर्णांक ret = 0;

	अगर (IS_ERR(bus))
		वापस PTR_ERR(bus);

	local_irq_save(flags);
	/* Don't set up bus a second समय unless marked offline */
	अगर (bus->offline) अणु
		/* If CDMM region is still set up, nothing to करो */
		अगर (bus->phys == mips_cdmm_cur_base())
			जाओ out;
		/*
		 * The CDMM region isn't set up as expected, so it needs
		 * reconfiguring, but then we can stop checking it.
		 */
		bus->offline = false;
	पूर्ण अन्यथा अगर (bus->phys > 1) अणु
		जाओ out;
	पूर्ण

	/* If the CDMM region is alपढ़ोy configured, inherit that setup */
	अगर (!bus->phys)
		bus->phys = mips_cdmm_cur_base();
	/* Otherwise, ask platक्रमm code क्रम suggestions */
	अगर (!bus->phys)
		bus->phys = mips_cdmm_phys_base();
	/* Otherwise, copy what other CPUs have करोne */
	अगर (!bus->phys)
		bus->phys = mips_cdmm_शेष_base;
	/* Otherwise, complain once */
	अगर (!bus->phys) अणु
		bus->phys = 1;
		/*
		 * If you hit this, either your bootloader needs to set up the
		 * CDMM on the boot CPU, or अन्यथा you need to implement
		 * mips_cdmm_phys_base() क्रम your platक्रमm (see यंत्र/cdmm.h).
		 */
		pr_err("cdmm%u: Failed to choose a physical base\n",
		       smp_processor_id());
	पूर्ण
	/* Alपढ़ोy complained? */
	अगर (bus->phys == 1) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Record our success क्रम other CPUs to copy */
	mips_cdmm_शेष_base = bus->phys;

	pr_debug("cdmm%u: Enabling CDMM region at %pa\n",
		 smp_processor_id(), &bus->phys);

	/* Enable CDMM */
	cdmmbase = पढ़ो_c0_cdmmbase();
	cdmmbase &= (1ul << MIPS_CDMMBASE_ADDR_SHIFT) - 1;
	cdmmbase |= (bus->phys >> MIPS_CDMMBASE_ADDR_START)
			<< MIPS_CDMMBASE_ADDR_SHIFT;
	cdmmbase |= MIPS_CDMMBASE_EN;
	ग_लिखो_c0_cdmmbase(cdmmbase);
	tlbw_use_hazard();

	bus->regs = (व्योम __iomem *)CKSEG1ADDR(bus->phys);
	bus->drbs = 1 + ((cdmmbase & MIPS_CDMMBASE_SIZE) >>
			 MIPS_CDMMBASE_SIZE_SHIFT);
	bus->drbs_reserved = !!(cdmmbase & MIPS_CDMMBASE_CI);

out:
	local_irq_restore(flags);
	वापस ret;
पूर्ण

/**
 * mips_cdmm_early_probe() - Minimally probe क्रम a specअगरic device on CDMM.
 * @dev_type:	CDMM type code to look क्रम.
 *
 * Minimally configure the in-CPU Common Device Memory Map (CDMM) and look क्रम a
 * specअगरic device. This can be used to find a device very early in boot क्रम
 * example to configure an early FDC console device.
 *
 * The caller must prevent migration to another CPU, either by disabling
 * pre-emption or by running from a pinned kernel thपढ़ो.
 *
 * Returns:	MMIO poपूर्णांकer to device memory. The caller can पढ़ो the ACSR
 *		रेजिस्टर to find more inक्रमmation about the device (such as the
 *		version number or the number of blocks).
 *		May वापस IOMEM_ERR_PTR(-त्रुटि_सं) in हाल of error, so check with
 *		IS_ERR().
 */
व्योम __iomem *mips_cdmm_early_probe(अचिन्हित पूर्णांक dev_type)
अणु
	काष्ठा mips_cdmm_bus *bus;
	व्योम __iomem *cdmm;
	u32 acsr;
	अचिन्हित पूर्णांक drb, type, size;
	पूर्णांक err;

	अगर (WARN_ON(!dev_type))
		वापस IOMEM_ERR_PTR(-ENODEV);

	bus = mips_cdmm_get_bus();
	err = mips_cdmm_setup(bus);
	अगर (err)
		वापस IOMEM_ERR_PTR(err);

	/* Skip the first block अगर it's reserved क्रम more रेजिस्टरs */
	drb = bus->drbs_reserved;
	cdmm = bus->regs;

	/* Look क्रम a specअगरic device type */
	क्रम (; drb < bus->drbs; drb += size + 1) अणु
		acsr = __raw_पढ़ोl(cdmm + drb * CDMM_DRB_SIZE);
		type = (acsr & CDMM_ACSR_DEVTYPE) >> CDMM_ACSR_DEVTYPE_SHIFT;
		अगर (type == dev_type)
			वापस cdmm + drb * CDMM_DRB_SIZE;
		size = (acsr & CDMM_ACSR_DEVSIZE) >> CDMM_ACSR_DEVSIZE_SHIFT;
	पूर्ण

	वापस IOMEM_ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL_GPL(mips_cdmm_early_probe);

/**
 * mips_cdmm_release() - Release a हटाओd CDMM device.
 * @dev:	Device object
 *
 * Clean up the काष्ठा mips_cdmm_device क्रम an unused CDMM device. This is
 * called स्वतःmatically by the driver core when a device is हटाओd.
 */
अटल व्योम mips_cdmm_release(काष्ठा device *dev)
अणु
	काष्ठा mips_cdmm_device *cdev = to_mips_cdmm_device(dev);

	kमुक्त(cdev);
पूर्ण

/**
 * mips_cdmm_bus_discover() - Discover the devices on the CDMM bus.
 * @bus:	CDMM bus inक्रमmation, must alपढ़ोy be set up.
 */
अटल व्योम mips_cdmm_bus_discover(काष्ठा mips_cdmm_bus *bus)
अणु
	व्योम __iomem *cdmm;
	u32 acsr;
	अचिन्हित पूर्णांक drb, type, size, rev;
	काष्ठा mips_cdmm_device *dev;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret = 0;
	पूर्णांक id = 0;

	/* Skip the first block अगर it's reserved क्रम more रेजिस्टरs */
	drb = bus->drbs_reserved;
	cdmm = bus->regs;

	/* Discover devices */
	bus->discovered = true;
	pr_info("cdmm%u discovery (%u blocks)\n", cpu, bus->drbs);
	क्रम (; drb < bus->drbs; drb += size + 1) अणु
		acsr = __raw_पढ़ोl(cdmm + drb * CDMM_DRB_SIZE);
		type = (acsr & CDMM_ACSR_DEVTYPE) >> CDMM_ACSR_DEVTYPE_SHIFT;
		size = (acsr & CDMM_ACSR_DEVSIZE) >> CDMM_ACSR_DEVSIZE_SHIFT;
		rev  = (acsr & CDMM_ACSR_DEVREV)  >> CDMM_ACSR_DEVREV_SHIFT;

		अगर (!type)
			जारी;

		pr_info("cdmm%u-%u: @%u (%#x..%#x), type 0x%02x, rev %u\n",
			cpu, id, drb, drb * CDMM_DRB_SIZE,
			(drb + size + 1) * CDMM_DRB_SIZE - 1,
			type, rev);

		dev = kzalloc(माप(*dev), GFP_KERNEL);
		अगर (!dev)
			अवरोध;

		dev->cpu = cpu;
		dev->res.start = bus->phys + drb * CDMM_DRB_SIZE;
		dev->res.end = bus->phys +
				(drb + size + 1) * CDMM_DRB_SIZE - 1;
		dev->res.flags = IORESOURCE_MEM;
		dev->type = type;
		dev->rev = rev;
		dev->dev.parent = get_cpu_device(cpu);
		dev->dev.bus = &mips_cdmm_bustype;
		dev->dev.id = atomic_inc_वापस(&mips_cdmm_next_id);
		dev->dev.release = mips_cdmm_release;

		dev_set_name(&dev->dev, "cdmm%u-%u", cpu, id);
		++id;
		ret = device_रेजिस्टर(&dev->dev);
		अगर (ret)
			put_device(&dev->dev);
	पूर्ण
पूर्ण


/*
 * CPU hotplug and initialisation
 *
 * All the CDMM driver callbacks need to be executed on the appropriate CPU from
 * workqueues. For the CPU callbacks, they need to be called क्रम all devices on
 * that CPU, so the work function calls bus_क्रम_each_dev, using a helper
 * (generated with BUILD_PERDEV_HELPER) to call the driver callback अगर the
 * device's CPU matches.
 */

/**
 * BUILD_PERDEV_HELPER() - Helper to call a CDMM driver callback अगर CPU matches.
 * @_name:	Name of CDMM driver callback function.
 *
 * Generates a bus_क्रम_each_dev callback function to call a specअगरic CDMM driver
 * callback function क्रम the device अगर the device's CPU matches that poपूर्णांकed to
 * by the data argument.
 *
 * This is used क्रम inक्रमming drivers क्रम all devices on a given CPU of some
 * event (such as the CPU going online/offline).
 *
 * It is expected to alपढ़ोy be called from the appropriate CPU.
 */
#घोषणा BUILD_PERDEV_HELPER(_name)					\
अटल पूर्णांक mips_cdmm_##_name##_helper(काष्ठा device *dev, व्योम *data)	\
अणु									\
	काष्ठा mips_cdmm_device *cdev = to_mips_cdmm_device(dev);	\
	काष्ठा mips_cdmm_driver *cdrv;					\
	अचिन्हित पूर्णांक cpu = *(अचिन्हित पूर्णांक *)data;			\
									\
	अगर (cdev->cpu != cpu || !dev->driver)				\
		वापस 0;						\
									\
	cdrv = to_mips_cdmm_driver(dev->driver);			\
	अगर (!cdrv->_name)						\
		वापस 0;						\
	वापस cdrv->_name(cdev);					\
पूर्ण

/* bus_क्रम_each_dev callback helper functions */
BUILD_PERDEV_HELPER(cpu_करोwn)       /* पूर्णांक mips_cdmm_cpu_करोwn_helper(...) */
BUILD_PERDEV_HELPER(cpu_up)         /* पूर्णांक mips_cdmm_cpu_up_helper(...) */

/**
 * mips_cdmm_cpu_करोwn_prep() - Callback क्रम CPUHP DOWN_PREP:
 *			       Tear करोwn the CDMM bus.
 * @cpu:	अचिन्हित पूर्णांक CPU number.
 *
 * This function is executed on the hotplugged CPU and calls the CDMM
 * driver cpu_करोwn callback क्रम all devices on that CPU.
 */
अटल पूर्णांक mips_cdmm_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mips_cdmm_bus *bus;
	दीर्घ ret;

	/* Inक्रमm all the devices on the bus */
	ret = bus_क्रम_each_dev(&mips_cdmm_bustype, शून्य, &cpu,
			       mips_cdmm_cpu_करोwn_helper);

	/*
	 * While bus is offline, each use of it should reconfigure it just in
	 * हाल it is first use when coming back online again.
	 */
	bus = mips_cdmm_get_bus();
	अगर (!IS_ERR(bus))
		bus->offline = true;

	वापस ret;
पूर्ण

/**
 * mips_cdmm_cpu_online() - Callback क्रम CPUHP ONLINE: Bring up the CDMM bus.
 * @cpu:	अचिन्हित पूर्णांक CPU number.
 *
 * This work_on_cpu callback function is executed on a given CPU to discover
 * CDMM devices on that CPU, or to call the CDMM driver cpu_up callback क्रम all
 * devices alपढ़ोy discovered on that CPU.
 *
 * It is used as work_on_cpu callback function during
 * initialisation. When CPUs are brought online the function is
 * invoked directly on the hotplugged CPU.
 */
अटल पूर्णांक mips_cdmm_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mips_cdmm_bus *bus;
	दीर्घ ret;

	bus = mips_cdmm_get_bus();
	ret = mips_cdmm_setup(bus);
	अगर (ret)
		वापस ret;

	/* Bus now set up, so we can drop the offline flag अगर still set */
	bus->offline = false;

	अगर (!bus->discovered)
		mips_cdmm_bus_discover(bus);
	अन्यथा
		/* Inक्रमm all the devices on the bus */
		ret = bus_क्रम_each_dev(&mips_cdmm_bustype, शून्य, &cpu,
				       mips_cdmm_cpu_up_helper);

	वापस ret;
पूर्ण

/**
 * mips_cdmm_init() - Initialise CDMM bus.
 *
 * Initialise CDMM bus, discover CDMM devices क्रम online CPUs, and arrange क्रम
 * hotplug notअगरications so the CDMM drivers can be kept up to date.
 */
अटल पूर्णांक __init mips_cdmm_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register the bus */
	ret = bus_रेजिस्टर(&mips_cdmm_bustype);
	अगर (ret)
		वापस ret;

	/* We want to be notअगरied about new CPUs */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "bus/cdmm:online",
				mips_cdmm_cpu_online, mips_cdmm_cpu_करोwn_prep);
	अगर (ret < 0)
		pr_warn("cdmm: Failed to register CPU notifier\n");

	वापस ret;
पूर्ण
subsys_initcall(mips_cdmm_init);
