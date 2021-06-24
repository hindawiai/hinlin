<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_X86IA64IO_H
#घोषणा _I8042_X86IA64IO_H


#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/x86_init.h>
#पूर्ण_अगर

/*
 * Names.
 */

#घोषणा I8042_KBD_PHYS_DESC "isa0060/serio0"
#घोषणा I8042_AUX_PHYS_DESC "isa0060/serio1"
#घोषणा I8042_MUX_PHYS_DESC "isa0060/serio%d"

/*
 * IRQs.
 */

#अगर defined(__ia64__)
# define I8042_MAP_IRQ(x)	isa_irq_to_vector((x))
#अन्यथा
# define I8042_MAP_IRQ(x)	(x)
#पूर्ण_अगर

#घोषणा I8042_KBD_IRQ	i8042_kbd_irq
#घोषणा I8042_AUX_IRQ	i8042_aux_irq

अटल पूर्णांक i8042_kbd_irq;
अटल पूर्णांक i8042_aux_irq;

/*
 * Register numbers.
 */

#घोषणा I8042_COMMAND_REG	i8042_command_reg
#घोषणा I8042_STATUS_REG	i8042_command_reg
#घोषणा I8042_DATA_REG		i8042_data_reg

अटल पूर्णांक i8042_command_reg = 0x64;
अटल पूर्णांक i8042_data_reg = 0x60;


अटल अंतरभूत पूर्णांक i8042_पढ़ो_data(व्योम)
अणु
	वापस inb(I8042_DATA_REG);
पूर्ण

अटल अंतरभूत पूर्णांक i8042_पढ़ो_status(व्योम)
अणु
	वापस inb(I8042_STATUS_REG);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_data(पूर्णांक val)
अणु
	outb(val, I8042_DATA_REG);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_command(पूर्णांक val)
अणु
	outb(val, I8042_COMMAND_REG);
पूर्ण

#अगर_घोषित CONFIG_X86

#समावेश <linux/dmi.h>

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_noloop_table[] = अणु
	अणु
		/*
		 * Arima-Rioworks HDAMB -
		 * AUX LOOP command करोes not उठाओ AUX IRQ
		 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "RIOWORKS"),
			DMI_MATCH(DMI_BOARD_NAME, "HDAMB"),
			DMI_MATCH(DMI_BOARD_VERSION, "Rev E"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ASUS G1S */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_BOARD_NAME, "G1S"),
			DMI_MATCH(DMI_BOARD_VERSION, "1.0"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ASUS P65UP5 - AUX LOOP command करोes not उठाओ AUX IRQ */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "P/I-P65UP5"),
			DMI_MATCH(DMI_BOARD_VERSION, "REV 2.X"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X750LN"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Compaq"),
			DMI_MATCH(DMI_PRODUCT_NAME , "ProLiant"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "8500"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Compaq"),
			DMI_MATCH(DMI_PRODUCT_NAME , "ProLiant"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "DL760"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Embedded Box PC 3000 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Embedded Box PC 3000"),
		पूर्ण,
	पूर्ण,
	अणु
		/* OQO Model 01 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "OQO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ZEPTO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "00"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ULI EV4873 - AUX LOOP करोes not work properly */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ULI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EV4873"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "5a"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Microsoft Virtual Machine */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Virtual Machine"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "VS2005R2"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Medion MAM 2070 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Notebook"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MAM 2070"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "5a"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Medion Akoya E7225 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Medion"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Akoya E7225"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1.0"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Blue FB5601 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "blue"),
			DMI_MATCH(DMI_PRODUCT_NAME, "FB5601"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "M606"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte M912 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "M912"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "01"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte M1022M netbook */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co.,Ltd."),
			DMI_MATCH(DMI_BOARD_NAME, "M1022E"),
			DMI_MATCH(DMI_BOARD_VERSION, "1.02"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte Spring Peak - defines wrong chassis type */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Spring Peak"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte T1005 - defines wrong chassis type ("Other") */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T1005"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte T1005M/P - defines wrong chassis type ("Other") */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T1005M/P"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion dv9700"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Rev 1"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PEGATRON CORPORATION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "C15B"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ByteSpeed LLC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ByteSpeed Laptop C15B"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Some Fujitsu notebooks are having trouble with touchpads अगर
 * active multiplexing mode is activated. Luckily they करोn't have
 * बाह्यal PS/2 ports so we can safely disable it.
 * ... apparently some Toshibas करोn't like MUX mode either and
 * die horrible death on reboot.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_nomux_table[] = अणु
	अणु
		/* Fujitsu Lअगरebook P7010/P7010D */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P7010"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu Lअगरebook P7010 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "0000000000"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu Lअगरebook P5020D */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook P Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu Lअगरebook S2000 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook S Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu Lअगरebook S6230 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook S6230"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu Lअगरebook U745 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK U745"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu T70H */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "FMVLT70H"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Lअगरebook T3010 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK T3010"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Lअगरebook E4010 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E4010"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Amilo Pro 2010 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pro V2010"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Amilo Pro 2030 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO PRO V2030"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * No data is coming from the touchscreen unless KBC
		 * is in legacy mode.
		 */
		/* Panasonic CF-29 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Matsushita"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CF-29"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP Pavilion DV4017EA -
		 * errors on MUX ports are reported without raising AUXDATA
		 * causing "spurious NAK" messages.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Pavilion dv4000 (EA032EA#ABF)"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP Pavilion ZT1000 -
		 * like DV4017EA करोes not उठाओ AUXERR क्रम errors on MUX ports.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion Notebook PC"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "HP Pavilion Notebook ZT1000"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * HP Pavilion DV4270ca -
		 * like DV4017EA करोes not उठाओ AUXERR क्रम errors on MUX ports.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Pavilion dv4000 (EH476UA#ABL)"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Satellite P10"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EQUIUM A110"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SATELLITE C850D"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ALIENWARE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Sentia"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Sharp Actius MM20 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SHARP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PC-MM20 Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Sony Vaio FS-115b */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FS115B"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Sony Vaio FZ-240E -
		 * reset and GET ID commands issued via KBD port are
		 * someबार being delivered to AUX3.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FZ240E"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Most (all?) VAIOs करो not have बाह्यal PS/2 ports nor
		 * they implement active multiplexing properly, and
		 * MUX discovery usually messes up keyboard/touchpad.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "VAIO"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Amoi M636/A737 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Amoi Electronics CO.,LTD."),
			DMI_MATCH(DMI_PRODUCT_NAME, "M636/A737 platform"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo 3000 n100 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "076804U"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo XiaoXin Air 12 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "80UN"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 1360"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5710 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5710"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 7738 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 7738"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gericom Bellagio */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Gericom"),
			DMI_MATCH(DMI_PRODUCT_NAME, "N34AS6"),
		पूर्ण,
	पूर्ण,
	अणु
		/* IBM 2656 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "2656"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell XPS M1530 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS M1530"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Compal HEL80I */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "COMPAL"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HEL80I"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Vostro 1510 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro1510"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5536 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5536"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "0100"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Vostro V13 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V13"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Newer HP Pavilion dv4 models */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion dv4 Notebook PC"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Asus X450LCP */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X450LCP"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Avatar AVIU-145A6 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "IC4I"),
		पूर्ण,
	पूर्ण,
	अणु
		/* TUXEDO BU1406 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Notebook"),
			DMI_MATCH(DMI_PRODUCT_NAME, "N24_25BU"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo LaVie Z */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo LaVie Z"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Acer Aspire 5738z
		 * Touchpad stops working in mux mode when dis- + re-enabled
		 * with the touchpad enable/disable toggle hotkey
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5738"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Entroware Proteus */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Entroware"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Proteus"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "EL07R4"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id i8042_dmi_क्रमcemux_table[] __initस्थिर = अणु
	अणु
		/*
		 * Sony Vaio VGN-CS series require MUX or the touch sensor
		 * buttons will disturb touchpad operation
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "VGN-CS"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * On some Asus laptops, just running self tests cause problems.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id i8042_dmi_noselftest_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		पूर्ण,
	पूर्ण, अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "31"), /* Convertible Notebook */
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_reset_table[] = अणु
	अणु
		/* MSI Wind U-100 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "U-100"),
			DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTERNATIONAL CO., LTD"),
		पूर्ण,
	पूर्ण,
	अणु
		/* LG Electronics X110 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "X110"),
			DMI_MATCH(DMI_BOARD_VENDOR, "LG Electronics Inc."),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire One 150 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AOA150"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire A114-31"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire A314-31"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire A315-31"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire ES1-132"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire ES1-332"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire ES1-432"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate Spin B118-RN"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Advent 4211 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "DIXONSXP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Advent 4211"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Medion Akoya Mini E1210 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "E1210"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Medion Akoya E1222 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "E122X"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Mivvy M310 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "VIOOO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "N10"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Vostro 1320 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 1320"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Vostro 1520 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 1520"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Vostro 1720 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 1720"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo Ideapad U455 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "20046"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo ThinkPad L460 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad L460"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Clevo P650RS, 650RP6, Sager NP8152-S, and others */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Notebook"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P65xRP"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo ThinkPad Twist S230u */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "33474HU"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Entroware Proteus */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Entroware"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Proteus"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "EL07R4"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_nopnp_table[] = अणु
	अणु
		/* Intel MBO Desktop D845PESV */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "D845PESV"),
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel Corporation"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Intel NUC D54250WYK - करोes not have i8042 controller but
		 * declares PS/2 devices in DSDT.
		 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "D54250WYK"),
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel Corporation"),
		पूर्ण,
	पूर्ण,
	अणु
		/* MSI Wind U-100 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "U-100"),
			DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTERNATIONAL CO., LTD"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5 A515 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "Grumpy_PK"),
			DMI_MATCH(DMI_BOARD_VENDOR, "PK"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_laptop_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Portable */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /* Laptop */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_CHASSIS_TYPE, "14"), /* Sub-Notebook */
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_noसमयout_table[] = अणु
	अणु
		/* Dell Vostro V13 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V13"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Newer HP Pavilion dv4 models */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Pavilion dv4 Notebook PC"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu A544 laptop */
		/* https://bugzilla.redhat.com/show_bug.cgi?id=1111138 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK A544"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu AH544 laptop */
		/* https://bugzilla.kernel.org/show_bug.cgi?id=69731 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK AH544"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu U574 laptop */
		/* https://bugzilla.kernel.org/show_bug.cgi?id=69731 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK U574"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Fujitsu UH554 laptop */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK UH544"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Some Wistron based laptops need us to explicitly enable the 'Dritek
 * keyboard extension' to make their extra keys start generating scancodes.
 * Originally, this was just confined to older laptops, but a few Acer laptops
 * have turned up in 2007 that also need this again.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_dritek_table[] = अणु
	अणु
		/* Acer Aspire 5100 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5100"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5610 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5610"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5630 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5630"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5650 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5650"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5680 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5680"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 5720 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5720"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire 9110 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 9110"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer TravelMate 660 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 660"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer TravelMate 2490 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 2490"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer TravelMate 4280 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 4280"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Some laptops need keyboard reset beक्रमe probing क्रम the trackpad to get
 * it detected, initialised & finally work.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id __initस्थिर i8042_dmi_kbdreset_table[] = अणु
	अणु
		/* Gigabyte P35 v2 - Elantech touchpad */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P35V2"),
		पूर्ण,
	पूर्ण,
		अणु
		/* Aorus bअक्रमed Gigabyte X3 Plus - Elantech touchpad */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X3"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte P34 - Elantech touchpad */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P34"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Gigabyte P57 - Elantech touchpad */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P57"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Schenker XMG C504 - Elantech touchpad */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "XMG"),
			DMI_MATCH(DMI_PRODUCT_NAME, "C504"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर /* CONFIG_X86 */

#अगर_घोषित CONFIG_PNP
#समावेश <linux/pnp.h>

अटल bool i8042_pnp_kbd_रेजिस्टरed;
अटल अचिन्हित पूर्णांक i8042_pnp_kbd_devices;
अटल bool i8042_pnp_aux_रेजिस्टरed;
अटल अचिन्हित पूर्णांक i8042_pnp_aux_devices;

अटल पूर्णांक i8042_pnp_command_reg;
अटल पूर्णांक i8042_pnp_data_reg;
अटल पूर्णांक i8042_pnp_kbd_irq;
अटल पूर्णांक i8042_pnp_aux_irq;

अटल अक्षर i8042_pnp_kbd_name[32];
अटल अक्षर i8042_pnp_aux_name[32];

अटल व्योम i8042_pnp_id_to_string(काष्ठा pnp_id *id, अक्षर *dst, पूर्णांक dst_size)
अणु
	strlcpy(dst, "PNP:", dst_size);

	जबतक (id) अणु
		strlcat(dst, " ", dst_size);
		strlcat(dst, id->id, dst_size);
		id = id->next;
	पूर्ण
पूर्ण

अटल पूर्णांक i8042_pnp_kbd_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *did)
अणु
	अगर (pnp_port_valid(dev, 0) && pnp_port_len(dev, 0) == 1)
		i8042_pnp_data_reg = pnp_port_start(dev,0);

	अगर (pnp_port_valid(dev, 1) && pnp_port_len(dev, 1) == 1)
		i8042_pnp_command_reg = pnp_port_start(dev, 1);

	अगर (pnp_irq_valid(dev,0))
		i8042_pnp_kbd_irq = pnp_irq(dev, 0);

	strlcpy(i8042_pnp_kbd_name, did->id, माप(i8042_pnp_kbd_name));
	अगर (म_माप(pnp_dev_name(dev))) अणु
		strlcat(i8042_pnp_kbd_name, ":", माप(i8042_pnp_kbd_name));
		strlcat(i8042_pnp_kbd_name, pnp_dev_name(dev), माप(i8042_pnp_kbd_name));
	पूर्ण
	i8042_pnp_id_to_string(dev->id, i8042_kbd_firmware_id,
			       माप(i8042_kbd_firmware_id));
	i8042_kbd_fwnode = dev_fwnode(&dev->dev);

	/* Keyboard ports are always supposed to be wakeup-enabled */
	device_set_wakeup_enable(&dev->dev, true);

	i8042_pnp_kbd_devices++;
	वापस 0;
पूर्ण

अटल पूर्णांक i8042_pnp_aux_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *did)
अणु
	अगर (pnp_port_valid(dev, 0) && pnp_port_len(dev, 0) == 1)
		i8042_pnp_data_reg = pnp_port_start(dev,0);

	अगर (pnp_port_valid(dev, 1) && pnp_port_len(dev, 1) == 1)
		i8042_pnp_command_reg = pnp_port_start(dev, 1);

	अगर (pnp_irq_valid(dev, 0))
		i8042_pnp_aux_irq = pnp_irq(dev, 0);

	strlcpy(i8042_pnp_aux_name, did->id, माप(i8042_pnp_aux_name));
	अगर (म_माप(pnp_dev_name(dev))) अणु
		strlcat(i8042_pnp_aux_name, ":", माप(i8042_pnp_aux_name));
		strlcat(i8042_pnp_aux_name, pnp_dev_name(dev), माप(i8042_pnp_aux_name));
	पूर्ण
	i8042_pnp_id_to_string(dev->id, i8042_aux_firmware_id,
			       माप(i8042_aux_firmware_id));

	i8042_pnp_aux_devices++;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pnp_device_id pnp_kbd_devids[] = अणु
	अणु .id = "PNP0300", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0301", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0302", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0303", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0304", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0305", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0306", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0309", .driver_data = 0 पूर्ण,
	अणु .id = "PNP030a", .driver_data = 0 पूर्ण,
	अणु .id = "PNP030b", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0320", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0343", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0344", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0345", .driver_data = 0 पूर्ण,
	अणु .id = "CPQA0D7", .driver_data = 0 पूर्ण,
	अणु .id = "", पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pnp, pnp_kbd_devids);

अटल काष्ठा pnp_driver i8042_pnp_kbd_driver = अणु
	.name           = "i8042 kbd",
	.id_table       = pnp_kbd_devids,
	.probe          = i8042_pnp_kbd_probe,
	.driver         = अणु
		.probe_type = PROBE_FORCE_SYNCHRONOUS,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pnp_device_id pnp_aux_devids[] = अणु
	अणु .id = "AUI0200", .driver_data = 0 पूर्ण,
	अणु .id = "FJC6000", .driver_data = 0 पूर्ण,
	अणु .id = "FJC6001", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f03", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f0b", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f0e", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f12", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f13", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f19", .driver_data = 0 पूर्ण,
	अणु .id = "PNP0f1c", .driver_data = 0 पूर्ण,
	अणु .id = "SYN0801", .driver_data = 0 पूर्ण,
	अणु .id = "", पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pnp, pnp_aux_devids);

अटल काष्ठा pnp_driver i8042_pnp_aux_driver = अणु
	.name           = "i8042 aux",
	.id_table       = pnp_aux_devids,
	.probe          = i8042_pnp_aux_probe,
	.driver         = अणु
		.probe_type = PROBE_FORCE_SYNCHRONOUS,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल व्योम i8042_pnp_निकास(व्योम)
अणु
	अगर (i8042_pnp_kbd_रेजिस्टरed) अणु
		i8042_pnp_kbd_रेजिस्टरed = false;
		pnp_unरेजिस्टर_driver(&i8042_pnp_kbd_driver);
	पूर्ण

	अगर (i8042_pnp_aux_रेजिस्टरed) अणु
		i8042_pnp_aux_रेजिस्टरed = false;
		pnp_unरेजिस्टर_driver(&i8042_pnp_aux_driver);
	पूर्ण
पूर्ण

अटल पूर्णांक __init i8042_pnp_init(व्योम)
अणु
	अक्षर kbd_irq_str[4] = अणु 0 पूर्ण, aux_irq_str[4] = अणु 0 पूर्ण;
	bool pnp_data_busted = false;
	पूर्णांक err;

#अगर_घोषित CONFIG_X86
	अगर (dmi_check_प्रणाली(i8042_dmi_nopnp_table))
		i8042_nopnp = true;
#पूर्ण_अगर

	अगर (i8042_nopnp) अणु
		pr_info("PNP detection disabled\n");
		वापस 0;
	पूर्ण

	err = pnp_रेजिस्टर_driver(&i8042_pnp_kbd_driver);
	अगर (!err)
		i8042_pnp_kbd_रेजिस्टरed = true;

	err = pnp_रेजिस्टर_driver(&i8042_pnp_aux_driver);
	अगर (!err)
		i8042_pnp_aux_रेजिस्टरed = true;

	अगर (!i8042_pnp_kbd_devices && !i8042_pnp_aux_devices) अणु
		i8042_pnp_निकास();
#अगर defined(__ia64__)
		वापस -ENODEV;
#अन्यथा
		pr_info("PNP: No PS/2 controller found.\n");
		अगर (x86_platक्रमm.legacy.i8042 !=
				X86_LEGACY_I8042_EXPECTED_PRESENT)
			वापस -ENODEV;
		pr_info("Probing ports directly.\n");
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	अगर (i8042_pnp_kbd_devices)
		snम_लिखो(kbd_irq_str, माप(kbd_irq_str),
			"%d", i8042_pnp_kbd_irq);
	अगर (i8042_pnp_aux_devices)
		snम_लिखो(aux_irq_str, माप(aux_irq_str),
			"%d", i8042_pnp_aux_irq);

	pr_info("PNP: PS/2 Controller [%s%s%s] at %#x,%#x irq %s%s%s\n",
		i8042_pnp_kbd_name, (i8042_pnp_kbd_devices && i8042_pnp_aux_devices) ? "," : "",
		i8042_pnp_aux_name,
		i8042_pnp_data_reg, i8042_pnp_command_reg,
		kbd_irq_str, (i8042_pnp_kbd_devices && i8042_pnp_aux_devices) ? "," : "",
		aux_irq_str);

#अगर defined(__ia64__)
	अगर (!i8042_pnp_kbd_devices)
		i8042_nokbd = true;
	अगर (!i8042_pnp_aux_devices)
		i8042_noaux = true;
#पूर्ण_अगर

	अगर (((i8042_pnp_data_reg & ~0xf) == (i8042_data_reg & ~0xf) &&
	      i8042_pnp_data_reg != i8042_data_reg) ||
	    !i8042_pnp_data_reg) अणु
		pr_warn("PNP: PS/2 controller has invalid data port %#x; using default %#x\n",
			i8042_pnp_data_reg, i8042_data_reg);
		i8042_pnp_data_reg = i8042_data_reg;
		pnp_data_busted = true;
	पूर्ण

	अगर (((i8042_pnp_command_reg & ~0xf) == (i8042_command_reg & ~0xf) &&
	      i8042_pnp_command_reg != i8042_command_reg) ||
	    !i8042_pnp_command_reg) अणु
		pr_warn("PNP: PS/2 controller has invalid command port %#x; using default %#x\n",
			i8042_pnp_command_reg, i8042_command_reg);
		i8042_pnp_command_reg = i8042_command_reg;
		pnp_data_busted = true;
	पूर्ण

	अगर (!i8042_nokbd && !i8042_pnp_kbd_irq) अणु
		pr_warn("PNP: PS/2 controller doesn't have KBD irq; using default %d\n",
			i8042_kbd_irq);
		i8042_pnp_kbd_irq = i8042_kbd_irq;
		pnp_data_busted = true;
	पूर्ण

	अगर (!i8042_noaux && !i8042_pnp_aux_irq) अणु
		अगर (!pnp_data_busted && i8042_pnp_kbd_irq) अणु
			pr_warn("PNP: PS/2 appears to have AUX port disabled, "
				"if this is incorrect please boot with i8042.nopnp\n");
			i8042_noaux = true;
		पूर्ण अन्यथा अणु
			pr_warn("PNP: PS/2 controller doesn't have AUX irq; using default %d\n",
				i8042_aux_irq);
			i8042_pnp_aux_irq = i8042_aux_irq;
		पूर्ण
	पूर्ण

	i8042_data_reg = i8042_pnp_data_reg;
	i8042_command_reg = i8042_pnp_command_reg;
	i8042_kbd_irq = i8042_pnp_kbd_irq;
	i8042_aux_irq = i8042_pnp_aux_irq;

#अगर_घोषित CONFIG_X86
	i8042_bypass_aux_irq_test = !pnp_data_busted &&
				    dmi_check_प्रणाली(i8042_dmi_laptop_table);
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अन्यथा  /* !CONFIG_PNP */
अटल अंतरभूत पूर्णांक i8042_pnp_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम i8042_pnp_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init i8042_platक्रमm_init(व्योम)
अणु
	पूर्णांक retval;

#अगर_घोषित CONFIG_X86
	u8 a20_on = 0xdf;
	/* Just वापस अगर platक्रमm करोes not have i8042 controller */
	अगर (x86_platक्रमm.legacy.i8042 == X86_LEGACY_I8042_PLATFORM_ABSENT)
		वापस -ENODEV;
#पूर्ण_अगर

/*
 * On ix86 platक्रमms touching the i8042 data रेजिस्टर region can करो really
 * bad things. Because of this the region is always reserved on ix86 boxes.
 *
 *	अगर (!request_region(I8042_DATA_REG, 16, "i8042"))
 *		वापस -EBUSY;
 */

	i8042_kbd_irq = I8042_MAP_IRQ(1);
	i8042_aux_irq = I8042_MAP_IRQ(12);

	retval = i8042_pnp_init();
	अगर (retval)
		वापस retval;

#अगर defined(__ia64__)
        i8042_reset = I8042_RESET_ALWAYS;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86
	/* Honor module parameter when value is not शेष */
	अगर (i8042_reset == I8042_RESET_DEFAULT) अणु
		अगर (dmi_check_प्रणाली(i8042_dmi_reset_table))
			i8042_reset = I8042_RESET_ALWAYS;

		अगर (dmi_check_प्रणाली(i8042_dmi_noselftest_table))
			i8042_reset = I8042_RESET_NEVER;
	पूर्ण

	अगर (dmi_check_प्रणाली(i8042_dmi_noloop_table))
		i8042_noloop = true;

	अगर (dmi_check_प्रणाली(i8042_dmi_nomux_table))
		i8042_nomux = true;

	अगर (dmi_check_प्रणाली(i8042_dmi_क्रमcemux_table))
		i8042_nomux = false;

	अगर (dmi_check_प्रणाली(i8042_dmi_noसमयout_table))
		i8042_noसमयout = true;

	अगर (dmi_check_प्रणाली(i8042_dmi_dritek_table))
		i8042_dritek = true;

	अगर (dmi_check_प्रणाली(i8042_dmi_kbdreset_table))
		i8042_kbdreset = true;

	/*
	 * A20 was alपढ़ोy enabled during early kernel init. But some buggy
	 * BIOSes (in MSI Laptops) require A20 to be enabled using 8042 to
	 * resume from S3. So we करो it here and hope that nothing अवरोधs.
	 */
	i8042_command(&a20_on, 0x10d1);
	i8042_command(शून्य, 0x00ff);	/* Null command क्रम SMM firmware */
#पूर्ण_अगर /* CONFIG_X86 */

	वापस retval;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
	i8042_pnp_निकास();
पूर्ण

#पूर्ण_अगर /* _I8042_X86IA64IO_H */
