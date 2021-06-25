<शैली गुरु>
/*
 * Product specअगरic probe and attach routines क्रम:
 *	aic7901 and aic7902 SCSI controllers
 *
 * Copyright (c) 1994-2001 Justin T. Gibbs.
 * Copyright (c) 2000-2002 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx_pci.c#92 $
 */

#समावेश "aic79xx_osm.h"
#समावेश "aic79xx_inline.h"
#समावेश "aic79xx_pci.h"

अटल अंतरभूत uपूर्णांक64_t
ahd_compose_id(u_पूर्णांक device, u_पूर्णांक venकरोr, u_पूर्णांक subdevice, u_पूर्णांक subvenकरोr)
अणु
	uपूर्णांक64_t id;

	id = subvenकरोr
	   | (subdevice << 16)
	   | ((uपूर्णांक64_t)venकरोr << 32)
	   | ((uपूर्णांक64_t)device << 48);

	वापस (id);
पूर्ण

#घोषणा ID_AIC7902_PCI_REV_A4		0x3
#घोषणा ID_AIC7902_PCI_REV_B0		0x10
#घोषणा SUBID_HP			0x0E11

#घोषणा DEVID_9005_HOSTRAID(id) ((id) & 0x80)

#घोषणा DEVID_9005_TYPE(id) ((id) & 0xF)
#घोषणा		DEVID_9005_TYPE_HBA		0x0	/* Standard Card */
#घोषणा		DEVID_9005_TYPE_HBA_2EXT	0x1	/* 2 External Ports */
#घोषणा		DEVID_9005_TYPE_IROC		0x8	/* Raid(0,1,10) Card */
#घोषणा		DEVID_9005_TYPE_MB		0xF	/* On Motherboard */

#घोषणा DEVID_9005_MFUNC(id) ((id) & 0x10)

#घोषणा DEVID_9005_PACKETIZED(id) ((id) & 0x8000)

#घोषणा SUBID_9005_TYPE(id) ((id) & 0xF)
#घोषणा		SUBID_9005_TYPE_HBA		0x0	/* Standard Card */
#घोषणा		SUBID_9005_TYPE_MB		0xF	/* On Motherboard */

#घोषणा SUBID_9005_AUTOTERM(id)	(((id) & 0x10) == 0)

#घोषणा SUBID_9005_LEGACYCONN_FUNC(id) ((id) & 0x20)

#घोषणा SUBID_9005_SEEPTYPE(id) (((id) & 0x0C0) >> 6)
#घोषणा		SUBID_9005_SEEPTYPE_NONE	0x0
#घोषणा		SUBID_9005_SEEPTYPE_4K		0x1

अटल ahd_device_setup_t ahd_aic7901_setup;
अटल ahd_device_setup_t ahd_aic7901A_setup;
अटल ahd_device_setup_t ahd_aic7902_setup;
अटल ahd_device_setup_t ahd_aic790X_setup;

अटल स्थिर काष्ठा ahd_pci_identity ahd_pci_ident_table[] =
अणु
	/* aic7901 based controllers */
	अणु
		ID_AHA_29320A,
		ID_ALL_MASK,
		"Adaptec 29320A Ultra320 SCSI adapter",
		ahd_aic7901_setup
	पूर्ण,
	अणु
		ID_AHA_29320ALP,
		ID_ALL_MASK,
		"Adaptec 29320ALP PCIx Ultra320 SCSI adapter",
		ahd_aic7901_setup
	पूर्ण,
	अणु
		ID_AHA_29320LPE,
		ID_ALL_MASK,
		"Adaptec 29320LPE PCIe Ultra320 SCSI adapter",
		ahd_aic7901_setup
	पूर्ण,
	/* aic7901A based controllers */
	अणु
		ID_AHA_29320LP,
		ID_ALL_MASK,
		"Adaptec 29320LP Ultra320 SCSI adapter",
		ahd_aic7901A_setup
	पूर्ण,
	/* aic7902 based controllers */	
	अणु
		ID_AHA_29320,
		ID_ALL_MASK,
		"Adaptec 29320 Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_29320B,
		ID_ALL_MASK,
		"Adaptec 29320B Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320,
		ID_ALL_MASK,
		"Adaptec 39320 Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320_B,
		ID_ALL_MASK,
		"Adaptec 39320 Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320_B_DELL,
		ID_ALL_MASK,
		"Adaptec (Dell OEM) 39320 Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320A,
		ID_ALL_MASK,
		"Adaptec 39320A Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320D,
		ID_ALL_MASK,
		"Adaptec 39320D Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320D_HP,
		ID_ALL_MASK,
		"Adaptec (HP OEM) 39320D Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320D_B,
		ID_ALL_MASK,
		"Adaptec 39320D Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	अणु
		ID_AHA_39320D_B_HP,
		ID_ALL_MASK,
		"Adaptec (HP OEM) 39320D Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण,
	/* Generic chip probes क्रम devices we करोn't know 'exactly' */
	अणु
		ID_AIC7901 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec AIC7901 Ultra320 SCSI adapter",
		ahd_aic7901_setup
	पूर्ण,
	अणु
		ID_AIC7901A & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec AIC7901A Ultra320 SCSI adapter",
		ahd_aic7901A_setup
	पूर्ण,
	अणु
		ID_AIC7902 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec AIC7902 Ultra320 SCSI adapter",
		ahd_aic7902_setup
	पूर्ण
पूर्ण;

अटल स्थिर u_पूर्णांक ahd_num_pci_devs = ARRAY_SIZE(ahd_pci_ident_table);
		
#घोषणा	DEVCONFIG		0x40
#घोषणा		PCIXINITPAT	0x0000E000ul
#घोषणा			PCIXINIT_PCI33_66	0x0000E000ul
#घोषणा			PCIXINIT_PCIX50_66	0x0000C000ul
#घोषणा			PCIXINIT_PCIX66_100	0x0000A000ul
#घोषणा			PCIXINIT_PCIX100_133	0x00008000ul
#घोषणा	PCI_BUS_MODES_INDEX(devconfig)	\
	(((devconfig) & PCIXINITPAT) >> 13)
अटल स्थिर अक्षर *pci_bus_modes[] =
अणु
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI bus mode unknown",
	"PCI-X 101-133MHz",
	"PCI-X 67-100MHz",
	"PCI-X 50-66MHz",
	"PCI 33 or 66MHz"
पूर्ण;

#घोषणा		TESTMODE	0x00000800ul
#घोषणा		IRDY_RST	0x00000200ul
#घोषणा		FRAME_RST	0x00000100ul
#घोषणा		PCI64BIT	0x00000080ul
#घोषणा		MRDCEN		0x00000040ul
#घोषणा		ENDIANSEL	0x00000020ul
#घोषणा		MIXQWENDIANEN	0x00000008ul
#घोषणा		DACEN		0x00000004ul
#घोषणा		STPWLEVEL	0x00000002ul
#घोषणा		QWENDIANSEL	0x00000001ul

#घोषणा	DEVCONFIG1		0x44
#घोषणा		PREQDIS		0x01

#घोषणा	CSIZE_LATTIME		0x0c
#घोषणा		CACHESIZE	0x000000fful
#घोषणा		LATTIME		0x0000ff00ul

अटल पूर्णांक	ahd_check_extport(काष्ठा ahd_softc *ahd);
अटल व्योम	ahd_configure_termination(काष्ठा ahd_softc *ahd,
					  u_पूर्णांक adapter_control);
अटल व्योम	ahd_pci_split_पूर्णांकr(काष्ठा ahd_softc *ahd, u_पूर्णांक पूर्णांकstat);
अटल व्योम	ahd_pci_पूर्णांकr(काष्ठा ahd_softc *ahd);

स्थिर काष्ठा ahd_pci_identity *
ahd_find_pci_device(ahd_dev_softc_t pci)
अणु
	uपूर्णांक64_t  full_id;
	uपूर्णांक16_t  device;
	uपूर्णांक16_t  venकरोr;
	uपूर्णांक16_t  subdevice;
	uपूर्णांक16_t  subvenकरोr;
	स्थिर काष्ठा ahd_pci_identity *entry;
	u_पूर्णांक	  i;

	venकरोr = ahd_pci_पढ़ो_config(pci, PCIR_DEVVENDOR, /*bytes*/2);
	device = ahd_pci_पढ़ो_config(pci, PCIR_DEVICE, /*bytes*/2);
	subvenकरोr = ahd_pci_पढ़ो_config(pci, PCIR_SUBVEND_0, /*bytes*/2);
	subdevice = ahd_pci_पढ़ो_config(pci, PCIR_SUBDEV_0, /*bytes*/2);
	full_id = ahd_compose_id(device,
				 venकरोr,
				 subdevice,
				 subvenकरोr);

	/*
	 * Controllers, mask out the IROC/HostRAID bit
	 */
	
	full_id &= ID_ALL_IROC_MASK;

	क्रम (i = 0; i < ahd_num_pci_devs; i++) अणु
		entry = &ahd_pci_ident_table[i];
		अगर (entry->full_id == (full_id & entry->id_mask)) अणु
			/* Honor exclusion entries. */
			अगर (entry->name == शून्य)
				वापस (शून्य);
			वापस (entry);
		पूर्ण
	पूर्ण
	वापस (शून्य);
पूर्ण

पूर्णांक
ahd_pci_config(काष्ठा ahd_softc *ahd, स्थिर काष्ठा ahd_pci_identity *entry)
अणु
	u_पूर्णांक		 command;
	uपूर्णांक32_t	 devconfig;
	uपूर्णांक16_t	 subvenकरोr; 
	पूर्णांक		 error;

	ahd->description = entry->name;
	/*
	 * Record अगर this is an HP board.
	 */
	subvenकरोr = ahd_pci_पढ़ो_config(ahd->dev_softc,
					PCIR_SUBVEND_0, /*bytes*/2);
	अगर (subvenकरोr == SUBID_HP)
		ahd->flags |= AHD_HP_BOARD;

	error = entry->setup(ahd);
	अगर (error != 0)
		वापस (error);
	
	devconfig = ahd_pci_पढ़ो_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	अगर ((devconfig & PCIXINITPAT) == PCIXINIT_PCI33_66) अणु
		ahd->chip |= AHD_PCI;
		/* Disable PCIX workarounds when running in PCI mode. */
		ahd->bugs &= ~AHD_PCIX_BUG_MASK;
	पूर्ण अन्यथा अणु
		ahd->chip |= AHD_PCIX;
	पूर्ण
	ahd->bus_description = pci_bus_modes[PCI_BUS_MODES_INDEX(devconfig)];

	ahd_घातer_state_change(ahd, AHD_POWER_STATE_D0);

	error = ahd_pci_map_रेजिस्टरs(ahd);
	अगर (error != 0)
		वापस (error);

	/*
	 * If we need to support high memory, enable dual
	 * address cycles.  This bit must be set to enable
	 * high address bit generation even अगर we are on a
	 * 64bit bus (PCI64BIT set in devconfig).
	 */
	अगर ((ahd->flags & (AHD_39BIT_ADDRESSING|AHD_64BIT_ADDRESSING)) != 0) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: Enabling 39Bit Addressing\n",
			       ahd_name(ahd));
		devconfig = ahd_pci_पढ़ो_config(ahd->dev_softc,
						DEVCONFIG, /*bytes*/4);
		devconfig |= DACEN;
		ahd_pci_ग_लिखो_config(ahd->dev_softc, DEVCONFIG,
				     devconfig, /*bytes*/4);
	पूर्ण
	
	/* Ensure busmastering is enabled */
	command = ahd_pci_पढ़ो_config(ahd->dev_softc, PCIR_COMMAND, /*bytes*/2);
	command |= PCIM_CMD_BUSMASTEREN;
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND, command, /*bytes*/2);

	error = ahd_softc_init(ahd);
	अगर (error != 0)
		वापस (error);

	ahd->bus_पूर्णांकr = ahd_pci_पूर्णांकr;

	error = ahd_reset(ahd, /*reinit*/FALSE);
	अगर (error != 0)
		वापस (ENXIO);

	ahd->pci_cachesize =
	    ahd_pci_पढ़ो_config(ahd->dev_softc, CSIZE_LATTIME,
				/*bytes*/1) & CACHESIZE;
	ahd->pci_cachesize *= 4;

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/* See अगर we have a SEEPROM and perक्रमm स्वतः-term */
	error = ahd_check_extport(ahd);
	अगर (error != 0)
		वापस (error);

	/* Core initialization */
	error = ahd_init(ahd);
	अगर (error != 0)
		वापस (error);
	ahd->init_level++;

	/*
	 * Allow पूर्णांकerrupts now that we are completely setup.
	 */
	वापस ahd_pci_map_पूर्णांक(ahd);
पूर्ण

व्योम __maybe_unused
ahd_pci_suspend(काष्ठा ahd_softc *ahd)
अणु
	/*
	 * Save chip रेजिस्टर configuration data क्रम chip resets
	 * that occur during runसमय and resume events.
	 */
	ahd->suspend_state.pci_state.devconfig =
	    ahd_pci_पढ़ो_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	ahd->suspend_state.pci_state.command =
	    ahd_pci_पढ़ो_config(ahd->dev_softc, PCIR_COMMAND, /*bytes*/1);
	ahd->suspend_state.pci_state.csize_latसमय =
	    ahd_pci_पढ़ो_config(ahd->dev_softc, CSIZE_LATTIME, /*bytes*/1);

पूर्ण

व्योम __maybe_unused
ahd_pci_resume(काष्ठा ahd_softc *ahd)
अणु
	ahd_pci_ग_लिखो_config(ahd->dev_softc, DEVCONFIG,
			     ahd->suspend_state.pci_state.devconfig, /*bytes*/4);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND,
			     ahd->suspend_state.pci_state.command, /*bytes*/1);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, CSIZE_LATTIME,
			     ahd->suspend_state.pci_state.csize_latसमय, /*bytes*/1);
पूर्ण

/*
 * Perक्रमm some simple tests that should catch situations where
 * our रेजिस्टरs are invalidly mapped.
 */
पूर्णांक
ahd_pci_test_रेजिस्टर_access(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक32_t cmd;
	u_पूर्णांक	 targpcistat;
	u_पूर्णांक	 pci_status1;
	पूर्णांक	 error;
	uपूर्णांक8_t	 hcntrl;

	error = EIO;

	/*
	 * Enable PCI error पूर्णांकerrupt status, but suppress NMIs
	 * generated by SERR उठाओd due to target पातs.
	 */
	cmd = ahd_pci_पढ़ो_config(ahd->dev_softc, PCIR_COMMAND, /*bytes*/2);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND,
			     cmd & ~PCIM_CMD_SERRESPEN, /*bytes*/2);

	/*
	 * First a simple test to see अगर any
	 * रेजिस्टरs can be पढ़ो.  Reading
	 * HCNTRL has no side effects and has
	 * at least one bit that is guaranteed to
	 * be zero so it is a good रेजिस्टर to
	 * use क्रम this test.
	 */
	hcntrl = ahd_inb(ahd, HCNTRL);
	अगर (hcntrl == 0xFF)
		जाओ fail;

	/*
	 * Next create a situation where ग_लिखो combining
	 * or पढ़ो prefetching could be initiated by the
	 * CPU or host bridge.  Our device करोes not support
	 * either, so look क्रम data corruption and/or flaged
	 * PCI errors.  First छोड़ो without causing another
	 * chip reset.
	 */
	hcntrl &= ~CHIPRST;
	ahd_outb(ahd, HCNTRL, hcntrl|PAUSE);
	जबतक (ahd_is_छोड़ोd(ahd) == 0)
		;

	/* Clear any PCI errors that occurred beक्रमe our driver attached. */
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	targpcistat = ahd_inb(ahd, TARGPCISTAT);
	ahd_outb(ahd, TARGPCISTAT, targpcistat);
	pci_status1 = ahd_pci_पढ़ो_config(ahd->dev_softc,
					  PCIR_STATUS + 1, /*bytes*/1);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_STATUS + 1,
			     pci_status1, /*bytes*/1);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRINT, CLRPCIINT);

	ahd_outb(ahd, SEQCTL0, PERRORDIS);
	ahd_outl(ahd, SRAM_BASE, 0x5aa555aa);
	अगर (ahd_inl(ahd, SRAM_BASE) != 0x5aa555aa)
		जाओ fail;

	अगर ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) अणु
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		targpcistat = ahd_inb(ahd, TARGPCISTAT);
		अगर ((targpcistat & STA) != 0)
			जाओ fail;
	पूर्ण

	error = 0;

fail:
	अगर ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) अणु

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		targpcistat = ahd_inb(ahd, TARGPCISTAT);

		/* Silently clear any latched errors. */
		ahd_outb(ahd, TARGPCISTAT, targpcistat);
		pci_status1 = ahd_pci_पढ़ो_config(ahd->dev_softc,
						  PCIR_STATUS + 1, /*bytes*/1);
		ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_STATUS + 1,
				     pci_status1, /*bytes*/1);
		ahd_outb(ahd, CLRINT, CLRPCIINT);
	पूर्ण
	ahd_outb(ahd, SEQCTL0, PERRORDIS|FAILDIS);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND, cmd, /*bytes*/2);
	वापस (error);
पूर्ण

/*
 * Check the बाह्यal port logic क्रम a serial eeprom
 * and termination/cable detection contrls.
 */
अटल पूर्णांक
ahd_check_extport(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	vpd_config vpd;
	काष्ठा	seeprom_config *sc;
	u_पूर्णांक	adapter_control;
	पूर्णांक	have_seeprom;
	पूर्णांक	error;

	sc = ahd->seep_config;
	have_seeprom = ahd_acquire_seeprom(ahd);
	अगर (have_seeprom) अणु
		u_पूर्णांक start_addr;

		/*
		 * Fetch VPD क्रम this function and parse it.
		 */
		अगर (bootverbose) 
			prपूर्णांकk("%s: Reading VPD from SEEPROM...",
			       ahd_name(ahd));

		/* Address is always in units of 16bit words */
		start_addr = ((2 * माप(*sc))
			    + (माप(vpd) * (ahd->channel - 'A'))) / 2;

		error = ahd_पढ़ो_seeprom(ahd, (uपूर्णांक16_t *)&vpd,
					 start_addr, माप(vpd)/2,
					 /*bytestream*/TRUE);
		अगर (error == 0)
			error = ahd_parse_vpddata(ahd, &vpd);
		अगर (bootverbose) 
			prपूर्णांकk("%s: VPD parsing %s\n",
			       ahd_name(ahd),
			       error == 0 ? "successful" : "failed");

		अगर (bootverbose) 
			prपूर्णांकk("%s: Reading SEEPROM...", ahd_name(ahd));

		/* Address is always in units of 16bit words */
		start_addr = (माप(*sc) / 2) * (ahd->channel - 'A');

		error = ahd_पढ़ो_seeprom(ahd, (uपूर्णांक16_t *)sc,
					 start_addr, माप(*sc)/2,
					 /*bytestream*/FALSE);

		अगर (error != 0) अणु
			prपूर्णांकk("Unable to read SEEPROM\n");
			have_seeprom = 0;
		पूर्ण अन्यथा अणु
			have_seeprom = ahd_verअगरy_cksum(sc);

			अगर (bootverbose) अणु
				अगर (have_seeprom == 0)
					prपूर्णांकk ("checksum error\n");
				अन्यथा
					prपूर्णांकk ("done.\n");
			पूर्ण
		पूर्ण
		ahd_release_seeprom(ahd);
	पूर्ण

	अगर (!have_seeprom) अणु
		u_पूर्णांक	  nvram_scb;

		/*
		 * Pull scratch ram settings and treat them as
		 * अगर they are the contents of an seeprom अगर
		 * the 'ADPT', 'BIOS', or 'ASPI' signature is found
		 * in SCB 0xFF.  We manually compose the data as 16bit
		 * values to aव्योम endian issues.
		 */
		ahd_set_scbptr(ahd, 0xFF);
		nvram_scb = ahd_inb_scbram(ahd, SCB_BASE + NVRAM_SCB_OFFSET);
		अगर (nvram_scb != 0xFF
		 && ((ahd_inb_scbram(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'D'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'T')
		  || (ahd_inb_scbram(ahd, SCB_BASE + 0) == 'B'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'I'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'O'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'S')
		  || (ahd_inb_scbram(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'S'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'I'))) अणु
			uपूर्णांक16_t *sc_data;
			पूर्णांक	  i;

			ahd_set_scbptr(ahd, nvram_scb);
			sc_data = (uपूर्णांक16_t *)sc;
			क्रम (i = 0; i < 64; i += 2)
				*sc_data++ = ahd_inw_scbram(ahd, SCB_BASE+i);
			have_seeprom = ahd_verअगरy_cksum(sc);
			अगर (have_seeprom)
				ahd->flags |= AHD_SCB_CONFIG_USED;
		पूर्ण
	पूर्ण

#अगर_घोषित AHD_DEBUG
	अगर (have_seeprom != 0
	 && (ahd_debug & AHD_DUMP_SEEPROM) != 0) अणु
		uपूर्णांक16_t *sc_data;
		पूर्णांक	  i;

		prपूर्णांकk("%s: Seeprom Contents:", ahd_name(ahd));
		sc_data = (uपूर्णांक16_t *)sc;
		क्रम (i = 0; i < (माप(*sc)); i += 2)
			prपूर्णांकk("\n\t0x%.4x", sc_data[i]);
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर

	अगर (!have_seeprom) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: No SEEPROM available.\n", ahd_name(ahd));
		ahd->flags |= AHD_USEDEFAULTS;
		error = ahd_शेष_config(ahd);
		adapter_control = CFAUTOTERM|CFSEAUTOTERM;
		kमुक्त(ahd->seep_config);
		ahd->seep_config = शून्य;
	पूर्ण अन्यथा अणु
		error = ahd_parse_cfgdata(ahd, sc);
		adapter_control = sc->adapter_control;
	पूर्ण
	अगर (error != 0)
		वापस (error);

	ahd_configure_termination(ahd, adapter_control);

	वापस (0);
पूर्ण

अटल व्योम
ahd_configure_termination(काष्ठा ahd_softc *ahd, u_पूर्णांक adapter_control)
अणु
	पूर्णांक	 error;
	u_पूर्णांक	 sxfrctl1;
	uपूर्णांक8_t	 termctl;
	uपूर्णांक32_t devconfig;

	devconfig = ahd_pci_पढ़ो_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	devconfig &= ~STPWLEVEL;
	अगर ((ahd->flags & AHD_STPWLEVEL_A) != 0)
		devconfig |= STPWLEVEL;
	अगर (bootverbose)
		prपूर्णांकk("%s: STPWLEVEL is %s\n",
		       ahd_name(ahd), (devconfig & STPWLEVEL) ? "on" : "off");
	ahd_pci_ग_लिखो_config(ahd->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);
 
	/* Make sure current sensing is off. */
	अगर ((ahd->flags & AHD_CURRENT_SENSING) != 0) अणु
		(व्योम)ahd_ग_लिखो_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, 0);
	पूर्ण

	/*
	 * Read to sense.  Write to set.
	 */
	error = ahd_पढ़ो_flexport(ahd, FLXADDR_TERMCTL, &termctl);
	अगर ((adapter_control & CFAUTOTERM) == 0) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: Manual Primary Termination\n",
			       ahd_name(ahd));
		termctl &= ~(FLX_TERMCTL_ENPRILOW|FLX_TERMCTL_ENPRIHIGH);
		अगर ((adapter_control & CFSTERM) != 0)
			termctl |= FLX_TERMCTL_ENPRILOW;
		अगर ((adapter_control & CFWSTERM) != 0)
			termctl |= FLX_TERMCTL_ENPRIHIGH;
	पूर्ण अन्यथा अगर (error != 0) अणु
		prपूर्णांकk("%s: Primary Auto-Term Sensing failed! "
		       "Using Defaults.\n", ahd_name(ahd));
		termctl = FLX_TERMCTL_ENPRILOW|FLX_TERMCTL_ENPRIHIGH;
	पूर्ण

	अगर ((adapter_control & CFSEAUTOTERM) == 0) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: Manual Secondary Termination\n",
			       ahd_name(ahd));
		termctl &= ~(FLX_TERMCTL_ENSECLOW|FLX_TERMCTL_ENSECHIGH);
		अगर ((adapter_control & CFSELOWTERM) != 0)
			termctl |= FLX_TERMCTL_ENSECLOW;
		अगर ((adapter_control & CFSEHIGHTERM) != 0)
			termctl |= FLX_TERMCTL_ENSECHIGH;
	पूर्ण अन्यथा अगर (error != 0) अणु
		prपूर्णांकk("%s: Secondary Auto-Term Sensing failed! "
		       "Using Defaults.\n", ahd_name(ahd));
		termctl |= FLX_TERMCTL_ENSECLOW|FLX_TERMCTL_ENSECHIGH;
	पूर्ण

	/*
	 * Now set the termination based on what we found.
	 */
	sxfrctl1 = ahd_inb(ahd, SXFRCTL1) & ~STPWEN;
	ahd->flags &= ~AHD_TERM_ENB_A;
	अगर ((termctl & FLX_TERMCTL_ENPRILOW) != 0) अणु
		ahd->flags |= AHD_TERM_ENB_A;
		sxfrctl1 |= STPWEN;
	पूर्ण
	/* Must set the latch once in order to be effective. */
	ahd_outb(ahd, SXFRCTL1, sxfrctl1|STPWEN);
	ahd_outb(ahd, SXFRCTL1, sxfrctl1);

	error = ahd_ग_लिखो_flexport(ahd, FLXADDR_TERMCTL, termctl);
	अगर (error != 0) अणु
		prपूर्णांकk("%s: Unable to set termination settings!\n",
		       ahd_name(ahd));
	पूर्ण अन्यथा अगर (bootverbose) अणु
		prपूर्णांकk("%s: Primary High byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENPRIHIGH) ? "En" : "Dis");

		prपूर्णांकk("%s: Primary Low byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENPRILOW) ? "En" : "Dis");

		prपूर्णांकk("%s: Secondary High byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENSECHIGH) ? "En" : "Dis");

		prपूर्णांकk("%s: Secondary Low byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENSECLOW) ? "En" : "Dis");
	पूर्ण
	वापस;
पूर्ण

#घोषणा	DPE	0x80
#घोषणा SSE	0x40
#घोषणा	RMA	0x20
#घोषणा	RTA	0x10
#घोषणा STA	0x08
#घोषणा DPR	0x01

अटल स्थिर अक्षर *split_status_source[] =
अणु
	"DFF0",
	"DFF1",
	"OVLY",
	"CMC",
पूर्ण;

अटल स्थिर अक्षर *pci_status_source[] =
अणु
	"DFF0",
	"DFF1",
	"SG",
	"CMC",
	"OVLY",
	"NONE",
	"MSI",
	"TARG"
पूर्ण;

अटल स्थिर अक्षर *split_status_strings[] =
अणु
	"%s: Received split response in %s.\n",
	"%s: Received split completion error message in %s\n",
	"%s: Receive overrun in %s\n",
	"%s: Count not complete in %s\n",
	"%s: Split completion data bucket in %s\n",
	"%s: Split completion address error in %s\n",
	"%s: Split completion byte count error in %s\n",
	"%s: Signaled Target-abort to early terminate a split in %s\n"
पूर्ण;

अटल स्थिर अक्षर *pci_status_strings[] =
अणु
	"%s: Data Parity Error has been reported via PERR# in %s\n",
	"%s: Target initial wait state error in %s\n",
	"%s: Split completion read data parity error in %s\n",
	"%s: Split completion address attribute parity error in %s\n",
	"%s: Received a Target Abort in %s\n",
	"%s: Received a Master Abort in %s\n",
	"%s: Signal System Error Detected in %s\n",
	"%s: Address or Write Phase Parity Error Detected in %s.\n"
पूर्ण;

अटल व्योम
ahd_pci_पूर्णांकr(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक8_t		pci_status[8];
	ahd_mode_state	saved_modes;
	u_पूर्णांक		pci_status1;
	u_पूर्णांक		पूर्णांकstat;
	u_पूर्णांक		i;
	u_पूर्णांक		reg;
	
	पूर्णांकstat = ahd_inb(ahd, INTSTAT);

	अगर ((पूर्णांकstat & SPLTINT) != 0)
		ahd_pci_split_पूर्णांकr(ahd, पूर्णांकstat);

	अगर ((पूर्णांकstat & PCIINT) == 0)
		वापस;

	prपूर्णांकk("%s: PCI error Interrupt\n", ahd_name(ahd));
	saved_modes = ahd_save_modes(ahd);
	ahd_dump_card_state(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	क्रम (i = 0, reg = DF0PCISTAT; i < 8; i++, reg++) अणु

		अगर (i == 5)
			जारी;
		pci_status[i] = ahd_inb(ahd, reg);
		/* Clear latched errors.  So our पूर्णांकerrupt deनिश्चितs. */
		ahd_outb(ahd, reg, pci_status[i]);
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		u_पूर्णांक bit;
	
		अगर (i == 5)
			जारी;

		क्रम (bit = 0; bit < 8; bit++) अणु

			अगर ((pci_status[i] & (0x1 << bit)) != 0) अणु
				स्थिर अक्षर *s;

				s = pci_status_strings[bit];
				अगर (i == 7/*TARG*/ && bit == 3)
					s = "%s: Signaled Target Abort\n";
				prपूर्णांकk(s, ahd_name(ahd), pci_status_source[i]);
			पूर्ण
		पूर्ण	
	पूर्ण
	pci_status1 = ahd_pci_पढ़ो_config(ahd->dev_softc,
					  PCIR_STATUS + 1, /*bytes*/1);
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_STATUS + 1,
			     pci_status1, /*bytes*/1);
	ahd_restore_modes(ahd, saved_modes);
	ahd_outb(ahd, CLRINT, CLRPCIINT);
	ahd_unछोड़ो(ahd);
पूर्ण

अटल व्योम
ahd_pci_split_पूर्णांकr(काष्ठा ahd_softc *ahd, u_पूर्णांक पूर्णांकstat)
अणु
	uपूर्णांक8_t		split_status[4];
	uपूर्णांक8_t		split_status1[4];
	uपूर्णांक8_t		sg_split_status[2];
	uपूर्णांक8_t		sg_split_status1[2];
	ahd_mode_state	saved_modes;
	u_पूर्णांक		i;
	uपूर्णांक16_t	pcix_status;

	/*
	 * Check क्रम splits in all modes.  Modes 0 and 1
	 * additionally have SG engine splits to look at.
	 */
	pcix_status = ahd_pci_पढ़ो_config(ahd->dev_softc, PCIXR_STATUS,
					  /*bytes*/2);
	prपूर्णांकk("%s: PCI Split Interrupt - PCI-X status = 0x%x\n",
	       ahd_name(ahd), pcix_status);
	saved_modes = ahd_save_modes(ahd);
	क्रम (i = 0; i < 4; i++) अणु
		ahd_set_modes(ahd, i, i);

		split_status[i] = ahd_inb(ahd, DCHSPLTSTAT0);
		split_status1[i] = ahd_inb(ahd, DCHSPLTSTAT1);
		/* Clear latched errors.  So our पूर्णांकerrupt deनिश्चितs. */
		ahd_outb(ahd, DCHSPLTSTAT0, split_status[i]);
		ahd_outb(ahd, DCHSPLTSTAT1, split_status1[i]);
		अगर (i > 1)
			जारी;
		sg_split_status[i] = ahd_inb(ahd, SGSPLTSTAT0);
		sg_split_status1[i] = ahd_inb(ahd, SGSPLTSTAT1);
		/* Clear latched errors.  So our पूर्णांकerrupt deनिश्चितs. */
		ahd_outb(ahd, SGSPLTSTAT0, sg_split_status[i]);
		ahd_outb(ahd, SGSPLTSTAT1, sg_split_status1[i]);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		u_पूर्णांक bit;

		क्रम (bit = 0; bit < 8; bit++) अणु

			अगर ((split_status[i] & (0x1 << bit)) != 0)
				prपूर्णांकk(split_status_strings[bit], ahd_name(ahd),
				       split_status_source[i]);

			अगर (i > 1)
				जारी;

			अगर ((sg_split_status[i] & (0x1 << bit)) != 0)
				prपूर्णांकk(split_status_strings[bit], ahd_name(ahd), "SG");
		पूर्ण
	पूर्ण
	/*
	 * Clear PCI-X status bits.
	 */
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIXR_STATUS,
			     pcix_status, /*bytes*/2);
	ahd_outb(ahd, CLRINT, CLRSPLTINT);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

अटल पूर्णांक
ahd_aic7901_setup(काष्ठा ahd_softc *ahd)
अणु

	ahd->chip = AHD_AIC7901;
	ahd->features = AHD_AIC7901_FE;
	वापस (ahd_aic790X_setup(ahd));
पूर्ण

अटल पूर्णांक
ahd_aic7901A_setup(काष्ठा ahd_softc *ahd)
अणु

	ahd->chip = AHD_AIC7901A;
	ahd->features = AHD_AIC7901A_FE;
	वापस (ahd_aic790X_setup(ahd));
पूर्ण

अटल पूर्णांक
ahd_aic7902_setup(काष्ठा ahd_softc *ahd)
अणु
	ahd->chip = AHD_AIC7902;
	ahd->features = AHD_AIC7902_FE;
	वापस (ahd_aic790X_setup(ahd));
पूर्ण

अटल पूर्णांक
ahd_aic790X_setup(काष्ठा ahd_softc *ahd)
अणु
	ahd_dev_softc_t pci;
	u_पूर्णांक rev;

	pci = ahd->dev_softc;
	rev = ahd_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev < ID_AIC7902_PCI_REV_A4) अणु
		prपूर्णांकk("%s: Unable to attach to unsupported chip revision %d\n",
		       ahd_name(ahd), rev);
		ahd_pci_ग_लिखो_config(pci, PCIR_COMMAND, 0, /*bytes*/2);
		वापस (ENXIO);
	पूर्ण
	ahd->channel = ahd_get_pci_function(pci) + 'A';
	अगर (rev < ID_AIC7902_PCI_REV_B0) अणु
		/*
		 * Enable A series workarounds.
		 */
		ahd->bugs |= AHD_SENT_SCB_UPDATE_BUG|AHD_ABORT_LQI_BUG
			  |  AHD_PKT_BITBUCKET_BUG|AHD_LONG_SETIMO_BUG
			  |  AHD_NLQICRC_DELAYED_BUG|AHD_SCSIRST_BUG
			  |  AHD_LQO_ATNO_BUG|AHD_AUTOFLUSH_BUG
			  |  AHD_CLRLQO_AUTOCLR_BUG|AHD_PCIX_MMAPIO_BUG
			  |  AHD_PCIX_CHIPRST_BUG|AHD_PCIX_SCBRAM_RD_BUG
			  |  AHD_PKTIZED_STATUS_BUG|AHD_PKT_LUN_BUG
			  |  AHD_MDFF_WSCBPTR_BUG|AHD_REG_SLOW_SETTLE_BUG
			  |  AHD_SET_MODE_BUG|AHD_BUSFREEREV_BUG
			  |  AHD_NONPACKFIFO_BUG|AHD_PACED_NEGTABLE_BUG
			  |  AHD_FAINT_LED_BUG;

		/*
		 * IO Cell parameter setup.
		 */
		AHD_SET_PRECOMP(ahd, AHD_PRECOMP_CUTBACK_29);

		अगर ((ahd->flags & AHD_HP_BOARD) == 0)
			AHD_SET_SLEWRATE(ahd, AHD_SLEWRATE_DEF_REVA);
	पूर्ण अन्यथा अणु
		/* This is revision B and newer. */
		बाह्य uपूर्णांक32_t aic79xx_slowcrc;
		u_पूर्णांक devconfig1;

		ahd->features |= AHD_RTI|AHD_NEW_IOCELL_OPTS
			      |  AHD_NEW_DFCNTRL_OPTS|AHD_FAST_CDB_DELIVERY
			      |  AHD_BUSFREEREV_BUG;
		ahd->bugs |= AHD_LQOOVERRUN_BUG|AHD_EARLY_REQ_BUG;

		/* If the user requested that the SLOWCRC bit to be set. */
		अगर (aic79xx_slowcrc)
			ahd->features |= AHD_AIC79XXB_SLOWCRC;

		/*
		 * Some issues have been resolved in the 7901B.
		 */
		अगर ((ahd->features & AHD_MULTI_FUNC) != 0)
			ahd->bugs |= AHD_INTCOLLISION_BUG|AHD_ABORT_LQI_BUG;

		/*
		 * IO Cell parameter setup.
		 */
		AHD_SET_PRECOMP(ahd, AHD_PRECOMP_CUTBACK_29);
		AHD_SET_SLEWRATE(ahd, AHD_SLEWRATE_DEF_REVB);
		AHD_SET_AMPLITUDE(ahd, AHD_AMPLITUDE_DEF);

		/*
		 * Set the PREQDIS bit क्रम H2B which disables some workaround
		 * that करोesn't work on regular PCI busses.
		 * XXX - Find out exactly what this करोes from the hardware
		 * 	 folks!
		 */
		devconfig1 = ahd_pci_पढ़ो_config(pci, DEVCONFIG1, /*bytes*/1);
		ahd_pci_ग_लिखो_config(pci, DEVCONFIG1,
				     devconfig1|PREQDIS, /*bytes*/1);
		devconfig1 = ahd_pci_पढ़ो_config(pci, DEVCONFIG1, /*bytes*/1);
	पूर्ण

	वापस (0);
पूर्ण
