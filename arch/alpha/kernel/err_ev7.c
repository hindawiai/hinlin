<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/err_ev7.c
 *
 *	Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 *	Error handling code supporting Alpha प्रणालीs
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/err_common.h>
#समावेश <यंत्र/err_ev7.h>

#समावेश "err_impl.h"
#समावेश "proto.h"

काष्ठा ev7_lf_subpackets *
ev7_collect_logout_frame_subpackets(काष्ठा el_subpacket *el_ptr,
				    काष्ठा ev7_lf_subpackets *lf_subpackets)
अणु
	काष्ठा el_subpacket *subpacket;
	पूर्णांक i;

	/*
	 * A Marvel machine check frame is always packaged in an
	 * el_subpacket of class HEADER, type LOGOUT_FRAME.
	 */
	अगर (el_ptr->class != EL_CLASS__HEADER || 
	    el_ptr->type != EL_TYPE__HEADER__LOGOUT_FRAME)
		वापस शून्य;

	/*
	 * It is a logout frame header. Look at the one subpacket.
	 */
	el_ptr = (काष्ठा el_subpacket *)
		((अचिन्हित दीर्घ)el_ptr + el_ptr->length);

	/*
	 * It has to be class PAL, type LOGOUT_FRAME.
	 */
	अगर (el_ptr->class != EL_CLASS__PAL ||
	    el_ptr->type != EL_TYPE__PAL__LOGOUT_FRAME)
		वापस शून्य;

	lf_subpackets->logout = (काष्ठा ev7_pal_logout_subpacket *)
		el_ptr->by_type.raw.data_start;

	/*
	 * Process the subpackets.
	 */
	subpacket = (काष्ठा el_subpacket *)
		((अचिन्हित दीर्घ)el_ptr + el_ptr->length);
	क्रम (i = 0;
	     subpacket && i < lf_subpackets->logout->subpacket_count;
	     subpacket = (काष्ठा el_subpacket *)
		     ((अचिन्हित दीर्घ)subpacket + subpacket->length), i++) अणु
		/*
		 * All subpackets should be class PAL.
		 */
		अगर (subpacket->class != EL_CLASS__PAL) अणु
			prपूर्णांकk("%s**UNEXPECTED SUBPACKET CLASS %d "
			       "IN LOGOUT FRAME (packet %d\n",
			       err_prपूर्णांक_prefix, subpacket->class, i);
			वापस शून्य;
		पूर्ण

		/*
		 * Remember the subpacket.
		 */
		चयन(subpacket->type) अणु
		हाल EL_TYPE__PAL__EV7_PROCESSOR:
			lf_subpackets->ev7 =
				(काष्ठा ev7_pal_processor_subpacket *)
				subpacket->by_type.raw.data_start;
			अवरोध;

		हाल EL_TYPE__PAL__EV7_RBOX:
			lf_subpackets->rbox = (काष्ठा ev7_pal_rbox_subpacket *)
				subpacket->by_type.raw.data_start;
			अवरोध;

		हाल EL_TYPE__PAL__EV7_ZBOX:
			lf_subpackets->zbox = (काष्ठा ev7_pal_zbox_subpacket *)
				subpacket->by_type.raw.data_start;
			अवरोध;

		हाल EL_TYPE__PAL__EV7_IO:
			lf_subpackets->io = (काष्ठा ev7_pal_io_subpacket *)
				subpacket->by_type.raw.data_start;
			अवरोध;

		हाल EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE:
		हाल EL_TYPE__PAL__ENV__AIRMOVER_FAN:
		हाल EL_TYPE__PAL__ENV__VOLTAGE:
		हाल EL_TYPE__PAL__ENV__INTRUSION:
		हाल EL_TYPE__PAL__ENV__POWER_SUPPLY:
		हाल EL_TYPE__PAL__ENV__LAN:
		हाल EL_TYPE__PAL__ENV__HOT_PLUG:
			lf_subpackets->env[ev7_lf_env_index(subpacket->type)] =
 				(काष्ठा ev7_pal_environmental_subpacket *)
				subpacket->by_type.raw.data_start;
			अवरोध;
				
		शेष:
			/*
			 * Don't know what kind of frame this is.
			 */
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस lf_subpackets;
पूर्ण

व्योम
ev7_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
	काष्ठा el_subpacket *el_ptr = (काष्ठा el_subpacket *)la_ptr;
	अक्षर *saved_err_prefix = err_prपूर्णांक_prefix;

	/*
	 * Sync the processor
	 */
	mb();
	draina();

	err_prपूर्णांक_prefix = KERN_CRIT;
	prपूर्णांकk("%s*CPU %s Error (Vector 0x%x) reported on CPU %d\n",
	       err_prपूर्णांक_prefix, 
	       (vector == SCB_Q_PROCERR) ? "Correctable" : "Uncorrectable",
	       (अचिन्हित पूर्णांक)vector, (पूर्णांक)smp_processor_id());
	el_process_subpacket(el_ptr);
	err_prपूर्णांक_prefix = saved_err_prefix;

	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
पूर्ण

अटल अक्षर *el_ev7_processor_subpacket_annotation[] = अणु
	"Subpacket Header",	"I_STAT",	"DC_STAT",
	"C_ADDR",		"C_SYNDROME_1",	"C_SYNDROME_0",
	"C_STAT",		"C_STS",	"MM_STAT",
	"EXC_ADDR",		"IER_CM",	"ISUM",
	"PAL_BASE",		"I_CTL",	"PROCESS_CONTEXT",
	"CBOX_CTL",		"CBOX_STP_CTL",	"CBOX_ACC_CTL",
	"CBOX_LCL_SET",		"CBOX_GLB_SET",	"BBOX_CTL",
	"BBOX_ERR_STS",		"BBOX_ERR_IDX",	"CBOX_DDP_ERR_STS",
	"BBOX_DAT_RMP",		शून्य
पूर्ण;

अटल अक्षर *el_ev7_zbox_subpacket_annotation[] = अणु
	"Subpacket Header", 	
	"ZBOX(0): DRAM_ERR_STATUS_2 / DRAM_ERR_STATUS_1",
	"ZBOX(0): DRAM_ERROR_CTL    / DRAM_ERR_STATUS_3",
	"ZBOX(0): DIFT_TIMEOUT      / DRAM_ERR_ADR",
	"ZBOX(0): FRC_ERR_ADR       / DRAM_MAPPER_CTL",
	"ZBOX(0): reserved          / DIFT_ERR_STATUS",
	"ZBOX(1): DRAM_ERR_STATUS_2 / DRAM_ERR_STATUS_1",
	"ZBOX(1): DRAM_ERROR_CTL    / DRAM_ERR_STATUS_3",
	"ZBOX(1): DIFT_TIMEOUT      / DRAM_ERR_ADR",
	"ZBOX(1): FRC_ERR_ADR       / DRAM_MAPPER_CTL",
	"ZBOX(1): reserved          / DIFT_ERR_STATUS",
	"CBOX_CTL",		"CBOX_STP_CTL",
	"ZBOX(0)_ERROR_PA",	"ZBOX(1)_ERROR_PA",
	"ZBOX(0)_ORED_SYNDROME","ZBOX(1)_ORED_SYNDROME",
	शून्य
पूर्ण;

अटल अक्षर *el_ev7_rbox_subpacket_annotation[] = अणु
	"Subpacket Header",	"RBOX_CFG",	"RBOX_N_CFG",
	"RBOX_S_CFG",		"RBOX_E_CFG",	"RBOX_W_CFG",
	"RBOX_N_ERR",		"RBOX_S_ERR",	"RBOX_E_ERR",
	"RBOX_W_ERR",		"RBOX_IO_CFG",	"RBOX_IO_ERR",
	"RBOX_L_ERR",		"RBOX_WHOAMI",	"RBOX_IMASL",
	"RBOX_INTQ",		"RBOX_INT",	शून्य
पूर्ण;

अटल अक्षर *el_ev7_io_subpacket_annotation[] = अणु
	"Subpacket Header",	"IO_ASIC_REV",	"IO_SYS_REV",
	"IO7_UPH",		"HPI_CTL",	"CRD_CTL",
	"HEI_CTL",		"PO7_ERROR_SUM","PO7_UNCRR_SYM",
	"PO7_CRRCT_SYM",	"PO7_UGBGE_SYM","PO7_ERR_PKT0",
	"PO7_ERR_PKT1",		"reserved",	"reserved",
	"PO0_ERR_SUM",		"PO0_TLB_ERR",	"PO0_SPL_COMPLT",
	"PO0_TRANS_SUM",	"PO0_FIRST_ERR","PO0_MULT_ERR",
	"DM CSR PH",		"DM CSR PH",	"DM CSR PH",
	"DM CSR PH",		"reserved",
	"PO1_ERR_SUM",		"PO1_TLB_ERR",	"PO1_SPL_COMPLT",
	"PO1_TRANS_SUM",	"PO1_FIRST_ERR","PO1_MULT_ERR",
	"DM CSR PH",		"DM CSR PH",	"DM CSR PH",
	"DM CSR PH",		"reserved",
	"PO2_ERR_SUM",		"PO2_TLB_ERR",	"PO2_SPL_COMPLT",
	"PO2_TRANS_SUM",	"PO2_FIRST_ERR","PO2_MULT_ERR",
	"DM CSR PH",		"DM CSR PH",	"DM CSR PH",
	"DM CSR PH",		"reserved",
	"PO3_ERR_SUM",		"PO3_TLB_ERR",	"PO3_SPL_COMPLT",
	"PO3_TRANS_SUM",	"PO3_FIRST_ERR","PO3_MULT_ERR",
	"DM CSR PH",		"DM CSR PH",	"DM CSR PH",
	"DM CSR PH",		"reserved",	
	शून्य
पूर्ण;
	
अटल काष्ठा el_subpacket_annotation el_ev7_pal_annotations[] = अणु
	SUBPACKET_ANNOTATION(EL_CLASS__PAL,
			     EL_TYPE__PAL__EV7_PROCESSOR,
			     1,
			     "EV7 Processor Subpacket",
			     el_ev7_processor_subpacket_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__PAL,
			     EL_TYPE__PAL__EV7_ZBOX,
			     1,
			     "EV7 ZBOX Subpacket",
			     el_ev7_zbox_subpacket_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__PAL,
			     EL_TYPE__PAL__EV7_RBOX,
			     1,
			     "EV7 RBOX Subpacket",
			     el_ev7_rbox_subpacket_annotation),
	SUBPACKET_ANNOTATION(EL_CLASS__PAL,
			     EL_TYPE__PAL__EV7_IO,
			     1,
			     "EV7 IO Subpacket",
			     el_ev7_io_subpacket_annotation)
पूर्ण;

अटल काष्ठा el_subpacket *
ev7_process_pal_subpacket(काष्ठा el_subpacket *header)
अणु
	काष्ठा ev7_pal_subpacket *packet;

	अगर (header->class != EL_CLASS__PAL) अणु
		prपूर्णांकk("%s  ** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_prपूर्णांक_prefix,
		       header->class, header->type);
		वापस शून्य;
	पूर्ण

	packet = (काष्ठा ev7_pal_subpacket *)header->by_type.raw.data_start;

	चयन(header->type) अणु
	हाल EL_TYPE__PAL__LOGOUT_FRAME:
		prपूर्णांकk("%s*** MCHK occurred on LPID %lld (RBOX %llx)\n",
		       err_prपूर्णांक_prefix,
		       packet->by_type.logout.whami, 
		       packet->by_type.logout.rbox_whami);
		el_prपूर्णांक_बारtamp(&packet->by_type.logout.बारtamp);
		prपूर्णांकk("%s  EXC_ADDR: %016llx\n"
		         "  HALT_CODE: %llx\n",
		       err_prपूर्णांक_prefix,
		       packet->by_type.logout.exc_addr,
		       packet->by_type.logout.halt_code);
		el_process_subpackets(header,
                                      packet->by_type.logout.subpacket_count);
		अवरोध;
	शेष:
		prपूर्णांकk("%s  ** PAL TYPE %d SUBPACKET\n", 
		       err_prपूर्णांक_prefix,
		       header->type);
		el_annotate_subpacket(header);
		अवरोध;
	पूर्ण
	
	वापस (काष्ठा el_subpacket *)((अचिन्हित दीर्घ)header + header->length);
पूर्ण

काष्ठा el_subpacket_handler ev7_pal_subpacket_handler =
	SUBPACKET_HANDLER_INIT(EL_CLASS__PAL, ev7_process_pal_subpacket);

व्योम __init
ev7_रेजिस्टर_error_handlers(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(el_ev7_pal_annotations); i++)
		cdl_रेजिस्टर_subpacket_annotation(&el_ev7_pal_annotations[i]);

	cdl_रेजिस्टर_subpacket_handler(&ev7_pal_subpacket_handler);
पूर्ण

