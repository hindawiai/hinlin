<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित	__HPET__
#घोषणा	__HPET__ 1

#समावेश <uapi/linux/hpet.h>


/*
 * Offsets पूर्णांकo HPET Registers
 */

काष्ठा hpet अणु
	u64 hpet_cap;		/* capabilities */
	u64 res0;		/* reserved */
	u64 hpet_config;	/* configuration */
	u64 res1;		/* reserved */
	u64 hpet_isr;		/* पूर्णांकerrupt status reg */
	u64 res2[25];		/* reserved */
	जोड़ अणु			/* मुख्य counter */
		u64 _hpet_mc64;
		u32 _hpet_mc32;
		अचिन्हित दीर्घ _hpet_mc;
	पूर्ण _u0;
	u64 res3;		/* reserved */
	काष्ठा hpet_समयr अणु
		u64 hpet_config;	/* configuration/cap */
		जोड़ अणु		/* समयr compare रेजिस्टर */
			u64 _hpet_hc64;
			u32 _hpet_hc32;
			अचिन्हित दीर्घ _hpet_compare;
		पूर्ण _u1;
		u64 hpet_fsb[2];	/* FSB route */
	पूर्ण hpet_समयrs[1];
पूर्ण;

#घोषणा	hpet_mc		_u0._hpet_mc
#घोषणा	hpet_compare	_u1._hpet_compare

#घोषणा	HPET_MAX_TIMERS	(32)
#घोषणा	HPET_MAX_IRQ	(32)

/*
 * HPET general capabilities रेजिस्टर
 */

#घोषणा	HPET_COUNTER_CLK_PERIOD_MASK	(0xffffffff00000000ULL)
#घोषणा	HPET_COUNTER_CLK_PERIOD_SHIFT	(32UL)
#घोषणा	HPET_VENDOR_ID_MASK		(0x00000000ffff0000ULL)
#घोषणा	HPET_VENDOR_ID_SHIFT		(16ULL)
#घोषणा	HPET_LEG_RT_CAP_MASK		(0x8000)
#घोषणा	HPET_COUNTER_SIZE_MASK		(0x2000)
#घोषणा	HPET_NUM_TIM_CAP_MASK		(0x1f00)
#घोषणा	HPET_NUM_TIM_CAP_SHIFT		(8ULL)

/*
 * HPET general configuration रेजिस्टर
 */

#घोषणा	HPET_LEG_RT_CNF_MASK		(2UL)
#घोषणा	HPET_ENABLE_CNF_MASK		(1UL)


/*
 * Timer configuration रेजिस्टर
 */

#घोषणा	Tn_INT_ROUTE_CAP_MASK		(0xffffffff00000000ULL)
#घोषणा	Tn_INT_ROUTE_CAP_SHIFT		(32UL)
#घोषणा	Tn_FSB_INT_DELCAP_MASK		(0x8000UL)
#घोषणा	Tn_FSB_INT_DELCAP_SHIFT		(15)
#घोषणा	Tn_FSB_EN_CNF_MASK		(0x4000UL)
#घोषणा	Tn_FSB_EN_CNF_SHIFT		(14)
#घोषणा	Tn_INT_ROUTE_CNF_MASK		(0x3e00UL)
#घोषणा	Tn_INT_ROUTE_CNF_SHIFT		(9)
#घोषणा	Tn_32MODE_CNF_MASK		(0x0100UL)
#घोषणा	Tn_VAL_SET_CNF_MASK		(0x0040UL)
#घोषणा	Tn_SIZE_CAP_MASK		(0x0020UL)
#घोषणा	Tn_PER_INT_CAP_MASK		(0x0010UL)
#घोषणा	Tn_TYPE_CNF_MASK		(0x0008UL)
#घोषणा	Tn_INT_ENB_CNF_MASK		(0x0004UL)
#घोषणा	Tn_INT_TYPE_CNF_MASK		(0x0002UL)

/*
 * Timer FSB Interrupt Route Register
 */

#घोषणा	Tn_FSB_INT_ADDR_MASK		(0xffffffff00000000ULL)
#घोषणा	Tn_FSB_INT_ADDR_SHIFT		(32UL)
#घोषणा	Tn_FSB_INT_VAL_MASK		(0x00000000ffffffffULL)

/*
 * exported पूर्णांकerfaces
 */

काष्ठा hpet_data अणु
	अचिन्हित दीर्घ hd_phys_address;
	व्योम __iomem *hd_address;
	अचिन्हित लघु hd_nirqs;
	अचिन्हित पूर्णांक hd_state;	/* समयr allocated */
	अचिन्हित पूर्णांक hd_irq[HPET_MAX_TIMERS];
पूर्ण;

अटल अंतरभूत व्योम hpet_reserve_समयr(काष्ठा hpet_data *hd, पूर्णांक समयr)
अणु
	hd->hd_state |= (1 << समयr);
	वापस;
पूर्ण

पूर्णांक hpet_alloc(काष्ठा hpet_data *);

#पूर्ण_अगर				/* !__HPET__ */
