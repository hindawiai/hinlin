<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spu_restore.c
 *
 * (C) Copyright IBM Corp. 2005
 *
 * SPU-side context restore sequence outlined in
 * Synergistic Processor Element Book IV
 *
 * Author: Mark Nutter <mnutter@us.ibm.com>
 */


#अगर_अघोषित LS_SIZE
#घोषणा LS_SIZE                 0x40000	/* 256K (in bytes) */
#पूर्ण_अगर

प्रकार अचिन्हित पूर्णांक u32;
प्रकार अचिन्हित दीर्घ दीर्घ u64;

#समावेश <spu_पूर्णांकrinsics.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश "spu_utils.h"

#घोषणा BR_INSTR		0x327fff80	/* br -4         */
#घोषणा NOP_INSTR		0x40200000	/* nop           */
#घोषणा HEQ_INSTR		0x7b000000	/* heq $0, $0    */
#घोषणा STOP_INSTR		0x00000000	/* stop 0x0      */
#घोषणा ILLEGAL_INSTR		0x00800000	/* illegal instr */
#घोषणा RESTORE_COMPLETE	0x00003ffc	/* stop 0x3ffc   */

अटल अंतरभूत व्योम fetch_regs_from_mem(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ls = (अचिन्हित पूर्णांक)&regs_spill[0];
	अचिन्हित पूर्णांक size = माप(regs_spill);
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0x40;	/* GET */

	spu_ग_लिखोch(MFC_LSA, ls);
	spu_ग_लिखोch(MFC_EAH, lscsa_ea.ui[0]);
	spu_ग_लिखोch(MFC_EAL, lscsa_ea.ui[1]);
	spu_ग_लिखोch(MFC_Size, size);
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम restore_upper_240kb(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ls = 16384;
	अचिन्हित पूर्णांक list = (अचिन्हित पूर्णांक)&dma_list[0];
	अचिन्हित पूर्णांक size = माप(dma_list);
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0x44;	/* GETL */

	/* Restore, Step 4:
	 *    Enqueue the GETL command (tag 0) to the MFC SPU command
	 *    queue to transfer the upper 240 kb of LS from CSA.
	 */
	spu_ग_लिखोch(MFC_LSA, ls);
	spu_ग_लिखोch(MFC_EAH, lscsa_ea.ui[0]);
	spu_ग_लिखोch(MFC_EAL, list);
	spu_ग_लिखोch(MFC_Size, size);
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम restore_decr(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक decr_running;
	अचिन्हित पूर्णांक decr;

	/* Restore, Step 6(moved):
	 *    If the LSCSA "decrementer running" flag is set
	 *    then ग_लिखो the SPU_WrDec channel with the
	 *    decrementer value from LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(decr_status);
	decr_running = regs_spill[offset].slot[0] & SPU_DECR_STATUS_RUNNING;
	अगर (decr_running) अणु
		offset = LSCSA_QW_OFFSET(decr);
		decr = regs_spill[offset].slot[0];
		spu_ग_लिखोch(SPU_WrDec, decr);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_ppu_mb(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक data;

	/* Restore, Step 11:
	 *    Write the MFC_WrOut_MB channel with the PPU_MB
	 *    data from LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(ppu_mb);
	data = regs_spill[offset].slot[0];
	spu_ग_लिखोch(SPU_WrOutMbox, data);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_ppuपूर्णांक_mb(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक data;

	/* Restore, Step 12:
	 *    Write the MFC_WrInt_MB channel with the PPUINT_MB
	 *    data from LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(ppuपूर्णांक_mb);
	data = regs_spill[offset].slot[0];
	spu_ग_लिखोch(SPU_WrOutIntrMbox, data);
पूर्ण

अटल अंतरभूत व्योम restore_fpcr(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	vector अचिन्हित पूर्णांक fpcr;

	/* Restore, Step 13:
	 *    Restore the भग्नing-poपूर्णांक status and control
	 *    रेजिस्टर from the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(fpcr);
	fpcr = regs_spill[offset].v;
	spu_mtfpscr(fpcr);
पूर्ण

अटल अंतरभूत व्योम restore_srr0(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक srr0;

	/* Restore, Step 14:
	 *    Restore the SPU SRR0 data from the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(srr0);
	srr0 = regs_spill[offset].slot[0];
	spu_ग_लिखोch(SPU_WrSRR0, srr0);
पूर्ण

अटल अंतरभूत व्योम restore_event_mask(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक event_mask;

	/* Restore, Step 15:
	 *    Restore the SPU_RdEventMsk data from the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(event_mask);
	event_mask = regs_spill[offset].slot[0];
	spu_ग_लिखोch(SPU_WrEventMask, event_mask);
पूर्ण

अटल अंतरभूत व्योम restore_tag_mask(व्योम)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक tag_mask;

	/* Restore, Step 16:
	 *    Restore the SPU_RdTagMsk data from the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(tag_mask);
	tag_mask = regs_spill[offset].slot[0];
	spu_ग_लिखोch(MFC_WrTagMask, tag_mask);
पूर्ण

अटल अंतरभूत व्योम restore_complete(व्योम)
अणु
	बाह्य व्योम निकास_fini(व्योम);
	अचिन्हित पूर्णांक *निकास_instrs = (अचिन्हित पूर्णांक *)निकास_fini;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक stopped_status;
	अचिन्हित पूर्णांक stopped_code;

	/* Restore, Step 18:
	 *    Issue a stop-and-संकेत inकाष्ठाion with
	 *    "good context restore" संकेत value.
	 *
	 * Restore, Step 19:
	 *    There may be additional inकाष्ठाions placed
	 *    here by the PPE Sequence क्रम SPU Context
	 *    Restore in order to restore the correct
	 *    "stopped state".
	 *
	 *    This step is handled here by analyzing the
	 *    LSCSA.stopped_status and then modअगरying the
	 *    निकास() function to behave appropriately.
	 */

	offset = LSCSA_QW_OFFSET(stopped_status);
	stopped_status = regs_spill[offset].slot[0];
	stopped_code = regs_spill[offset].slot[1];

	चयन (stopped_status) अणु
	हाल SPU_STOPPED_STATUS_P_I:
		/* SPU_Status[P,I]=1.  Add illegal inकाष्ठाion
		 * followed by stop-and-संकेत inकाष्ठाion after
		 * end of restore code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = ILLEGAL_INSTR;
		निकास_instrs[2] = STOP_INSTR | stopped_code;
		अवरोध;
	हाल SPU_STOPPED_STATUS_P_H:
		/* SPU_Status[P,H]=1.  Add 'heq $0, $0' followed
		 * by stop-and-संकेत inकाष्ठाion after end of
		 * restore code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = HEQ_INSTR;
		निकास_instrs[2] = STOP_INSTR | stopped_code;
		अवरोध;
	हाल SPU_STOPPED_STATUS_S_P:
		/* SPU_Status[S,P]=1.  Add nop inकाष्ठाion
		 * followed by 'br -4' after end of restore
		 * code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = STOP_INSTR | stopped_code;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	हाल SPU_STOPPED_STATUS_S_I:
		/* SPU_Status[S,I]=1.  Add  illegal inकाष्ठाion
		 * followed by 'br -4' after end of restore code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = ILLEGAL_INSTR;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	हाल SPU_STOPPED_STATUS_I:
		/* SPU_Status[I]=1. Add illegal inकाष्ठाion followed
		 * by infinite loop after end of restore sequence.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = ILLEGAL_INSTR;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	हाल SPU_STOPPED_STATUS_S:
		/* SPU_Status[S]=1. Add two 'nop' inकाष्ठाions. */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = NOP_INSTR;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	हाल SPU_STOPPED_STATUS_H:
		/* SPU_Status[H]=1. Add 'heq $0, $0' inकाष्ठाion
		 * after end of restore code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = HEQ_INSTR;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	हाल SPU_STOPPED_STATUS_P:
		/* SPU_Status[P]=1. Add stop-and-संकेत inकाष्ठाion
		 * after end of restore code.
		 */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = STOP_INSTR | stopped_code;
		अवरोध;
	हाल SPU_STOPPED_STATUS_R:
		/* SPU_Status[I,S,H,P,R]=0. Add infinite loop. */
		निकास_instrs[0] = RESTORE_COMPLETE;
		निकास_instrs[1] = NOP_INSTR;
		निकास_instrs[2] = NOP_INSTR;
		निकास_instrs[3] = BR_INSTR;
		अवरोध;
	शेष:
		/* SPU_Status[R]=1. No additional inकाष्ठाions. */
		अवरोध;
	पूर्ण
	spu_sync();
पूर्ण

/**
 * मुख्य - entry poपूर्णांक क्रम SPU-side context restore.
 *
 * This code deviates from the करोcumented sequence in the
 * following aspects:
 *
 *	1. The EA क्रम LSCSA is passed from PPE in the
 *	   संकेत notअगरication channels.
 *	2. The रेजिस्टर spill area is pulled by SPU
 *	   पूर्णांकo LS, rather than pushed by PPE.
 *	3. All 128 रेजिस्टरs are restored by निकास().
 *	4. The निकास() function is modअगरied at run
 *	   समय in order to properly restore the
 *	   SPU_Status रेजिस्टर.
 */
पूर्णांक मुख्य()
अणु
	addr64 lscsa_ea;

	lscsa_ea.ui[0] = spu_पढ़ोch(SPU_RdSigNotअगरy1);
	lscsa_ea.ui[1] = spu_पढ़ोch(SPU_RdSigNotअगरy2);
	fetch_regs_from_mem(lscsa_ea);

	set_event_mask();		/* Step 1.  */
	set_tag_mask();			/* Step 2.  */
	build_dma_list(lscsa_ea);	/* Step 3.  */
	restore_upper_240kb(lscsa_ea);	/* Step 4.  */
					/* Step 5: करोne by 'exit'. */
	enqueue_putllc(lscsa_ea);	/* Step 7. */
	set_tag_update();		/* Step 8. */
	पढ़ो_tag_status();		/* Step 9. */
	restore_decr();			/* moved Step 6. */
	पढ़ो_llar_status();		/* Step 10. */
	ग_लिखो_ppu_mb();			/* Step 11. */
	ग_लिखो_ppuपूर्णांक_mb();		/* Step 12. */
	restore_fpcr();			/* Step 13. */
	restore_srr0();			/* Step 14. */
	restore_event_mask();		/* Step 15. */
	restore_tag_mask();		/* Step 16. */
					/* Step 17. करोne by 'exit'. */
	restore_complete();		/* Step 18. */

	वापस 0;
पूर्ण
