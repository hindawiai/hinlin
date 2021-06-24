<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#समावेश "sym_glue.h"

/*
 *  Macros used क्रम all firmwares.
 */
#घोषणा	SYM_GEN_A(s, label)	((लघु) दुरत्व(s, label)),
#घोषणा	SYM_GEN_B(s, label)	((लघु) दुरत्व(s, label)),
#घोषणा	SYM_GEN_Z(s, label)	((लघु) दुरत्व(s, label)),
#घोषणा	PADDR_A(label)		SYM_GEN_PADDR_A(काष्ठा SYM_FWA_SCR, label)
#घोषणा	PADDR_B(label)		SYM_GEN_PADDR_B(काष्ठा SYM_FWB_SCR, label)


#अगर	SYM_CONF_GENERIC_SUPPORT
/*
 *  Allocate firmware #1 script area.
 */
#घोषणा	SYM_FWA_SCR		sym_fw1a_scr
#घोषणा	SYM_FWB_SCR		sym_fw1b_scr
#घोषणा	SYM_FWZ_SCR		sym_fw1z_scr
#समावेश "sym_fw1.h"
अटल काष्ठा sym_fwa_ofs sym_fw1a_ofs = अणु
	SYM_GEN_FW_A(काष्ठा SYM_FWA_SCR)
पूर्ण;
अटल काष्ठा sym_fwb_ofs sym_fw1b_ofs = अणु
	SYM_GEN_FW_B(काष्ठा SYM_FWB_SCR)
पूर्ण;
अटल काष्ठा sym_fwz_ofs sym_fw1z_ofs = अणु
	SYM_GEN_FW_Z(काष्ठा SYM_FWZ_SCR)
पूर्ण;
#अघोषित	SYM_FWA_SCR
#अघोषित	SYM_FWB_SCR
#अघोषित	SYM_FWZ_SCR
#पूर्ण_अगर	/* SYM_CONF_GENERIC_SUPPORT */

/*
 *  Allocate firmware #2 script area.
 */
#घोषणा	SYM_FWA_SCR		sym_fw2a_scr
#घोषणा	SYM_FWB_SCR		sym_fw2b_scr
#घोषणा	SYM_FWZ_SCR		sym_fw2z_scr
#समावेश "sym_fw2.h"
अटल काष्ठा sym_fwa_ofs sym_fw2a_ofs = अणु
	SYM_GEN_FW_A(काष्ठा SYM_FWA_SCR)
पूर्ण;
अटल काष्ठा sym_fwb_ofs sym_fw2b_ofs = अणु
	SYM_GEN_FW_B(काष्ठा SYM_FWB_SCR)
	SYM_GEN_B(काष्ठा SYM_FWB_SCR, start64)
	SYM_GEN_B(काष्ठा SYM_FWB_SCR, pm_handle)
पूर्ण;
अटल काष्ठा sym_fwz_ofs sym_fw2z_ofs = अणु
	SYM_GEN_FW_Z(काष्ठा SYM_FWZ_SCR)
पूर्ण;
#अघोषित	SYM_FWA_SCR
#अघोषित	SYM_FWB_SCR
#अघोषित	SYM_FWZ_SCR

#अघोषित	SYM_GEN_A
#अघोषित	SYM_GEN_B
#अघोषित	SYM_GEN_Z
#अघोषित	PADDR_A
#अघोषित	PADDR_B

#अगर	SYM_CONF_GENERIC_SUPPORT
/*
 *  Patch routine क्रम firmware #1.
 */
अटल व्योम
sym_fw1_patch(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_fw1a_scr *scripta0;
	काष्ठा sym_fw1b_scr *scriptb0;

	scripta0 = (काष्ठा sym_fw1a_scr *) np->scripta0;
	scriptb0 = (काष्ठा sym_fw1b_scr *) np->scriptb0;

	/*
	 *  Remove LED support अगर not needed.
	 */
	अगर (!(np->features & FE_LED0)) अणु
		scripta0->idle[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->reselected[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->start[0]	= cpu_to_scr(SCR_NO_OP);
	पूर्ण

#अगर_घोषित SYM_CONF_IARB_SUPPORT
	/*
	 *    If user करोes not want to use IMMEDIATE ARBITRATION
	 *    when we are reselected जबतक attempting to arbitrate,
	 *    patch the SCRIPTS accordingly with a SCRIPT NO_OP.
	 */
	अगर (!SYM_CONF_SET_IARB_ON_ARB_LOST)
		scripta0->ungetjob[0] = cpu_to_scr(SCR_NO_OP);
#पूर्ण_अगर
	/*
	 *  Patch some data in SCRIPTS.
	 *  - start and करोne queue initial bus address.
	 *  - target bus address table bus address.
	 */
	scriptb0->startpos[0]	= cpu_to_scr(np->squeue_ba);
	scriptb0->करोne_pos[0]	= cpu_to_scr(np->dqueue_ba);
	scriptb0->targtbl[0]	= cpu_to_scr(np->targtbl_ba);
पूर्ण
#पूर्ण_अगर	/* SYM_CONF_GENERIC_SUPPORT */

/*
 *  Patch routine क्रम firmware #2.
 */
अटल व्योम
sym_fw2_patch(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	काष्ठा sym_hcb *np = sym_data->ncb;
	काष्ठा sym_fw2a_scr *scripta0;
	काष्ठा sym_fw2b_scr *scriptb0;

	scripta0 = (काष्ठा sym_fw2a_scr *) np->scripta0;
	scriptb0 = (काष्ठा sym_fw2b_scr *) np->scriptb0;

	/*
	 *  Remove LED support अगर not needed.
	 */
	अगर (!(np->features & FE_LED0)) अणु
		scripta0->idle[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->reselected[0]	= cpu_to_scr(SCR_NO_OP);
		scripta0->start[0]	= cpu_to_scr(SCR_NO_OP);
	पूर्ण

#अगर   SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  Remove useless 64 bit DMA specअगरic SCRIPTS, 
	 *  when this feature is not available.
	 */
	अगर (!use_dac(np)) अणु
		scripta0->is_dmap_dirty[0] = cpu_to_scr(SCR_NO_OP);
		scripta0->is_dmap_dirty[1] = 0;
		scripta0->is_dmap_dirty[2] = cpu_to_scr(SCR_NO_OP);
		scripta0->is_dmap_dirty[3] = 0;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित SYM_CONF_IARB_SUPPORT
	/*
	 *    If user करोes not want to use IMMEDIATE ARBITRATION
	 *    when we are reselected जबतक attempting to arbitrate,
	 *    patch the SCRIPTS accordingly with a SCRIPT NO_OP.
	 */
	अगर (!SYM_CONF_SET_IARB_ON_ARB_LOST)
		scripta0->ungetjob[0] = cpu_to_scr(SCR_NO_OP);
#पूर्ण_अगर
	/*
	 *  Patch some variable in SCRIPTS.
	 *  - start and करोne queue initial bus address.
	 *  - target bus address table bus address.
	 */
	scriptb0->startpos[0]	= cpu_to_scr(np->squeue_ba);
	scriptb0->करोne_pos[0]	= cpu_to_scr(np->dqueue_ba);
	scriptb0->targtbl[0]	= cpu_to_scr(np->targtbl_ba);

	/*
	 *  Remove the load of SCNTL4 on reselection अगर not a C10.
	 */
	अगर (!(np->features & FE_C10)) अणु
		scripta0->resel_scntl4[0] = cpu_to_scr(SCR_NO_OP);
		scripta0->resel_scntl4[1] = cpu_to_scr(0);
	पूर्ण

	/*
	 *  Remove a couple of work-arounds specअगरic to C1010 अगर 
	 *  they are not desirable. See `sym_fw2.h' क्रम more details.
	 */
	अगर (!(pdev->device == PCI_DEVICE_ID_LSI_53C1010_66 &&
	      pdev->revision < 0x1 &&
	      np->pciclk_khz < 60000)) अणु
		scripta0->datao_phase[0] = cpu_to_scr(SCR_NO_OP);
		scripta0->datao_phase[1] = cpu_to_scr(0);
	पूर्ण
	अगर (!(pdev->device == PCI_DEVICE_ID_LSI_53C1010_33 /* &&
	      pdev->revision < 0xff */)) अणु
		scripta0->sel_करोne[0] = cpu_to_scr(SCR_NO_OP);
		scripta0->sel_करोne[1] = cpu_to_scr(0);
	पूर्ण

	/*
	 *  Patch some other variables in SCRIPTS.
	 *  These ones are loaded by the SCRIPTS processor.
	 */
	scriptb0->pm0_data_addr[0] =
		cpu_to_scr(np->scripta_ba + 
			   दुरत्व(काष्ठा sym_fw2a_scr, pm0_data));
	scriptb0->pm1_data_addr[0] =
		cpu_to_scr(np->scripta_ba + 
			   दुरत्व(काष्ठा sym_fw2a_scr, pm1_data));
पूर्ण

/*
 *  Fill the data area in scripts.
 *  To be करोne क्रम all firmwares.
 */
अटल व्योम
sym_fw_fill_data (u32 *in, u32 *out)
अणु
	पूर्णांक	i;

	क्रम (i = 0; i < SYM_CONF_MAX_SG; i++) अणु
		*in++  = SCR_CHMOV_TBL ^ SCR_DATA_IN;
		*in++  = दुरत्व (काष्ठा sym_dsb, data[i]);
		*out++ = SCR_CHMOV_TBL ^ SCR_DATA_OUT;
		*out++ = दुरत्व (काष्ठा sym_dsb, data[i]);
	पूर्ण
पूर्ण

/*
 *  Setup useful script bus addresses.
 *  To be करोne क्रम all firmwares.
 */
अटल व्योम 
sym_fw_setup_bus_addresses(काष्ठा sym_hcb *np, काष्ठा sym_fw *fw)
अणु
	u32 *pa;
	u_लघु *po;
	पूर्णांक i;

	/*
	 *  Build the bus address table क्रम script A 
	 *  from the script A offset table.
	 */
	po = (u_लघु *) fw->a_ofs;
	pa = (u32 *) &np->fwa_bas;
	क्रम (i = 0 ; i < माप(np->fwa_bas)/माप(u32) ; i++)
		pa[i] = np->scripta_ba + po[i];

	/*
	 *  Same क्रम script B.
	 */
	po = (u_लघु *) fw->b_ofs;
	pa = (u32 *) &np->fwb_bas;
	क्रम (i = 0 ; i < माप(np->fwb_bas)/माप(u32) ; i++)
		pa[i] = np->scriptb_ba + po[i];

	/*
	 *  Same क्रम script Z.
	 */
	po = (u_लघु *) fw->z_ofs;
	pa = (u32 *) &np->fwz_bas;
	क्रम (i = 0 ; i < माप(np->fwz_bas)/माप(u32) ; i++)
		pa[i] = np->scriptz_ba + po[i];
पूर्ण

#अगर	SYM_CONF_GENERIC_SUPPORT
/*
 *  Setup routine क्रम firmware #1.
 */
अटल व्योम 
sym_fw1_setup(काष्ठा sym_hcb *np, काष्ठा sym_fw *fw)
अणु
	काष्ठा sym_fw1a_scr *scripta0;

	scripta0 = (काष्ठा sym_fw1a_scr *) np->scripta0;

	/*
	 *  Fill variable parts in scripts.
	 */
	sym_fw_fill_data(scripta0->data_in, scripta0->data_out);

	/*
	 *  Setup bus addresses used from the C code..
	 */
	sym_fw_setup_bus_addresses(np, fw);
पूर्ण
#पूर्ण_अगर	/* SYM_CONF_GENERIC_SUPPORT */

/*
 *  Setup routine क्रम firmware #2.
 */
अटल व्योम 
sym_fw2_setup(काष्ठा sym_hcb *np, काष्ठा sym_fw *fw)
अणु
	काष्ठा sym_fw2a_scr *scripta0;

	scripta0 = (काष्ठा sym_fw2a_scr *) np->scripta0;

	/*
	 *  Fill variable parts in scripts.
	 */
	sym_fw_fill_data(scripta0->data_in, scripta0->data_out);

	/*
	 *  Setup bus addresses used from the C code..
	 */
	sym_fw_setup_bus_addresses(np, fw);
पूर्ण

/*
 *  Allocate firmware descriptors.
 */
#अगर	SYM_CONF_GENERIC_SUPPORT
अटल काष्ठा sym_fw sym_fw1 = SYM_FW_ENTRY(sym_fw1, "NCR-generic");
#पूर्ण_अगर	/* SYM_CONF_GENERIC_SUPPORT */
अटल काष्ठा sym_fw sym_fw2 = SYM_FW_ENTRY(sym_fw2, "LOAD/STORE-based");

/*
 *  Find the most appropriate firmware क्रम a chip.
 */
काष्ठा sym_fw * 
sym_find_firmware(काष्ठा sym_chip *chip)
अणु
	अगर (chip->features & FE_LDSTR)
		वापस &sym_fw2;
#अगर	SYM_CONF_GENERIC_SUPPORT
	अन्यथा अगर (!(chip->features & (FE_PFEN|FE_NOPM|FE_DAC)))
		वापस &sym_fw1;
#पूर्ण_अगर
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 *  Bind a script to physical addresses.
 */
व्योम sym_fw_bind_script(काष्ठा sym_hcb *np, u32 *start, पूर्णांक len)
अणु
	u32 opcode, new, old, पंचांगp1, पंचांगp2;
	u32 *end, *cur;
	पूर्णांक relocs;

	cur = start;
	end = start + len/4;

	जबतक (cur < end) अणु

		opcode = *cur;

		/*
		 *  If we क्रमget to change the length
		 *  in scripts, a field will be
		 *  padded with 0. This is an illegal
		 *  command.
		 */
		अगर (opcode == 0) अणु
			म_लिखो ("%s: ERROR0 IN SCRIPT at %d.\n",
				sym_name(np), (पूर्णांक) (cur-start));
			++cur;
			जारी;
		पूर्ण

		/*
		 *  We use the bogus value 0xf00ff00f ;-)
		 *  to reserve data area in SCRIPTS.
		 */
		अगर (opcode == SCR_DATA_ZERO) अणु
			*cur++ = 0;
			जारी;
		पूर्ण

		अगर (DEBUG_FLAGS & DEBUG_SCRIPT)
			म_लिखो ("%d:  <%x>\n", (पूर्णांक) (cur-start),
				(अचिन्हित)opcode);

		/*
		 *  We करोn't have to decode ALL commands
		 */
		चयन (opcode >> 28) अणु
		हाल 0xf:
			/*
			 *  LOAD / STORE DSA relative, करोn't relocate.
			 */
			relocs = 0;
			अवरोध;
		हाल 0xe:
			/*
			 *  LOAD / STORE असलolute.
			 */
			relocs = 1;
			अवरोध;
		हाल 0xc:
			/*
			 *  COPY has TWO arguments.
			 */
			relocs = 2;
			पंचांगp1 = cur[1];
			पंचांगp2 = cur[2];
			अगर ((पंचांगp1 ^ पंचांगp2) & 3) अणु
				म_लिखो ("%s: ERROR1 IN SCRIPT at %d.\n",
					sym_name(np), (पूर्णांक) (cur-start));
			पूर्ण
			/*
			 *  If PREFETCH feature not enabled, हटाओ 
			 *  the NO FLUSH bit अगर present.
			 */
			अगर ((opcode & SCR_NO_FLUSH) &&
			    !(np->features & FE_PFEN)) अणु
				opcode = (opcode & ~SCR_NO_FLUSH);
			पूर्ण
			अवरोध;
		हाल 0x0:
			/*
			 *  MOVE/CHMOV (असलolute address)
			 */
			अगर (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 1;
			अवरोध;
		हाल 0x1:
			/*
			 *  MOVE/CHMOV (table indirect)
			 */
			अगर (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 0;
			अवरोध;
#अगर_घोषित SYM_CONF_TARGET_ROLE_SUPPORT
		हाल 0x2:
			/*
			 *  MOVE/CHMOV in target role (असलolute address)
			 */
			opcode &= ~0x20000000;
			अगर (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 1;
			अवरोध;
		हाल 0x3:
			/*
			 *  MOVE/CHMOV in target role (table indirect)
			 */
			opcode &= ~0x20000000;
			अगर (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 0;
			अवरोध;
#पूर्ण_अगर
		हाल 0x8:
			/*
			 *  JUMP / CALL
			 *  करोn't relocate अगर relative :-)
			 */
			अगर (opcode & 0x00800000)
				relocs = 0;
			अन्यथा अगर ((opcode & 0xf8400000) == 0x80400000)/*JUMP64*/
				relocs = 2;
			अन्यथा
				relocs = 1;
			अवरोध;
		हाल 0x4:
		हाल 0x5:
		हाल 0x6:
		हाल 0x7:
			relocs = 1;
			अवरोध;
		शेष:
			relocs = 0;
			अवरोध;
		पूर्ण

		/*
		 *  Scriptअगरy:) the opcode.
		 */
		*cur++ = cpu_to_scr(opcode);

		/*
		 *  If no relocation, assume 1 argument 
		 *  and just scriptize:) it.
		 */
		अगर (!relocs) अणु
			*cur = cpu_to_scr(*cur);
			++cur;
			जारी;
		पूर्ण

		/*
		 *  Otherwise perक्रमms all needed relocations.
		 */
		जबतक (relocs--) अणु
			old = *cur;

			चयन (old & RELOC_MASK) अणु
			हाल RELOC_REGISTER:
				new = (old & ~RELOC_MASK) + np->mmio_ba;
				अवरोध;
			हाल RELOC_LABEL_A:
				new = (old & ~RELOC_MASK) + np->scripta_ba;
				अवरोध;
			हाल RELOC_LABEL_B:
				new = (old & ~RELOC_MASK) + np->scriptb_ba;
				अवरोध;
			हाल RELOC_SOFTC:
				new = (old & ~RELOC_MASK) + np->hcb_ba;
				अवरोध;
			हाल 0:
				/*
				 *  Don't relocate a 0 address.
				 *  They are mostly used क्रम patched or 
				 *  script self-modअगरied areas.
				 */
				अगर (old == 0) अणु
					new = old;
					अवरोध;
				पूर्ण
				fallthrough;
			शेष:
				new = 0;
				panic("sym_fw_bind_script: "
				      "weird relocation %x\n", old);
				अवरोध;
			पूर्ण

			*cur++ = cpu_to_scr(new);
		पूर्ण
	पूर्ण
पूर्ण
