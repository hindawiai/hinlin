<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_IO_H
#घोषणा EF4_IO_H

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
 * ef4_nic::biu_lock क्रम this.
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
#घोषणा EF4_USE_QWORD_IO 1
#पूर्ण_अगर

#अगर_घोषित EF4_USE_QWORD_IO
अटल अंतरभूत व्योम _ef4_ग_लिखोq(काष्ठा ef4_nic *efx, __le64 value,
				  अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोq((__क्रमce u64)value, efx->membase + reg);
पूर्ण
अटल अंतरभूत __le64 _ef4_पढ़ोq(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक reg)
अणु
	वापस (__क्रमce __le64)__raw_पढ़ोq(efx->membase + reg);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम _ef4_ग_लिखोd(काष्ठा ef4_nic *efx, __le32 value,
				  अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl((__क्रमce u32)value, efx->membase + reg);
पूर्ण
अटल अंतरभूत __le32 _ef4_पढ़ोd(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक reg)
अणु
	वापस (__क्रमce __le32)__raw_पढ़ोl(efx->membase + reg);
पूर्ण

/* Write a normal 128-bit CSR, locking as appropriate. */
अटल अंतरभूत व्योम ef4_ग_लिखोo(काष्ठा ef4_nic *efx, स्थिर ef4_oword_t *value,
			      अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with " EF4_OWORD_FMT "\n", reg,
		   EF4_OWORD_VAL(*value));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EF4_USE_QWORD_IO
	_ef4_ग_लिखोq(efx, value->u64[0], reg + 0);
	_ef4_ग_लिखोq(efx, value->u64[1], reg + 8);
#अन्यथा
	_ef4_ग_लिखोd(efx, value->u32[0], reg + 0);
	_ef4_ग_लिखोd(efx, value->u32[1], reg + 4);
	_ef4_ग_लिखोd(efx, value->u32[2], reg + 8);
	_ef4_ग_लिखोd(efx, value->u32[3], reg + 12);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);
पूर्ण

/* Write 64-bit SRAM through the supplied mapping, locking as appropriate. */
अटल अंतरभूत व्योम ef4_sram_ग_लिखोq(काष्ठा ef4_nic *efx, व्योम __iomem *membase,
				   स्थिर ef4_qword_t *value, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक addr = index * माप(*value);
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing SRAM address %x with " EF4_QWORD_FMT "\n",
		   addr, EF4_QWORD_VAL(*value));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EF4_USE_QWORD_IO
	__raw_ग_लिखोq((__क्रमce u64)value->u64[0], membase + addr);
#अन्यथा
	__raw_ग_लिखोl((__क्रमce u32)value->u32[0], membase + addr);
	__raw_ग_लिखोl((__क्रमce u32)value->u32[1], membase + addr + 4);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);
पूर्ण

/* Write a 32-bit CSR or the last dword of a special 128-bit CSR */
अटल अंतरभूत व्योम ef4_ग_लिखोd(काष्ठा ef4_nic *efx, स्थिर ef4_dword_t *value,
			      अचिन्हित पूर्णांक reg)
अणु
	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with "EF4_DWORD_FMT"\n",
		   reg, EF4_DWORD_VAL(*value));

	/* No lock required */
	_ef4_ग_लिखोd(efx, value->u32[0], reg);
पूर्ण

/* Read a 128-bit CSR, locking as appropriate. */
अटल अंतरभूत व्योम ef4_पढ़ोo(काष्ठा ef4_nic *efx, ef4_oword_t *value,
			     अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	spin_lock_irqsave(&efx->biu_lock, flags);
	value->u32[0] = _ef4_पढ़ोd(efx, reg + 0);
	value->u32[1] = _ef4_पढ़ोd(efx, reg + 4);
	value->u32[2] = _ef4_पढ़ोd(efx, reg + 8);
	value->u32[3] = _ef4_पढ़ोd(efx, reg + 12);
	spin_unlock_irqrestore(&efx->biu_lock, flags);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from register %x, got " EF4_OWORD_FMT "\n", reg,
		   EF4_OWORD_VAL(*value));
पूर्ण

/* Read 64-bit SRAM through the supplied mapping, locking as appropriate. */
अटल अंतरभूत व्योम ef4_sram_पढ़ोq(काष्ठा ef4_nic *efx, व्योम __iomem *membase,
				  ef4_qword_t *value, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक addr = index * माप(*value);
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	spin_lock_irqsave(&efx->biu_lock, flags);
#अगर_घोषित EF4_USE_QWORD_IO
	value->u64[0] = (__क्रमce __le64)__raw_पढ़ोq(membase + addr);
#अन्यथा
	value->u32[0] = (__क्रमce __le32)__raw_पढ़ोl(membase + addr);
	value->u32[1] = (__क्रमce __le32)__raw_पढ़ोl(membase + addr + 4);
#पूर्ण_अगर
	spin_unlock_irqrestore(&efx->biu_lock, flags);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from SRAM address %x, got "EF4_QWORD_FMT"\n",
		   addr, EF4_QWORD_VAL(*value));
पूर्ण

/* Read a 32-bit CSR or SRAM */
अटल अंतरभूत व्योम ef4_पढ़ोd(काष्ठा ef4_nic *efx, ef4_dword_t *value,
				अचिन्हित पूर्णांक reg)
अणु
	value->u32[0] = _ef4_पढ़ोd(efx, reg);
	netअगर_vdbg(efx, hw, efx->net_dev,
		   "read from register %x, got "EF4_DWORD_FMT"\n",
		   reg, EF4_DWORD_VAL(*value));
पूर्ण

/* Write a 128-bit CSR क्रमming part of a table */
अटल अंतरभूत व्योम
ef4_ग_लिखोo_table(काष्ठा ef4_nic *efx, स्थिर ef4_oword_t *value,
		 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक index)
अणु
	ef4_ग_लिखोo(efx, value, reg + index * माप(ef4_oword_t));
पूर्ण

/* Read a 128-bit CSR क्रमming part of a table */
अटल अंतरभूत व्योम ef4_पढ़ोo_table(काष्ठा ef4_nic *efx, ef4_oword_t *value,
				     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक index)
अणु
	ef4_पढ़ोo(efx, value, reg + index * माप(ef4_oword_t));
पूर्ण

/* Page size used as step between per-VI रेजिस्टरs */
#घोषणा EF4_VI_PAGE_SIZE 0x2000

/* Calculate offset to page-mapped रेजिस्टर */
#घोषणा EF4_PAGED_REG(page, reg) \
	((page) * EF4_VI_PAGE_SIZE + (reg))

/* Write the whole of RX_DESC_UPD or TX_DESC_UPD */
अटल अंतरभूत व्योम _ef4_ग_लिखोo_page(काष्ठा ef4_nic *efx, ef4_oword_t *value,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक page)
अणु
	reg = EF4_PAGED_REG(page, reg);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing register %x with " EF4_OWORD_FMT "\n", reg,
		   EF4_OWORD_VAL(*value));

#अगर_घोषित EF4_USE_QWORD_IO
	_ef4_ग_लिखोq(efx, value->u64[0], reg + 0);
	_ef4_ग_लिखोq(efx, value->u64[1], reg + 8);
#अन्यथा
	_ef4_ग_लिखोd(efx, value->u32[0], reg + 0);
	_ef4_ग_लिखोd(efx, value->u32[1], reg + 4);
	_ef4_ग_लिखोd(efx, value->u32[2], reg + 8);
	_ef4_ग_लिखोd(efx, value->u32[3], reg + 12);
#पूर्ण_अगर
पूर्ण
#घोषणा ef4_ग_लिखोo_page(efx, value, reg, page)				\
	_ef4_ग_लिखोo_page(efx, value,					\
			 reg +						\
			 BUILD_BUG_ON_ZERO((reg) != 0x830 && (reg) != 0xa10), \
			 page)

/* Write a page-mapped 32-bit CSR (EVQ_RPTR, EVQ_TMR (EF10), or the
 * high bits of RX_DESC_UPD or TX_DESC_UPD)
 */
अटल अंतरभूत व्योम
_ef4_ग_लिखोd_page(काष्ठा ef4_nic *efx, स्थिर ef4_dword_t *value,
		 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक page)
अणु
	ef4_ग_लिखोd(efx, value, EF4_PAGED_REG(page, reg));
पूर्ण
#घोषणा ef4_ग_लिखोd_page(efx, value, reg, page)				\
	_ef4_ग_लिखोd_page(efx, value,					\
			 reg +						\
			 BUILD_BUG_ON_ZERO((reg) != 0x400 &&		\
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
अटल अंतरभूत व्योम _ef4_ग_लिखोd_page_locked(काष्ठा ef4_nic *efx,
					   स्थिर ef4_dword_t *value,
					   अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक page)
अणु
	अचिन्हित दीर्घ flags __attribute__ ((unused));

	अगर (page == 0) अणु
		spin_lock_irqsave(&efx->biu_lock, flags);
		ef4_ग_लिखोd(efx, value, EF4_PAGED_REG(page, reg));
		spin_unlock_irqrestore(&efx->biu_lock, flags);
	पूर्ण अन्यथा अणु
		ef4_ग_लिखोd(efx, value, EF4_PAGED_REG(page, reg));
	पूर्ण
पूर्ण
#घोषणा ef4_ग_लिखोd_page_locked(efx, value, reg, page)			\
	_ef4_ग_लिखोd_page_locked(efx, value,				\
				reg + BUILD_BUG_ON_ZERO((reg) != 0x420), \
				page)

#पूर्ण_अगर /* EF4_IO_H */
