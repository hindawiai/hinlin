<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/err_marvel.c
 *
 *	Copyright (C) 2001 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/console.h>
#समावेश <यंत्र/core_marvel.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/err_common.h>
#समावेश <यंत्र/err_ev7.h>

#समावेश "err_impl.h"
#समावेश "proto.h"

अटल व्योम
marvel_prपूर्णांक_680_frame(काष्ठा ev7_lf_subpackets *lf_subpackets)
अणु
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	काष्ठा ev7_pal_environmental_subpacket *env;
	काष्ठा अणु पूर्णांक type; अक्षर *name; पूर्ण ev_packets[] = अणु
		अणु EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE,
		  "Ambient Temperature" पूर्ण,
		अणु EL_TYPE__PAL__ENV__AIRMOVER_FAN,
		  "AirMover / Fan" पूर्ण,
		अणु EL_TYPE__PAL__ENV__VOLTAGE,
		  "Voltage" पूर्ण,
		अणु EL_TYPE__PAL__ENV__INTRUSION,
		  "Intrusion" पूर्ण,
		अणु EL_TYPE__PAL__ENV__POWER_SUPPLY,
		  "Power Supply" पूर्ण,
		अणु EL_TYPE__PAL__ENV__LAN,
		  "LAN" पूर्ण,
		अणु EL_TYPE__PAL__ENV__HOT_PLUG,
		  "Hot Plug" पूर्ण,
		अणु 0, शून्य पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; ev_packets[i].type != 0; i++) अणु
		env = lf_subpackets->env[ev7_lf_env_index(ev_packets[i].type)];
		अगर (!env)
			जारी;

		prपूर्णांकk("%s**%s event (cabinet %d, drawer %d)\n",
		       err_prपूर्णांक_prefix,
		       ev_packets[i].name,
		       env->cabinet,
		       env->drawer);
		prपूर्णांकk("%s   Module Type: 0x%x - Unit ID 0x%x - "
		       "Condition 0x%x\n",
		       err_prपूर्णांक_prefix,
		       env->module_type,
		       env->unit_id,
		       env->condition);
	पूर्ण
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */
पूर्ण

अटल पूर्णांक
marvel_process_680_frame(काष्ठा ev7_lf_subpackets *lf_subpackets, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;
	पूर्णांक i;

	क्रम (i = ev7_lf_env_index(EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE);
	     i <= ev7_lf_env_index(EL_TYPE__PAL__ENV__HOT_PLUG);
	     i++) अणु
		अगर (lf_subpackets->env[i])
			status = MCHK_DISPOSITION_REPORT;
	पूर्ण

	अगर (prपूर्णांक)
		marvel_prपूर्णांक_680_frame(lf_subpackets);

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_VERBOSE_MCHECK

अटल व्योम
marvel_prपूर्णांक_err_cyc(u64 err_cyc)
अणु
	अटल अक्षर *packet_desc[] = अणु
		"No Error",
		"UNKNOWN",
		"1 cycle (1 or 2 flit packet)",
		"2 cycles (3 flit packet)",
		"9 cycles (18 flit packet)",
		"10 cycles (19 flit packet)",
		"UNKNOWN",
		"UNKNOWN",
		"UNKNOWN"
	पूर्ण;

#घोषणा IO7__ERR_CYC__ODD_FLT	(1UL <<  0)
#घोषणा IO7__ERR_CYC__EVN_FLT	(1UL <<  1)
#घोषणा IO7__ERR_CYC__PACKET__S	(6)
#घोषणा IO7__ERR_CYC__PACKET__M	(0x7)
#घोषणा IO7__ERR_CYC__LOC	(1UL <<  5)
#घोषणा IO7__ERR_CYC__CYCLE__S	(2)
#घोषणा IO7__ERR_CYC__CYCLE__M	(0x7)

	prपूर्णांकk("%s        Packet In Error: %s\n"
	       "%s        Error in %s, cycle %lld%s%s\n",
	       err_prपूर्णांक_prefix, 
	       packet_desc[EXTRACT(err_cyc, IO7__ERR_CYC__PACKET)],
	       err_prपूर्णांक_prefix,
	       (err_cyc & IO7__ERR_CYC__LOC) ? "DATA" : "HEADER",
	       EXTRACT(err_cyc, IO7__ERR_CYC__CYCLE),
	       (err_cyc & IO7__ERR_CYC__ODD_FLT) ? " [ODD Flit]": "",
	       (err_cyc & IO7__ERR_CYC__EVN_FLT) ? " [Even Flit]": "");
पूर्ण

अटल व्योम
marvel_prपूर्णांक_po7_crrct_sym(u64 crrct_sym)
अणु
#घोषणा IO7__PO7_CRRCT_SYM__SYN__S	(0)
#घोषणा IO7__PO7_CRRCT_SYM__SYN__M	(0x7f)
#घोषणा IO7__PO7_CRRCT_SYM__ERR_CYC__S	(7)   /* ERR_CYC + ODD_FLT + EVN_FLT */
#घोषणा IO7__PO7_CRRCT_SYM__ERR_CYC__M	(0x1ff)


	prपूर्णांकk("%s      Correctable Error Symptoms:\n"
	       "%s        Syndrome: 0x%llx\n",
	       err_prपूर्णांक_prefix,
	       err_prपूर्णांक_prefix, EXTRACT(crrct_sym, IO7__PO7_CRRCT_SYM__SYN));
	marvel_prपूर्णांक_err_cyc(EXTRACT(crrct_sym, IO7__PO7_CRRCT_SYM__ERR_CYC));
पूर्ण

अटल व्योम
marvel_prपूर्णांक_po7_uncrr_sym(u64 uncrr_sym, u64 valid_mask)
अणु
	अटल अक्षर *clk_names[] = अणु "_h[0]", "_h[1]", "_n[0]", "_n[1]" पूर्ण;
	अटल अक्षर *clk_decode[] = अणु
		"No Error",
		"One extra rising edge",
		"Two extra rising edges",
		"Lost one clock"
	पूर्ण;
	अटल अक्षर *port_names[] = अणु "Port 0", 	"Port 1", 
				      "Port 2", 	"Port 3",
				      "Unknown Port",	"Unknown Port",
				      "Unknown Port",	"Port 7" पूर्ण;
	पूर्णांक scratch, i;

#घोषणा IO7__PO7_UNCRR_SYM__SYN__S	    (0)
#घोषणा IO7__PO7_UNCRR_SYM__SYN__M	    (0x7f)
#घोषणा IO7__PO7_UNCRR_SYM__ERR_CYC__S	    (7)      /* ERR_CYC + ODD_FLT... */
#घोषणा IO7__PO7_UNCRR_SYM__ERR_CYC__M	    (0x1ff)  /* ... + EVN_FLT        */
#घोषणा IO7__PO7_UNCRR_SYM__CLK__S	    (16)
#घोषणा IO7__PO7_UNCRR_SYM__CLK__M	    (0xff)
#घोषणा IO7__PO7_UNCRR_SYM__CDT_OVF_TO__REQ (1UL << 24)
#घोषणा IO7__PO7_UNCRR_SYM__CDT_OVF_TO__RIO (1UL << 25)
#घोषणा IO7__PO7_UNCRR_SYM__CDT_OVF_TO__WIO (1UL << 26)
#घोषणा IO7__PO7_UNCRR_SYM__CDT_OVF_TO__BLK (1UL << 27)
#घोषणा IO7__PO7_UNCRR_SYM__CDT_OVF_TO__NBK (1UL << 28)
#घोषणा IO7__PO7_UNCRR_SYM__OVF__READIO	    (1UL << 29)
#घोषणा IO7__PO7_UNCRR_SYM__OVF__WRITEIO    (1UL << 30)
#घोषणा IO7__PO7_UNCRR_SYM__OVF__FWD        (1UL << 31)
#घोषणा IO7__PO7_UNCRR_SYM__VICTIM_SP__S    (32)
#घोषणा IO7__PO7_UNCRR_SYM__VICTIM_SP__M    (0xff)
#घोषणा IO7__PO7_UNCRR_SYM__DETECT_SP__S    (40)
#घोषणा IO7__PO7_UNCRR_SYM__DETECT_SP__M    (0xff)
#घोषणा IO7__PO7_UNCRR_SYM__STRV_VTR__S     (48)
#घोषणा IO7__PO7_UNCRR_SYM__STRV_VTR__M     (0x3ff)

#घोषणा IO7__STRV_VTR__LSI__INTX__S	    (0)
#घोषणा IO7__STRV_VTR__LSI__INTX__M	    (0x3)
#घोषणा IO7__STRV_VTR__LSI__SLOT__S	    (2)
#घोषणा IO7__STRV_VTR__LSI__SLOT__M	    (0x7)
#घोषणा IO7__STRV_VTR__LSI__BUS__S	    (5)
#घोषणा IO7__STRV_VTR__LSI__BUS__M	    (0x3)
#घोषणा IO7__STRV_VTR__MSI__INTNUM__S	    (0)
#घोषणा IO7__STRV_VTR__MSI__INTNUM__M	    (0x1ff)
#घोषणा IO7__STRV_VTR__IS_MSI		    (1UL << 9)

	prपूर्णांकk("%s      Uncorrectable Error Symptoms:\n", err_prपूर्णांक_prefix);
	uncrr_sym &= valid_mask;

	अगर (EXTRACT(valid_mask, IO7__PO7_UNCRR_SYM__SYN))
		prपूर्णांकk("%s        Syndrome: 0x%llx\n",
		       err_prपूर्णांक_prefix, 
		       EXTRACT(uncrr_sym, IO7__PO7_UNCRR_SYM__SYN));

	अगर (EXTRACT(valid_mask, IO7__PO7_UNCRR_SYM__ERR_CYC))
		marvel_prपूर्णांक_err_cyc(EXTRACT(uncrr_sym, 
					     IO7__PO7_UNCRR_SYM__ERR_CYC));

	scratch = EXTRACT(uncrr_sym, IO7__PO7_UNCRR_SYM__CLK);
	क्रम (i = 0; i < 4; i++, scratch >>= 2) अणु
		अगर (scratch & 0x3)
			prपूर्णांकk("%s        Clock %s: %s\n",
			       err_prपूर्णांक_prefix,
			       clk_names[i], clk_decode[scratch & 0x3]);
	पूर्ण

	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__CDT_OVF_TO__REQ) 
		prपूर्णांकk("%s       REQ Credit Timeout or Overflow\n",
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__CDT_OVF_TO__RIO) 
		prपूर्णांकk("%s       RIO Credit Timeout or Overflow\n",
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__CDT_OVF_TO__WIO) 
		prपूर्णांकk("%s       WIO Credit Timeout or Overflow\n",
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__CDT_OVF_TO__BLK) 
		prपूर्णांकk("%s       BLK Credit Timeout or Overflow\n",
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__CDT_OVF_TO__NBK) 
		prपूर्णांकk("%s       NBK Credit Timeout or Overflow\n",
		       err_prपूर्णांक_prefix);

	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__OVF__READIO) 
		prपूर्णांकk("%s       Read I/O Buffer Overflow\n", 
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__OVF__WRITEIO) 
		prपूर्णांकk("%s       Write I/O Buffer Overflow\n", 
		       err_prपूर्णांक_prefix);
	अगर (uncrr_sym & IO7__PO7_UNCRR_SYM__OVF__FWD) 
		prपूर्णांकk("%s       FWD Buffer Overflow\n", 
		       err_prपूर्णांक_prefix);

	अगर ((scratch = EXTRACT(uncrr_sym, IO7__PO7_UNCRR_SYM__VICTIM_SP))) अणु
		पूर्णांक lost = scratch & (1UL << 4);
		scratch &= ~lost;
		क्रम (i = 0; i < 8; i++, scratch >>= 1) अणु
			अगर (!(scratch & 1))
				जारी;
			prपूर्णांकk("%s        Error Response sent to %s",
			       err_prपूर्णांक_prefix, port_names[i]);
		पूर्ण
		अगर (lost)
			prपूर्णांकk("%s        Lost Error sent somewhere else\n",
			       err_prपूर्णांक_prefix);
	पूर्ण
	
	अगर ((scratch = EXTRACT(uncrr_sym, IO7__PO7_UNCRR_SYM__DETECT_SP))) अणु
		क्रम (i = 0; i < 8; i++, scratch >>= 1) अणु
			अगर (!(scratch & 1))
				जारी;
			prपूर्णांकk("%s        Error Reported by %s",
			       err_prपूर्णांक_prefix, port_names[i]);
		पूर्ण
	पूर्ण

	अगर (EXTRACT(valid_mask, IO7__PO7_UNCRR_SYM__STRV_VTR)) अणु
		अक्षर starvation_message[80];

		scratch = EXTRACT(uncrr_sym, IO7__PO7_UNCRR_SYM__STRV_VTR);
		अगर (scratch & IO7__STRV_VTR__IS_MSI) 
			प्र_लिखो(starvation_message, 
				"MSI Interrupt 0x%x",
				EXTRACT(scratch, IO7__STRV_VTR__MSI__INTNUM));
		अन्यथा
			प्र_लिखो(starvation_message,
				"LSI INT%c for Bus:Slot (%d:%d)\n",
				'A' + EXTRACT(scratch, 
					      IO7__STRV_VTR__LSI__INTX),
				EXTRACT(scratch, IO7__STRV_VTR__LSI__BUS),
				EXTRACT(scratch, IO7__STRV_VTR__LSI__SLOT));

		prपूर्णांकk("%s        Starvation Int Trigger By: %s\n",
		       err_prपूर्णांक_prefix, starvation_message);
	पूर्ण
पूर्ण

अटल व्योम
marvel_prपूर्णांक_po7_ugbge_sym(u64 ugbge_sym)
अणु
	अक्षर opcode_str[10];

#घोषणा IO7__PO7_UGBGE_SYM__UPH_PKT_OFF__S	(6)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_PKT_OFF__M	(0xfffffffful)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_OPCODE__S	(40)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_OPCODE__M	(0xff)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_SRC_PORT__S	(48)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_SRC_PORT__M	(0xf)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_DEST_PID__S	(52)
#घोषणा IO7__PO7_UGBGE_SYM__UPH_DEST_PID__M	(0x7ff)
#घोषणा IO7__PO7_UGBGE_SYM__VALID		(1UL << 63)

	अगर (!(ugbge_sym & IO7__PO7_UGBGE_SYM__VALID))
		वापस;

	चयन(EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE)) अणु
	हाल 0x51:
		प्र_लिखो(opcode_str, "Wr32");
		अवरोध;
	हाल 0x50:
		प्र_लिखो(opcode_str, "WrQW");
		अवरोध;
	हाल 0x54:
		प्र_लिखो(opcode_str, "WrIPR");
		अवरोध;
	हाल 0xD8:
		प्र_लिखो(opcode_str, "Victim");
		अवरोध;
	हाल 0xC5:
		प्र_लिखो(opcode_str, "BlkIO");
		अवरोध;
	शेष:
		प्र_लिखो(opcode_str, "0x%llx\n",
			EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE));
		अवरोध;
	पूर्ण

	prपूर्णांकk("%s      Up Hose Garbage Symptom:\n"
	       "%s        Source Port: %lld - Dest PID: %lld - OpCode: %s\n",
	       err_prपूर्णांक_prefix,
	       err_prपूर्णांक_prefix, 
	       EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_SRC_PORT),
	       EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_DEST_PID),
	       opcode_str);

	अगर (0xC5 != EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_OPCODE))
		prपूर्णांकk("%s        Packet Offset 0x%08llx\n",
		       err_prपूर्णांक_prefix,
		       EXTRACT(ugbge_sym, IO7__PO7_UGBGE_SYM__UPH_PKT_OFF));
पूर्ण

अटल व्योम
marvel_prपूर्णांक_po7_err_sum(काष्ठा ev7_pal_io_subpacket *io)
अणु
	u64	uncrr_sym_valid = 0;

#घोषणा IO7__PO7_ERRSUM__CR_SBE		(1UL << 32)
#घोषणा IO7__PO7_ERRSUM__CR_SBE2	(1UL << 33)
#घोषणा IO7__PO7_ERRSUM__CR_PIO_WBYTE	(1UL << 34)
#घोषणा IO7__PO7_ERRSUM__CR_CSR_NXM	(1UL << 35)
#घोषणा IO7__PO7_ERRSUM__CR_RPID_ACV	(1UL << 36)
#घोषणा IO7__PO7_ERRSUM__CR_RSP_NXM	(1UL << 37)
#घोषणा IO7__PO7_ERRSUM__CR_ERR_RESP	(1UL << 38)
#घोषणा IO7__PO7_ERRSUM__CR_CLK_DERR	(1UL << 39)
#घोषणा IO7__PO7_ERRSUM__CR_DAT_DBE	(1UL << 40)
#घोषणा IO7__PO7_ERRSUM__CR_DAT_GRBG	(1UL << 41)
#घोषणा IO7__PO7_ERRSUM__MAF_TO		(1UL << 42)
#घोषणा IO7__PO7_ERRSUM__UGBGE		(1UL << 43)
#घोषणा IO7__PO7_ERRSUM__UN_MAF_LOST	(1UL << 44)
#घोषणा IO7__PO7_ERRSUM__UN_PKT_OVF	(1UL << 45)
#घोषणा IO7__PO7_ERRSUM__UN_CDT_OVF	(1UL << 46)
#घोषणा IO7__PO7_ERRSUM__UN_DEALLOC	(1UL << 47)
#घोषणा IO7__PO7_ERRSUM__BH_CDT_TO	(1UL << 51)
#घोषणा IO7__PO7_ERRSUM__BH_CLK_HDR	(1UL << 52)
#घोषणा IO7__PO7_ERRSUM__BH_DBE_HDR	(1UL << 53)
#घोषणा IO7__PO7_ERRSUM__BH_GBG_HDR	(1UL << 54)
#घोषणा IO7__PO7_ERRSUM__BH_BAD_CMD	(1UL << 55)
#घोषणा IO7__PO7_ERRSUM__HLT_INT	(1UL << 56)
#घोषणा IO7__PO7_ERRSUM__HP_INT		(1UL << 57)
#घोषणा IO7__PO7_ERRSUM__CRD_INT	(1UL << 58)
#घोषणा IO7__PO7_ERRSUM__STV_INT	(1UL << 59)
#घोषणा IO7__PO7_ERRSUM__HRD_INT	(1UL << 60)
#घोषणा IO7__PO7_ERRSUM__BH_SUM		(1UL << 61)
#घोषणा IO7__PO7_ERRSUM__ERR_LST	(1UL << 62)
#घोषणा IO7__PO7_ERRSUM__ERR_VALID	(1UL << 63)

#घोषणा IO7__PO7_ERRSUM__ERR_MASK	(IO7__PO7_ERRSUM__ERR_VALID |	\
					 IO7__PO7_ERRSUM__CR_SBE)

	/*
	 * Single bit errors aren't covered by ERR_VALID.
	 */
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_SBE) अणु
		prपूर्णांकk("%s    %sSingle Bit Error(s) detected/corrected\n",
		       err_prपूर्णांक_prefix,
		       (io->po7_error_sum & IO7__PO7_ERRSUM__CR_SBE2) 
		       ? "Multiple " : "");
		marvel_prपूर्णांक_po7_crrct_sym(io->po7_crrct_sym);
	पूर्ण

	/*
	 * Neither are the पूर्णांकerrupt status bits
	 */
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__HLT_INT)
		prपूर्णांकk("%s    Halt Interrupt posted", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__HP_INT) अणु
		prपूर्णांकk("%s    Hot Plug Event Interrupt posted", 
		       err_prपूर्णांक_prefix);
		uncrr_sym_valid |= GEN_MASK(IO7__PO7_UNCRR_SYM__DETECT_SP);
	पूर्ण
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CRD_INT)
		prपूर्णांकk("%s    Correctable Error Interrupt posted", 
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__STV_INT) अणु
		prपूर्णांकk("%s    Starvation Interrupt posted", err_prपूर्णांक_prefix);
		uncrr_sym_valid |= GEN_MASK(IO7__PO7_UNCRR_SYM__STRV_VTR);
	पूर्ण
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__HRD_INT) अणु
		prपूर्णांकk("%s    Hard Error Interrupt posted", err_prपूर्णांक_prefix);
		uncrr_sym_valid |= GEN_MASK(IO7__PO7_UNCRR_SYM__DETECT_SP);
	पूर्ण

	/*
	 * Everything अन्यथा is valid only with ERR_VALID, so skip to the end
	 * (uncrr_sym check) unless ERR_VALID is set.
	 */
	अगर (!(io->po7_error_sum & IO7__PO7_ERRSUM__ERR_VALID)) 
		जाओ check_uncrr_sym;

	/*
	 * Since ERR_VALID is set, VICTIM_SP in uncrr_sym is valid.
	 * For bits [29:0] to also be valid, the following bits must
	 * not be set:
	 *	CR_PIO_WBYTE	CR_CSR_NXM	CR_RSP_NXM
	 *	CR_ERR_RESP	MAF_TO
	 */
	uncrr_sym_valid |= GEN_MASK(IO7__PO7_UNCRR_SYM__VICTIM_SP);
	अगर (!(io->po7_error_sum & (IO7__PO7_ERRSUM__CR_PIO_WBYTE |
				   IO7__PO7_ERRSUM__CR_CSR_NXM |
				   IO7__PO7_ERRSUM__CR_RSP_NXM |
				   IO7__PO7_ERRSUM__CR_ERR_RESP |
				   IO7__PO7_ERRSUM__MAF_TO)))
		uncrr_sym_valid |= 0x3ffffffful;

	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_PIO_WBYTE)
		prपूर्णांकk("%s    Write byte into IO7 CSR\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_CSR_NXM)
		prपूर्णांकk("%s    PIO to non-existent CSR\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_RPID_ACV)
		prपूर्णांकk("%s    Bus Requester PID (Access Violation)\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_RSP_NXM)
		prपूर्णांकk("%s    Received NXM response from EV7\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_ERR_RESP)
		prपूर्णांकk("%s    Received ERROR RESPONSE\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_CLK_DERR)
		prपूर्णांकk("%s    Clock error on data flit\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_DAT_DBE)
		prपूर्णांकk("%s    Double Bit Error Data Error Detected\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__CR_DAT_GRBG)
		prपूर्णांकk("%s    Garbage Encoding Detected on the data\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__UGBGE) अणु
		prपूर्णांकk("%s    Garbage Encoding sent up hose\n",
		       err_prपूर्णांक_prefix);
		marvel_prपूर्णांक_po7_ugbge_sym(io->po7_ugbge_sym);
	पूर्ण
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__UN_MAF_LOST)
		prपूर्णांकk("%s    Orphan response (unexpected response)\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__UN_PKT_OVF)
		prपूर्णांकk("%s    Down hose packet overflow\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__UN_CDT_OVF)
		prपूर्णांकk("%s    Down hose credit overflow\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__UN_DEALLOC)
		prपूर्णांकk("%s    Unexpected or bad dealloc field\n",
		       err_prपूर्णांक_prefix);

	/*
	 * The black hole events.
	 */
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__MAF_TO)
		prपूर्णांकk("%s    BLACK HOLE: Timeout for all responses\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__BH_CDT_TO)
		prपूर्णांकk("%s    BLACK HOLE: Credit Timeout\n", err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__BH_CLK_HDR)
		prपूर्णांकk("%s    BLACK HOLE: Clock check on header\n", 
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__BH_DBE_HDR)
		prपूर्णांकk("%s    BLACK HOLE: Uncorrectable Error on header\n",
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__BH_GBG_HDR)
		prपूर्णांकk("%s    BLACK HOLE: Garbage on header\n", 
		       err_prपूर्णांक_prefix);
	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__BH_BAD_CMD)
		prपूर्णांकk("%s    BLACK HOLE: Bad EV7 command\n", 
		       err_prपूर्णांक_prefix);

	अगर (io->po7_error_sum & IO7__PO7_ERRSUM__ERR_LST) 
		prपूर्णांकk("%s    Lost Error\n", err_prपूर्णांक_prefix);

	prपूर्णांकk("%s    Failing Packet:\n"
	       "%s      Cycle 1: %016llx\n"
	       "%s      Cycle 2: %016llx\n",
	       err_prपूर्णांक_prefix,
	       err_prपूर्णांक_prefix, io->po7_err_pkt0,
	       err_prपूर्णांक_prefix, io->po7_err_pkt1);
	/*
	 * If there are any valid bits in UNCRR sym क्रम this err, 
	 * prपूर्णांक UNCRR_SYM as well.
	 */
check_uncrr_sym:
	अगर (uncrr_sym_valid)
		marvel_prपूर्णांक_po7_uncrr_sym(io->po7_uncrr_sym, uncrr_sym_valid);
पूर्ण

अटल व्योम
marvel_prपूर्णांक_pox_tlb_err(u64 tlb_err)
अणु
	अटल अक्षर *tlb_errors[] = अणु
		"No Error",
		"North Port Signaled Error fetching TLB entry",
		"PTE invalid or UCC or GBG error on this entry",
		"Address did not hit any DMA window"
	पूर्ण;

#घोषणा IO7__POX_TLBERR__ERR_VALID		(1UL << 63)
#घोषणा IO7__POX_TLBERR__ERRCODE__S		(0)
#घोषणा IO7__POX_TLBERR__ERRCODE__M		(0x3)
#घोषणा IO7__POX_TLBERR__ERR_TLB_PTR__S		(3)
#घोषणा IO7__POX_TLBERR__ERR_TLB_PTR__M		(0x7)
#घोषणा IO7__POX_TLBERR__FADDR__S		(6)
#घोषणा IO7__POX_TLBERR__FADDR__M		(0x3fffffffffful)

	अगर (!(tlb_err & IO7__POX_TLBERR__ERR_VALID))
		वापस;

	prपूर्णांकk("%s      TLB Error on index 0x%llx:\n"
	       "%s        - %s\n"
	       "%s        - Addr: 0x%016llx\n",
	       err_prपूर्णांक_prefix,
	       EXTRACT(tlb_err, IO7__POX_TLBERR__ERR_TLB_PTR),
	       err_prपूर्णांक_prefix,
	       tlb_errors[EXTRACT(tlb_err, IO7__POX_TLBERR__ERRCODE)],
	       err_prपूर्णांक_prefix,
	       EXTRACT(tlb_err, IO7__POX_TLBERR__FADDR) << 6);
पूर्ण

अटल  व्योम
marvel_prपूर्णांक_pox_spl_cmplt(u64 spl_cmplt)
अणु
	अक्षर message[80];

#घोषणा IO7__POX_SPLCMPLT__MESSAGE__S		(0)
#घोषणा IO7__POX_SPLCMPLT__MESSAGE__M		(0x0fffffffful)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_BUS__S	(40)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_BUS__M	(0xfful)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_DEV__S	(35)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_DEV__M	(0x1ful)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_FUNC__S	(32)
#घोषणा IO7__POX_SPLCMPLT__SOURCE_FUNC__M	(0x07ul)

#घोषणा IO7__POX_SPLCMPLT__MSG_CLASS__S		(28)
#घोषणा IO7__POX_SPLCMPLT__MSG_CLASS__M		(0xf)
#घोषणा IO7__POX_SPLCMPLT__MSG_INDEX__S		(20)
#घोषणा IO7__POX_SPLCMPLT__MSG_INDEX__M		(0xff)
#घोषणा IO7__POX_SPLCMPLT__MSG_CLASSINDEX__S	(20)
#घोषणा IO7__POX_SPLCMPLT__MSG_CLASSINDEX__M    (0xfff)
#घोषणा IO7__POX_SPLCMPLT__REM_LOWER_ADDR__S	(12)
#घोषणा IO7__POX_SPLCMPLT__REM_LOWER_ADDR__M	(0x7f)
#घोषणा IO7__POX_SPLCMPLT__REM_BYTE_COUNT__S	(0)
#घोषणा IO7__POX_SPLCMPLT__REM_BYTE_COUNT__M	(0xfff)

	prपूर्णांकk("%s      Split Completion Error:\n"	
	       "%s         Source (Bus:Dev:Func): %lld:%lld:%lld\n",
	       err_prपूर्णांक_prefix,
	       err_prपूर्णांक_prefix,
	       EXTRACT(spl_cmplt, IO7__POX_SPLCMPLT__SOURCE_BUS),
	       EXTRACT(spl_cmplt, IO7__POX_SPLCMPLT__SOURCE_DEV),
	       EXTRACT(spl_cmplt, IO7__POX_SPLCMPLT__SOURCE_FUNC));

	चयन(EXTRACT(spl_cmplt, IO7__POX_SPLCMPLT__MSG_CLASSINDEX)) अणु
	हाल 0x000:
		प्र_लिखो(message, "Normal completion");
		अवरोध;
	हाल 0x100:
		प्र_लिखो(message, "Bridge - Master Abort");
		अवरोध;
	हाल 0x101:
		प्र_लिखो(message, "Bridge - Target Abort");
		अवरोध;
	हाल 0x102:
		प्र_लिखो(message, "Bridge - Uncorrectable Write Data Error");
		अवरोध;
	हाल 0x200:
		प्र_लिखो(message, "Byte Count Out of Range");
		अवरोध;
	हाल 0x201:
		प्र_लिखो(message, "Uncorrectable Split Write Data Error");
		अवरोध;
	शेष:
		प्र_लिखो(message, "%08llx\n",
			EXTRACT(spl_cmplt, IO7__POX_SPLCMPLT__MESSAGE));
		अवरोध;
	पूर्ण
	prपूर्णांकk("%s	   Message: %s\n", err_prपूर्णांक_prefix, message);
पूर्ण

अटल व्योम
marvel_prपूर्णांक_pox_trans_sum(u64 trans_sum)
अणु
	अटल स्थिर अक्षर * स्थिर pcix_cmd[] = अणु
		"Interrupt Acknowledge",
		"Special Cycle",
		"I/O Read",
		"I/O Write",
		"Reserved",
		"Reserved / Device ID Message",
		"Memory Read",
		"Memory Write",
		"Reserved / Alias to Memory Read Block",
		"Reserved / Alias to Memory Write Block",
		"Configuration Read",
		"Configuration Write",
		"Memory Read Multiple / Split Completion",
		"Dual Address Cycle",
		"Memory Read Line / Memory Read Block",
		"Memory Write and Invalidate / Memory Write Block"
	पूर्ण;

#घोषणा IO7__POX_TRANSUM__PCI_ADDR__S		(0)
#घोषणा IO7__POX_TRANSUM__PCI_ADDR__M		(0x3fffffffffffful)
#घोषणा IO7__POX_TRANSUM__DAC			(1UL << 50)
#घोषणा IO7__POX_TRANSUM__PCIX_MASTER_SLOT__S	(52)
#घोषणा IO7__POX_TRANSUM__PCIX_MASTER_SLOT__M	(0xf)
#घोषणा IO7__POX_TRANSUM__PCIX_CMD__S		(56)
#घोषणा IO7__POX_TRANSUM__PCIX_CMD__M		(0xf)
#घोषणा IO7__POX_TRANSUM__ERR_VALID		(1UL << 63)

	अगर (!(trans_sum & IO7__POX_TRANSUM__ERR_VALID))
		वापस;

	prपूर्णांकk("%s      Transaction Summary:\n"
	       "%s        Command: 0x%llx - %s\n"
	       "%s        Address: 0x%016llx%s\n"
	       "%s        PCI-X Master Slot: 0x%llx\n",
	       err_prपूर्णांक_prefix, 
	       err_prपूर्णांक_prefix, 
	       EXTRACT(trans_sum, IO7__POX_TRANSUM__PCIX_CMD),
	       pcix_cmd[EXTRACT(trans_sum, IO7__POX_TRANSUM__PCIX_CMD)],
	       err_prपूर्णांक_prefix,
	       EXTRACT(trans_sum, IO7__POX_TRANSUM__PCI_ADDR),
	       (trans_sum & IO7__POX_TRANSUM__DAC) ? " (DAC)" : "",
	       err_prपूर्णांक_prefix,
	       EXTRACT(trans_sum, IO7__POX_TRANSUM__PCIX_MASTER_SLOT));
पूर्ण

अटल व्योम
marvel_prपूर्णांक_pox_err(u64 err_sum, काष्ठा ev7_pal_io_one_port *port)
अणु
#घोषणा IO7__POX_ERRSUM__AGP_REQQ_OVFL    (1UL <<  4)
#घोषणा IO7__POX_ERRSUM__AGP_SYNC_ERR     (1UL <<  5)
#घोषणा IO7__POX_ERRSUM__MRETRY_TO        (1UL <<  6)
#घोषणा IO7__POX_ERRSUM__PCIX_UX_SPL      (1UL <<  7)
#घोषणा IO7__POX_ERRSUM__PCIX_SPLIT_TO    (1UL <<  8)
#घोषणा IO7__POX_ERRSUM__PCIX_DISCARD_SPL (1UL <<  9)
#घोषणा IO7__POX_ERRSUM__DMA_RD_TO        (1UL << 10)
#घोषणा IO7__POX_ERRSUM__CSR_NXM_RD       (1UL << 11)
#घोषणा IO7__POX_ERRSUM__CSR_NXM_WR       (1UL << 12)
#घोषणा IO7__POX_ERRSUM__DMA_TO           (1UL << 13)
#घोषणा IO7__POX_ERRSUM__ALL_MABORTS      (1UL << 14)
#घोषणा IO7__POX_ERRSUM__MABORT		  (1UL << 15)
#घोषणा IO7__POX_ERRSUM__MABORT_MASK	  (IO7__POX_ERRSUM__ALL_MABORTS|\
					   IO7__POX_ERRSUM__MABORT)
#घोषणा IO7__POX_ERRSUM__PT_TABORT        (1UL << 16)
#घोषणा IO7__POX_ERRSUM__PM_TABORT        (1UL << 17)
#घोषणा IO7__POX_ERRSUM__TABORT_MASK      (IO7__POX_ERRSUM__PT_TABORT | \
                                           IO7__POX_ERRSUM__PM_TABORT)
#घोषणा IO7__POX_ERRSUM__SERR             (1UL << 18)
#घोषणा IO7__POX_ERRSUM__ADDRERR_STB      (1UL << 19)
#घोषणा IO7__POX_ERRSUM__DETECTED_SERR    (1UL << 20)
#घोषणा IO7__POX_ERRSUM__PERR             (1UL << 21)
#घोषणा IO7__POX_ERRSUM__DATAERR_STB_NIOW (1UL << 22)
#घोषणा IO7__POX_ERRSUM__DETECTED_PERR    (1UL << 23)
#घोषणा IO7__POX_ERRSUM__PM_PERR          (1UL << 24)
#घोषणा IO7__POX_ERRSUM__PT_SCERROR       (1UL << 26)
#घोषणा IO7__POX_ERRSUM__HUNG_BUS         (1UL << 28)
#घोषणा IO7__POX_ERRSUM__UPE_ERROR__S     (51)
#घोषणा IO7__POX_ERRSUM__UPE_ERROR__M     (0xffUL)
#घोषणा IO7__POX_ERRSUM__UPE_ERROR        GEN_MASK(IO7__POX_ERRSUM__UPE_ERROR)
#घोषणा IO7__POX_ERRSUM__TLB_ERR          (1UL << 59)
#घोषणा IO7__POX_ERRSUM__ERR_VALID        (1UL << 63)

#घोषणा IO7__POX_ERRSUM__TRANS_SUM__MASK  (IO7__POX_ERRSUM__MRETRY_TO |       \
					   IO7__POX_ERRSUM__PCIX_UX_SPL |     \
					   IO7__POX_ERRSUM__PCIX_SPLIT_TO |   \
					   IO7__POX_ERRSUM__DMA_TO |          \
					   IO7__POX_ERRSUM__MABORT_MASK |     \
					   IO7__POX_ERRSUM__TABORT_MASK |     \
					   IO7__POX_ERRSUM__SERR |            \
					   IO7__POX_ERRSUM__ADDRERR_STB |     \
					   IO7__POX_ERRSUM__PERR |            \
					   IO7__POX_ERRSUM__DATAERR_STB_NIOW |\
					   IO7__POX_ERRSUM__DETECTED_PERR |   \
					   IO7__POX_ERRSUM__PM_PERR |         \
					   IO7__POX_ERRSUM__PT_SCERROR |      \
					   IO7__POX_ERRSUM__UPE_ERROR)

	अगर (!(err_sum & IO7__POX_ERRSUM__ERR_VALID))
		वापस;

	/*
	 * First the transaction summary errors
	 */
	अगर (err_sum & IO7__POX_ERRSUM__MRETRY_TO)
		prपूर्णांकk("%s    IO7 Master Retry Timeout expired\n",
		       err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PCIX_UX_SPL)
		prपूर्णांकk("%s    Unexpected Split Completion\n",
		       err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PCIX_SPLIT_TO)
		prपूर्णांकk("%s    IO7 Split Completion Timeout expired\n",
		       err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__DMA_TO)
		prपूर्णांकk("%s    Hung bus during DMA transaction\n",
		       err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__MABORT_MASK)
		prपूर्णांकk("%s    Master Abort\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PT_TABORT)
		prपूर्णांकk("%s    IO7 Asserted Target Abort\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PM_TABORT)
		prपूर्णांकk("%s    IO7 Received Target Abort\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__ADDRERR_STB) अणु
		prपूर्णांकk("%s    Address or PCI-X Attribute Parity Error\n", 
		       err_prपूर्णांक_prefix);
		अगर (err_sum & IO7__POX_ERRSUM__SERR)
			prपूर्णांकk("%s     IO7 Asserted SERR\n", err_prपूर्णांक_prefix);
	पूर्ण
	अगर (err_sum & IO7__POX_ERRSUM__PERR) अणु
		अगर (err_sum & IO7__POX_ERRSUM__DATAERR_STB_NIOW)
			prपूर्णांकk("%s    IO7 Detected Data Parity Error\n",
			       err_prपूर्णांक_prefix);
		अन्यथा
			prपूर्णांकk("%s    Split Completion Response with "
			       "Parity Error\n", err_prपूर्णांक_prefix);
	पूर्ण
	अगर (err_sum & IO7__POX_ERRSUM__DETECTED_PERR)
		prपूर्णांकk("%s    PERR detected\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PM_PERR)
		prपूर्णांकk("%s    PERR while IO7 is master\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PT_SCERROR) अणु
		prपूर्णांकk("%s    IO7 Received Split Completion Error message\n",
		       err_prपूर्णांक_prefix);
		marvel_prपूर्णांक_pox_spl_cmplt(port->pox_spl_cmplt);
	पूर्ण
	अगर (err_sum & IO7__POX_ERRSUM__UPE_ERROR) अणु
		अचिन्हित पूर्णांक upe_error = EXTRACT(err_sum,
						 IO7__POX_ERRSUM__UPE_ERROR);
		पूर्णांक i;
		अटल अक्षर *upe_errors[] = अणु
			"Parity Error on MSI write data",
			"MSI read (MSI window is write only",
			"TLB - Invalid WR transaction",
			"TLB - Invalid RD transaction",
			"DMA - WR error (see north port)",
			"DMA - RD error (see north port)",
			"PPR - WR error (see north port)",
			"PPR - RD error (see north port)"
		पूर्ण;

		prपूर्णांकk("%s    UPE Error:\n", err_prपूर्णांक_prefix);
		क्रम (i = 0; i < 8; i++) अणु
			अगर (upe_error & (1 << i))
				prपूर्णांकk("%s      %s\n", err_prपूर्णांक_prefix,
				       upe_errors[i]);
		पूर्ण
	पूर्ण

	/*
	 * POx_TRANS_SUM, अगर appropriate.
	 */
	अगर (err_sum & IO7__POX_ERRSUM__TRANS_SUM__MASK) 
		marvel_prपूर्णांक_pox_trans_sum(port->pox_trans_sum);

	/*
	 * Then TLB_ERR.
	 */
	अगर (err_sum & IO7__POX_ERRSUM__TLB_ERR) अणु
		prपूर्णांकk("%s    TLB ERROR\n", err_prपूर्णांक_prefix);
		marvel_prपूर्णांक_pox_tlb_err(port->pox_tlb_err);
	पूर्ण

	/*
	 * And the single bit status errors.
	 */
	अगर (err_sum & IO7__POX_ERRSUM__AGP_REQQ_OVFL)
		prपूर्णांकk("%s    AGP Request Queue Overflow\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__AGP_SYNC_ERR)
		prपूर्णांकk("%s    AGP Sync Error\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__PCIX_DISCARD_SPL)
		prपूर्णांकk("%s    Discarded split completion\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__DMA_RD_TO)
		prपूर्णांकk("%s    DMA Read Timeout\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__CSR_NXM_RD)
		prपूर्णांकk("%s    CSR NXM READ\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__CSR_NXM_WR)
		prपूर्णांकk("%s    CSR NXM WRITE\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__DETECTED_SERR)
		prपूर्णांकk("%s    SERR detected\n", err_prपूर्णांक_prefix);
	अगर (err_sum & IO7__POX_ERRSUM__HUNG_BUS)
		prपूर्णांकk("%s    HUNG BUS detected\n", err_prपूर्णांक_prefix);
पूर्ण

#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

अटल काष्ठा ev7_pal_io_subpacket *
marvel_find_io7_with_error(काष्ठा ev7_lf_subpackets *lf_subpackets)
अणु
	काष्ठा ev7_pal_io_subpacket *io = lf_subpackets->io;
	काष्ठा io7 *io7;
	पूर्णांक i;

	/*
	 * Caller must provide the packet to fill
	 */
	अगर (!io)
		वापस शून्य;

	/*
	 * Fill the subpacket with the console's standard fill pattern
	 */
	स_रखो(io, 0x55, माप(*io));

	क्रम (io7 = शून्य; शून्य != (io7 = marvel_next_io7(io7)); ) अणु
		अचिन्हित दीर्घ err_sum = 0;

		err_sum |= io7->csrs->PO7_ERROR_SUM.csr;
		क्रम (i = 0; i < IO7_NUM_PORTS; i++) अणु
			अगर (!io7->ports[i].enabled)
				जारी;
			err_sum |= io7->ports[i].csrs->POx_ERR_SUM.csr;
		पूर्ण

		/*
		 * Is there at least one error? 
		 */
		अगर (err_sum & (1UL << 63))
			अवरोध;
	पूर्ण

	/*
	 * Did we find an IO7 with an error?
	 */
	अगर (!io7)
		वापस शून्य;

	/*
	 * We have an IO7 with an error. 
	 *
	 * Fill in the IO subpacket.
	 */
	io->io_asic_rev   = io7->csrs->IO_ASIC_REV.csr;
	io->io_sys_rev    = io7->csrs->IO_SYS_REV.csr;
	io->io7_uph       = io7->csrs->IO7_UPH.csr;
	io->hpi_ctl       = io7->csrs->HPI_CTL.csr;
	io->crd_ctl       = io7->csrs->CRD_CTL.csr;
	io->hei_ctl       = io7->csrs->HEI_CTL.csr;
	io->po7_error_sum = io7->csrs->PO7_ERROR_SUM.csr;
	io->po7_uncrr_sym = io7->csrs->PO7_UNCRR_SYM.csr;
	io->po7_crrct_sym = io7->csrs->PO7_CRRCT_SYM.csr;
	io->po7_ugbge_sym = io7->csrs->PO7_UGBGE_SYM.csr;
	io->po7_err_pkt0  = io7->csrs->PO7_ERR_PKT[0].csr;
	io->po7_err_pkt1  = io7->csrs->PO7_ERR_PKT[1].csr;
	
	क्रम (i = 0; i < IO7_NUM_PORTS; i++) अणु
		io7_ioport_csrs *csrs = io7->ports[i].csrs;

		अगर (!io7->ports[i].enabled)
			जारी;

		io->ports[i].pox_err_sum   = csrs->POx_ERR_SUM.csr;
		io->ports[i].pox_tlb_err   = csrs->POx_TLB_ERR.csr;
		io->ports[i].pox_spl_cmplt = csrs->POx_SPL_COMPLT.csr;
		io->ports[i].pox_trans_sum = csrs->POx_TRANS_SUM.csr;
		io->ports[i].pox_first_err = csrs->POx_FIRST_ERR.csr;
		io->ports[i].pox_mult_err  = csrs->POx_MULT_ERR.csr;
		io->ports[i].pox_dm_source = csrs->POx_DM_SOURCE.csr;
		io->ports[i].pox_dm_dest   = csrs->POx_DM_DEST.csr;
		io->ports[i].pox_dm_size   = csrs->POx_DM_SIZE.csr;
		io->ports[i].pox_dm_ctrl   = csrs->POx_DM_CTRL.csr;

		/*
		 * Ack this port's errors, अगर any. POx_ERR_SUM must be last.
		 *
		 * Most of the error रेजिस्टरs get cleared and unlocked when
		 * the associated bits in POx_ERR_SUM are cleared (by writing
		 * 1). POx_TLB_ERR is an exception and must be explicitly 
		 * cleared.
		 */
		csrs->POx_TLB_ERR.csr = io->ports[i].pox_tlb_err;
		csrs->POx_ERR_SUM.csr =	io->ports[i].pox_err_sum;
		mb();
		csrs->POx_ERR_SUM.csr;		
	पूर्ण

	/*
	 * Ack any port 7 error(s).
	 */
	io7->csrs->PO7_ERROR_SUM.csr = io->po7_error_sum;
	mb();
	io7->csrs->PO7_ERROR_SUM.csr;
	
	/*
	 * Correct the io7_pid.
	 */
	lf_subpackets->io_pid = io7->pe;

	वापस io;
पूर्ण

अटल पूर्णांक
marvel_process_io_error(काष्ठा ev7_lf_subpackets *lf_subpackets, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
	काष्ठा ev7_pal_io_subpacket *io = lf_subpackets->io;
	पूर्णांक i;
#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

#घोषणा MARVEL_IO_ERR_VALID(x)  ((x) & (1UL << 63))

	अगर (!lf_subpackets->logout || !lf_subpackets->io)
		वापस status;

	/*
	 * The PALcode only builds an IO subpacket अगर there is a 
	 * locally connected IO7. In the हालs of
	 *	1) a uniprocessor kernel
	 *	2) an mp kernel beक्रमe the local secondary has called in
	 * error पूर्णांकerrupts are all directed to the primary processor.
	 * In that हाल, we may not have an IO subpacket at all and, event
	 * अगर we करो, it may not be the right now. 
	 *
	 * If the RBOX indicates an I/O error पूर्णांकerrupt, make sure we have
	 * the correct IO7 inक्रमmation. If we करोn't have an IO subpacket
	 * or it's the wrong one, try to find the right one.
	 *
	 * RBOX I/O error पूर्णांकerrupts are indicated by RBOX_INT<29> and
	 * RBOX_INT<10>.
	 */
	अगर ((lf_subpackets->io->po7_error_sum & (1UL << 32)) ||
	    ((lf_subpackets->io->po7_error_sum        |
	      lf_subpackets->io->ports[0].pox_err_sum |
	      lf_subpackets->io->ports[1].pox_err_sum |
	      lf_subpackets->io->ports[2].pox_err_sum |
	      lf_subpackets->io->ports[3].pox_err_sum) & (1UL << 63))) अणु
		/*
		 * Either we have no IO subpacket or no error is
		 * indicated in the one we करो have. Try find the
		 * one with the error.
		 */
		अगर (!marvel_find_io7_with_error(lf_subpackets))
			वापस status;
	पूर्ण

	/*
	 * We have an IO7 indicating an error - we're going to report it
	 */
	status = MCHK_DISPOSITION_REPORT;

#अगर_घोषित CONFIG_VERBOSE_MCHECK

	अगर (!prपूर्णांक)
		वापस status;

	prपूर्णांकk("%s*Error occurred on IO7 at PID %u\n", 
	       err_prपूर्णांक_prefix, lf_subpackets->io_pid);

	/*
	 * Check port 7 first
	 */
	अगर (lf_subpackets->io->po7_error_sum & IO7__PO7_ERRSUM__ERR_MASK) अणु
		marvel_prपूर्णांक_po7_err_sum(io);

#अगर 0
		prपूर्णांकk("%s  PORT 7 ERROR:\n"
		       "%s    PO7_ERROR_SUM: %016llx\n"
		       "%s    PO7_UNCRR_SYM: %016llx\n"
		       "%s    PO7_CRRCT_SYM: %016llx\n"
		       "%s    PO7_UGBGE_SYM: %016llx\n"
		       "%s    PO7_ERR_PKT0:  %016llx\n"
		       "%s    PO7_ERR_PKT1:  %016llx\n",
		       err_prपूर्णांक_prefix,
		       err_prपूर्णांक_prefix, io->po7_error_sum,
		       err_prपूर्णांक_prefix, io->po7_uncrr_sym,
		       err_prपूर्णांक_prefix, io->po7_crrct_sym,
		       err_prपूर्णांक_prefix, io->po7_ugbge_sym,
		       err_prपूर्णांक_prefix, io->po7_err_pkt0,
		       err_prपूर्णांक_prefix, io->po7_err_pkt1);
#पूर्ण_अगर
	पूर्ण

	/*
	 * Then loop through the ports
	 */
	क्रम (i = 0; i < IO7_NUM_PORTS; i++) अणु
		अगर (!MARVEL_IO_ERR_VALID(io->ports[i].pox_err_sum))
			जारी;

		prपूर्णांकk("%s  PID %u PORT %d POx_ERR_SUM: %016llx\n",
		       err_prपूर्णांक_prefix, 
		       lf_subpackets->io_pid, i, io->ports[i].pox_err_sum);
		marvel_prपूर्णांक_pox_err(io->ports[i].pox_err_sum, &io->ports[i]);

		prपूर्णांकk("%s  [ POx_FIRST_ERR: %016llx ]\n",
		       err_prपूर्णांक_prefix, io->ports[i].pox_first_err);
		marvel_prपूर्णांक_pox_err(io->ports[i].pox_first_err, 
				     &io->ports[i]);

	पूर्ण


#पूर्ण_अगर /* CONFIG_VERBOSE_MCHECK */

	वापस status;
पूर्ण

अटल पूर्णांक
marvel_process_logout_frame(काष्ठा ev7_lf_subpackets *lf_subpackets, पूर्णांक prपूर्णांक)
अणु
	पूर्णांक status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	/*
	 * I/O error? 
	 */
#घोषणा EV7__RBOX_INT__IO_ERROR__MASK 0x20000400ul
	अगर (lf_subpackets->logout &&
	    (lf_subpackets->logout->rbox_पूर्णांक & 0x20000400ul))
		status = marvel_process_io_error(lf_subpackets, prपूर्णांक);

	/*
	 * Probing behind PCI-X bridges can cause machine checks on
	 * Marvel when the probe is handled by the bridge as a split
	 * completion transaction. The symptom is an ERROR_RESPONSE 
	 * to a CONFIG address. Since these errors will happen in
	 * normal operation, dismiss them.
	 *
	 * Dismiss अगर:
	 *	C_STAT		= 0x14 		(Error Response)
	 *	C_STS<3>	= 0    		(C_ADDR valid)
	 *	C_ADDR<42>	= 1    		(I/O)
	 *	C_ADDR<31:22>	= 111110xxb	(PCI Config space)
	 */
	अगर (lf_subpackets->ev7 &&
	    (lf_subpackets->ev7->c_stat == 0x14) &&
	    !(lf_subpackets->ev7->c_sts & 0x8) &&
	    ((lf_subpackets->ev7->c_addr & 0x400ff000000ul) 
	     == 0x400fe000000ul))
		status = MCHK_DISPOSITION_DISMISS;

	वापस status;
पूर्ण

व्योम
marvel_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_subpacket *el_ptr = (काष्ठा el_subpacket *)la_ptr;
	पूर्णांक (*process_frame)(काष्ठा ev7_lf_subpackets *, पूर्णांक) = शून्य;
	काष्ठा ev7_lf_subpackets subpacket_collection = अणु शून्य, पूर्ण;
	काष्ठा ev7_pal_io_subpacket scratch_io_packet = अणु 0, पूर्ण;
	काष्ठा ev7_lf_subpackets *lf_subpackets = शून्य;
	पूर्णांक disposition = MCHK_DISPOSITION_UNKNOWN_ERROR;
	अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;
	अक्षर *error_type = शून्य;

	/*
	 * Sync the processor
	 */
	mb();
	draina();

	चयन(vector) अणु
	हाल SCB_Q_SYSEVENT:
		process_frame = marvel_process_680_frame;
		error_type = "System Event";
		अवरोध;

	हाल SCB_Q_SYSMCHK:
		process_frame = marvel_process_logout_frame;
		error_type = "System Uncorrectable Error";
		अवरोध;

	हाल SCB_Q_SYSERR:
		process_frame = marvel_process_logout_frame;
		error_type = "System Correctable Error";
		अवरोध;

	शेष:
		/* Don't know it - pass it up.  */
		ev7_machine_check(vector, la_ptr);
		वापस;
	पूर्ण	

	/*
	 * A प्रणाली event or error has occurred, handle it here.
	 *
	 * Any errors in the logout frame have alपढ़ोy been cleared by the
	 * PALcode, so just parse it.
	 */
	err_prपूर्णांक_prefix = KERN_CRIT;

	/* 
	 * Parse the logout frame without prपूर्णांकing first. If the only error(s)
	 * found are classअगरied as "dismissable", then just dismiss them and
	 * करोn't prपूर्णांक any message
	 */
	lf_subpackets = 
		ev7_collect_logout_frame_subpackets(el_ptr,
						    &subpacket_collection);
	अगर (process_frame && lf_subpackets && lf_subpackets->logout) अणु
		/*
		 * We might not have the correct (or any) I/O subpacket.
		 * [ See marvel_process_io_error() क्रम explanation. ]
		 * If we करोn't have one, poपूर्णांक the io subpacket in
		 * lf_subpackets at scratch_io_packet so that 
		 * marvel_find_io7_with_error() will have someplace to
		 * store the info.
		 */
		अगर (!lf_subpackets->io)
			lf_subpackets->io = &scratch_io_packet;

		/*
		 * Default io_pid to the processor reporting the error
		 * [this will get changed in marvel_find_io7_with_error()
		 * अगर a dअगरferent one is needed]
		 */
		lf_subpackets->io_pid = lf_subpackets->logout->whami;

		/*
		 * Evaluate the frames.
		 */
		disposition = process_frame(lf_subpackets, 0);
	पूर्ण
	चयन(disposition) अणु
	हाल MCHK_DISPOSITION_DISMISS:
		/* Nothing to करो. */
		अवरोध;

	हाल MCHK_DISPOSITION_REPORT:
		/* Recognized error, report it. */
		prपूर्णांकk("%s*%s (Vector 0x%x) reported on CPU %d\n",
		       err_prपूर्णांक_prefix, error_type,
		       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
		el_prपूर्णांक_बारtamp(&lf_subpackets->logout->बारtamp);
		process_frame(lf_subpackets, 1);
		अवरोध;

	शेष:
		/* Unknown - dump the annotated subpackets. */
		prपूर्णांकk("%s*%s (Vector 0x%x) reported on CPU %d\n",
		       err_prपूर्णांक_prefix, error_type,
		       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
		el_process_subpacket(el_ptr);
		अवरोध;

	पूर्ण

	err_prपूर्णांक_prefix = saved_err_prefix;

        /* Release the logout frame.  */
	wrmces(0x7);
	mb();
पूर्ण

व्योम __init
marvel_रेजिस्टर_error_handlers(व्योम)
अणु
	ev7_रेजिस्टर_error_handlers();
पूर्ण
