<शैली गुरु>
/*
 *  Copyright (C) 2007-2009 Geert Uytterhoeven
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/zorro.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigayle.h>
#समावेश <यंत्र/byteorder.h>


#अगर_घोषित CONFIG_ZORRO

अटल स्थिर काष्ठा resource zorro_resources[] __initस्थिर = अणु
	/* Zorro II regions (on Zorro II/III) */
	अणु
		.name	= "Zorro II exp",
		.start	= 0x00e80000,
		.end	= 0x00efffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "Zorro II mem",
		.start	= 0x00200000,
		.end	= 0x009fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* Zorro III regions (on Zorro III only) */
	अणु
		.name	= "Zorro III exp",
		.start	= 0xff000000,
		.end	= 0xffffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "Zorro III cfg",
		.start	= 0x40000000,
		.end	= 0x7fffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;


अटल पूर्णांक __init amiga_init_bus(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक n;

	अगर (!MACH_IS_AMIGA || !AMIGAHW_PRESENT(ZORRO))
		वापस -ENODEV;

	n = AMIGAHW_PRESENT(ZORRO3) ? 4 : 2;
	pdev = platक्रमm_device_रेजिस्टर_simple("amiga-zorro", -1,
					       zorro_resources, n);
	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

subsys_initcall(amiga_init_bus);


अटल पूर्णांक __init z_dev_present(zorro_id id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < zorro_num_स्वतःcon; i++) अणु
		स्थिर काष्ठा ExpansionRom *rom = &zorro_स्वतःcon_init[i].rom;
		अगर (be16_to_cpu(rom->er_Manufacturer) == ZORRO_MANUF(id) &&
		    rom->er_Product == ZORRO_PROD(id))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_ZORRO */

अटल अंतरभूत पूर्णांक z_dev_present(zorro_id id) अणु वापस 0; पूर्ण

#पूर्ण_अगर /* !CONFIG_ZORRO */


अटल स्थिर काष्ठा resource a3000_scsi_resource __initस्थिर = अणु
	.start	= 0xdd0000,
	.end	= 0xdd00ff,
	.flags	= IORESOURCE_MEM,
पूर्ण;


अटल स्थिर काष्ठा resource a4000t_scsi_resource __initस्थिर = अणु
	.start	= 0xdd0000,
	.end	= 0xdd0fff,
	.flags	= IORESOURCE_MEM,
पूर्ण;


अटल स्थिर काष्ठा resource a1200_ide_resource __initस्थिर = अणु
	.start	= 0xda0000,
	.end	= 0xda1fff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल स्थिर काष्ठा gayle_ide_platक्रमm_data a1200_ide_pdata __initस्थिर = अणु
	.base		= 0xda0000,
	.irqport	= 0xda9000,
	.explicit_ack	= 1,
पूर्ण;


अटल स्थिर काष्ठा resource a4000_ide_resource __initस्थिर = अणु
	.start	= 0xdd2000,
	.end	= 0xdd3fff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल स्थिर काष्ठा gayle_ide_platक्रमm_data a4000_ide_pdata __initस्थिर = अणु
	.base		= 0xdd2020,
	.irqport	= 0xdd3020,
	.explicit_ack	= 0,
पूर्ण;


अटल स्थिर काष्ठा resource amiga_rtc_resource __initस्थिर = अणु
	.start	= 0x00dc0000,
	.end	= 0x00dcffff,
	.flags	= IORESOURCE_MEM,
पूर्ण;


अटल पूर्णांक __init amiga_init_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक error;

	अगर (!MACH_IS_AMIGA)
		वापस -ENODEV;

	/* video hardware */
	अगर (AMIGAHW_PRESENT(AMI_VIDEO)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-video", -1, शून्य,
						       0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण


	/* sound hardware */
	अगर (AMIGAHW_PRESENT(AMI_AUDIO)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-audio", -1, शून्य,
						       0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण


	/* storage पूर्णांकerfaces */
	अगर (AMIGAHW_PRESENT(AMI_FLOPPY)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-floppy", -1,
						       शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(A3000_SCSI)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-a3000-scsi", -1,
						       &a3000_scsi_resource, 1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(A4000_SCSI)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-a4000t-scsi", -1,
						       &a4000t_scsi_resource,
						       1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(A1200_IDE) ||
	    z_dev_present(ZORRO_PROD_MTEC_VIPER_MK_V_E_MATRIX_530_SCSI_IDE)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-gayle-ide", -1,
						       &a1200_ide_resource, 1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
		error = platक्रमm_device_add_data(pdev, &a1200_ide_pdata,
						 माप(a1200_ide_pdata));
		अगर (error)
			वापस error;
	पूर्ण

	अगर (AMIGAHW_PRESENT(A4000_IDE)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-gayle-ide", -1,
						       &a4000_ide_resource, 1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
		error = platक्रमm_device_add_data(pdev, &a4000_ide_pdata,
						 माप(a4000_ide_pdata));
		अगर (error)
			वापस error;
	पूर्ण


	/* other I/O hardware */
	अगर (AMIGAHW_PRESENT(AMI_KEYBOARD)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-keyboard", -1,
						       शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(AMI_MOUSE)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-mouse", -1, शून्य,
						       0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(AMI_SERIAL)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-serial", -1,
						       शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(AMI_PARALLEL)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("amiga-parallel", -1,
						       शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण


	/* real समय घड़ीs */
	अगर (AMIGAHW_PRESENT(A2000_CLK)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("rtc-msm6242", -1,
						       &amiga_rtc_resource, 1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	अगर (AMIGAHW_PRESENT(A3000_CLK)) अणु
		pdev = platक्रमm_device_रेजिस्टर_simple("rtc-rp5c01", -1,
						       &amiga_rtc_resource, 1);
		अगर (IS_ERR(pdev))
			वापस PTR_ERR(pdev);
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(amiga_init_devices);
