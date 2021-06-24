<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// originally in linux/arch/arm/plat-s3c24xx/pm.c
//
// Copyright (c) 2004-2008 Simtec Electronics
//	http://armlinux.simtec.co.uk
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C Power Mangament - suspend/resume memory corruption check.

#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>

#समावेश <linux/soc/samsung/s3c-pm.h>

#अगर CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE < 1
#त्रुटि CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE must be a positive non-zero value
#पूर्ण_अगर

/* suspend checking code...
 *
 * this next area करोes a set of crc checks over all the installed
 * memory, so the प्रणाली can verअगरy अगर the resume was ok.
 *
 * CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE defines the block-size क्रम the CRC,
 * increasing it will mean that the area corrupted will be less easy to spot,
 * and reducing the size will cause the CRC save area to grow
*/

#घोषणा CHECK_CHUNKSIZE (CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE * 1024)

अटल u32 crc_size;	/* size needed क्रम the crc block */
अटल u32 *crcs;	/* allocated over suspend/resume */

प्रकार u32 *(run_fn_t)(काष्ठा resource *ptr, u32 *arg);

/* s3c_pm_run_res
 *
 * go through the given resource list, and look क्रम प्रणाली ram
*/

अटल व्योम s3c_pm_run_res(काष्ठा resource *ptr, run_fn_t fn, u32 *arg)
अणु
	जबतक (ptr != शून्य) अणु
		अगर (ptr->child != शून्य)
			s3c_pm_run_res(ptr->child, fn, arg);

		अगर ((ptr->flags & IORESOURCE_SYSTEM_RAM)
				== IORESOURCE_SYSTEM_RAM) अणु
			S3C_PMDBG("Found system RAM at %08lx..%08lx\n",
				  (अचिन्हित दीर्घ)ptr->start,
				  (अचिन्हित दीर्घ)ptr->end);
			arg = (fn)(ptr, arg);
		पूर्ण

		ptr = ptr->sibling;
	पूर्ण
पूर्ण

अटल व्योम s3c_pm_run_sysram(run_fn_t fn, u32 *arg)
अणु
	s3c_pm_run_res(&iomem_resource, fn, arg);
पूर्ण

अटल u32 *s3c_pm_countram(काष्ठा resource *res, u32 *val)
अणु
	u32 size = (u32)resource_size(res);

	size += CHECK_CHUNKSIZE-1;
	size /= CHECK_CHUNKSIZE;

	S3C_PMDBG("Area %08lx..%08lx, %d blocks\n",
		  (अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end, size);

	*val += size * माप(u32);
	वापस val;
पूर्ण

/* s3c_pm_prepare_check
 *
 * prepare the necessary inक्रमmation क्रम creating the CRCs. This
 * must be करोne beक्रमe the final save, as it will require memory
 * allocating, and thus touching bits of the kernel we करो not
 * know about.
*/

व्योम s3c_pm_check_prepare(व्योम)
अणु
	crc_size = 0;

	s3c_pm_run_sysram(s3c_pm_countram, &crc_size);

	S3C_PMDBG("s3c_pm_prepare_check: %u checks needed\n", crc_size);

	crcs = kदो_स्मृति(crc_size+4, GFP_KERNEL);
	अगर (crcs == शून्य)
		prपूर्णांकk(KERN_ERR "Cannot allocated CRC save area\n");
पूर्ण

अटल u32 *s3c_pm_makecheck(काष्ठा resource *res, u32 *val)
अणु
	अचिन्हित दीर्घ addr, left;

	क्रम (addr = res->start; addr < res->end;
	     addr += CHECK_CHUNKSIZE) अणु
		left = res->end - addr;

		अगर (left > CHECK_CHUNKSIZE)
			left = CHECK_CHUNKSIZE;

		*val = crc32_le(~0, phys_to_virt(addr), left);
		val++;
	पूर्ण

	वापस val;
पूर्ण

/* s3c_pm_check_store
 *
 * compute the CRC values क्रम the memory blocks beक्रमe the final
 * sleep.
*/

व्योम s3c_pm_check_store(व्योम)
अणु
	अगर (crcs != शून्य)
		s3c_pm_run_sysram(s3c_pm_makecheck, crcs);
पूर्ण

/* in_region
 *
 * वापस TRUE अगर the area defined by ptr..ptr+size contains the
 * what..what+whatsz
*/

अटल अंतरभूत पूर्णांक in_region(व्योम *ptr, पूर्णांक size, व्योम *what, माप_प्रकार whatsz)
अणु
	अगर ((what+whatsz) < ptr)
		वापस 0;

	अगर (what > (ptr+size))
		वापस 0;

	वापस 1;
पूर्ण

/**
 * s3c_pm_runcheck() - helper to check a resource on restore.
 * @res: The resource to check
 * @val: Poपूर्णांकer to list of CRC32 values to check.
 *
 * Called from the s3c_pm_check_restore() via s3c_pm_run_sysram(), this
 * function runs the given memory resource checking it against the stored
 * CRC to ensure that memory is restored. The function tries to skip as
 * many of the areas used during the suspend process.
 */
अटल u32 *s3c_pm_runcheck(काष्ठा resource *res, u32 *val)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ left;
	व्योम *stkpage;
	व्योम *ptr;
	u32 calc;

	stkpage = (व्योम *)((u32)&calc & ~PAGE_MASK);

	क्रम (addr = res->start; addr < res->end;
	     addr += CHECK_CHUNKSIZE) अणु
		left = res->end - addr;

		अगर (left > CHECK_CHUNKSIZE)
			left = CHECK_CHUNKSIZE;

		ptr = phys_to_virt(addr);

		अगर (in_region(ptr, left, stkpage, 4096)) अणु
			S3C_PMDBG("skipping %08lx, has stack in\n", addr);
			जाओ skip_check;
		पूर्ण

		अगर (in_region(ptr, left, crcs, crc_size)) अणु
			S3C_PMDBG("skipping %08lx, has crc block in\n", addr);
			जाओ skip_check;
		पूर्ण

		/* calculate and check the checksum */

		calc = crc32_le(~0, ptr, left);
		अगर (calc != *val) अणु
			prपूर्णांकk(KERN_ERR "Restore CRC error at "
			       "%08lx (%08x vs %08x)\n", addr, calc, *val);

			S3C_PMDBG("Restore CRC error at %08lx (%08x vs %08x)\n",
			    addr, calc, *val);
		पूर्ण

	skip_check:
		val++;
	पूर्ण

	वापस val;
पूर्ण

/**
 * s3c_pm_check_restore() - memory check called on resume
 *
 * check the CRCs after the restore event and मुक्त the memory used
 * to hold them
*/
व्योम s3c_pm_check_restore(व्योम)
अणु
	अगर (crcs != शून्य)
		s3c_pm_run_sysram(s3c_pm_runcheck, crcs);
पूर्ण

/**
 * s3c_pm_check_cleanup() - मुक्त memory resources
 *
 * Free the resources that where allocated by the suspend
 * memory check code. We करो this separately from the
 * s3c_pm_check_restore() function as we cannot call any
 * functions that might sleep during that resume.
 */
व्योम s3c_pm_check_cleanup(व्योम)
अणु
	kमुक्त(crcs);
	crcs = शून्य;
पूर्ण

