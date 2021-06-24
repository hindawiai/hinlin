<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
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

#अगर_अघोषित	SYM_FW_H
#घोषणा	SYM_FW_H
/*
 *  Macro used to generate पूर्णांकerfaces क्रम script A.
 */
#घोषणा SYM_GEN_FW_A(s)							\
	SYM_GEN_A(s, start)		SYM_GEN_A(s, getjob_begin)	\
	SYM_GEN_A(s, getjob_end)					\
	SYM_GEN_A(s, select)		SYM_GEN_A(s, wf_sel_करोne)	\
	SYM_GEN_A(s, send_ident)					\
	SYM_GEN_A(s, dispatch)		SYM_GEN_A(s, init)		\
	SYM_GEN_A(s, clrack)		SYM_GEN_A(s, complete_error)	\
	SYM_GEN_A(s, करोne)		SYM_GEN_A(s, करोne_end)		\
	SYM_GEN_A(s, idle)		SYM_GEN_A(s, ungetjob)		\
	SYM_GEN_A(s, reselect)						\
	SYM_GEN_A(s, resel_tag)		SYM_GEN_A(s, resel_dsa)		\
	SYM_GEN_A(s, resel_no_tag)					\
	SYM_GEN_A(s, data_in)		SYM_GEN_A(s, data_in2)		\
	SYM_GEN_A(s, data_out)		SYM_GEN_A(s, data_out2)		\
	SYM_GEN_A(s, pm0_data)		SYM_GEN_A(s, pm1_data)

/*
 *  Macro used to generate पूर्णांकerfaces क्रम script B.
 */
#घोषणा SYM_GEN_FW_B(s)							\
	SYM_GEN_B(s, no_data)						\
	SYM_GEN_B(s, sel_क्रम_पात)	SYM_GEN_B(s, sel_क्रम_पात_1)	\
	SYM_GEN_B(s, msg_bad)		SYM_GEN_B(s, msg_weird)		\
	SYM_GEN_B(s, wdtr_resp)		SYM_GEN_B(s, send_wdtr)		\
	SYM_GEN_B(s, sdtr_resp)		SYM_GEN_B(s, send_sdtr)		\
	SYM_GEN_B(s, ppr_resp)		SYM_GEN_B(s, send_ppr)		\
	SYM_GEN_B(s, nego_bad_phase)					\
	SYM_GEN_B(s, ident_अवरोध) 	SYM_GEN_B(s, ident_अवरोध_atn)	\
	SYM_GEN_B(s, sdata_in)		SYM_GEN_B(s, resel_bad_lun)	\
	SYM_GEN_B(s, bad_i_t_l)		SYM_GEN_B(s, bad_i_t_l_q)	\
	SYM_GEN_B(s, wsr_ma_helper)

/*
 *  Macro used to generate पूर्णांकerfaces क्रम script Z.
 */
#घोषणा SYM_GEN_FW_Z(s)							\
	SYM_GEN_Z(s, snooptest)		SYM_GEN_Z(s, snoखोलोd)

/*
 *  Generates काष्ठाure पूर्णांकerface that contains 
 *  offsets within script A, B and Z.
 */
#घोषणा	SYM_GEN_A(s, label)	s label;
#घोषणा	SYM_GEN_B(s, label)	s label;
#घोषणा	SYM_GEN_Z(s, label)	s label;
काष्ठा sym_fwa_ofs अणु
	SYM_GEN_FW_A(u_लघु)
पूर्ण;
काष्ठा sym_fwb_ofs अणु
	SYM_GEN_FW_B(u_लघु)
	SYM_GEN_B(u_लघु, start64)
	SYM_GEN_B(u_लघु, pm_handle)
पूर्ण;
काष्ठा sym_fwz_ofs अणु
	SYM_GEN_FW_Z(u_लघु)
पूर्ण;

/*
 *  Generates काष्ठाure पूर्णांकerface that contains 
 *  bus addresses within script A, B and Z.
 */
काष्ठा sym_fwa_ba अणु
	SYM_GEN_FW_A(u32)
पूर्ण;
काष्ठा sym_fwb_ba अणु
	SYM_GEN_FW_B(u32)
	SYM_GEN_B(u32, start64);
	SYM_GEN_B(u32, pm_handle);
पूर्ण;
काष्ठा sym_fwz_ba अणु
	SYM_GEN_FW_Z(u32)
पूर्ण;
#अघोषित	SYM_GEN_A
#अघोषित	SYM_GEN_B
#अघोषित	SYM_GEN_Z

/*
 *  Let cc know about the name of the controller data काष्ठाure.
 *  We need this क्रम function prototype declarations just below.
 */
काष्ठा sym_hcb;

/*
 *  Generic काष्ठाure that defines a firmware.
 */ 
काष्ठा sym_fw अणु
	अक्षर	*name;		/* Name we want to prपूर्णांक out	*/
	u32	*a_base;	/* Poपूर्णांकer to script A ढाँचा	*/
	पूर्णांक	a_size;		/* Size of script A		*/
	काष्ठा	sym_fwa_ofs
		*a_ofs;		/* Useful offsets in script A	*/
	u32	*b_base;	/* Poपूर्णांकer to script B ढाँचा	*/
	पूर्णांक	b_size;		/* Size of script B		*/
	काष्ठा	sym_fwb_ofs
		*b_ofs;		/* Useful offsets in script B	*/
	u32	*z_base;	/* Poपूर्णांकer to script Z ढाँचा	*/
	पूर्णांक	z_size;		/* Size of script Z		*/
	काष्ठा	sym_fwz_ofs
		*z_ofs;		/* Useful offsets in script Z	*/
	/* Setup and patch methods क्रम this firmware */
	व्योम	(*setup)(काष्ठा sym_hcb *, काष्ठा sym_fw *);
	व्योम	(*patch)(काष्ठा Scsi_Host *);
पूर्ण;

/*
 *  Macro used to declare a firmware.
 */
#घोषणा SYM_FW_ENTRY(fw, name)					\
अणु								\
	name,							\
	(u32 *) &fw##a_scr, माप(fw##a_scr), &fw##a_ofs,	\
	(u32 *) &fw##b_scr, माप(fw##b_scr), &fw##b_ofs,	\
	(u32 *) &fw##z_scr, माप(fw##z_scr), &fw##z_ofs,	\
	fw##_setup, fw##_patch					\
पूर्ण

/*
 *  Macros used from the C code to get useful
 *  SCRIPTS bus addresses.
 */
#घोषणा SCRIPTA_BA(np, label)	(np->fwa_bas.label)
#घोषणा SCRIPTB_BA(np, label)	(np->fwb_bas.label)
#घोषणा SCRIPTZ_BA(np, label)	(np->fwz_bas.label)

/*
 *  Macros used by scripts definitions.
 *
 *  HADDR_1 generates a reference to a field of the controller data.
 *  HADDR_2 generates a reference to a field of the controller data
 *          with offset.
 *  RADDR_1 generates a reference to a script processor रेजिस्टर.
 *  RADDR_2 generates a reference to a script processor रेजिस्टर
 *          with offset.
 *  PADDR_A generates a reference to another part of script A.
 *  PADDR_B generates a reference to another part of script B.
 *
 *  SYM_GEN_PADDR_A and SYM_GEN_PADDR_B are used to define respectively 
 *  the PADDR_A and PADDR_B macros क्रम each firmware by setting argument 
 *  `s' to the name of the corresponding काष्ठाure.
 *
 *  SCR_DATA_ZERO is used to allocate a DWORD of data in scripts areas.
 */

#घोषणा	RELOC_SOFTC	0x40000000
#घोषणा	RELOC_LABEL_A	0x50000000
#घोषणा	RELOC_REGISTER	0x60000000
#घोषणा	RELOC_LABEL_B	0x80000000
#घोषणा	RELOC_MASK	0xf0000000

#घोषणा	HADDR_1(label)	   (RELOC_SOFTC    | दुरत्व(काष्ठा sym_hcb, label))
#घोषणा	HADDR_2(label,ofs) (RELOC_SOFTC    | \
				(दुरत्व(काष्ठा sym_hcb, label)+(ofs)))
#घोषणा	RADDR_1(label)	   (RELOC_REGISTER | REG(label))
#घोषणा	RADDR_2(label,ofs) (RELOC_REGISTER | ((REG(label))+(ofs)))

#घोषणा SYM_GEN_PADDR_A(s, label) (RELOC_LABEL_A  | दुरत्व(s, label))
#घोषणा SYM_GEN_PADDR_B(s, label) (RELOC_LABEL_B  | दुरत्व(s, label))

#घोषणा SCR_DATA_ZERO	0xf00ff00f

#पूर्ण_अगर	/* SYM_FW_H */
