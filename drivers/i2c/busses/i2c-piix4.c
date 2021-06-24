<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1998 - 2002 Froकरो Looijaard <froकरोl@dds.nl> and
    Philip Edelbrock <phil@netroedge.com>

*/

/*
   Supports:
	Intel PIIX4, 440MX
	Serverworks OSB4, CSB5, CSB6, HT-1000, HT-1100
	ATI IXP200, IXP300, IXP400, SB600, SB700/SP5100, SB800
	AMD Hudson-2, ML, CZ
	Hygon CZ
	SMSC Victory66

   Note: we assume there can only be one device, with one or more
   SMBus पूर्णांकerfaces.
   The device can रेजिस्टर multiple i2c_adapters (up to PIIX4_MAX_ADAPTERS).
   For devices supporting multiple ports the i2c_adapter should provide
   an i2c_algorithm to access them.
*/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>


/* PIIX4 SMBus address offsets */
#घोषणा SMBHSTSTS	(0 + piix4_smba)
#घोषणा SMBHSLVSTS	(1 + piix4_smba)
#घोषणा SMBHSTCNT	(2 + piix4_smba)
#घोषणा SMBHSTCMD	(3 + piix4_smba)
#घोषणा SMBHSTADD	(4 + piix4_smba)
#घोषणा SMBHSTDAT0	(5 + piix4_smba)
#घोषणा SMBHSTDAT1	(6 + piix4_smba)
#घोषणा SMBBLKDAT	(7 + piix4_smba)
#घोषणा SMBSLVCNT	(8 + piix4_smba)
#घोषणा SMBSHDWCMD	(9 + piix4_smba)
#घोषणा SMBSLVEVT	(0xA + piix4_smba)
#घोषणा SMBSLVDAT	(0xC + piix4_smba)

/* count क्रम request_region */
#घोषणा SMBIOSIZE	9

/* PCI Address Constants */
#घोषणा SMBBA		0x090
#घोषणा SMBHSTCFG	0x0D2
#घोषणा SMBSLVC		0x0D3
#घोषणा SMBSHDW1	0x0D4
#घोषणा SMBSHDW2	0x0D5
#घोषणा SMBREV		0x0D6

/* Other settings */
#घोषणा MAX_TIMEOUT	500
#घोषणा  ENABLE_INT9	0

/* PIIX4 स्थिरants */
#घोषणा PIIX4_QUICK		0x00
#घोषणा PIIX4_BYTE		0x04
#घोषणा PIIX4_BYTE_DATA		0x08
#घोषणा PIIX4_WORD_DATA		0x0C
#घोषणा PIIX4_BLOCK_DATA	0x14

/* Multi-port स्थिरants */
#घोषणा PIIX4_MAX_ADAPTERS	4
#घोषणा HUDSON2_MAIN_PORTS	2 /* HUDSON2, KERNCZ reserves ports 3, 4 */

/* SB800 स्थिरants */
#घोषणा SB800_PIIX4_SMB_IDX		0xcd6

#घोषणा KERNCZ_IMC_IDX			0x3e
#घोषणा KERNCZ_IMC_DATA			0x3f

/*
 * SB800 port is selected by bits 2:1 of the smb_en रेजिस्टर (0x2c)
 * or the smb_sel रेजिस्टर (0x2e), depending on bit 0 of रेजिस्टर 0x2f.
 * Hudson-2/Bolton port is always selected by bits 2:1 of रेजिस्टर 0x2f.
 */
#घोषणा SB800_PIIX4_PORT_IDX		0x2c
#घोषणा SB800_PIIX4_PORT_IDX_ALT	0x2e
#घोषणा SB800_PIIX4_PORT_IDX_SEL	0x2f
#घोषणा SB800_PIIX4_PORT_IDX_MASK	0x06
#घोषणा SB800_PIIX4_PORT_IDX_SHIFT	1

/* On kerncz and Hudson2, SmBus0Sel is at bit 20:19 of PMx00 DecodeEn */
#घोषणा SB800_PIIX4_PORT_IDX_KERNCZ		0x02
#घोषणा SB800_PIIX4_PORT_IDX_MASK_KERNCZ	0x18
#घोषणा SB800_PIIX4_PORT_IDX_SHIFT_KERNCZ	3

/* insmod parameters */

/* If क्रमce is set to anything dअगरferent from 0, we क्रमcibly enable the
   PIIX4. DANGEROUS! */
अटल पूर्णांक क्रमce;
module_param (क्रमce, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce, "Forcibly enable the PIIX4. DANGEROUS!");

/* If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
   the PIIX4 at the given address. VERY DANGEROUS! */
अटल पूर्णांक क्रमce_addr;
module_param_hw(क्रमce_addr, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(क्रमce_addr,
		 "Forcibly enable the PIIX4 at the given address. "
		 "EXTREMELY DANGEROUS!");

अटल पूर्णांक srvrworks_csb5_delay;
अटल काष्ठा pci_driver piix4_driver;

अटल स्थिर काष्ठा dmi_प्रणाली_id piix4_dmi_blacklist[] = अणु
	अणु
		.ident = "Sapphire AM2RD790",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "SAPPHIRE Inc."),
			DMI_MATCH(DMI_BOARD_NAME, "PC-AM2RD790"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "DFI Lanparty UT 790FX",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "DFI Inc."),
			DMI_MATCH(DMI_BOARD_NAME, "LP UT 790FX"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* The IBM entry is in a separate table because we only check it
   on Intel-based प्रणालीs */
अटल स्थिर काष्ठा dmi_प्रणाली_id piix4_dmi_ibm[] = अणु
	अणु
		.ident = "IBM",
		.matches = अणु DMI_MATCH(DMI_SYS_VENDOR, "IBM"), पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * SB800 globals
 */
अटल u8 piix4_port_sel_sb800;
अटल u8 piix4_port_mask_sb800;
अटल u8 piix4_port_shअगरt_sb800;
अटल स्थिर अक्षर *piix4_मुख्य_port_names_sb800[PIIX4_MAX_ADAPTERS] = अणु
	" port 0", " port 2", " port 3", " port 4"
पूर्ण;
अटल स्थिर अक्षर *piix4_aux_port_name_sb800 = " port 1";

काष्ठा i2c_piix4_adapdata अणु
	अचिन्हित लघु smba;

	/* SB800 */
	bool sb800_मुख्य;
	bool notअगरy_imc;
	u8 port;		/* Port number, shअगरted */
पूर्ण;

अटल पूर्णांक piix4_setup(काष्ठा pci_dev *PIIX4_dev,
		       स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित अक्षर temp;
	अचिन्हित लघु piix4_smba;

	अगर ((PIIX4_dev->venकरोr == PCI_VENDOR_ID_SERVERWORKS) &&
	    (PIIX4_dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5))
		srvrworks_csb5_delay = 1;

	/* On some motherboards, it was reported that accessing the SMBus
	   caused severe hardware problems */
	अगर (dmi_check_प्रणाली(piix4_dmi_blacklist)) अणु
		dev_err(&PIIX4_dev->dev,
			"Accessing the SMBus on this system is unsafe!\n");
		वापस -EPERM;
	पूर्ण

	/* Don't access SMBus on IBM प्रणालीs which get corrupted eeproms */
	अगर (dmi_check_प्रणाली(piix4_dmi_ibm) &&
			PIIX4_dev->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		dev_err(&PIIX4_dev->dev, "IBM system detected; this module "
			"may corrupt your serial eeprom! Refusing to load "
			"module!\n");
		वापस -EPERM;
	पूर्ण

	/* Determine the address of the SMBus areas */
	अगर (क्रमce_addr) अणु
		piix4_smba = क्रमce_addr & 0xfff0;
		क्रमce = 0;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_word(PIIX4_dev, SMBBA, &piix4_smba);
		piix4_smba &= 0xfff0;
		अगर(piix4_smba == 0) अणु
			dev_err(&PIIX4_dev->dev, "SMBus base address "
				"uninitialized - upgrade BIOS or use "
				"force_addr=0xaddr\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		वापस -ENODEV;

	अगर (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) अणु
		dev_err(&PIIX4_dev->dev, "SMBus region 0x%x already in use!\n",
			piix4_smba);
		वापस -EBUSY;
	पूर्ण

	pci_पढ़ो_config_byte(PIIX4_dev, SMBHSTCFG, &temp);

	/* If क्रमce_addr is set, we program the new address here. Just to make
	   sure, we disable the PIIX4 first. */
	अगर (क्रमce_addr) अणु
		pci_ग_लिखो_config_byte(PIIX4_dev, SMBHSTCFG, temp & 0xfe);
		pci_ग_लिखो_config_word(PIIX4_dev, SMBBA, piix4_smba);
		pci_ग_लिखो_config_byte(PIIX4_dev, SMBHSTCFG, temp | 0x01);
		dev_info(&PIIX4_dev->dev, "WARNING: SMBus interface set to "
			"new address %04x!\n", piix4_smba);
	पूर्ण अन्यथा अगर ((temp & 1) == 0) अणु
		अगर (क्रमce) अणु
			/* This should never need to be करोne, but has been
			 * noted that many Dell machines have the SMBus
			 * पूर्णांकerface on the PIIX4 disabled!? NOTE: This assumes
			 * I/O space and other allocations WERE करोne by the
			 * Bios!  Don't complain अगर your hardware करोes weird
			 * things after enabling this. :') Check क्रम Bios
			 * updates beक्रमe resorting to this.
			 */
			pci_ग_लिखो_config_byte(PIIX4_dev, SMBHSTCFG,
					      temp | 1);
			dev_notice(&PIIX4_dev->dev,
				   "WARNING: SMBus interface has been FORCEFULLY ENABLED!\n");
		पूर्ण अन्यथा अणु
			dev_err(&PIIX4_dev->dev,
				"SMBus Host Controller not enabled!\n");
			release_region(piix4_smba, SMBIOSIZE);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (((temp & 0x0E) == 8) || ((temp & 0x0E) == 2))
		dev_dbg(&PIIX4_dev->dev, "Using IRQ for SMBus\n");
	अन्यथा अगर ((temp & 0x0E) == 0)
		dev_dbg(&PIIX4_dev->dev, "Using SMI# for SMBus\n");
	अन्यथा
		dev_err(&PIIX4_dev->dev, "Illegal Interrupt configuration "
			"(or code out of date)!\n");

	pci_पढ़ो_config_byte(PIIX4_dev, SMBREV, &temp);
	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Controller at 0x%x, revision %d\n",
		 piix4_smba, temp);

	वापस piix4_smba;
पूर्ण

अटल पूर्णांक piix4_setup_sb800(काष्ठा pci_dev *PIIX4_dev,
			     स्थिर काष्ठा pci_device_id *id, u8 aux)
अणु
	अचिन्हित लघु piix4_smba;
	u8 smba_en_lo, smba_en_hi, smb_en, smb_en_status, port_sel;
	u8 i2ccfg, i2ccfg_offset = 0x10;

	/* SB800 and later SMBus करोes not support क्रमcing address */
	अगर (क्रमce || क्रमce_addr) अणु
		dev_err(&PIIX4_dev->dev, "SMBus does not support "
			"forcing address!\n");
		वापस -EINVAL;
	पूर्ण

	/* Determine the address of the SMBus areas */
	अगर ((PIIX4_dev->venकरोr == PCI_VENDOR_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     PIIX4_dev->revision >= 0x41) ||
	    (PIIX4_dev->venकरोr == PCI_VENDOR_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS &&
	     PIIX4_dev->revision >= 0x49) ||
	    (PIIX4_dev->venकरोr == PCI_VENDOR_ID_HYGON &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS))
		smb_en = 0x00;
	अन्यथा
		smb_en = (aux) ? 0x28 : 0x2c;

	अगर (!request_muxed_region(SB800_PIIX4_SMB_IDX, 2, "sb800_piix4_smb")) अणु
		dev_err(&PIIX4_dev->dev,
			"SMB base address index region 0x%x already in use.\n",
			SB800_PIIX4_SMB_IDX);
		वापस -EBUSY;
	पूर्ण

	outb_p(smb_en, SB800_PIIX4_SMB_IDX);
	smba_en_lo = inb_p(SB800_PIIX4_SMB_IDX + 1);
	outb_p(smb_en + 1, SB800_PIIX4_SMB_IDX);
	smba_en_hi = inb_p(SB800_PIIX4_SMB_IDX + 1);

	release_region(SB800_PIIX4_SMB_IDX, 2);

	अगर (!smb_en) अणु
		smb_en_status = smba_en_lo & 0x10;
		piix4_smba = smba_en_hi << 8;
		अगर (aux)
			piix4_smba |= 0x20;
	पूर्ण अन्यथा अणु
		smb_en_status = smba_en_lo & 0x01;
		piix4_smba = ((smba_en_hi << 8) | smba_en_lo) & 0xffe0;
	पूर्ण

	अगर (!smb_en_status) अणु
		dev_err(&PIIX4_dev->dev,
			"SMBus Host Controller not enabled!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		वापस -ENODEV;

	अगर (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) अणु
		dev_err(&PIIX4_dev->dev, "SMBus region 0x%x already in use!\n",
			piix4_smba);
		वापस -EBUSY;
	पूर्ण

	/* Aux SMBus करोes not support IRQ inक्रमmation */
	अगर (aux) अणु
		dev_info(&PIIX4_dev->dev,
			 "Auxiliary SMBus Host Controller at 0x%x\n",
			 piix4_smba);
		वापस piix4_smba;
	पूर्ण

	/* Request the SMBus I2C bus config region */
	अगर (!request_region(piix4_smba + i2ccfg_offset, 1, "i2ccfg")) अणु
		dev_err(&PIIX4_dev->dev, "SMBus I2C bus config region "
			"0x%x already in use!\n", piix4_smba + i2ccfg_offset);
		release_region(piix4_smba, SMBIOSIZE);
		वापस -EBUSY;
	पूर्ण
	i2ccfg = inb_p(piix4_smba + i2ccfg_offset);
	release_region(piix4_smba + i2ccfg_offset, 1);

	अगर (i2ccfg & 1)
		dev_dbg(&PIIX4_dev->dev, "Using IRQ for SMBus\n");
	अन्यथा
		dev_dbg(&PIIX4_dev->dev, "Using SMI# for SMBus\n");

	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Controller at 0x%x, revision %d\n",
		 piix4_smba, i2ccfg >> 4);

	/* Find which रेजिस्टर is used क्रम port selection */
	अगर (PIIX4_dev->venकरोr == PCI_VENDOR_ID_AMD ||
	    PIIX4_dev->venकरोr == PCI_VENDOR_ID_HYGON) अणु
		अगर (PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ||
		    (PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
		     PIIX4_dev->revision >= 0x1F)) अणु
			piix4_port_sel_sb800 = SB800_PIIX4_PORT_IDX_KERNCZ;
			piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK_KERNCZ;
			piix4_port_shअगरt_sb800 = SB800_PIIX4_PORT_IDX_SHIFT_KERNCZ;
		पूर्ण अन्यथा अणु
			piix4_port_sel_sb800 = SB800_PIIX4_PORT_IDX_ALT;
			piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK;
			piix4_port_shअगरt_sb800 = SB800_PIIX4_PORT_IDX_SHIFT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!request_muxed_region(SB800_PIIX4_SMB_IDX, 2,
					  "sb800_piix4_smb")) अणु
			release_region(piix4_smba, SMBIOSIZE);
			वापस -EBUSY;
		पूर्ण

		outb_p(SB800_PIIX4_PORT_IDX_SEL, SB800_PIIX4_SMB_IDX);
		port_sel = inb_p(SB800_PIIX4_SMB_IDX + 1);
		piix4_port_sel_sb800 = (port_sel & 0x01) ?
				       SB800_PIIX4_PORT_IDX_ALT :
				       SB800_PIIX4_PORT_IDX;
		piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK;
		piix4_port_shअगरt_sb800 = SB800_PIIX4_PORT_IDX_SHIFT;
		release_region(SB800_PIIX4_SMB_IDX, 2);
	पूर्ण

	dev_info(&PIIX4_dev->dev,
		 "Using register 0x%02x for SMBus port selection\n",
		 (अचिन्हित पूर्णांक)piix4_port_sel_sb800);

	वापस piix4_smba;
पूर्ण

अटल पूर्णांक piix4_setup_aux(काष्ठा pci_dev *PIIX4_dev,
			   स्थिर काष्ठा pci_device_id *id,
			   अचिन्हित लघु base_reg_addr)
अणु
	/* Set up auxiliary SMBus controllers found on some
	 * AMD chipsets e.g. SP5100 (SB700 derivative) */

	अचिन्हित लघु piix4_smba;

	/* Read address of auxiliary SMBus controller */
	pci_पढ़ो_config_word(PIIX4_dev, base_reg_addr, &piix4_smba);
	अगर ((piix4_smba & 1) == 0) अणु
		dev_dbg(&PIIX4_dev->dev,
			"Auxiliary SMBus controller not enabled\n");
		वापस -ENODEV;
	पूर्ण

	piix4_smba &= 0xfff0;
	अगर (piix4_smba == 0) अणु
		dev_dbg(&PIIX4_dev->dev,
			"Auxiliary SMBus base address uninitialized\n");
		वापस -ENODEV;
	पूर्ण

	अगर (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		वापस -ENODEV;

	अगर (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) अणु
		dev_err(&PIIX4_dev->dev, "Auxiliary SMBus region 0x%x "
			"already in use!\n", piix4_smba);
		वापस -EBUSY;
	पूर्ण

	dev_info(&PIIX4_dev->dev,
		 "Auxiliary SMBus Host Controller at 0x%x\n",
		 piix4_smba);

	वापस piix4_smba;
पूर्ण

अटल पूर्णांक piix4_transaction(काष्ठा i2c_adapter *piix4_adapter)
अणु
	काष्ठा i2c_piix4_adapdata *adapdata = i2c_get_adapdata(piix4_adapter);
	अचिन्हित लघु piix4_smba = adapdata->smba;
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	dev_dbg(&piix4_adapter->dev, "Transaction (pre): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	अगर ((temp = inb_p(SMBHSTSTS)) != 0x00) अणु
		dev_dbg(&piix4_adapter->dev, "SMBus busy (%02x). "
			"Resetting...\n", temp);
		outb_p(temp, SMBHSTSTS);
		अगर ((temp = inb_p(SMBHSTSTS)) != 0x00) अणु
			dev_err(&piix4_adapter->dev, "Failed! (%02x)\n", temp);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			dev_dbg(&piix4_adapter->dev, "Successful!\n");
		पूर्ण
	पूर्ण

	/* start the transaction by setting bit 6 */
	outb_p(inb(SMBHSTCNT) | 0x040, SMBHSTCNT);

	/* We will always रुको क्रम a fraction of a second! (See PIIX4 करोcs errata) */
	अगर (srvrworks_csb5_delay) /* Extra delay क्रम SERVERWORKS_CSB5 */
		usleep_range(2000, 2100);
	अन्यथा
		usleep_range(250, 500);

	जबतक ((++समयout < MAX_TIMEOUT) &&
	       ((temp = inb_p(SMBHSTSTS)) & 0x01))
		usleep_range(250, 500);

	/* If the SMBus is still busy, we give up */
	अगर (समयout == MAX_TIMEOUT) अणु
		dev_err(&piix4_adapter->dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	पूर्ण

	अगर (temp & 0x10) अणु
		result = -EIO;
		dev_err(&piix4_adapter->dev, "Error: Failed bus transaction\n");
	पूर्ण

	अगर (temp & 0x08) अणु
		result = -EIO;
		dev_dbg(&piix4_adapter->dev, "Bus collision! SMBus may be "
			"locked until next hard reset. (sorry!)\n");
		/* Clock stops and slave is stuck in mid-transmission */
	पूर्ण

	अगर (temp & 0x04) अणु
		result = -ENXIO;
		dev_dbg(&piix4_adapter->dev, "Error: no response!\n");
	पूर्ण

	अगर (inb_p(SMBHSTSTS) != 0x00)
		outb_p(inb(SMBHSTSTS), SMBHSTSTS);

	अगर ((temp = inb_p(SMBHSTSTS)) != 0x00) अणु
		dev_err(&piix4_adapter->dev, "Failed reset at end of "
			"transaction (%02x)\n", temp);
	पूर्ण
	dev_dbg(&piix4_adapter->dev, "Transaction (post): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));
	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 piix4_access(काष्ठा i2c_adapter * adap, u16 addr,
		 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		 u8 command, पूर्णांक size, जोड़ i2c_smbus_data * data)
अणु
	काष्ठा i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);
	अचिन्हित लघु piix4_smba = adapdata->smba;
	पूर्णांक i, len;
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outb_p((addr << 1) | पढ़ो_ग_लिखो,
		       SMBHSTADD);
		size = PIIX4_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outb_p((addr << 1) | पढ़ो_ग_लिखो,
		       SMBHSTADD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD);
		size = PIIX4_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb_p((addr << 1) | पढ़ो_ग_लिखो,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = PIIX4_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb_p((addr << 1) | पढ़ो_ग_लिखो,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0);
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		पूर्ण
		size = PIIX4_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p((addr << 1) | पढ़ो_ग_लिखो,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
				वापस -EINVAL;
			outb_p(len, SMBHSTDAT0);
			inb_p(SMBHSTCNT);	/* Reset SMBBLKDAT */
			क्रम (i = 1; i <= len; i++)
				outb_p(data->block[i], SMBBLKDAT);
		पूर्ण
		size = PIIX4_BLOCK_DATA;
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	outb_p((size & 0x1C) + (ENABLE_INT9 & 1), SMBHSTCNT);

	status = piix4_transaction(adap);
	अगर (status)
		वापस status;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == PIIX4_QUICK))
		वापस 0;


	चयन (size) अणु
	हाल PIIX4_BYTE:
	हाल PIIX4_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल PIIX4_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		अवरोध;
	हाल PIIX4_BLOCK_DATA:
		data->block[0] = inb_p(SMBHSTDAT0);
		अगर (data->block[0] == 0 || data->block[0] > I2C_SMBUS_BLOCK_MAX)
			वापस -EPROTO;
		inb_p(SMBHSTCNT);	/* Reset SMBBLKDAT */
		क्रम (i = 1; i <= data->block[0]; i++)
			data->block[i] = inb_p(SMBBLKDAT);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल uपूर्णांक8_t piix4_imc_पढ़ो(uपूर्णांक8_t idx)
अणु
	outb_p(idx, KERNCZ_IMC_IDX);
	वापस inb_p(KERNCZ_IMC_DATA);
पूर्ण

अटल व्योम piix4_imc_ग_लिखो(uपूर्णांक8_t idx, uपूर्णांक8_t value)
अणु
	outb_p(idx, KERNCZ_IMC_IDX);
	outb_p(value, KERNCZ_IMC_DATA);
पूर्ण

अटल पूर्णांक piix4_imc_sleep(व्योम)
अणु
	पूर्णांक समयout = MAX_TIMEOUT;

	अगर (!request_muxed_region(KERNCZ_IMC_IDX, 2, "smbus_kerncz_imc"))
		वापस -EBUSY;

	/* clear response रेजिस्टर */
	piix4_imc_ग_लिखो(0x82, 0x00);
	/* request ownership flag */
	piix4_imc_ग_लिखो(0x83, 0xB4);
	/* kick off IMC Mailbox command 96 */
	piix4_imc_ग_लिखो(0x80, 0x96);

	जबतक (समयout--) अणु
		अगर (piix4_imc_पढ़ो(0x82) == 0xfa) अणु
			release_region(KERNCZ_IMC_IDX, 2);
			वापस 0;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	release_region(KERNCZ_IMC_IDX, 2);
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम piix4_imc_wakeup(व्योम)
अणु
	पूर्णांक समयout = MAX_TIMEOUT;

	अगर (!request_muxed_region(KERNCZ_IMC_IDX, 2, "smbus_kerncz_imc"))
		वापस;

	/* clear response रेजिस्टर */
	piix4_imc_ग_लिखो(0x82, 0x00);
	/* release ownership flag */
	piix4_imc_ग_लिखो(0x83, 0xB5);
	/* kick off IMC Mailbox command 96 */
	piix4_imc_ग_लिखो(0x80, 0x96);

	जबतक (समयout--) अणु
		अगर (piix4_imc_पढ़ो(0x82) == 0xfa)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	release_region(KERNCZ_IMC_IDX, 2);
पूर्ण

/*
 * Handles access to multiple SMBus ports on the SB800.
 * The port is selected by bits 2:1 of the smb_en रेजिस्टर (0x2c).
 * Returns negative त्रुटि_सं on error.
 *
 * Note: The selected port must be वापसed to the initial selection to aव्योम
 * problems on certain प्रणालीs.
 */
अटल s32 piix4_access_sb800(काष्ठा i2c_adapter *adap, u16 addr,
		 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		 u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);
	अचिन्हित लघु piix4_smba = adapdata->smba;
	पूर्णांक retries = MAX_TIMEOUT;
	पूर्णांक smbslvcnt;
	u8 smba_en_lo;
	u8 port;
	पूर्णांक retval;

	अगर (!request_muxed_region(SB800_PIIX4_SMB_IDX, 2, "sb800_piix4_smb"))
		वापस -EBUSY;

	/* Request the SMBUS semaphore, aव्योम conflicts with the IMC */
	smbslvcnt  = inb_p(SMBSLVCNT);
	करो अणु
		outb_p(smbslvcnt | 0x10, SMBSLVCNT);

		/* Check the semaphore status */
		smbslvcnt  = inb_p(SMBSLVCNT);
		अगर (smbslvcnt & 0x10)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (--retries);
	/* SMBus is still owned by the IMC, we give up */
	अगर (!retries) अणु
		retval = -EBUSY;
		जाओ release;
	पूर्ण

	/*
	 * Notअगरy the IMC (Integrated Micro Controller) अगर required.
	 * Among other responsibilities, the IMC is in अक्षरge of monitoring
	 * the System fans and temperature sensors, and act accordingly.
	 * All this is करोne through SMBus and can/will collide
	 * with our transactions अगर they are दीर्घ (BLOCK_DATA).
	 * Thereक्रमe we need to request the ownership flag during those
	 * transactions.
	 */
	अगर ((size == I2C_SMBUS_BLOCK_DATA) && adapdata->notअगरy_imc) अणु
		पूर्णांक ret;

		ret = piix4_imc_sleep();
		चयन (ret) अणु
		हाल -EBUSY:
			dev_warn(&adap->dev,
				 "IMC base address index region 0x%x already in use.\n",
				 KERNCZ_IMC_IDX);
			अवरोध;
		हाल -ETIMEDOUT:
			dev_warn(&adap->dev,
				 "Failed to communicate with the IMC.\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* If IMC communication fails करो not retry */
		अगर (ret) अणु
			dev_warn(&adap->dev,
				 "Continuing without IMC notification.\n");
			adapdata->notअगरy_imc = false;
		पूर्ण
	पूर्ण

	outb_p(piix4_port_sel_sb800, SB800_PIIX4_SMB_IDX);
	smba_en_lo = inb_p(SB800_PIIX4_SMB_IDX + 1);

	port = adapdata->port;
	अगर ((smba_en_lo & piix4_port_mask_sb800) != port)
		outb_p((smba_en_lo & ~piix4_port_mask_sb800) | port,
		       SB800_PIIX4_SMB_IDX + 1);

	retval = piix4_access(adap, addr, flags, पढ़ो_ग_लिखो,
			      command, size, data);

	outb_p(smba_en_lo, SB800_PIIX4_SMB_IDX + 1);

	/* Release the semaphore */
	outb_p(smbslvcnt | 0x20, SMBSLVCNT);

	अगर ((size == I2C_SMBUS_BLOCK_DATA) && adapdata->notअगरy_imc)
		piix4_imc_wakeup();

release:
	release_region(SB800_PIIX4_SMB_IDX, 2);
	वापस retval;
पूर्ण

अटल u32 piix4_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= piix4_access,
	.functionality	= piix4_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm piix4_smbus_algorithm_sb800 = अणु
	.smbus_xfer	= piix4_access_sb800,
	.functionality	= piix4_func,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id piix4_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443MX_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP200_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP300_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_HUDSON2_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_KERNCZ_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HYGON, PCI_DEVICE_ID_AMD_KERNCZ_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS,
		     PCI_DEVICE_ID_SERVERWORKS_OSB4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS,
		     PCI_DEVICE_ID_SERVERWORKS_CSB5) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS,
		     PCI_DEVICE_ID_SERVERWORKS_CSB6) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS,
		     PCI_DEVICE_ID_SERVERWORKS_HT1000SB) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SERVERWORKS,
		     PCI_DEVICE_ID_SERVERWORKS_HT1100LD) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, piix4_ids);

अटल काष्ठा i2c_adapter *piix4_मुख्य_adapters[PIIX4_MAX_ADAPTERS];
अटल काष्ठा i2c_adapter *piix4_aux_adapter;
अटल पूर्णांक piix4_adapter_count;

अटल पूर्णांक piix4_add_adapter(काष्ठा pci_dev *dev, अचिन्हित लघु smba,
			     bool sb800_मुख्य, u8 port, bool notअगरy_imc,
			     u8 hw_port_nr, स्थिर अक्षर *name,
			     काष्ठा i2c_adapter **padap)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_piix4_adapdata *adapdata;
	पूर्णांक retval;

	adap = kzalloc(माप(*adap), GFP_KERNEL);
	अगर (adap == शून्य) अणु
		release_region(smba, SMBIOSIZE);
		वापस -ENOMEM;
	पूर्ण

	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adap->algo = sb800_मुख्य ? &piix4_smbus_algorithm_sb800
				: &smbus_algorithm;

	adapdata = kzalloc(माप(*adapdata), GFP_KERNEL);
	अगर (adapdata == शून्य) अणु
		kमुक्त(adap);
		release_region(smba, SMBIOSIZE);
		वापस -ENOMEM;
	पूर्ण

	adapdata->smba = smba;
	adapdata->sb800_मुख्य = sb800_मुख्य;
	adapdata->port = port << piix4_port_shअगरt_sb800;
	adapdata->notअगरy_imc = notअगरy_imc;

	/* set up the sysfs linkage to our parent device */
	adap->dev.parent = &dev->dev;

	अगर (has_acpi_companion(&dev->dev)) अणु
		acpi_preset_companion(&adap->dev,
				      ACPI_COMPANION(&dev->dev),
				      hw_port_nr);
	पूर्ण

	snम_लिखो(adap->name, माप(adap->name),
		"SMBus PIIX4 adapter%s at %04x", name, smba);

	i2c_set_adapdata(adap, adapdata);

	retval = i2c_add_adapter(adap);
	अगर (retval) अणु
		kमुक्त(adapdata);
		kमुक्त(adap);
		release_region(smba, SMBIOSIZE);
		वापस retval;
	पूर्ण

	*padap = adap;
	वापस 0;
पूर्ण

अटल पूर्णांक piix4_add_adapters_sb800(काष्ठा pci_dev *dev, अचिन्हित लघु smba,
				    bool notअगरy_imc)
अणु
	काष्ठा i2c_piix4_adapdata *adapdata;
	पूर्णांक port;
	पूर्णांक retval;

	अगर (dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ||
	    (dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     dev->revision >= 0x1F)) अणु
		piix4_adapter_count = HUDSON2_MAIN_PORTS;
	पूर्ण अन्यथा अणु
		piix4_adapter_count = PIIX4_MAX_ADAPTERS;
	पूर्ण

	क्रम (port = 0; port < piix4_adapter_count; port++) अणु
		u8 hw_port_nr = port == 0 ? 0 : port + 1;

		retval = piix4_add_adapter(dev, smba, true, port, notअगरy_imc,
					   hw_port_nr,
					   piix4_मुख्य_port_names_sb800[port],
					   &piix4_मुख्य_adapters[port]);
		अगर (retval < 0)
			जाओ error;
	पूर्ण

	वापस retval;

error:
	dev_err(&dev->dev,
		"Error setting up SB800 adapters. Unregistering!\n");
	जबतक (--port >= 0) अणु
		adapdata = i2c_get_adapdata(piix4_मुख्य_adapters[port]);
		अगर (adapdata->smba) अणु
			i2c_del_adapter(piix4_मुख्य_adapters[port]);
			kमुक्त(adapdata);
			kमुक्त(piix4_मुख्य_adapters[port]);
			piix4_मुख्य_adapters[port] = शून्य;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक piix4_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक retval;
	bool is_sb800 = false;

	अगर ((dev->venकरोr == PCI_VENDOR_ID_ATI &&
	     dev->device == PCI_DEVICE_ID_ATI_SBX00_SMBUS &&
	     dev->revision >= 0x40) ||
	    dev->venकरोr == PCI_VENDOR_ID_AMD ||
	    dev->venकरोr == PCI_VENDOR_ID_HYGON) अणु
		bool notअगरy_imc = false;
		is_sb800 = true;

		अगर ((dev->venकरोr == PCI_VENDOR_ID_AMD ||
		     dev->venकरोr == PCI_VENDOR_ID_HYGON) &&
		    dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS) अणु
			u8 imc;

			/*
			 * Detect अगर IMC is active or not, this method is
			 * described on coreboot's AMD IMC notes
			 */
			pci_bus_पढ़ो_config_byte(dev->bus, PCI_DEVFN(0x14, 3),
						 0x40, &imc);
			अगर (imc & 0x80)
				notअगरy_imc = true;
		पूर्ण

		/* base address location etc changed in SB800 */
		retval = piix4_setup_sb800(dev, id, 0);
		अगर (retval < 0)
			वापस retval;

		/*
		 * Try to रेजिस्टर multiplexed मुख्य SMBus adapter,
		 * give up अगर we can't
		 */
		retval = piix4_add_adapters_sb800(dev, retval, notअगरy_imc);
		अगर (retval < 0)
			वापस retval;
	पूर्ण अन्यथा अणु
		retval = piix4_setup(dev, id);
		अगर (retval < 0)
			वापस retval;

		/* Try to रेजिस्टर मुख्य SMBus adapter, give up अगर we can't */
		retval = piix4_add_adapter(dev, retval, false, 0, false, 0,
					   "", &piix4_मुख्य_adapters[0]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	/* Check क्रम auxiliary SMBus on some AMD chipsets */
	retval = -ENODEV;

	अगर (dev->venकरोr == PCI_VENDOR_ID_ATI &&
	    dev->device == PCI_DEVICE_ID_ATI_SBX00_SMBUS) अणु
		अगर (dev->revision < 0x40) अणु
			retval = piix4_setup_aux(dev, id, 0x58);
		पूर्ण अन्यथा अणु
			/* SB800 added aux bus too */
			retval = piix4_setup_sb800(dev, id, 1);
		पूर्ण
	पूर्ण

	अगर (dev->venकरोr == PCI_VENDOR_ID_AMD &&
	    (dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ||
	     dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS)) अणु
		retval = piix4_setup_sb800(dev, id, 1);
	पूर्ण

	अगर (retval > 0) अणु
		/* Try to add the aux adapter अगर it exists,
		 * piix4_add_adapter will clean up अगर this fails */
		piix4_add_adapter(dev, retval, false, 0, false, 1,
				  is_sb800 ? piix4_aux_port_name_sb800 : "",
				  &piix4_aux_adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम piix4_adap_हटाओ(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);

	अगर (adapdata->smba) अणु
		i2c_del_adapter(adap);
		अगर (adapdata->port == (0 << piix4_port_shअगरt_sb800))
			release_region(adapdata->smba, SMBIOSIZE);
		kमुक्त(adapdata);
		kमुक्त(adap);
	पूर्ण
पूर्ण

अटल व्योम piix4_हटाओ(काष्ठा pci_dev *dev)
अणु
	पूर्णांक port = piix4_adapter_count;

	जबतक (--port >= 0) अणु
		अगर (piix4_मुख्य_adapters[port]) अणु
			piix4_adap_हटाओ(piix4_मुख्य_adapters[port]);
			piix4_मुख्य_adapters[port] = शून्य;
		पूर्ण
	पूर्ण

	अगर (piix4_aux_adapter) अणु
		piix4_adap_हटाओ(piix4_aux_adapter);
		piix4_aux_adapter = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver piix4_driver = अणु
	.name		= "piix4_smbus",
	.id_table	= piix4_ids,
	.probe		= piix4_probe,
	.हटाओ		= piix4_हटाओ,
पूर्ण;

module_pci_driver(piix4_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_AUTHOR("Philip Edelbrock <phil@netroedge.com>");
MODULE_DESCRIPTION("PIIX4 SMBus driver");
MODULE_LICENSE("GPL");
