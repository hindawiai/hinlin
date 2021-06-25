<शैली गुरु>
/*
 * Common INTC2 रेजिस्टर accessors
 *
 * Copyright (C) 2007, 2008 Magnus Damm
 * Copyright (C) 2009, 2010 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/पन.स>
#समावेश "internals.h"

अचिन्हित दीर्घ पूर्णांकc_phys_to_virt(काष्ठा पूर्णांकc_desc_पूर्णांक *d, अचिन्हित दीर्घ address)
अणु
	काष्ठा पूर्णांकc_winकरोw *winकरोw;
	पूर्णांक k;

	/* scan through physical winकरोws and convert address */
	क्रम (k = 0; k < d->nr_winकरोws; k++) अणु
		winकरोw = d->winकरोw + k;

		अगर (address < winकरोw->phys)
			जारी;

		अगर (address >= (winकरोw->phys + winकरोw->size))
			जारी;

		address -= winकरोw->phys;
		address += (अचिन्हित दीर्घ)winकरोw->virt;

		वापस address;
	पूर्ण

	/* no winकरोws defined, रेजिस्टर must be 1:1 mapped virt:phys */
	वापस address;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकc_get_reg(काष्ठा पूर्णांकc_desc_पूर्णांक *d, अचिन्हित दीर्घ address)
अणु
	अचिन्हित पूर्णांक k;

	address = पूर्णांकc_phys_to_virt(d, address);

	क्रम (k = 0; k < d->nr_reg; k++) अणु
		अगर (d->reg[k] == address)
			वापस k;
	पूर्ण

	BUG();
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकc_set_field_from_handle(अचिन्हित पूर्णांक value,
					अचिन्हित पूर्णांक field_value,
					अचिन्हित पूर्णांक handle)
अणु
	अचिन्हित पूर्णांक width = _INTC_WIDTH(handle);
	अचिन्हित पूर्णांक shअगरt = _INTC_SHIFT(handle);

	value &= ~(((1 << width) - 1) << shअगरt);
	value |= field_value << shअगरt;
	वापस value;
पूर्ण

अचिन्हित दीर्घ पूर्णांकc_get_field_from_handle(अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक handle)
अणु
	अचिन्हित पूर्णांक width = _INTC_WIDTH(handle);
	अचिन्हित पूर्णांक shअगरt = _INTC_SHIFT(handle);
	अचिन्हित पूर्णांक mask = ((1 << width) - 1) << shअगरt;

	वापस (value & mask) >> shअगरt;
पूर्ण

अटल अचिन्हित दीर्घ test_8(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			    अचिन्हित दीर्घ ignore)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	वापस पूर्णांकc_get_field_from_handle(__raw_पढ़ोb(ptr), h);
पूर्ण

अटल अचिन्हित दीर्घ test_16(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			     अचिन्हित दीर्घ ignore)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	वापस पूर्णांकc_get_field_from_handle(__raw_पढ़ोw(ptr), h);
पूर्ण

अटल अचिन्हित दीर्घ test_32(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			     अचिन्हित दीर्घ ignore)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	वापस पूर्णांकc_get_field_from_handle(__raw_पढ़ोl(ptr), h);
पूर्ण

अटल अचिन्हित दीर्घ ग_लिखो_8(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			     अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	__raw_ग_लिखोb(पूर्णांकc_set_field_from_handle(0, data, h), ptr);
	(व्योम)__raw_पढ़ोb(ptr);	/* Defeat ग_लिखो posting */
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ग_लिखो_16(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			      अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	__raw_ग_लिखोw(पूर्णांकc_set_field_from_handle(0, data, h), ptr);
	(व्योम)__raw_पढ़ोw(ptr);	/* Defeat ग_लिखो posting */
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ग_लिखो_32(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			      अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	__raw_ग_लिखोl(पूर्णांकc_set_field_from_handle(0, data, h), ptr);
	(व्योम)__raw_पढ़ोl(ptr);	/* Defeat ग_लिखो posting */
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ modअगरy_8(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			      अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक value;
	local_irq_save(flags);
	value = पूर्णांकc_set_field_from_handle(__raw_पढ़ोb(ptr), data, h);
	__raw_ग_लिखोb(value, ptr);
	(व्योम)__raw_पढ़ोb(ptr);	/* Defeat ग_लिखो posting */
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ modअगरy_16(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			       अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक value;
	local_irq_save(flags);
	value = पूर्णांकc_set_field_from_handle(__raw_पढ़ोw(ptr), data, h);
	__raw_ग_लिखोw(value, ptr);
	(व्योम)__raw_पढ़ोw(ptr);	/* Defeat ग_लिखो posting */
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ modअगरy_32(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h,
			       अचिन्हित दीर्घ data)
अणु
	व्योम __iomem *ptr = (व्योम __iomem *)addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक value;
	local_irq_save(flags);
	value = पूर्णांकc_set_field_from_handle(__raw_पढ़ोl(ptr), data, h);
	__raw_ग_लिखोl(value, ptr);
	(व्योम)__raw_पढ़ोl(ptr);	/* Defeat ग_लिखो posting */
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकc_mode_field(अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ handle,
				     अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
						अचिन्हित दीर्घ,
						अचिन्हित दीर्घ),
				     अचिन्हित पूर्णांक irq)
अणु
	वापस fn(addr, handle, ((1 << _INTC_WIDTH(handle)) - 1));
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकc_mode_zero(अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ handle,
				    अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ),
				    अचिन्हित पूर्णांक irq)
अणु
	वापस fn(addr, handle, 0);
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकc_mode_prio(अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ handle,
				    अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ),
				    अचिन्हित पूर्णांक irq)
अणु
	वापस fn(addr, handle, पूर्णांकc_get_prio_level(irq));
पूर्ण

अचिन्हित दीर्घ (*पूर्णांकc_reg_fns[])(अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ h,
				अचिन्हित दीर्घ data) = अणु
	[REG_FN_TEST_BASE + 0] = test_8,
	[REG_FN_TEST_BASE + 1] = test_16,
	[REG_FN_TEST_BASE + 3] = test_32,
	[REG_FN_WRITE_BASE + 0] = ग_लिखो_8,
	[REG_FN_WRITE_BASE + 1] = ग_लिखो_16,
	[REG_FN_WRITE_BASE + 3] = ग_लिखो_32,
	[REG_FN_MODIFY_BASE + 0] = modअगरy_8,
	[REG_FN_MODIFY_BASE + 1] = modअगरy_16,
	[REG_FN_MODIFY_BASE + 3] = modअगरy_32,
पूर्ण;

अचिन्हित दीर्घ (*पूर्णांकc_enable_fns[])(अचिन्हित दीर्घ addr,
				   अचिन्हित दीर्घ handle,
				   अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
					    अचिन्हित दीर्घ,
					    अचिन्हित दीर्घ),
				   अचिन्हित पूर्णांक irq) = अणु
	[MODE_ENABLE_REG] = पूर्णांकc_mode_field,
	[MODE_MASK_REG] = पूर्णांकc_mode_zero,
	[MODE_DUAL_REG] = पूर्णांकc_mode_field,
	[MODE_PRIO_REG] = पूर्णांकc_mode_prio,
	[MODE_PCLR_REG] = पूर्णांकc_mode_prio,
पूर्ण;

अचिन्हित दीर्घ (*पूर्णांकc_disable_fns[])(अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ handle,
				    अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
					     अचिन्हित दीर्घ,
					     अचिन्हित दीर्घ),
				    अचिन्हित पूर्णांक irq) = अणु
	[MODE_ENABLE_REG] = पूर्णांकc_mode_zero,
	[MODE_MASK_REG] = पूर्णांकc_mode_field,
	[MODE_DUAL_REG] = पूर्णांकc_mode_field,
	[MODE_PRIO_REG] = पूर्णांकc_mode_zero,
	[MODE_PCLR_REG] = पूर्णांकc_mode_field,
पूर्ण;

अचिन्हित दीर्घ (*पूर्णांकc_enable_noprio_fns[])(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ handle,
					  अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
						अचिन्हित दीर्घ,
						अचिन्हित दीर्घ),
					  अचिन्हित पूर्णांक irq) = अणु
	[MODE_ENABLE_REG] = पूर्णांकc_mode_field,
	[MODE_MASK_REG] = पूर्णांकc_mode_zero,
	[MODE_DUAL_REG] = पूर्णांकc_mode_field,
	[MODE_PRIO_REG] = पूर्णांकc_mode_field,
	[MODE_PCLR_REG] = पूर्णांकc_mode_field,
पूर्ण;
