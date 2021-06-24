<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spu_save.c
 *
 * (C) Copyright IBM Corp. 2005
 *
 * SPU-side context save sequence outlined in
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

अटल अंतरभूत व्योम save_event_mask(व्योम)
अणु
	अचिन्हित पूर्णांक offset;

	/* Save, Step 2:
	 *    Read the SPU_RdEventMsk channel and save to the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(event_mask);
	regs_spill[offset].slot[0] = spu_पढ़ोch(SPU_RdEventMask);
पूर्ण

अटल अंतरभूत व्योम save_tag_mask(व्योम)
अणु
	अचिन्हित पूर्णांक offset;

	/* Save, Step 3:
	 *    Read the SPU_RdTagMsk channel and save to the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(tag_mask);
	regs_spill[offset].slot[0] = spu_पढ़ोch(MFC_RdTagMask);
पूर्ण

अटल अंतरभूत व्योम save_upper_240kb(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ls = 16384;
	अचिन्हित पूर्णांक list = (अचिन्हित पूर्णांक)&dma_list[0];
	अचिन्हित पूर्णांक size = माप(dma_list);
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0x24;	/* PUTL */

	/* Save, Step 7:
	 *    Enqueue the PUTL command (tag 0) to the MFC SPU command
	 *    queue to transfer the reमुख्यing 240 kb of LS to CSA.
	 */
	spu_ग_लिखोch(MFC_LSA, ls);
	spu_ग_लिखोch(MFC_EAH, lscsa_ea.ui[0]);
	spu_ग_लिखोch(MFC_EAL, list);
	spu_ग_लिखोch(MFC_Size, size);
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम save_fpcr(व्योम)
अणु
	// vector अचिन्हित पूर्णांक fpcr;
	अचिन्हित पूर्णांक offset;

	/* Save, Step 9:
	 *    Issue the भग्नing-poपूर्णांक status and control रेजिस्टर
	 *    पढ़ो inकाष्ठाion, and save to the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(fpcr);
	regs_spill[offset].v = spu_mffpscr();
पूर्ण

अटल अंतरभूत व्योम save_decr(व्योम)
अणु
	अचिन्हित पूर्णांक offset;

	/* Save, Step 10:
	 *    Read and save the SPU_RdDec channel data to
	 *    the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(decr);
	regs_spill[offset].slot[0] = spu_पढ़ोch(SPU_RdDec);
पूर्ण

अटल अंतरभूत व्योम save_srr0(व्योम)
अणु
	अचिन्हित पूर्णांक offset;

	/* Save, Step 11:
	 *    Read and save the SPU_WSRR0 channel data to
	 *    the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(srr0);
	regs_spill[offset].slot[0] = spu_पढ़ोch(SPU_RdSRR0);
पूर्ण

अटल अंतरभूत व्योम spill_regs_to_mem(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ls = (अचिन्हित पूर्णांक)&regs_spill[0];
	अचिन्हित पूर्णांक size = माप(regs_spill);
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0x20;	/* PUT */

	/* Save, Step 13:
	 *    Enqueue a PUT command (tag 0) to send the LSCSA
	 *    to the CSA.
	 */
	spu_ग_लिखोch(MFC_LSA, ls);
	spu_ग_लिखोch(MFC_EAH, lscsa_ea.ui[0]);
	spu_ग_लिखोch(MFC_EAL, lscsa_ea.ui[1]);
	spu_ग_लिखोch(MFC_Size, size);
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम enqueue_sync(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0xCC;

	/* Save, Step 14:
	 *    Enqueue an MFC_SYNC command (tag 0).
	 */
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम save_complete(व्योम)
अणु
	/* Save, Step 18:
	 *    Issue a stop-and-संकेत inकाष्ठाion indicating
	 *    "save complete".  Note: This function will not
	 *    वापस!!
	 */
	spu_stop(SPU_SAVE_COMPLETE);
पूर्ण

/**
 * मुख्य - entry poपूर्णांक क्रम SPU-side context save.
 *
 * This code deviates from the करोcumented sequence as follows:
 *
 *      1. The EA क्रम LSCSA is passed from PPE in the
 *         संकेत notअगरication channels.
 *      2. All 128 रेजिस्टरs are saved by crt0.o.
 */
पूर्णांक मुख्य()
अणु
	addr64 lscsa_ea;

	lscsa_ea.ui[0] = spu_पढ़ोch(SPU_RdSigNotअगरy1);
	lscsa_ea.ui[1] = spu_पढ़ोch(SPU_RdSigNotअगरy2);

	/* Step 1: करोne by निकास(). */
	save_event_mask();	/* Step 2.  */
	save_tag_mask();	/* Step 3.  */
	set_event_mask();	/* Step 4.  */
	set_tag_mask();		/* Step 5.  */
	build_dma_list(lscsa_ea);	/* Step 6.  */
	save_upper_240kb(lscsa_ea);	/* Step 7.  */
	/* Step 8: करोne by निकास(). */
	save_fpcr();		/* Step 9.  */
	save_decr();		/* Step 10. */
	save_srr0();		/* Step 11. */
	enqueue_putllc(lscsa_ea);	/* Step 12. */
	spill_regs_to_mem(lscsa_ea);	/* Step 13. */
	enqueue_sync(lscsa_ea);	/* Step 14. */
	set_tag_update();	/* Step 15. */
	पढ़ो_tag_status();	/* Step 16. */
	पढ़ो_llar_status();	/* Step 17. */
	save_complete();	/* Step 18. */

	वापस 0;
पूर्ण
