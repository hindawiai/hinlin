<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Implement 'Simple Boot Flag Specification 2.0'
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/mc146818rtc.h>

#घोषणा SBF_RESERVED (0x78)
#घोषणा SBF_PNPOS    (1<<0)
#घोषणा SBF_BOOTING  (1<<1)
#घोषणा SBF_DIAG     (1<<2)
#घोषणा SBF_PARITY   (1<<7)

पूर्णांक sbf_port __initdata = -1;	/* set via acpi_boot_init() */

अटल पूर्णांक __init parity(u8 v)
अणु
	पूर्णांक x = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		x ^= (v & 1);
		v >>= 1;
	पूर्ण

	वापस x;
पूर्ण

अटल व्योम __init sbf_ग_लिखो(u8 v)
अणु
	अचिन्हित दीर्घ flags;

	अगर (sbf_port != -1) अणु
		v &= ~SBF_PARITY;
		अगर (!parity(v))
			v |= SBF_PARITY;

		prपूर्णांकk(KERN_INFO "Simple Boot Flag at 0x%x set to 0x%x\n",
			sbf_port, v);

		spin_lock_irqsave(&rtc_lock, flags);
		CMOS_WRITE(v, sbf_port);
		spin_unlock_irqrestore(&rtc_lock, flags);
	पूर्ण
पूर्ण

अटल u8 __init sbf_पढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u8 v;

	अगर (sbf_port == -1)
		वापस 0;

	spin_lock_irqsave(&rtc_lock, flags);
	v = CMOS_READ(sbf_port);
	spin_unlock_irqrestore(&rtc_lock, flags);

	वापस v;
पूर्ण

अटल पूर्णांक __init sbf_value_valid(u8 v)
अणु
	अगर (v & SBF_RESERVED)		/* Reserved bits */
		वापस 0;
	अगर (!parity(v))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक __init sbf_init(व्योम)
अणु
	u8 v;

	अगर (sbf_port == -1)
		वापस 0;

	v = sbf_पढ़ो();
	अगर (!sbf_value_valid(v)) अणु
		prपूर्णांकk(KERN_WARNING "Simple Boot Flag value 0x%x read from "
			"CMOS RAM was invalid\n", v);
	पूर्ण

	v &= ~SBF_RESERVED;
	v &= ~SBF_BOOTING;
	v &= ~SBF_DIAG;
#अगर defined(CONFIG_ISAPNP)
	v |= SBF_PNPOS;
#पूर्ण_अगर
	sbf_ग_लिखो(v);

	वापस 0;
पूर्ण
arch_initcall(sbf_init);
