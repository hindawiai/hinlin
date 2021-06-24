<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************/

/*
 *      nettel.c -- mappings क्रम NETtel/SecureEdge/SnapGear (x86) boards.
 *
 *      (C) Copyright 2000-2001, Greg Ungerer (gerg@snapgear.com)
 *      (C) Copyright 2001-2002, SnapGear (www.snapgear.com)
 */

/****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/reboot.h>
#समावेश <linux/err.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/root_dev.h>
#समावेश <यंत्र/पन.स>

/****************************************************************************/

#घोषणा INTEL_BUSWIDTH		1
#घोषणा AMD_WINDOW_MAXSIZE	0x00200000
#घोषणा AMD_BUSWIDTH	 	1

/*
 *	PAR masks and shअगरts, assuming 64K pages.
 */
#घोषणा SC520_PAR_ADDR_MASK	0x00003fff
#घोषणा SC520_PAR_ADDR_SHIFT	16
#घोषणा SC520_PAR_TO_ADDR(par) \
	(((par)&SC520_PAR_ADDR_MASK) << SC520_PAR_ADDR_SHIFT)

#घोषणा SC520_PAR_SIZE_MASK	0x01ffc000
#घोषणा SC520_PAR_SIZE_SHIFT	2
#घोषणा SC520_PAR_TO_SIZE(par) \
	((((par)&SC520_PAR_SIZE_MASK) << SC520_PAR_SIZE_SHIFT) + (64*1024))

#घोषणा SC520_PAR(cs, addr, size) \
	((cs) | \
	((((size)-(64*1024)) >> SC520_PAR_SIZE_SHIFT) & SC520_PAR_SIZE_MASK) | \
	(((addr) >> SC520_PAR_ADDR_SHIFT) & SC520_PAR_ADDR_MASK))

#घोषणा SC520_PAR_BOOTCS	0x8a000000
#घोषणा	SC520_PAR_ROMCS1	0xaa000000
#घोषणा SC520_PAR_ROMCS2	0xca000000	/* Cache disabled, 64K page */

अटल व्योम *nettel_mmcrp = शून्य;

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
अटल काष्ठा mtd_info *पूर्णांकel_mtd;
#पूर्ण_अगर
अटल काष्ठा mtd_info *amd_mtd;

/****************************************************************************/

/****************************************************************************/

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
अटल काष्ठा map_info nettel_पूर्णांकel_map = अणु
	.name = "SnapGear Intel",
	.size = 0,
	.bankwidth = INTEL_BUSWIDTH,
पूर्ण;

अटल काष्ठा mtd_partition nettel_पूर्णांकel_partitions[] = अणु
	अणु
		.name = "SnapGear kernel",
		.offset = 0,
		.size = 0x000e0000
	पूर्ण,
	अणु
		.name = "SnapGear filesystem",
		.offset = 0x00100000,
	पूर्ण,
	अणु
		.name = "SnapGear config",
		.offset = 0x000e0000,
		.size = 0x00020000
	पूर्ण,
	अणु
		.name = "SnapGear Intel",
		.offset = 0
	पूर्ण,
	अणु
		.name = "SnapGear BIOS Config",
		.offset = 0x007e0000,
		.size = 0x00020000
	पूर्ण,
	अणु
		.name = "SnapGear BIOS",
		.offset = 0x007e0000,
		.size = 0x00020000
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा map_info nettel_amd_map = अणु
	.name = "SnapGear AMD",
	.size = AMD_WINDOW_MAXSIZE,
	.bankwidth = AMD_BUSWIDTH,
पूर्ण;

अटल स्थिर काष्ठा mtd_partition nettel_amd_partitions[] = अणु
	अणु
		.name = "SnapGear BIOS config",
		.offset = 0x000e0000,
		.size = 0x00010000
	पूर्ण,
	अणु
		.name = "SnapGear BIOS",
		.offset = 0x000f0000,
		.size = 0x00010000
	पूर्ण,
	अणु
		.name = "SnapGear AMD",
		.offset = 0
	पूर्ण,
	अणु
		.name = "SnapGear high BIOS",
		.offset = 0x001f0000,
		.size = 0x00010000
	पूर्ण
पूर्ण;

#घोषणा NUM_AMD_PARTITIONS ARRAY_SIZE(nettel_amd_partitions)

/****************************************************************************/

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT

/*
 *	Set the Intel flash back to पढ़ो mode since some old boot
 *	loaders करोn't.
 */
अटल पूर्णांक nettel_reboot_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *v)
अणु
	काष्ठा cfi_निजी *cfi = nettel_पूर्णांकel_map.fldrv_priv;
	अचिन्हित दीर्घ b;

	/* Make sure all FLASH chips are put back पूर्णांकo पढ़ो mode */
	क्रम (b = 0; (b < nettel_पूर्णांकel_partitions[3].size); b += 0x100000) अणु
		cfi_send_gen_cmd(0xff, 0x55, b, &nettel_पूर्णांकel_map, cfi,
			cfi->device_type, शून्य);
	पूर्ण
	वापस(NOTIFY_OK);
पूर्ण

अटल काष्ठा notअगरier_block nettel_notअगरier_block = अणु
	nettel_reboot_notअगरier, शून्य, 0
पूर्ण;

#पूर्ण_अगर

/****************************************************************************/

अटल पूर्णांक __init nettel_init(व्योम)
अणु
	अस्थिर अचिन्हित दीर्घ *amdpar;
	अचिन्हित दीर्घ amdaddr, maxsize;
	पूर्णांक num_amd_partitions=0;
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	अस्थिर अचिन्हित दीर्घ *पूर्णांकel0par, *पूर्णांकel1par;
	अचिन्हित दीर्घ orig_bootcspar, orig_romcs1par;
	अचिन्हित दीर्घ पूर्णांकel0addr, पूर्णांकel0size;
	अचिन्हित दीर्घ पूर्णांकel1addr, पूर्णांकel1size;
	पूर्णांक पूर्णांकelboot, पूर्णांकel0cs, पूर्णांकel1cs;
	पूर्णांक num_पूर्णांकel_partitions;
#पूर्ण_अगर
	पूर्णांक rc = 0;

	nettel_mmcrp = (व्योम *) ioremap(0xfffef000, 4096);
	अगर (nettel_mmcrp == शून्य) अणु
		prपूर्णांकk("SNAPGEAR: failed to disable MMCR cache??\n");
		वापस(-EIO);
	पूर्ण

	/* Set CPU घड़ी to be 33.000MHz */
	*((अचिन्हित अक्षर *) (nettel_mmcrp + 0xc64)) = 0x01;

	amdpar = (अस्थिर अचिन्हित दीर्घ *) (nettel_mmcrp + 0xc4);

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	पूर्णांकelboot = 0;
	पूर्णांकel0cs = SC520_PAR_ROMCS1;
	पूर्णांकel0par = (अस्थिर अचिन्हित दीर्घ *) (nettel_mmcrp + 0xc0);
	पूर्णांकel1cs = SC520_PAR_ROMCS2;
	पूर्णांकel1par = (अस्थिर अचिन्हित दीर्घ *) (nettel_mmcrp + 0xbc);

	/*
	 *	Save the CS settings then ensure ROMCS1 and ROMCS2 are off,
	 *	otherwise they might clash with where we try to map BOOTCS.
	 */
	orig_bootcspar = *amdpar;
	orig_romcs1par = *पूर्णांकel0par;
	*पूर्णांकel0par = 0;
	*पूर्णांकel1par = 0;
#पूर्ण_अगर

	/*
	 *	The first thing to करो is determine अगर we have a separate
	 *	boot FLASH device. Typically this is a small (1 to 2MB)
	 *	AMD FLASH part. It seems that device size is about the
	 *	only way to tell अगर this is the हाल...
	 */
	amdaddr = 0x20000000;
	maxsize = AMD_WINDOW_MAXSIZE;

	*amdpar = SC520_PAR(SC520_PAR_BOOTCS, amdaddr, maxsize);
	__यंत्र__ ("wbinvd");

	nettel_amd_map.phys = amdaddr;
	nettel_amd_map.virt = ioremap(amdaddr, maxsize);
	अगर (!nettel_amd_map.virt) अणु
		prपूर्णांकk("SNAPGEAR: failed to ioremap() BOOTCS\n");
		iounmap(nettel_mmcrp);
		वापस(-EIO);
	पूर्ण
	simple_map_init(&nettel_amd_map);

	अगर ((amd_mtd = करो_map_probe("jedec_probe", &nettel_amd_map))) अणु
		prपूर्णांकk(KERN_NOTICE "SNAPGEAR: AMD flash device size = %dK\n",
			(पूर्णांक)(amd_mtd->size>>10));

		amd_mtd->owner = THIS_MODULE;

		/* The high BIOS partition is only present क्रम 2MB units */
		num_amd_partitions = NUM_AMD_PARTITIONS;
		अगर (amd_mtd->size < AMD_WINDOW_MAXSIZE)
			num_amd_partitions--;
		/* Don't add the partition until after the primary INTEL's */

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
		/*
		 *	Map the Intel flash पूर्णांकo memory after the AMD
		 *	It has to start on a multiple of maxsize.
		 */
		maxsize = SC520_PAR_TO_SIZE(orig_romcs1par);
		अगर (maxsize < (32 * 1024 * 1024))
			maxsize = (32 * 1024 * 1024);
		पूर्णांकel0addr = amdaddr + maxsize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
		/* INTEL boot FLASH */
		पूर्णांकelboot++;

		अगर (!orig_romcs1par) अणु
			पूर्णांकel0cs = SC520_PAR_BOOTCS;
			पूर्णांकel0par = (अस्थिर अचिन्हित दीर्घ *)
				(nettel_mmcrp + 0xc4);
			पूर्णांकel1cs = SC520_PAR_ROMCS1;
			पूर्णांकel1par = (अस्थिर अचिन्हित दीर्घ *)
				(nettel_mmcrp + 0xc0);

			पूर्णांकel0addr = SC520_PAR_TO_ADDR(orig_bootcspar);
			maxsize = SC520_PAR_TO_SIZE(orig_bootcspar);
		पूर्ण अन्यथा अणु
			/* Kernel base is on ROMCS1, not BOOTCS */
			पूर्णांकel0cs = SC520_PAR_ROMCS1;
			पूर्णांकel0par = (अस्थिर अचिन्हित दीर्घ *)
				(nettel_mmcrp + 0xc0);
			पूर्णांकel1cs = SC520_PAR_BOOTCS;
			पूर्णांकel1par = (अस्थिर अचिन्हित दीर्घ *)
				(nettel_mmcrp + 0xc4);

			पूर्णांकel0addr = SC520_PAR_TO_ADDR(orig_romcs1par);
			maxsize = SC520_PAR_TO_SIZE(orig_romcs1par);
		पूर्ण

		/* Destroy useless AMD MTD mapping */
		amd_mtd = शून्य;
		iounmap(nettel_amd_map.virt);
		nettel_amd_map.virt = शून्य;
#अन्यथा
		/* Only AMD flash supported */
		rc = -ENXIO;
		जाओ out_unmap2;
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	/*
	 *	We have determined the INTEL FLASH configuration, so lets
	 *	go ahead and probe क्रम them now.
	 */

	/* Set PAR to the maximum size */
	अगर (maxsize < (32 * 1024 * 1024))
		maxsize = (32 * 1024 * 1024);
	*पूर्णांकel0par = SC520_PAR(पूर्णांकel0cs, पूर्णांकel0addr, maxsize);

	/* Turn other PAR off so the first probe करोesn't find it */
	*पूर्णांकel1par = 0;

	/* Probe क्रम the size of the first Intel flash */
	nettel_पूर्णांकel_map.size = maxsize;
	nettel_पूर्णांकel_map.phys = पूर्णांकel0addr;
	nettel_पूर्णांकel_map.virt = ioremap(पूर्णांकel0addr, maxsize);
	अगर (!nettel_पूर्णांकel_map.virt) अणु
		prपूर्णांकk("SNAPGEAR: failed to ioremap() ROMCS1\n");
		rc = -EIO;
		जाओ out_unmap2;
	पूर्ण
	simple_map_init(&nettel_पूर्णांकel_map);

	पूर्णांकel_mtd = करो_map_probe("cfi_probe", &nettel_पूर्णांकel_map);
	अगर (!पूर्णांकel_mtd) अणु
		rc = -ENXIO;
		जाओ out_unmap1;
	पूर्ण

	/* Set PAR to the detected size */
	पूर्णांकel0size = पूर्णांकel_mtd->size;
	*पूर्णांकel0par = SC520_PAR(पूर्णांकel0cs, पूर्णांकel0addr, पूर्णांकel0size);

	/*
	 *	Map second Intel FLASH right after first. Set its size to the
	 *	same maxsize used क्रम the first Intel FLASH.
	 */
	पूर्णांकel1addr = पूर्णांकel0addr + पूर्णांकel0size;
	*पूर्णांकel1par = SC520_PAR(पूर्णांकel1cs, पूर्णांकel1addr, maxsize);
	__यंत्र__ ("wbinvd");

	maxsize += पूर्णांकel0size;

	/* Delete the old map and probe again to करो both chips */
	map_destroy(पूर्णांकel_mtd);
	पूर्णांकel_mtd = शून्य;
	iounmap(nettel_पूर्णांकel_map.virt);

	nettel_पूर्णांकel_map.size = maxsize;
	nettel_पूर्णांकel_map.virt = ioremap(पूर्णांकel0addr, maxsize);
	अगर (!nettel_पूर्णांकel_map.virt) अणु
		prपूर्णांकk("SNAPGEAR: failed to ioremap() ROMCS1/2\n");
		rc = -EIO;
		जाओ out_unmap2;
	पूर्ण

	पूर्णांकel_mtd = करो_map_probe("cfi_probe", &nettel_पूर्णांकel_map);
	अगर (! पूर्णांकel_mtd) अणु
		rc = -ENXIO;
		जाओ out_unmap1;
	पूर्ण

	पूर्णांकel1size = पूर्णांकel_mtd->size - पूर्णांकel0size;
	अगर (पूर्णांकel1size > 0) अणु
		*पूर्णांकel1par = SC520_PAR(पूर्णांकel1cs, पूर्णांकel1addr, पूर्णांकel1size);
		__यंत्र__ ("wbinvd");
	पूर्ण अन्यथा अणु
		*पूर्णांकel1par = 0;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "SNAPGEAR: Intel flash device size = %lldKiB\n",
	       (अचिन्हित दीर्घ दीर्घ)(पूर्णांकel_mtd->size >> 10));

	पूर्णांकel_mtd->owner = THIS_MODULE;

	num_पूर्णांकel_partitions = ARRAY_SIZE(nettel_पूर्णांकel_partitions);

	अगर (पूर्णांकelboot) अणु
		/*
		 *	Adjust offset and size of last boot partition.
		 *	Must allow क्रम BIOS region at end of FLASH.
		 */
		nettel_पूर्णांकel_partitions[1].size = (पूर्णांकel0size + पूर्णांकel1size) -
			(1024*1024 + पूर्णांकel_mtd->erasesize);
		nettel_पूर्णांकel_partitions[3].size = पूर्णांकel0size + पूर्णांकel1size;
		nettel_पूर्णांकel_partitions[4].offset =
			(पूर्णांकel0size + पूर्णांकel1size) - पूर्णांकel_mtd->erasesize;
		nettel_पूर्णांकel_partitions[4].size = पूर्णांकel_mtd->erasesize;
		nettel_पूर्णांकel_partitions[5].offset =
			nettel_पूर्णांकel_partitions[4].offset;
		nettel_पूर्णांकel_partitions[5].size =
			nettel_पूर्णांकel_partitions[4].size;
	पूर्ण अन्यथा अणु
		/* No BIOS regions when AMD boot */
		num_पूर्णांकel_partitions -= 2;
	पूर्ण
	rc = mtd_device_रेजिस्टर(पूर्णांकel_mtd, nettel_पूर्णांकel_partitions,
				 num_पूर्णांकel_partitions);
	अगर (rc)
		जाओ out_map_destroy;
#पूर्ण_अगर

	अगर (amd_mtd) अणु
		rc = mtd_device_रेजिस्टर(amd_mtd, nettel_amd_partitions,
					 num_amd_partitions);
		अगर (rc)
			जाओ out_mtd_unreg;
	पूर्ण

#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	रेजिस्टर_reboot_notअगरier(&nettel_notअगरier_block);
#पूर्ण_अगर

	वापस rc;

out_mtd_unreg:
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	mtd_device_unरेजिस्टर(पूर्णांकel_mtd);
out_map_destroy:
	map_destroy(पूर्णांकel_mtd);
out_unmap1:
	iounmap(nettel_पूर्णांकel_map.virt);
#पूर्ण_अगर

out_unmap2:
	iounmap(nettel_mmcrp);
	iounmap(nettel_amd_map.virt);

	वापस rc;
पूर्ण

/****************************************************************************/

अटल व्योम __निकास nettel_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	unरेजिस्टर_reboot_notअगरier(&nettel_notअगरier_block);
#पूर्ण_अगर
	अगर (amd_mtd) अणु
		mtd_device_unरेजिस्टर(amd_mtd);
		map_destroy(amd_mtd);
	पूर्ण
	अगर (nettel_mmcrp) अणु
		iounmap(nettel_mmcrp);
		nettel_mmcrp = शून्य;
	पूर्ण
	अगर (nettel_amd_map.virt) अणु
		iounmap(nettel_amd_map.virt);
		nettel_amd_map.virt = शून्य;
	पूर्ण
#अगर_घोषित CONFIG_MTD_CFI_INTELEXT
	अगर (पूर्णांकel_mtd) अणु
		mtd_device_unरेजिस्टर(पूर्णांकel_mtd);
		map_destroy(पूर्णांकel_mtd);
	पूर्ण
	अगर (nettel_पूर्णांकel_map.virt) अणु
		iounmap(nettel_पूर्णांकel_map.virt);
		nettel_पूर्णांकel_map.virt = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/****************************************************************************/

module_init(nettel_init);
module_निकास(nettel_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Ungerer <gerg@snapgear.com>");
MODULE_DESCRIPTION("SnapGear/SecureEdge FLASH support");

/****************************************************************************/
