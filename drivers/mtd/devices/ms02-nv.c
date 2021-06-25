<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Copyright (c) 2001 Maciej W. Rozycki
 */

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/kn02.h>
#समावेश <यंत्र/dec/kn03.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/paccess.h>

#समावेश "ms02-nv.h"


अटल अक्षर version[] __initdata =
	"ms02-nv.c: v.1.0.0  13 Aug 2001  Maciej W. Rozycki.\n";

MODULE_AUTHOR("Maciej W. Rozycki <macro@linux-mips.org>");
MODULE_DESCRIPTION("DEC MS02-NV NVRAM module driver");
MODULE_LICENSE("GPL");


/*
 * Addresses we probe क्रम an MS02-NV at.  Modules may be located
 * at any 8MiB boundary within a 0MiB up to 112MiB range or at any 32MiB
 * boundary within a 0MiB up to 448MiB range.  We करोn't support a module
 * at 0MiB, though.
 */
अटल uदीर्घ ms02nv_addrs[] __initdata = अणु
	0x07000000, 0x06800000, 0x06000000, 0x05800000, 0x05000000,
	0x04800000, 0x04000000, 0x03800000, 0x03000000, 0x02800000,
	0x02000000, 0x01800000, 0x01000000, 0x00800000
पूर्ण;

अटल स्थिर अक्षर ms02nv_name[] = "DEC MS02-NV NVRAM";
अटल स्थिर अक्षर ms02nv_res_diag_ram[] = "Diagnostic RAM";
अटल स्थिर अक्षर ms02nv_res_user_ram[] = "General-purpose RAM";
अटल स्थिर अक्षर ms02nv_res_csr[] = "Control and status register";

अटल काष्ठा mtd_info *root_ms02nv_mtd;


अटल पूर्णांक ms02nv_पढ़ो(काष्ठा mtd_info *mtd, loff_t from,
			माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा ms02nv_निजी *mp = mtd->priv;

	स_नकल(buf, mp->uaddr + from, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक ms02nv_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to,
			माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा ms02nv_निजी *mp = mtd->priv;

	स_नकल(mp->uaddr + to, buf, len);
	*retlen = len;
	वापस 0;
पूर्ण


अटल अंतरभूत uपूर्णांक ms02nv_probe_one(uदीर्घ addr)
अणु
	ms02nv_uपूर्णांक *ms02nv_diagp;
	ms02nv_uपूर्णांक *ms02nv_magicp;
	uपूर्णांक ms02nv_diag;
	uपूर्णांक ms02nv_magic;
	माप_प्रकार size;

	पूर्णांक err;

	/*
	 * The firmware ग_लिखोs MS02NV_ID at MS02NV_MAGIC and also
	 * a diagnostic status at MS02NV_DIAG.
	 */
	ms02nv_diagp = (ms02nv_uपूर्णांक *)(CKSEG1ADDR(addr + MS02NV_DIAG));
	ms02nv_magicp = (ms02nv_uपूर्णांक *)(CKSEG1ADDR(addr + MS02NV_MAGIC));
	err = get_dbe(ms02nv_magic, ms02nv_magicp);
	अगर (err)
		वापस 0;
	अगर (ms02nv_magic != MS02NV_ID)
		वापस 0;

	ms02nv_diag = *ms02nv_diagp;
	size = (ms02nv_diag & MS02NV_DIAG_SIZE_MASK) << MS02NV_DIAG_SIZE_SHIFT;
	अगर (size > MS02NV_CSR)
		size = MS02NV_CSR;

	वापस size;
पूर्ण

अटल पूर्णांक __init ms02nv_init_one(uदीर्घ addr)
अणु
	काष्ठा mtd_info *mtd;
	काष्ठा ms02nv_निजी *mp;
	काष्ठा resource *mod_res;
	काष्ठा resource *diag_res;
	काष्ठा resource *user_res;
	काष्ठा resource *csr_res;
	uदीर्घ fixaddr;
	माप_प्रकार size, fixsize;

	अटल पूर्णांक version_prपूर्णांकed;

	पूर्णांक ret = -ENODEV;

	/* The module decodes 8MiB of address space. */
	mod_res = kzalloc(माप(*mod_res), GFP_KERNEL);
	अगर (!mod_res)
		वापस -ENOMEM;

	mod_res->name = ms02nv_name;
	mod_res->start = addr;
	mod_res->end = addr + MS02NV_SLOT_SIZE - 1;
	mod_res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	अगर (request_resource(&iomem_resource, mod_res) < 0)
		जाओ err_out_mod_res;

	size = ms02nv_probe_one(addr);
	अगर (!size)
		जाओ err_out_mod_res_rel;

	अगर (!version_prपूर्णांकed) अणु
		prपूर्णांकk(KERN_INFO "%s", version);
		version_prपूर्णांकed = 1;
	पूर्ण

	ret = -ENOMEM;
	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd)
		जाओ err_out_mod_res_rel;
	mp = kzalloc(माप(*mp), GFP_KERNEL);
	अगर (!mp)
		जाओ err_out_mtd;

	mtd->priv = mp;
	mp->resource.module = mod_res;

	/* Firmware's diagnostic NVRAM area. */
	diag_res = kzalloc(माप(*diag_res), GFP_KERNEL);
	अगर (!diag_res)
		जाओ err_out_mp;

	diag_res->name = ms02nv_res_diag_ram;
	diag_res->start = addr;
	diag_res->end = addr + MS02NV_RAM - 1;
	diag_res->flags = IORESOURCE_BUSY;
	request_resource(mod_res, diag_res);

	mp->resource.diag_ram = diag_res;

	/* User-available general-purpose NVRAM area. */
	user_res = kzalloc(माप(*user_res), GFP_KERNEL);
	अगर (!user_res)
		जाओ err_out_diag_res;

	user_res->name = ms02nv_res_user_ram;
	user_res->start = addr + MS02NV_RAM;
	user_res->end = addr + size - 1;
	user_res->flags = IORESOURCE_BUSY;
	request_resource(mod_res, user_res);

	mp->resource.user_ram = user_res;

	/* Control and status रेजिस्टर. */
	csr_res = kzalloc(माप(*csr_res), GFP_KERNEL);
	अगर (!csr_res)
		जाओ err_out_user_res;

	csr_res->name = ms02nv_res_csr;
	csr_res->start = addr + MS02NV_CSR;
	csr_res->end = addr + MS02NV_CSR + 3;
	csr_res->flags = IORESOURCE_BUSY;
	request_resource(mod_res, csr_res);

	mp->resource.csr = csr_res;

	mp->addr = phys_to_virt(addr);
	mp->size = size;

	/*
	 * Hide the firmware's diagnostic area.  It may get destroyed
	 * upon a reboot.  Take paging पूर्णांकo account क्रम mapping support.
	 */
	fixaddr = (addr + MS02NV_RAM + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	fixsize = (size - (fixaddr - addr)) & ~(PAGE_SIZE - 1);
	mp->uaddr = phys_to_virt(fixaddr);

	mtd->type = MTD_RAM;
	mtd->flags = MTD_CAP_RAM;
	mtd->size = fixsize;
	mtd->name = ms02nv_name;
	mtd->owner = THIS_MODULE;
	mtd->_पढ़ो = ms02nv_पढ़ो;
	mtd->_ग_लिखो = ms02nv_ग_लिखो;
	mtd->ग_लिखोsize = 1;

	ret = -EIO;
	अगर (mtd_device_रेजिस्टर(mtd, शून्य, 0)) अणु
		prपूर्णांकk(KERN_ERR
			"ms02-nv: Unable to register MTD device, aborting!\n");
		जाओ err_out_csr_res;
	पूर्ण

	prपूर्णांकk(KERN_INFO "mtd%d: %s at 0x%08lx, size %zuMiB.\n",
		mtd->index, ms02nv_name, addr, size >> 20);

	mp->next = root_ms02nv_mtd;
	root_ms02nv_mtd = mtd;

	वापस 0;


err_out_csr_res:
	release_resource(csr_res);
	kमुक्त(csr_res);
err_out_user_res:
	release_resource(user_res);
	kमुक्त(user_res);
err_out_diag_res:
	release_resource(diag_res);
	kमुक्त(diag_res);
err_out_mp:
	kमुक्त(mp);
err_out_mtd:
	kमुक्त(mtd);
err_out_mod_res_rel:
	release_resource(mod_res);
err_out_mod_res:
	kमुक्त(mod_res);
	वापस ret;
पूर्ण

अटल व्योम __निकास ms02nv_हटाओ_one(व्योम)
अणु
	काष्ठा mtd_info *mtd = root_ms02nv_mtd;
	काष्ठा ms02nv_निजी *mp = mtd->priv;

	root_ms02nv_mtd = mp->next;

	mtd_device_unरेजिस्टर(mtd);

	release_resource(mp->resource.csr);
	kमुक्त(mp->resource.csr);
	release_resource(mp->resource.user_ram);
	kमुक्त(mp->resource.user_ram);
	release_resource(mp->resource.diag_ram);
	kमुक्त(mp->resource.diag_ram);
	release_resource(mp->resource.module);
	kमुक्त(mp->resource.module);
	kमुक्त(mp);
	kमुक्त(mtd);
पूर्ण


अटल पूर्णांक __init ms02nv_init(व्योम)
अणु
	अस्थिर u32 *csr;
	uपूर्णांक stride = 0;
	पूर्णांक count = 0;
	पूर्णांक i;

	चयन (mips_machtype) अणु
	हाल MACH_DS5000_200:
		csr = (अस्थिर u32 *)CKSEG1ADDR(KN02_SLOT_BASE + KN02_CSR);
		अगर (*csr & KN02_CSR_BNK32M)
			stride = 2;
		अवरोध;
	हाल MACH_DS5000_2X0:
	हाल MACH_DS5900:
		csr = (अस्थिर u32 *)CKSEG1ADDR(KN03_SLOT_BASE + IOASIC_MCR);
		अगर (*csr & KN03_MCR_BNK32M)
			stride = 2;
		अवरोध;
	शेष:
		वापस -ENODEV;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ms02nv_addrs); i++)
		अगर (!ms02nv_init_one(ms02nv_addrs[i] << stride))
			count++;

	वापस (count > 0) ? 0 : -ENODEV;
पूर्ण

अटल व्योम __निकास ms02nv_cleanup(व्योम)
अणु
	जबतक (root_ms02nv_mtd)
		ms02nv_हटाओ_one();
पूर्ण


module_init(ms02nv_init);
module_निकास(ms02nv_cleanup);
