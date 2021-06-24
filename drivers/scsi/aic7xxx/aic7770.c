<शैली गुरु>
/*
 * Product specअगरic probe and attach routines क्रम:
 * 	27/284X and aic7770 motherboard SCSI controllers
 *
 * Copyright (c) 1994-1998, 2000, 2001 Justin T. Gibbs.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7770.c#32 $
 *
 * $FreeBSD$
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_inline.h"
#समावेश "aic7xxx_93cx6.h"

#घोषणा ID_AIC7770	0x04907770
#घोषणा ID_AHA_274x	0x04907771
#घोषणा ID_AHA_284xB	0x04907756 /* BIOS enabled */
#घोषणा ID_AHA_284x	0x04907757 /* BIOS disabled*/
#घोषणा	ID_OLV_274x	0x04907782 /* Olivetti OEM */
#घोषणा	ID_OLV_274xD	0x04907783 /* Olivetti OEM (Dअगरferential) */

अटल पूर्णांक aic7770_chip_init(काष्ठा ahc_softc *ahc);
अटल पूर्णांक aha2840_load_seeprom(काष्ठा ahc_softc *ahc);
अटल ahc_device_setup_t ahc_aic7770_VL_setup;
अटल ahc_device_setup_t ahc_aic7770_EISA_setup;
अटल ahc_device_setup_t ahc_aic7770_setup;

काष्ठा aic7770_identity aic7770_ident_table[] =
अणु
	अणु
		ID_AHA_274x,
		0xFFFFFFFF,
		"Adaptec 274X SCSI adapter",
		ahc_aic7770_EISA_setup
	पूर्ण,
	अणु
		ID_AHA_284xB,
		0xFFFFFFFE,
		"Adaptec 284X SCSI adapter",
		ahc_aic7770_VL_setup
	पूर्ण,
	अणु
		ID_AHA_284x,
		0xFFFFFFFE,
		"Adaptec 284X SCSI adapter (BIOS Disabled)",
		ahc_aic7770_VL_setup
	पूर्ण,
	अणु
		ID_OLV_274x,
		0xFFFFFFFF,
		"Adaptec (Olivetti OEM) 274X SCSI adapter",
		ahc_aic7770_EISA_setup
	पूर्ण,
	अणु
		ID_OLV_274xD,
		0xFFFFFFFF,
		"Adaptec (Olivetti OEM) 274X Differential SCSI adapter",
		ahc_aic7770_EISA_setup
	पूर्ण,
	/* Generic chip probes क्रम devices we करोn't know 'exactly' */
	अणु
		ID_AIC7770,
		0xFFFFFFFF,
		"Adaptec aic7770 SCSI adapter",
		ahc_aic7770_EISA_setup
	पूर्ण
पूर्ण;
स्थिर पूर्णांक ahc_num_aic7770_devs = ARRAY_SIZE(aic7770_ident_table);

काष्ठा aic7770_identity *
aic7770_find_device(uपूर्णांक32_t id)
अणु
	काष्ठा	aic7770_identity *entry;
	पूर्णांक	i;

	क्रम (i = 0; i < ahc_num_aic7770_devs; i++) अणु
		entry = &aic7770_ident_table[i];
		अगर (entry->full_id == (id & entry->id_mask))
			वापस (entry);
	पूर्ण
	वापस (शून्य);
पूर्ण

पूर्णांक
aic7770_config(काष्ठा ahc_softc *ahc, काष्ठा aic7770_identity *entry, u_पूर्णांक io)
अणु
	पूर्णांक	error;
	पूर्णांक	have_seeprom;
	u_पूर्णांक	hostconf;
	u_पूर्णांक   irq;
	u_पूर्णांक	पूर्णांकdef;

	error = entry->setup(ahc);
	have_seeprom = 0;
	अगर (error != 0)
		वापस (error);

	error = aic7770_map_रेजिस्टरs(ahc, io);
	अगर (error != 0)
		वापस (error);

	/*
	 * Beक्रमe we जारी probing the card, ensure that
	 * its पूर्णांकerrupts are *disabled*.  We करोn't want
	 * a misstep to hang the machine in an पूर्णांकerrupt
	 * storm.
	 */
	ahc_पूर्णांकr_enable(ahc, FALSE);

	ahc->description = entry->name;
	error = ahc_softc_init(ahc);
	अगर (error != 0)
		वापस (error);

	ahc->bus_chip_init = aic7770_chip_init;

	error = ahc_reset(ahc, /*reinit*/FALSE);
	अगर (error != 0)
		वापस (error);

	/* Make sure we have a valid पूर्णांकerrupt vector */
	पूर्णांकdef = ahc_inb(ahc, INTDEF);
	irq = पूर्णांकdef & VECTOR;
	चयन (irq) अणु
	हाल 9:
	हाल 10:
	हाल 11:
	हाल 12:
	हाल 14:
	हाल 15:
		अवरोध;
	शेष:
		prपूर्णांकk("aic7770_config: invalid irq setting %d\n", पूर्णांकdef);
		वापस (ENXIO);
	पूर्ण

	अगर ((पूर्णांकdef & EDGE_TRIG) != 0)
		ahc->flags |= AHC_EDGE_INTERRUPT;

	चयन (ahc->chip & (AHC_EISA|AHC_VL)) अणु
	हाल AHC_EISA:
	अणु
		u_पूर्णांक biosctrl;
		u_पूर्णांक scsiconf;
		u_पूर्णांक scsiconf1;

		biosctrl = ahc_inb(ahc, HA_274_BIOSCTRL);
		scsiconf = ahc_inb(ahc, SCSICONF);
		scsiconf1 = ahc_inb(ahc, SCSICONF + 1);

		/* Get the primary channel inक्रमmation */
		अगर ((biosctrl & CHANNEL_B_PRIMARY) != 0)
			ahc->flags |= 1;

		अगर ((biosctrl & BIOSMODE) == BIOSDISABLED) अणु
			ahc->flags |= AHC_USEDEFAULTS;
		पूर्ण अन्यथा अणु
			अगर ((ahc->features & AHC_WIDE) != 0) अणु
				ahc->our_id = scsiconf1 & HWSCSIID;
				अगर (scsiconf & TERM_ENB)
					ahc->flags |= AHC_TERM_ENB_A;
			पूर्ण अन्यथा अणु
				ahc->our_id = scsiconf & HSCSIID;
				ahc->our_id_b = scsiconf1 & HSCSIID;
				अगर (scsiconf & TERM_ENB)
					ahc->flags |= AHC_TERM_ENB_A;
				अगर (scsiconf1 & TERM_ENB)
					ahc->flags |= AHC_TERM_ENB_B;
			पूर्ण
		पूर्ण
		अगर ((ahc_inb(ahc, HA_274_BIOSGLOBAL) & HA_274_EXTENDED_TRANS))
			ahc->flags |= AHC_EXTENDED_TRANS_A|AHC_EXTENDED_TRANS_B;
		अवरोध;
	पूर्ण
	हाल AHC_VL:
	अणु
		have_seeprom = aha2840_load_seeprom(ahc);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	अगर (have_seeprom == 0) अणु
		kमुक्त(ahc->seep_config);
		ahc->seep_config = शून्य;
	पूर्ण

	/*
	 * Ensure स्वतःflush is enabled
	 */
	ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) & ~AUTOFLUSHDIS);

	/* Setup the FIFO threshold and the bus off समय */
	hostconf = ahc_inb(ahc, HOSTCONF);
	ahc_outb(ahc, BUSSPD, hostconf & DFTHRSH);
	ahc_outb(ahc, BUSTIME, (hostconf << 2) & BOFF);

	ahc->bus_softc.aic7770_softc.busspd = hostconf & DFTHRSH;
	ahc->bus_softc.aic7770_softc.busसमय = (hostconf << 2) & BOFF;

	/*
	 * Generic aic7xxx initialization.
	 */
	error = ahc_init(ahc);
	अगर (error != 0)
		वापस (error);

	error = aic7770_map_पूर्णांक(ahc, irq);
	अगर (error != 0)
		वापस (error);

	ahc->init_level++;

	/*
	 * Enable the board's BUS drivers
	 */
	ahc_outb(ahc, BCTL, ENABLE);
	वापस (0);
पूर्ण

अटल पूर्णांक
aic7770_chip_init(काष्ठा ahc_softc *ahc)
अणु
	ahc_outb(ahc, BUSSPD, ahc->bus_softc.aic7770_softc.busspd);
	ahc_outb(ahc, BUSTIME, ahc->bus_softc.aic7770_softc.busसमय);
	ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) & ~AUTOFLUSHDIS);
	ahc_outb(ahc, BCTL, ENABLE);
	वापस (ahc_chip_init(ahc));
पूर्ण

/*
 * Read the 284x SEEPROM.
 */
अटल पूर्णांक
aha2840_load_seeprom(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	seeprom_descriptor sd;
	काष्ठा	seeprom_config *sc;
	पूर्णांक	have_seeprom;
	uपूर्णांक8_t scsi_conf;

	sd.sd_ahc = ahc;
	sd.sd_control_offset = SEECTL_2840;
	sd.sd_status_offset = STATUS_2840;
	sd.sd_dataout_offset = STATUS_2840;		
	sd.sd_chip = C46;
	sd.sd_MS = 0;
	sd.sd_RDY = EEPROM_TF;
	sd.sd_CS = CS_2840;
	sd.sd_CK = CK_2840;
	sd.sd_DO = DO_2840;
	sd.sd_DI = DI_2840;
	sc = ahc->seep_config;

	अगर (bootverbose)
		prपूर्णांकk("%s: Reading SEEPROM...", ahc_name(ahc));
	have_seeprom = ahc_पढ़ो_seeprom(&sd, (uपूर्णांक16_t *)sc,
					/*start_addr*/0, माप(*sc)/2);

	अगर (have_seeprom) अणु

		अगर (ahc_verअगरy_cksum(sc) == 0) अणु
			अगर(bootverbose)
				prपूर्णांकk ("checksum error\n");
			have_seeprom = 0;
		पूर्ण अन्यथा अगर (bootverbose) अणु
			prपूर्णांकk("done.\n");
		पूर्ण
	पूर्ण

	अगर (!have_seeprom) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: No SEEPROM available\n", ahc_name(ahc));
		ahc->flags |= AHC_USEDEFAULTS;
	पूर्ण अन्यथा अणु
		/*
		 * Put the data we've collected करोwn पूर्णांकo SRAM
		 * where ahc_init will find it.
		 */
		पूर्णांक	 i;
		पूर्णांक	 max_targ;
		uपूर्णांक16_t discenable;

		max_targ = (ahc->features & AHC_WIDE) != 0 ? 16 : 8;
		discenable = 0;
		क्रम (i = 0; i < max_targ; i++)अणु
			uपूर्णांक8_t target_settings;

			target_settings = (sc->device_flags[i] & CFXFER) << 4;
			अगर (sc->device_flags[i] & CFSYNCH)
				target_settings |= SOFS;
			अगर (sc->device_flags[i] & CFWIDEB)
				target_settings |= WIDEXFER;
			अगर (sc->device_flags[i] & CFDISC)
				discenable |= (0x01 << i);
			ahc_outb(ahc, TARG_SCSIRATE + i, target_settings);
		पूर्ण
		ahc_outb(ahc, DISC_DSB, ~(discenable & 0xff));
		ahc_outb(ahc, DISC_DSB + 1, ~((discenable >> 8) & 0xff));

		ahc->our_id = sc->brसमय_id & CFSCSIID;

		scsi_conf = (ahc->our_id & 0x7);
		अगर (sc->adapter_control & CFSPARITY)
			scsi_conf |= ENSPCHK;
		अगर (sc->adapter_control & CFRESETB)
			scsi_conf |= RESET_SCSI;

		अगर (sc->bios_control & CF284XEXTEND)		
			ahc->flags |= AHC_EXTENDED_TRANS_A;
		/* Set SCSICONF info */
		ahc_outb(ahc, SCSICONF, scsi_conf);

		अगर (sc->adapter_control & CF284XSTERM)
			ahc->flags |= AHC_TERM_ENB_A;
	पूर्ण
	वापस (have_seeprom);
पूर्ण

अटल पूर्णांक
ahc_aic7770_VL_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7770_setup(ahc);
	ahc->chip |= AHC_VL;
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aic7770_EISA_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7770_setup(ahc);
	ahc->chip |= AHC_EISA;
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aic7770_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc->channel = 'A';
	ahc->channel_b = 'B';
	ahc->chip = AHC_AIC7770;
	ahc->features = AHC_AIC7770_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG;
	ahc->flags |= AHC_PAGESCBS;
	ahc->inकाष्ठाion_ram_size = 448;
	वापस (0);
पूर्ण
