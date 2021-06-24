<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_IRQ_H
#घोषणा _ALPHA_IRQ_H

/*
 *	linux/include/alpha/irq.h
 *
 *	(C) 1994 Linus Torvalds
 */

#समावेश <linux/linkage.h>

#अगर   defined(CONFIG_ALPHA_GENERIC)

/* Here NR_IRQS is not exact, but rather an upper bound.  This is used
   many places throughout the kernel to size अटल arrays.  That's ok,
   we'll use alpha_mv.nr_irqs when we want the real thing.  */

/* When LEGACY_START_ADDRESS is selected, we leave out:
     TITAN
     WILDFIRE
     MARVEL

   This helps keep the kernel object size reasonable क्रम the majority
   of machines.
*/

# अगर defined(CONFIG_ALPHA_LEGACY_START_ADDRESS)
#  define NR_IRQS      (128)           /* max is RAWHIDE/TAKARA */
# अन्यथा
#  define NR_IRQS      (32768 + 16)    /* marvel - 32 pids */
# endअगर

#या_अगर defined(CONFIG_ALPHA_CABRIOLET) || \
      defined(CONFIG_ALPHA_EB66P)     || \
      defined(CONFIG_ALPHA_EB164)     || \
      defined(CONFIG_ALPHA_PC164)     || \
      defined(CONFIG_ALPHA_LX164)
# define NR_IRQS	35

#या_अगर defined(CONFIG_ALPHA_EB66)      || \
      defined(CONFIG_ALPHA_EB64P)     || \
      defined(CONFIG_ALPHA_MIKASA)
# define NR_IRQS	32

#या_अगर defined(CONFIG_ALPHA_ALCOR)     || \
      defined(CONFIG_ALPHA_MIATA)     || \
      defined(CONFIG_ALPHA_RUFFIAN)   || \
      defined(CONFIG_ALPHA_RX164)     || \
      defined(CONFIG_ALPHA_NORITAKE)
# define NR_IRQS	48

#या_अगर defined(CONFIG_ALPHA_SABLE)     || \
      defined(CONFIG_ALPHA_SX164)
# define NR_IRQS	40

#या_अगर defined(CONFIG_ALPHA_DP264) || \
      defined(CONFIG_ALPHA_LYNX)  || \
      defined(CONFIG_ALPHA_SHARK)
# define NR_IRQS	64

#या_अगर defined(CONFIG_ALPHA_TITAN)
#घोषणा NR_IRQS		80

#या_अगर defined(CONFIG_ALPHA_RAWHIDE) || \
      defined(CONFIG_ALPHA_TAKARA) || \
      defined(CONFIG_ALPHA_EIGER)
# define NR_IRQS	128

#या_अगर defined(CONFIG_ALPHA_WILDFIRE)
# define NR_IRQS	2048 /* enuff क्रम 8 QBBs */

#या_अगर defined(CONFIG_ALPHA_MARVEL)
# define NR_IRQS	(32768 + 16) 	/* marvel - 32 pids*/

#अन्यथा /* everyone अन्यथा */
# define NR_IRQS	16
#पूर्ण_अगर

अटल __अंतरभूत__ पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	/*
	 * XXX is this true क्रम all Alpha's?  The old serial driver
	 * did it this way क्रम years without any complaपूर्णांकs, so....
	 */
	वापस ((irq == 2) ? 9 : irq);
पूर्ण

काष्ठा pt_regs;
बाह्य व्योम (*perf_irq)(अचिन्हित दीर्घ, काष्ठा pt_regs *);

#पूर्ण_अगर /* _ALPHA_IRQ_H */
