<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * imr.c -- Intel Isolated Memory Region driver
 *
 * Copyright(c) 2013 Intel Corporation.
 * Copyright(c) 2015 Bryan O'Donoghue <pure.logic@nexus-software.ie>
 *
 * IMR रेजिस्टरs define an isolated region of memory that can
 * be masked to prohibit certain प्रणाली agents from accessing memory.
 * When a device behind a masked port perक्रमms an access - snooped or
 * not, an IMR may optionally prevent that transaction from changing
 * the state of memory or from getting correct data in response to the
 * operation.
 *
 * Write data will be dropped and पढ़ोs will वापस 0xFFFFFFFF, the
 * प्रणाली will reset and प्रणाली BIOS will prपूर्णांक out an error message to
 * inक्रमm the user that an IMR has been violated.
 *
 * This code is based on the Linux MTRR code and reference code from
 * Intel's Quark BSP EFI, Linux and grub code.
 *
 * See quark-x1000-datasheet.pdf क्रम रेजिस्टर definitions.
 * http://www.पूर्णांकel.com/content/dam/www/खुला/us/en/करोcuments/datasheets/quark-x1000-datasheet.pdf
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र-generic/sections.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/imr.h>
#समावेश <यंत्र/iosf_mbi.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>

काष्ठा imr_device अणु
	bool		init;
	काष्ठा mutex	lock;
	पूर्णांक		max_imr;
	पूर्णांक		reg_base;
पूर्ण;

अटल काष्ठा imr_device imr_dev;

/*
 * IMR पढ़ो/ग_लिखो mask control रेजिस्टरs.
 * See quark-x1000-datasheet.pdf sections 12.7.4.5 and 12.7.4.6 क्रम
 * bit definitions.
 *
 * addr_hi
 * 31		Lock bit
 * 30:24	Reserved
 * 23:2		1 KiB aligned lo address
 * 1:0		Reserved
 *
 * addr_hi
 * 31:24	Reserved
 * 23:2		1 KiB aligned hi address
 * 1:0		Reserved
 */
#घोषणा IMR_LOCK	BIT(31)

काष्ठा imr_regs अणु
	u32 addr_lo;
	u32 addr_hi;
	u32 rmask;
	u32 wmask;
पूर्ण;

#घोषणा IMR_NUM_REGS	(माप(काष्ठा imr_regs)/माप(u32))
#घोषणा IMR_SHIFT	8
#घोषणा imr_to_phys(x)	((x) << IMR_SHIFT)
#घोषणा phys_to_imr(x)	((x) >> IMR_SHIFT)

/**
 * imr_is_enabled - true अगर an IMR is enabled false otherwise.
 *
 * Determines अगर an IMR is enabled based on address range and पढ़ो/ग_लिखो
 * mask. An IMR set with an address range set to zero and a पढ़ो/ग_लिखो
 * access mask set to all is considered to be disabled. An IMR in any
 * other state - क्रम example set to zero but without पढ़ो/ग_लिखो access
 * all is considered to be enabled. This definition of disabled is how
 * firmware चयनes off an IMR and is मुख्यtained in kernel क्रम
 * consistency.
 *
 * @imr:	poपूर्णांकer to IMR descriptor.
 * @वापस:	true अगर IMR enabled false अगर disabled.
 */
अटल अंतरभूत पूर्णांक imr_is_enabled(काष्ठा imr_regs *imr)
अणु
	वापस !(imr->rmask == IMR_READ_ACCESS_ALL &&
		 imr->wmask == IMR_WRITE_ACCESS_ALL &&
		 imr_to_phys(imr->addr_lo) == 0 &&
		 imr_to_phys(imr->addr_hi) == 0);
पूर्ण

/**
 * imr_पढ़ो - पढ़ो an IMR at a given index.
 *
 * Requires caller to hold imr mutex.
 *
 * @idev:	poपूर्णांकer to imr_device काष्ठाure.
 * @imr_id:	IMR entry to पढ़ो.
 * @imr:	IMR काष्ठाure representing address and access masks.
 * @वापस:	0 on success or error code passed from mbi_iosf on failure.
 */
अटल पूर्णांक imr_पढ़ो(काष्ठा imr_device *idev, u32 imr_id, काष्ठा imr_regs *imr)
अणु
	u32 reg = imr_id * IMR_NUM_REGS + idev->reg_base;
	पूर्णांक ret;

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->addr_lo);
	अगर (ret)
		वापस ret;

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->addr_hi);
	अगर (ret)
		वापस ret;

	ret = iosf_mbi_पढ़ो(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->rmask);
	अगर (ret)
		वापस ret;

	वापस iosf_mbi_पढ़ो(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->wmask);
पूर्ण

/**
 * imr_ग_लिखो - ग_लिखो an IMR at a given index.
 *
 * Requires caller to hold imr mutex.
 * Note lock bits need to be written independently of address bits.
 *
 * @idev:	poपूर्णांकer to imr_device काष्ठाure.
 * @imr_id:	IMR entry to ग_लिखो.
 * @imr:	IMR काष्ठाure representing address and access masks.
 * @वापस:	0 on success or error code passed from mbi_iosf on failure.
 */
अटल पूर्णांक imr_ग_लिखो(काष्ठा imr_device *idev, u32 imr_id, काष्ठा imr_regs *imr)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg = imr_id * IMR_NUM_REGS + idev->reg_base;
	पूर्णांक ret;

	local_irq_save(flags);

	ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->addr_lo);
	अगर (ret)
		जाओ failed;

	ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->addr_hi);
	अगर (ret)
		जाओ failed;

	ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->rmask);
	अगर (ret)
		जाओ failed;

	ret = iosf_mbi_ग_लिखो(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->wmask);
	अगर (ret)
		जाओ failed;

	local_irq_restore(flags);
	वापस 0;
failed:
	/*
	 * If writing to the IOSF failed then we're in an unknown state,
	 * likely a very bad state. An IMR in an invalid state will almost
	 * certainly lead to a memory access violation.
	 */
	local_irq_restore(flags);
	WARN(ret, "IOSF-MBI write fail range 0x%08x-0x%08x unreliable\n",
	     imr_to_phys(imr->addr_lo), imr_to_phys(imr->addr_hi) + IMR_MASK);

	वापस ret;
पूर्ण

/**
 * imr_dbgfs_state_show - prपूर्णांक state of IMR रेजिस्टरs.
 *
 * @s:		poपूर्णांकer to seq_file क्रम output.
 * @unused:	unused parameter.
 * @वापस:	0 on success or error code passed from mbi_iosf on failure.
 */
अटल पूर्णांक imr_dbgfs_state_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	phys_addr_t base;
	phys_addr_t end;
	पूर्णांक i;
	काष्ठा imr_device *idev = s->निजी;
	काष्ठा imr_regs imr;
	माप_प्रकार size;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&idev->lock);

	क्रम (i = 0; i < idev->max_imr; i++) अणु

		ret = imr_पढ़ो(idev, i, &imr);
		अगर (ret)
			अवरोध;

		/*
		 * Remember to add IMR_ALIGN bytes to size to indicate the
		 * inherent IMR_ALIGN size bytes contained in the masked away
		 * lower ten bits.
		 */
		अगर (imr_is_enabled(&imr)) अणु
			base = imr_to_phys(imr.addr_lo);
			end = imr_to_phys(imr.addr_hi) + IMR_MASK;
			size = end - base + 1;
		पूर्ण अन्यथा अणु
			base = 0;
			end = 0;
			size = 0;
		पूर्ण
		seq_म_लिखो(s, "imr%02i: base=%pa, end=%pa, size=0x%08zx "
			   "rmask=0x%08x, wmask=0x%08x, %s, %s\n", i,
			   &base, &end, size, imr.rmask, imr.wmask,
			   imr_is_enabled(&imr) ? "enabled " : "disabled",
			   imr.addr_lo & IMR_LOCK ? "locked" : "unlocked");
	पूर्ण

	mutex_unlock(&idev->lock);
	वापस ret;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(imr_dbgfs_state);

/**
 * imr_debugfs_रेजिस्टर - रेजिस्टर debugfs hooks.
 *
 * @idev:	poपूर्णांकer to imr_device काष्ठाure.
 */
अटल व्योम imr_debugfs_रेजिस्टर(काष्ठा imr_device *idev)
अणु
	debugfs_create_file("imr_state", 0444, शून्य, idev,
			    &imr_dbgfs_state_fops);
पूर्ण

/**
 * imr_check_params - check passed address range IMR alignment and non-zero size
 *
 * @base:	base address of पूर्णांकended IMR.
 * @size:	size of पूर्णांकended IMR.
 * @वापस:	zero on valid range -EINVAL on unaligned base/size.
 */
अटल पूर्णांक imr_check_params(phys_addr_t base, माप_प्रकार size)
अणु
	अगर ((base & IMR_MASK) || (size & IMR_MASK)) अणु
		pr_err("base %pa size 0x%08zx must align to 1KiB\n",
			&base, size);
		वापस -EINVAL;
	पूर्ण
	अगर (size == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * imr_raw_size - account क्रम the IMR_ALIGN bytes that addr_hi appends.
 *
 * IMR addr_hi has a built in offset of plus IMR_ALIGN (0x400) bytes from the
 * value in the रेजिस्टर. We need to subtract IMR_ALIGN bytes from input sizes
 * as a result.
 *
 * @size:	input size bytes.
 * @वापस:	reduced size.
 */
अटल अंतरभूत माप_प्रकार imr_raw_size(माप_प्रकार size)
अणु
	वापस size - IMR_ALIGN;
पूर्ण

/**
 * imr_address_overlap - detects an address overlap.
 *
 * @addr:	address to check against an existing IMR.
 * @imr:	imr being checked.
 * @वापस:	true क्रम overlap false क्रम no overlap.
 */
अटल अंतरभूत पूर्णांक imr_address_overlap(phys_addr_t addr, काष्ठा imr_regs *imr)
अणु
	वापस addr >= imr_to_phys(imr->addr_lo) && addr <= imr_to_phys(imr->addr_hi);
पूर्ण

/**
 * imr_add_range - add an Isolated Memory Region.
 *
 * @base:	physical base address of region aligned to 1KiB.
 * @size:	physical size of region in bytes must be aligned to 1KiB.
 * @पढ़ो_mask:	पढ़ो access mask.
 * @ग_लिखो_mask:	ग_लिखो access mask.
 * @वापस:	zero on success or negative value indicating error.
 */
पूर्णांक imr_add_range(phys_addr_t base, माप_प्रकार size,
		  अचिन्हित पूर्णांक rmask, अचिन्हित पूर्णांक wmask)
अणु
	phys_addr_t end;
	अचिन्हित पूर्णांक i;
	काष्ठा imr_device *idev = &imr_dev;
	काष्ठा imr_regs imr;
	माप_प्रकार raw_size;
	पूर्णांक reg;
	पूर्णांक ret;

	अगर (WARN_ONCE(idev->init == false, "driver not initialized"))
		वापस -ENODEV;

	ret = imr_check_params(base, size);
	अगर (ret)
		वापस ret;

	/* Tweak the size value. */
	raw_size = imr_raw_size(size);
	end = base + raw_size;

	/*
	 * Check क्रम reserved IMR value common to firmware, kernel and grub
	 * indicating a disabled IMR.
	 */
	imr.addr_lo = phys_to_imr(base);
	imr.addr_hi = phys_to_imr(end);
	imr.rmask = rmask;
	imr.wmask = wmask;
	अगर (!imr_is_enabled(&imr))
		वापस -ENOTSUPP;

	mutex_lock(&idev->lock);

	/*
	 * Find a मुक्त IMR जबतक checking क्रम an existing overlapping range.
	 * Note there's no restriction in silicon to prevent IMR overlaps.
	 * For the sake of simplicity and ease in defining/debugging an IMR
	 * memory map we exclude IMR overlaps.
	 */
	reg = -1;
	क्रम (i = 0; i < idev->max_imr; i++) अणु
		ret = imr_पढ़ो(idev, i, &imr);
		अगर (ret)
			जाओ failed;

		/* Find overlap @ base or end of requested range. */
		ret = -EINVAL;
		अगर (imr_is_enabled(&imr)) अणु
			अगर (imr_address_overlap(base, &imr))
				जाओ failed;
			अगर (imr_address_overlap(end, &imr))
				जाओ failed;
		पूर्ण अन्यथा अणु
			reg = i;
		पूर्ण
	पूर्ण

	/* Error out अगर we have no मुक्त IMR entries. */
	अगर (reg == -1) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	pr_debug("add %d phys %pa-%pa size %zx mask 0x%08x wmask 0x%08x\n",
		 reg, &base, &end, raw_size, rmask, wmask);

	/* Enable IMR at specअगरied range and access mask. */
	imr.addr_lo = phys_to_imr(base);
	imr.addr_hi = phys_to_imr(end);
	imr.rmask = rmask;
	imr.wmask = wmask;

	ret = imr_ग_लिखो(idev, reg, &imr);
	अगर (ret < 0) अणु
		/*
		 * In the highly unlikely event iosf_mbi_ग_लिखो failed
		 * attempt to rollback the IMR setup skipping the trapping
		 * of further IOSF ग_लिखो failures.
		 */
		imr.addr_lo = 0;
		imr.addr_hi = 0;
		imr.rmask = IMR_READ_ACCESS_ALL;
		imr.wmask = IMR_WRITE_ACCESS_ALL;
		imr_ग_लिखो(idev, reg, &imr);
	पूर्ण
failed:
	mutex_unlock(&idev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imr_add_range);

/**
 * __imr_हटाओ_range - delete an Isolated Memory Region.
 *
 * This function allows you to delete an IMR by its index specअगरied by reg or
 * by address range specअगरied by base and size respectively. If you specअगरy an
 * index on its own the base and size parameters are ignored.
 * imr_हटाओ_range(0, base, size); delete IMR at index 0 base/size ignored.
 * imr_हटाओ_range(-1, base, size); delete IMR from base to base+size.
 *
 * @reg:	imr index to हटाओ.
 * @base:	physical base address of region aligned to 1 KiB.
 * @size:	physical size of region in bytes aligned to 1 KiB.
 * @वापस:	-EINVAL on invalid range or out or range id
 *		-ENODEV अगर reg is valid but no IMR exists or is locked
 *		0 on success.
 */
अटल पूर्णांक __imr_हटाओ_range(पूर्णांक reg, phys_addr_t base, माप_प्रकार size)
अणु
	phys_addr_t end;
	bool found = false;
	अचिन्हित पूर्णांक i;
	काष्ठा imr_device *idev = &imr_dev;
	काष्ठा imr_regs imr;
	माप_प्रकार raw_size;
	पूर्णांक ret = 0;

	अगर (WARN_ONCE(idev->init == false, "driver not initialized"))
		वापस -ENODEV;

	/*
	 * Validate address range अगर deleting by address, अन्यथा we are
	 * deleting by index where base and size will be ignored.
	 */
	अगर (reg == -1) अणु
		ret = imr_check_params(base, size);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Tweak the size value. */
	raw_size = imr_raw_size(size);
	end = base + raw_size;

	mutex_lock(&idev->lock);

	अगर (reg >= 0) अणु
		/* If a specअगरic IMR is given try to use it. */
		ret = imr_पढ़ो(idev, reg, &imr);
		अगर (ret)
			जाओ failed;

		अगर (!imr_is_enabled(&imr) || imr.addr_lo & IMR_LOCK) अणु
			ret = -ENODEV;
			जाओ failed;
		पूर्ण
		found = true;
	पूर्ण अन्यथा अणु
		/* Search क्रम match based on address range. */
		क्रम (i = 0; i < idev->max_imr; i++) अणु
			ret = imr_पढ़ो(idev, i, &imr);
			अगर (ret)
				जाओ failed;

			अगर (!imr_is_enabled(&imr) || imr.addr_lo & IMR_LOCK)
				जारी;

			अगर ((imr_to_phys(imr.addr_lo) == base) &&
			    (imr_to_phys(imr.addr_hi) == end)) अणु
				found = true;
				reg = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		ret = -ENODEV;
		जाओ failed;
	पूर्ण

	pr_debug("remove %d phys %pa-%pa size %zx\n", reg, &base, &end, raw_size);

	/* Tear करोwn the IMR. */
	imr.addr_lo = 0;
	imr.addr_hi = 0;
	imr.rmask = IMR_READ_ACCESS_ALL;
	imr.wmask = IMR_WRITE_ACCESS_ALL;

	ret = imr_ग_लिखो(idev, reg, &imr);

failed:
	mutex_unlock(&idev->lock);
	वापस ret;
पूर्ण

/**
 * imr_हटाओ_range - delete an Isolated Memory Region by address
 *
 * This function allows you to delete an IMR by an address range specअगरied
 * by base and size respectively.
 * imr_हटाओ_range(base, size); delete IMR from base to base+size.
 *
 * @base:	physical base address of region aligned to 1 KiB.
 * @size:	physical size of region in bytes aligned to 1 KiB.
 * @वापस:	-EINVAL on invalid range or out or range id
 *		-ENODEV अगर reg is valid but no IMR exists or is locked
 *		0 on success.
 */
पूर्णांक imr_हटाओ_range(phys_addr_t base, माप_प्रकार size)
अणु
	वापस __imr_हटाओ_range(-1, base, size);
पूर्ण
EXPORT_SYMBOL_GPL(imr_हटाओ_range);

/**
 * imr_clear - delete an Isolated Memory Region by index
 *
 * This function allows you to delete an IMR by an address range specअगरied
 * by the index of the IMR. Useful क्रम initial sanitization of the IMR
 * address map.
 * imr_ge(base, size); delete IMR from base to base+size.
 *
 * @reg:	imr index to हटाओ.
 * @वापस:	-EINVAL on invalid range or out or range id
 *		-ENODEV अगर reg is valid but no IMR exists or is locked
 *		0 on success.
 */
अटल अंतरभूत पूर्णांक imr_clear(पूर्णांक reg)
अणु
	वापस __imr_हटाओ_range(reg, 0, 0);
पूर्ण

/**
 * imr_fixup_memmap - Tear करोwn IMRs used during bootup.
 *
 * BIOS and Grub both setup IMRs around compressed kernel, initrd memory
 * that need to be हटाओd beक्रमe the kernel hands out one of the IMR
 * enहालd addresses to a करोwnstream DMA agent such as the SD or Ethernet.
 * IMRs on Galileo are setup to immediately reset the प्रणाली on violation.
 * As a result अगर you're running a root filesystem from SD - you'll need
 * the boot-समय IMRs torn करोwn or you'll find seemingly अक्रमom resets when
 * using your fileप्रणाली.
 *
 * @idev:	poपूर्णांकer to imr_device काष्ठाure.
 * @वापस:
 */
अटल व्योम __init imr_fixup_memmap(काष्ठा imr_device *idev)
अणु
	phys_addr_t base = virt_to_phys(&_text);
	माप_प्रकार size = virt_to_phys(&__end_rodata) - base;
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;
	पूर्णांक ret;

	/* Tear करोwn all existing unlocked IMRs. */
	क्रम (i = 0; i < idev->max_imr; i++)
		imr_clear(i);

	start = (अचिन्हित दीर्घ)_text;
	end = (अचिन्हित दीर्घ)__end_rodata - 1;

	/*
	 * Setup an unlocked IMR around the physical extent of the kernel
	 * from the beginning of the .text section to the end of the
	 * .rodata section as one physically contiguous block.
	 *
	 * We करोn't round up @size since it is alपढ़ोy PAGE_SIZE aligned.
	 * See vmlinux.lds.S क्रम details.
	 */
	ret = imr_add_range(base, size, IMR_CPU, IMR_CPU);
	अगर (ret < 0) अणु
		pr_err("unable to setup IMR for kernel: %zu KiB (%lx - %lx)\n",
			size / 1024, start, end);
	पूर्ण अन्यथा अणु
		pr_info("protecting kernel .text - .rodata: %zu KiB (%lx - %lx)\n",
			size / 1024, start, end);
	पूर्ण

पूर्ण

अटल स्थिर काष्ठा x86_cpu_id imr_ids[] __initस्थिर = अणु
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 5, INTEL_FAM5_QUARK_X1000, शून्य),
	अणुपूर्ण
पूर्ण;

/**
 * imr_init - entry poपूर्णांक क्रम IMR driver.
 *
 * वापस: -ENODEV क्रम no IMR support 0 अगर good to go.
 */
अटल पूर्णांक __init imr_init(व्योम)
अणु
	काष्ठा imr_device *idev = &imr_dev;

	अगर (!x86_match_cpu(imr_ids) || !iosf_mbi_available())
		वापस -ENODEV;

	idev->max_imr = QUARK_X1000_IMR_MAX;
	idev->reg_base = QUARK_X1000_IMR_REGBASE;
	idev->init = true;

	mutex_init(&idev->lock);
	imr_debugfs_रेजिस्टर(idev);
	imr_fixup_memmap(idev);
	वापस 0;
पूर्ण
device_initcall(imr_init);
