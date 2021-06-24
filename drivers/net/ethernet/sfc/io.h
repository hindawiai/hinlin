<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_IO_H
#घोषणा EFX_IO_H

#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

/**************************************************************************
 *
 * NIC रेजिस्टर I/O
 *
 **************************************************************************
 *
 * Notes on locking strategy क्रम the Falcon architecture:
 *
 * Many CSRs are very wide and cannot be पढ़ो or written atomically.
 * Writes from the host are buffered by the Bus Interface Unit (BIU)
 * up to 128 bits.  Whenever the host ग_लिखोs part of such a रेजिस्टर,
 * the BIU collects the written value and करोes not ग_लिखो to the
 * underlying रेजिस्टर until all 4 dwords have been written.  A
 * similar buffering scheme applies to host access to the NIC's 64-bit
 * SRAM.
 *
 * Writes to dअगरferent CSRs and 64-bit SRAM words must be serialised,
 * since पूर्णांकerleaved access can result in lost ग_लिखोs.  We use
 * efx_nic::biu_lock क्रम this.
 *
 * We also serialise पढ़ोs from 128-bit CSRs and SRAM with the same
 * spinlock.  This may not be necessary, but it करोesn't really matter
 * as there are no such पढ़ोs on the fast path.
 *
 * The DMA descriptor poपूर्णांकers (RX_DESC_UPD and TX_DESC_UPD) are
 * 128-bit but are special-हालd in the BIU to aव्योम the need क्रम
 * locking in the host:
 *
 * - They are ग_लिखो-only.
 * - The semantics of writing to these रेजिस्टरs are such that
 *   replacing the low 96 bits with zero करोes not affect functionality.
 * - If the host ग_लिखोs to the last dword address of such a रेजिस्टर
 *   (i.e. the high 32 bits) the underlying रेजिस्टर will always be
 *   written.  If the collector and the current ग_लिखो together करो not
 *   provide values क्रम all 128 bits of the रेजिस्टर, the low 96 bits
 *   will be written as zero.
 * - If the host ग_लिखोs to the address of any other part of such a
 *   रेजिस्टर जबतक the collector alपढ़ोy holds values क्रम some other
 *   रेजिस्टर, the ग_लिखो is discarded and the collector मुख्यtains its
 *   current state.
 *
 * The EF10 architecture exposes very few रेजिस्टरs to the host and
 * most of them are only 32 bits wide.  The only exceptions are the MC
 * करोorbell रेजिस्टर pair, which has its own latching, and
 * TX_DESC_UPD, which works in a similar way to the Falcon
 * architecture.
 */

#अगर BITS_PER_LONG == 64
#घोषणा EFX_USE_QWORD_IO 1
#पूर्ण_अगर

/* Hardware issue requires that only 64-bit naturally aligned ग_लिखोs
 * are seen by hardware. Its not strictly necessary to restrict to
 * x86_64 arch, but करोne क्रम safety since unusual ग_लिखो combining behaviour
 * can अवरोध PIO.
 */
#अगर_घोषित CONFIG_X86_64
/* PIO is a win only अगर ग_लिखो-combining is possible */
#अगर_घोषित ARCH_HAS_IOREMAP_WC
#घोषणा EFX_USE_PIO 1
#पूर्ण_अगर
#पूर्ण_अगर

अटल अंतरभूत u32 efx_reg(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक reg)
अणु
	वापस efx->reg_base + reg;
पूर्ण

#अगर_घोषित EFX_USE_QWORD_IO
अटल अंतरभूत व्योम _efx_ग_लिखोq(काष्ठा efx_nic *efx, __le64 value,
				  अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोq((__क्रमce u64)value, efx->membase + reg);
पूर्ण
अटल अंतरभूत __le64 _efx_पढ़ोq(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक reg)
अणु
	वापस (__क्रमce __le64)__raw_पढ़ोq(efx->membase + reg);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम _efx_ग_लिखोd(काष्ठा efx_nic *efx, __le32 value,
				  अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl((__क्रमce u32)value, efx->membase + reg);
पूर्ण
अटल अंतरभूत __le32 _efx_पढ़ोd(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक reg)
अणु
	वापस (__क्रमce __le32)__raw_पढ़ोl(efx->membase + reg);
पूर्ण

/* Write a normal 128-bit CSR, locking as appropriate. */
अटल अंतरभूत व्योम efx_ग_लिखोo(काष्ठा efx_nic *efx, स्थिर efx_oword_t *value,
			      अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with " EFX_OWORD_FMT "\n", reg,
		   EFX_OWORD_VAL(*value));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EFX_USE_QWORD_IO
	_efx_ग_लिखोq(efx, value->u64[0], reg + 0);
	_efx_ग_लिखोq(efx, value->u64[1], reg + 8);
#अन्यथा
	_efx_ग_लिखोd(efx, value->u32[0], reg + 0);
	_efx_ग_लिखोd(efx, value->u32[1], reg + 4);
	_efx_ग_लिखोd(efx, value->u32[2], reg + 8);
	_efx_ग_लिखोd(efx, value->u32[3], reg + 12);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);
पूर्ण

/* Write 64-bit SRAM through the supplied mapping, locking as appropriate. */
अटल अंतरभूत व्योम efx_sram_ग_लिखोq(काष्ठा efx_nic *efx, व्योम __iomem *membase,
				   स्थिर efx_qword_t *value, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक addr = index * माप(*value);
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing SRAM address %x with " EFX_QWORD_FMT "\n",
		   addr, EFX_QWORD_VAL(*value));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EFX_USE_QWORD_IO
	__raw_ग_लिखोq((__क्रमce u64)value->u64[0], membase + addr);
#अन्यथा
	__raw_ग_लिखोl((__क्रमce u32)value->u32[0], membase + addr);
	__raw_ग_लिखोl((__क्रमce u32)value->u32[1], membase + addr + 4);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);
पूर्ण

/* Write a 32-bit CSR or the last dword of a special 128-bit CSR */
अटल अंतरभूत व्योम efx_ग_लिखोd(काष्ठा efx_nic *efx, स्थिर efx_dword_t *value,
			      अचिन्हित पूर्णांक reg)
अणु
	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with "EFX_DWORD_FMT"\n",
		   reg, EFX_DWORD_VAL(*value));

	/* No lock required */
	_efx_ग_लिखोd(efx, value->u32[0], reg);
पूर्ण

/* Read a 128-bit CSR, locking as appropriate. */
अटल अंतरभूत व्योम efx_पढ़ोo(काष्ठा efx_nic *efx, efx_oword_t *value,
			     अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	spin_lock_irqsave(&efx->biu_lock, flags);
	value->u32[0] = _efx_पढ़ोd(efx, reg + 0);
	value->u32[1] = _efx_पढ़ोd(efx, reg + 4);
	value->u32[2] = _efx_पढ़ोd(efx, reg + 8);
	value->u32[3] = _efx_पढ़ोd(efx, reg + 12);
	spin_unlock_irqrestore(&efx->biu_lock, flags);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from register %x, got " EFX_OWORD_FMT "\n", reg,
		   EFX_OWORD_VAL(*value));
पूर्ण

/* Read 64-bit SRAM through the supplied mapping, locking as appropriate. */
अटल अंतरभूत व्योम efx_sram_पढ़ोq(काष्ठा efx_nic *efx, व्योम __iomem *membase,
				  efx_qword_t *value, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक addr = index * माप(*value);
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EFX_USE_QWORD_IO
	value->u64[0] = (__क्रमce __le64)__raw_पढ़ोq(membase + addr);
#अन्यथा
	value->u32[0] = (__क्रमce __le32)__raw_पढ़ोl(membase + addr);
	value->u32[1] = (__क्रमce __le32)__raw_पढ़ोl(membase + addr + 4);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from SRAM address %x, got "EFX_QWORD_FMT"\n",
		   addr, EFX_QWORD_VAL(*value));
पूर्ण

/* Read a 32-bit CSR or SRAM */
अटल अंतरभूत व्योम efx_पढ़ोd(काष्ठा efx_nic *efx, efx_dword_t *value,
				अचिन्हित पूर्णांक reg)
अणु
	value->u32[0] = _efx_पढ़ोd(efx, reg);
	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from register %x, got "EFX_DWORD_FMT"\n",
		   reg, EFX_DWORD_VAL(*value));
पूर्ण

/* Write a 128-bit CSR क्रमming part of a table */
अटल अंतरभूत व्योम
efx_ग_लिखोo_table(काष्ठा efx_nic *efx, स्थिर efx_oword_t *value,
		 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक index)
अणु
	efx_ग_लिखोo(efx, value, reg + index * माप(efx_oword_t));
पूर्ण

/* Read a 128-bit CSR क्रमming part of a table */
अटल अंतरभूत व्योम efx_पढ़ोo_table(काष्ठा efx_nic *efx, efx_oword_t *value,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक index)
अणु
	efx_पढ़ोo(efx, value, reg + index * माप(efx_oword_t));
पूर्ण

/* शेष VI stride (step between per-VI रेजिस्टरs) is 8K on EF10 and
 * 64K on EF100
 */
#घोषणा EFX_DEFAULT_VI_STRIDE		0x2000
#घोषणा EF100_DEFAULT_VI_STRIDE		0x10000

/* Calculate offset to page-mapped रेजिस्टर */
अटल अंतरभूत अचिन्हित पूर्णांक efx_paged_reg(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक page,
					 अचिन्हित पूर्णांक reg)
अणु
	वापस page * efx->vi_stride + reg;
पूर्ण

/* Write the whole of RX_DESC_UPD or TX_DESC_UPD */
अटल अंतरभूत व्योम _efx_ग_लिखोo_page(काष्ठा efx_nic *efx, efx_oword_t *value,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक page)
अणु
	reg = efx_paged_reg(efx, page, reg);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with " EFX_OWORD_FMT "\n", reg,
		   EFX_OWORD_VAL(*value));

#अगर_घोषित EFX_USE_QWORD_IO
	_efx_ग_लिखोq(efx, value->u64[0], reg + 0);
	_efx_ग_लिखोq(efx, value->u64[1], reg + 8);
#अन्यथा
	_efx_ग_लिखोd(efx, value->u32[0], reg + 0);
	_efx_ग_लिखोd(efx, value->u32[1], reg + 4);
	_efx_ग_लिखोd(efx, value->u32[2], reg + 8);
	_efx_ग_लिखोd(efx, value->u32[3], reg + 12);
#पूर्ण_अगर
पूर्ण
#घोषणा efx_ग_लिखोo_page(efx, value, reg, page)				\
	_efx_ग_लिखोo_page(efx, value,					\
			 reg +						\
			 BUILD_BUG_ON_ZERO((reg) != 0x830 && (reg) != 0xa10), \
			 page)

/* Write a page-mapped 32-bit CSR (EVQ_RPTR, EVQ_TMR (EF10), or the
 * high bits of RX_DESC_UPD or TX_DESC_UPD)
 */
अटल अंतरभूत व्योम
_efx_ग_लिखोd_page(काष्ठा efx_nic *efx, स्थिर efx_dword_t *value,
		 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक page)
अणु
	efx_ग_लिखोd(efx, value, efx_paged_reg(efx, page, reg));
पूर्ण
#घोषणा efx_ग_लिखोd_page(efx, value, reg, page)				\
	_efx_ग_लिखोd_page(efx, value,					\
			 reg +						\
			 BUILD_BUG_ON_ZERO((reg) != 0x180 &&		\
					   (reg) != 0x200 &&		\
					   (reg) != 0x400 &&		\
					   (reg) != 0x420 &&		\
					   (reg) != 0x830 &&		\
					   (reg) != 0x83c &&		\
					   (reg) != 0xa18 &&		\
					   (reg) != 0xa1c),		\
			 page)

/* Write TIMER_COMMAND.  This is a page-mapped 32-bit CSR, but a bug
 * in the BIU means that ग_लिखोs to TIMER_COMMAND[0] invalidate the
 * collector रेजिस्टर.
 */
अटल अंतरभूत व्योम _efx_ग_लिखोd_page_locked(काष्ठा efx_nic *efx,
					   स्थिर efx_dword_t *value,
					   अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक page)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	अगर (page == 0) अणु
		spin_lock_irqsave(&efx->biu_lock, flags);
		efx_ग_लिखोd(efx, value, efx_paged_reg(efx, page, reg));
		spin_unlock_irqrestore(&efx->biu_lock, flags);
	पूर्ण अन्यथा अणु
		efx_ग_लिखोd(efx, value, efx_paged_reg(efx, page, reg));
	पूर्ण
पूर्ण
#घोषणा efx_ग_लिखोd_page_locked(efx, value, reg, page)			\
	_efx_ग_लिखोd_page_locked(efx, value,				\
				reg + BUILD_BUG_ON_ZERO((reg) != 0x420), \
				page)

#पूर्ण_अगर /* EFX_IO_H */
