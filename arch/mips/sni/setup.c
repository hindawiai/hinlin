<शैली गुरु>
/*
 * Setup poपूर्णांकers to hardware-dependent routines.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 97, 98, 2000, 03, 04, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2006,2007 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */
#समावेश <linux/eisa.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/console.h>
#समावेश <linux/fb.h>
#समावेश <linux/screen_info.h>

#अगर_घोषित CONFIG_FW_ARC
#समावेश <यंत्र/fw/arc/types.h>
#समावेश <यंत्र/sgialib.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_FW_SNIPROM
#समावेश <यंत्र/mipsprom.h>
#पूर्ण_अगर

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sni.h>

अचिन्हित पूर्णांक sni_brd_type;
EXPORT_SYMBOL(sni_brd_type);

बाह्य व्योम sni_machine_restart(अक्षर *command);
बाह्य व्योम sni_machine_घातer_off(व्योम);

अटल व्योम __init sni_display_setup(व्योम)
अणु
#अगर defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE) && defined(CONFIG_FW_ARC)
	काष्ठा screen_info *si = &screen_info;
	DISPLAY_STATUS *di;

	di = ArcGetDisplayStatus(1);

	अगर (di) अणु
		si->orig_x		= di->CursorXPosition;
		si->orig_y		= di->CursorYPosition;
		si->orig_video_cols	= di->CursorMaxXPosition;
		si->orig_video_lines	= di->CursorMaxYPosition;
		si->orig_video_isVGA	= VIDEO_TYPE_VGAC;
		si->orig_video_poपूर्णांकs	= 16;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sni_console_setup(व्योम)
अणु
#अगर_अघोषित CONFIG_FW_ARC
	अक्षर *ctype;
	अक्षर *cdev;
	अक्षर *baud;
	पूर्णांक port;
	अटल अक्षर options[8] __initdata;

	cdev = prom_दो_पर्या("console_dev");
	अगर (म_भेदन(cdev, "tty", 3) == 0) अणु
		ctype = prom_दो_पर्या("console");
		चयन (*ctype) अणु
		शेष:
		हाल 'l':
			port = 0;
			baud = prom_दो_पर्या("lbaud");
			अवरोध;
		हाल 'r':
			port = 1;
			baud = prom_दो_पर्या("rbaud");
			अवरोध;
		पूर्ण
		अगर (baud)
			म_नकल(options, baud);
		अगर (म_भेदन(cdev, "tty552", 6) == 0)
			add_preferred_console("ttyS", port,
					      baud ? options : शून्य);
		अन्यथा
			add_preferred_console("ttySC", port,
					      baud ? options : शून्य);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम __init sni_idprom_dump(व्योम)
अणु
	पूर्णांक	i;

	pr_debug("SNI IDProm dump:\n");
	क्रम (i = 0; i < 256; i++) अणु
		अगर (i%16 == 0)
			pr_debug("%04x ", i);

		prपूर्णांकk("%02x ", *(अचिन्हित अक्षर *) (SNI_IDPROM_BASE + i));

		अगर (i % 16 == 15)
			prपूर्णांकk("\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम __init plat_mem_setup(व्योम)
अणु
	पूर्णांक cputype;

	set_io_port_base(SNI_PORT_BASE);
//	ioport_resource.end = sni_io_resource.end;

	/*
	 * Setup (E)ISA I/O memory access stuff
	 */
#अगर_घोषित CONFIG_EISA
	EISA_bus = 1;
#पूर्ण_अगर

	sni_brd_type = *(अचिन्हित अक्षर *)SNI_IDPROM_BRDTYPE;
	cputype = *(अचिन्हित अक्षर *)SNI_IDPROM_CPUTYPE;
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_TOWER_OASIC:
		चयन (cputype) अणु
		हाल SNI_CPU_M8030:
			प्रणाली_type = "RM400-330";
			अवरोध;
		हाल SNI_CPU_M8031:
			प्रणाली_type = "RM400-430";
			अवरोध;
		हाल SNI_CPU_M8037:
			प्रणाली_type = "RM400-530";
			अवरोध;
		हाल SNI_CPU_M8034:
			प्रणाली_type = "RM400-730";
			अवरोध;
		शेष:
			प्रणाली_type = "RM400-xxx";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SNI_BRD_MINITOWER:
		चयन (cputype) अणु
		हाल SNI_CPU_M8021:
		हाल SNI_CPU_M8043:
			प्रणाली_type = "RM400-120";
			अवरोध;
		हाल SNI_CPU_M8040:
			प्रणाली_type = "RM400-220";
			अवरोध;
		हाल SNI_CPU_M8053:
			प्रणाली_type = "RM400-225";
			अवरोध;
		हाल SNI_CPU_M8050:
			प्रणाली_type = "RM400-420";
			अवरोध;
		शेष:
			प्रणाली_type = "RM400-xxx";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SNI_BRD_PCI_TOWER:
		प्रणाली_type = "RM400-Cxx";
		अवरोध;
	हाल SNI_BRD_RM200:
		प्रणाली_type = "RM200-xxx";
		अवरोध;
	हाल SNI_BRD_PCI_MTOWER:
		प्रणाली_type = "RM300-Cxx";
		अवरोध;
	हाल SNI_BRD_PCI_DESKTOP:
		चयन (पढ़ो_c0_prid() & PRID_IMP_MASK) अणु
		हाल PRID_IMP_R4600:
		हाल PRID_IMP_R4700:
			प्रणाली_type = "RM200-C20";
			अवरोध;
		हाल PRID_IMP_R5000:
			प्रणाली_type = "RM200-C40";
			अवरोध;
		शेष:
			प्रणाली_type = "RM200-Cxx";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SNI_BRD_PCI_TOWER_CPLUS:
		प्रणाली_type = "RM400-Exx";
		अवरोध;
	हाल SNI_BRD_PCI_MTOWER_CPLUS:
		प्रणाली_type = "RM300-Exx";
		अवरोध;
	पूर्ण
	pr_debug("Found SNI brdtype %02x name %s\n", sni_brd_type, प्रणाली_type);

#अगर_घोषित DEBUG
	sni_idprom_dump();
#पूर्ण_अगर

	चयन (sni_brd_type) अणु
	हाल SNI_BRD_10:
	हाल SNI_BRD_10NEW:
	हाल SNI_BRD_TOWER_OASIC:
	हाल SNI_BRD_MINITOWER:
		sni_a20r_init();
		अवरोध;

	हाल SNI_BRD_PCI_TOWER:
	हाल SNI_BRD_PCI_TOWER_CPLUS:
		sni_pcit_init();
		अवरोध;

	हाल SNI_BRD_RM200:
		sni_rm200_init();
		अवरोध;

	हाल SNI_BRD_PCI_MTOWER:
	हाल SNI_BRD_PCI_DESKTOP:
	हाल SNI_BRD_PCI_MTOWER_CPLUS:
		sni_pcimt_init();
		अवरोध;
	पूर्ण

	_machine_restart = sni_machine_restart;
	pm_घातer_off = sni_machine_घातer_off;

	sni_display_setup();
	sni_console_setup();
पूर्ण

#अगर_घोषित CONFIG_PCI

#समावेश <linux/pci.h>
#समावेश <video/vga.h>
#समावेश <video/cirrus.h>

अटल व्योम quirk_cirrus_ram_size(काष्ठा pci_dev *dev)
अणु
	u16 cmd;

	/*
	 * firmware करोesn't set the ram size correct, so we
	 * need to करो it here, otherwise we get screen corruption
	 * on older Cirrus chips
	 */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर ((cmd & (PCI_COMMAND_IO|PCI_COMMAND_MEMORY))
		== (PCI_COMMAND_IO|PCI_COMMAND_MEMORY)) अणु
		vga_wseq(शून्य, CL_SEQR6, 0x12); /* unlock all extension रेजिस्टरs */
		vga_wseq(शून्य, CL_SEQRF, 0x18);
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CIRRUS, PCI_DEVICE_ID_CIRRUS_5434_8,
			quirk_cirrus_ram_size);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CIRRUS, PCI_DEVICE_ID_CIRRUS_5436,
			quirk_cirrus_ram_size);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_CIRRUS, PCI_DEVICE_ID_CIRRUS_5446,
			quirk_cirrus_ram_size);
#पूर्ण_अगर
