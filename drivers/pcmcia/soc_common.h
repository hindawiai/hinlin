<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/drivers/pcmcia/soc_common.h
 *
 * Copyright (C) 2000 John G Dorsey <john+@cs.cmu.edu>
 *
 * This file contains definitions क्रम the PCMCIA support code common to
 * पूर्णांकegrated SOCs like the SA-11x0 and PXA2xx microprocessors.
 */
#अगर_अघोषित _ASM_ARCH_PCMCIA
#घोषणा _ASM_ARCH_PCMCIA

/* include the world */
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>


काष्ठा device;
काष्ठा gpio_desc;
काष्ठा pcmcia_low_level;
काष्ठा regulator;

काष्ठा soc_pcmcia_regulator अणु
	काष्ठा regulator	*reg;
	bool			on;
पूर्ण;

/*
 * This काष्ठाure encapsulates per-socket state which we might need to
 * use when responding to a Card Services query of some kind.
 */
काष्ठा soc_pcmcia_socket अणु
	काष्ठा pcmcia_socket	socket;

	/*
	 * Info from low level handler
	 */
	अचिन्हित पूर्णांक		nr;
	काष्ठा clk		*clk;

	/*
	 * Core PCMCIA state
	 */
	स्थिर काष्ठा pcmcia_low_level *ops;

	अचिन्हित पूर्णांक		status;
	socket_state_t		cs_state;

	अचिन्हित लघु		spd_io[MAX_IO_WIN];
	अचिन्हित लघु		spd_mem[MAX_WIN];
	अचिन्हित लघु		spd_attr[MAX_WIN];

	काष्ठा resource		res_skt;
	काष्ठा resource		res_io;
	काष्ठा resource		res_mem;
	काष्ठा resource		res_attr;
	व्योम __iomem		*virt_io;

	काष्ठा अणु
		पूर्णांक		gpio;
		काष्ठा gpio_desc *desc;
		अचिन्हित पूर्णांक	irq;
		स्थिर अक्षर	*name;
	पूर्ण stat[6];
#घोषणा SOC_STAT_CD		0	/* Card detect */
#घोषणा SOC_STAT_BVD1		1	/* BATDEAD / IOSTSCHG */
#घोषणा SOC_STAT_BVD2		2	/* BATWARN / IOSPKR */
#घोषणा SOC_STAT_RDY		3	/* Ready / Interrupt */
#घोषणा SOC_STAT_VS1		4	/* Voltage sense 1 */
#घोषणा SOC_STAT_VS2		5	/* Voltage sense 2 */

	काष्ठा gpio_desc	*gpio_reset;
	काष्ठा gpio_desc	*gpio_bus_enable;
	काष्ठा soc_pcmcia_regulator vcc;
	काष्ठा soc_pcmcia_regulator vpp;

	अचिन्हित पूर्णांक		irq_state;

#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	cpufreq_nb;
#पूर्ण_अगर
	काष्ठा समयr_list	poll_समयr;
	काष्ठा list_head	node;
	व्योम *driver_data;
पूर्ण;

काष्ठा skt_dev_info अणु
	पूर्णांक nskt;
	काष्ठा soc_pcmcia_socket skt[];
पूर्ण;

काष्ठा pcmcia_state अणु
  अचिन्हित detect: 1,
            पढ़ोy: 1,
             bvd1: 1,
             bvd2: 1,
           wrprot: 1,
            vs_3v: 1,
            vs_Xv: 1;
पूर्ण;

काष्ठा pcmcia_low_level अणु
	काष्ठा module *owner;

	/* first socket in प्रणाली */
	पूर्णांक first;
	/* nr of sockets */
	पूर्णांक nr;

	पूर्णांक (*hw_init)(काष्ठा soc_pcmcia_socket *);
	व्योम (*hw_shutकरोwn)(काष्ठा soc_pcmcia_socket *);

	व्योम (*socket_state)(काष्ठा soc_pcmcia_socket *, काष्ठा pcmcia_state *);
	पूर्णांक (*configure_socket)(काष्ठा soc_pcmcia_socket *, स्थिर socket_state_t *);

	/*
	 * Enable card status IRQs on (re-)initialisation.  This can
	 * be called at initialisation, घातer management event, or
	 * pcmcia event.
	 */
	व्योम (*socket_init)(काष्ठा soc_pcmcia_socket *);

	/*
	 * Disable card status IRQs and PCMCIA bus on suspend.
	 */
	व्योम (*socket_suspend)(काष्ठा soc_pcmcia_socket *);

	/*
	 * Hardware specअगरic timing routines.
	 * If provided, the get_timing routine overrides the SOC शेष.
	 */
	अचिन्हित पूर्णांक (*get_timing)(काष्ठा soc_pcmcia_socket *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	पूर्णांक (*set_timing)(काष्ठा soc_pcmcia_socket *);
	पूर्णांक (*show_timing)(काष्ठा soc_pcmcia_socket *, अक्षर *);

#अगर_घोषित CONFIG_CPU_FREQ
	/*
	 * CPUFREQ support.
	 */
	पूर्णांक (*frequency_change)(काष्ठा soc_pcmcia_socket *, अचिन्हित दीर्घ, काष्ठा cpufreq_freqs *);
#पूर्ण_अगर
पूर्ण;


काष्ठा soc_pcmcia_timing अणु
	अचिन्हित लघु io;
	अचिन्हित लघु mem;
	अचिन्हित लघु attr;
पूर्ण;

बाह्य व्योम soc_common_pcmcia_get_timing(काष्ठा soc_pcmcia_socket *, काष्ठा soc_pcmcia_timing *);

व्योम soc_pcmcia_init_one(काष्ठा soc_pcmcia_socket *skt,
	स्थिर काष्ठा pcmcia_low_level *ops, काष्ठा device *dev);
व्योम soc_pcmcia_हटाओ_one(काष्ठा soc_pcmcia_socket *skt);
पूर्णांक soc_pcmcia_add_one(काष्ठा soc_pcmcia_socket *skt);
पूर्णांक soc_pcmcia_request_gpiods(काष्ठा soc_pcmcia_socket *skt);

व्योम soc_common_cf_socket_state(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा pcmcia_state *state);

पूर्णांक soc_pcmcia_regulator_set(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा soc_pcmcia_regulator *r, पूर्णांक v);

#अगर_घोषित CONFIG_PCMCIA_DEBUG

बाह्य व्योम soc_pcmcia_debug(काष्ठा soc_pcmcia_socket *skt, स्थिर अक्षर *func,
			     पूर्णांक lvl, स्थिर अक्षर *fmt, ...);

#घोषणा debug(skt, lvl, fmt, arg...) \
	soc_pcmcia_debug(skt, __func__, lvl, fmt , ## arg)

#अन्यथा
#घोषणा debug(skt, lvl, fmt, arg...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


/*
 * The PC Card Standard, Release 7, section 4.13.4, says that twIORD
 * has a minimum value of 165ns. Section 4.13.5 says that twIOWR has
 * a minimum value of 165ns, as well. Section 4.7.2 (describing
 * common and attribute memory ग_लिखो timing) says that twWE has a
 * minimum value of 150ns क्रम a 250ns cycle समय (क्रम 5V operation;
 * see section 4.7.4), or 300ns क्रम a 600ns cycle समय (क्रम 3.3V
 * operation, also section 4.7.4). Section 4.7.3 says that taOE
 * has a maximum value of 150ns क्रम a 300ns cycle समय (क्रम 5V
 * operation), or 300ns क्रम a 600ns cycle समय (क्रम 3.3V operation).
 *
 * When configuring memory maps, Card Services appears to aकरोpt the policy
 * that a memory access समय of "0" means "use the default." The शेष
 * PCMCIA I/O command width समय is 165ns. The शेष PCMCIA 5V attribute
 * and memory command width समय is 150ns; the PCMCIA 3.3V attribute and
 * memory command width समय is 300ns.
 */
#घोषणा SOC_PCMCIA_IO_ACCESS		(165)
#घोषणा SOC_PCMCIA_5V_MEM_ACCESS	(150)
#घोषणा SOC_PCMCIA_3V_MEM_ACCESS	(300)
#घोषणा SOC_PCMCIA_ATTR_MEM_ACCESS	(300)

/*
 * The socket driver actually works nicely in पूर्णांकerrupt-driven क्रमm,
 * so the (relatively infrequent) polling is "just to be sure."
 */
#घोषणा SOC_PCMCIA_POLL_PERIOD    (2*HZ)


/* I/O pins replacing memory pins
 * (PCMCIA System Architecture, 2nd ed., by Don Anderson, p.75)
 *
 * These संकेतs change meaning when going from memory-only to
 * memory-or-I/O पूर्णांकerface:
 */
#घोषणा iostschg bvd1
#घोषणा iospkr   bvd2

#पूर्ण_अगर
