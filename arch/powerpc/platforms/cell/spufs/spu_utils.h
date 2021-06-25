<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * utils.h: Utilities क्रम SPU-side of the context चयन operation.
 *
 * (C) Copyright IBM 2005
 */

#अगर_अघोषित _SPU_CONTEXT_UTILS_H_
#घोषणा _SPU_CONTEXT_UTILS_H_

/*
 * 64-bit safe EA.
 */
प्रकार जोड़ अणु
	अचिन्हित दीर्घ दीर्घ ull;
	अचिन्हित पूर्णांक ui[2];
पूर्ण addr64;

/*
 * 128-bit रेजिस्टर ढाँचा.
 */
प्रकार जोड़ अणु
	अचिन्हित पूर्णांक slot[4];
	vector अचिन्हित पूर्णांक v;
पूर्ण spu_reg128v;

/*
 * DMA list काष्ठाure.
 */
काष्ठा dma_list_elem अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक ea_low;
पूर्ण;

/*
 * Declare storage क्रम 8-byte aligned DMA list.
 */
काष्ठा dma_list_elem dma_list[15] __attribute__ ((aligned(8)));

/*
 * External definition क्रम storage
 * declared in crt0.
 */
बाह्य spu_reg128v regs_spill[NR_SPU_SPILL_REGS];

/*
 * Compute LSCSA byte offset क्रम a given field.
 */
अटल काष्ठा spu_lscsa *dummy = (काष्ठा spu_lscsa *)0;
#घोषणा LSCSA_BYTE_OFFSET(_field)  \
	((अक्षर *)(&(dummy->_field)) - (अक्षर *)(&(dummy->gprs[0].slot[0])))
#घोषणा LSCSA_QW_OFFSET(_field)  (LSCSA_BYTE_OFFSET(_field) >> 4)

अटल अंतरभूत व्योम set_event_mask(व्योम)
अणु
	अचिन्हित पूर्णांक event_mask = 0;

	/* Save, Step 4:
	 * Restore, Step 1:
	 *    Set the SPU_RdEventMsk channel to zero to mask
	 *    all events.
	 */
	spu_ग_लिखोch(SPU_WrEventMask, event_mask);
पूर्ण

अटल अंतरभूत व्योम set_tag_mask(व्योम)
अणु
	अचिन्हित पूर्णांक tag_mask = 1;

	/* Save, Step 5:
	 * Restore, Step 2:
	 *    Set the SPU_WrTagMsk channel to '01' to unmask
	 *    only tag group 0.
	 */
	spu_ग_लिखोch(MFC_WrTagMask, tag_mask);
पूर्ण

अटल अंतरभूत व्योम build_dma_list(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ea_low;
	पूर्णांक i;

	/* Save, Step 6:
	 * Restore, Step 3:
	 *    Update the effective address क्रम the CSA in the
	 *    pre-canned DMA-list in local storage.
	 */
	ea_low = lscsa_ea.ui[1];
	ea_low += LSCSA_BYTE_OFFSET(ls[16384]);

	क्रम (i = 0; i < 15; i++, ea_low += 16384) अणु
		dma_list[i].size = 16384;
		dma_list[i].ea_low = ea_low;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम enqueue_putllc(addr64 lscsa_ea)
अणु
	अचिन्हित पूर्णांक ls = 0;
	अचिन्हित पूर्णांक size = 128;
	अचिन्हित पूर्णांक tag_id = 0;
	अचिन्हित पूर्णांक cmd = 0xB4;	/* PUTLLC */

	/* Save, Step 12:
	 * Restore, Step 7:
	 *    Send a PUTLLC (tag 0) command to the MFC using
	 *    an effective address in the CSA in order to
	 *    हटाओ any possible lock-line reservation.
	 */
	spu_ग_लिखोch(MFC_LSA, ls);
	spu_ग_लिखोch(MFC_EAH, lscsa_ea.ui[0]);
	spu_ग_लिखोch(MFC_EAL, lscsa_ea.ui[1]);
	spu_ग_लिखोch(MFC_Size, size);
	spu_ग_लिखोch(MFC_TagID, tag_id);
	spu_ग_लिखोch(MFC_Cmd, cmd);
पूर्ण

अटल अंतरभूत व्योम set_tag_update(व्योम)
अणु
	अचिन्हित पूर्णांक update_any = 1;

	/* Save, Step 15:
	 * Restore, Step 8:
	 *    Write the MFC_TagUpdate channel with '01'.
	 */
	spu_ग_लिखोch(MFC_WrTagUpdate, update_any);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_tag_status(व्योम)
अणु
	/* Save, Step 16:
	 * Restore, Step 9:
	 *    Read the MFC_TagStat channel data.
	 */
	spu_पढ़ोch(MFC_RdTagStat);
पूर्ण

अटल अंतरभूत व्योम पढ़ो_llar_status(व्योम)
अणु
	/* Save, Step 17:
	 * Restore, Step 10:
	 *    Read the MFC_AtomicStat channel data.
	 */
	spu_पढ़ोch(MFC_RdAtomicStat);
पूर्ण

#पूर्ण_अगर				/* _SPU_CONTEXT_UTILS_H_ */
