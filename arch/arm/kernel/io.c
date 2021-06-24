<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

अटल DEFINE_RAW_SPINLOCK(__io_lock);

/*
 * Generic atomic MMIO modअगरy.
 *
 * Allows thपढ़ो-safe access to रेजिस्टरs shared by unrelated subप्रणालीs.
 * The access is रक्षित by a single MMIO-wide lock.
 */
व्योम atomic_io_modअगरy_relaxed(व्योम __iomem *reg, u32 mask, u32 set)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&__io_lock, flags);
	value = पढ़ोl_relaxed(reg) & ~mask;
	value |= (set & mask);
	ग_लिखोl_relaxed(value, reg);
	raw_spin_unlock_irqrestore(&__io_lock, flags);
पूर्ण
EXPORT_SYMBOL(atomic_io_modअगरy_relaxed);

व्योम atomic_io_modअगरy(व्योम __iomem *reg, u32 mask, u32 set)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&__io_lock, flags);
	value = पढ़ोl_relaxed(reg) & ~mask;
	value |= (set & mask);
	ग_लिखोl(value, reg);
	raw_spin_unlock_irqrestore(&__io_lock, flags);
पूर्ण
EXPORT_SYMBOL(atomic_io_modअगरy);

/*
 * Copy data from IO memory space to "real" memory space.
 * This needs to be optimized.
 */
व्योम _स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, माप_प्रकार count)
अणु
	अचिन्हित अक्षर *t = to;
	जबतक (count) अणु
		count--;
		*t = पढ़ोb(from);
		t++;
		from++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(_स_नकल_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
 * This needs to be optimized.
 */
व्योम _स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *f = from;
	जबतक (count) अणु
		count--;
		ग_लिखोb(*f, to);
		f++;
		to++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(_स_नकल_toio);

/*
 * "memset" on IO memory space.
 * This needs to be optimized.
 */
व्योम _स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, माप_प्रकार count)
अणु
	जबतक (count) अणु
		count--;
		ग_लिखोb(c, dst);
		dst++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(_स_रखो_io);
