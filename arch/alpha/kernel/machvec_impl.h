<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	linux/arch/alpha/kernel/machvec_impl.h
 *
 *	Copyright (C) 1997, 1998  Riअक्षरd Henderson
 *
 * This file has goodies to help simplअगरy instantiation of machine vectors.
 */

/* Whee.  These प्रणालीs करोn't have an HAE:
       IRONGATE, MARVEL, POLARIS, TSUNAMI, TITAN, WILDFIRE
   Fix things up क्रम the GENERIC kernel by defining the HAE address
   to be that of the cache. Now we can पढ़ो and ग_लिखो it as we like.  ;-)  */
#घोषणा IRONGATE_HAE_ADDRESS	(&alpha_mv.hae_cache)
#घोषणा MARVEL_HAE_ADDRESS	(&alpha_mv.hae_cache)
#घोषणा POLARIS_HAE_ADDRESS	(&alpha_mv.hae_cache)
#घोषणा TSUNAMI_HAE_ADDRESS	(&alpha_mv.hae_cache)
#घोषणा TITAN_HAE_ADDRESS	(&alpha_mv.hae_cache)
#घोषणा WILDFIRE_HAE_ADDRESS	(&alpha_mv.hae_cache)

#अगर_घोषित CIA_ONE_HAE_WINDOW
#घोषणा CIA_HAE_ADDRESS		(&alpha_mv.hae_cache)
#पूर्ण_अगर
#अगर_घोषित MCPCIA_ONE_HAE_WINDOW
#घोषणा MCPCIA_HAE_ADDRESS	(&alpha_mv.hae_cache)
#पूर्ण_अगर
#अगर_घोषित T2_ONE_HAE_WINDOW
#घोषणा T2_HAE_ADDRESS		(&alpha_mv.hae_cache)
#पूर्ण_अगर

/* Only a few प्रणालीs करोn't define IACK_SC, handling all पूर्णांकerrupts through
   the SRM console.  But splitting out that one हाल from IO() below
   seems like such a pain.  Define this to get things to compile.  */
#घोषणा JENSEN_IACK_SC		1
#घोषणा T2_IACK_SC		1
#घोषणा WILDFIRE_IACK_SC	1 /* FIXME */

/*
 * Some helpful macros क्रम filling in the blanks.
 */

#घोषणा CAT1(x,y)  x##y
#घोषणा CAT(x,y)   CAT1(x,y)

#घोषणा DO_DEFAULT_RTC			.rtc_port = 0x70

#घोषणा DO_EV4_MMU							\
	.max_asn =			EV4_MAX_ASN,			\
	.mv_चयन_mm =			ev4_चयन_mm,			\
	.mv_activate_mm =		ev4_activate_mm,		\
	.mv_flush_tlb_current =		ev4_flush_tlb_current,		\
	.mv_flush_tlb_current_page =	ev4_flush_tlb_current_page

#घोषणा DO_EV5_MMU							\
	.max_asn =			EV5_MAX_ASN,			\
	.mv_चयन_mm =			ev5_चयन_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_flush_tlb_current =		ev5_flush_tlb_current,		\
	.mv_flush_tlb_current_page =	ev5_flush_tlb_current_page

#घोषणा DO_EV6_MMU							\
	.max_asn =			EV6_MAX_ASN,			\
	.mv_चयन_mm =			ev5_चयन_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_flush_tlb_current =		ev5_flush_tlb_current,		\
	.mv_flush_tlb_current_page =	ev5_flush_tlb_current_page

#घोषणा DO_EV7_MMU							\
	.max_asn =			EV6_MAX_ASN,			\
	.mv_चयन_mm =			ev5_चयन_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_flush_tlb_current =		ev5_flush_tlb_current,		\
	.mv_flush_tlb_current_page =	ev5_flush_tlb_current_page

#घोषणा IO_LITE(UP,low)							\
	.hae_रेजिस्टर =		(अचिन्हित दीर्घ *) CAT(UP,_HAE_ADDRESS),	\
	.iack_sc =		CAT(UP,_IACK_SC),			\
	.mv_ioपढ़ो8 =		CAT(low,_ioपढ़ो8),			\
	.mv_ioपढ़ो16 =		CAT(low,_ioपढ़ो16),			\
	.mv_ioपढ़ो32 =		CAT(low,_ioपढ़ो32),			\
	.mv_ioग_लिखो8 =		CAT(low,_ioग_लिखो8),			\
	.mv_ioग_लिखो16 =		CAT(low,_ioग_लिखो16),			\
	.mv_ioग_लिखो32 =		CAT(low,_ioग_लिखो32),			\
	.mv_पढ़ोb =		CAT(low,_पढ़ोb),			\
	.mv_पढ़ोw =		CAT(low,_पढ़ोw),			\
	.mv_पढ़ोl =		CAT(low,_पढ़ोl),			\
	.mv_पढ़ोq =		CAT(low,_पढ़ोq),			\
	.mv_ग_लिखोb =		CAT(low,_ग_लिखोb),			\
	.mv_ग_लिखोw =		CAT(low,_ग_लिखोw),			\
	.mv_ग_लिखोl =		CAT(low,_ग_लिखोl),			\
	.mv_ग_लिखोq =		CAT(low,_ग_लिखोq),			\
	.mv_ioporपंचांगap =		CAT(low,_ioporपंचांगap),			\
	.mv_ioremap =		CAT(low,_ioremap),			\
	.mv_iounmap =		CAT(low,_iounmap),			\
	.mv_is_ioaddr =		CAT(low,_is_ioaddr),			\
	.mv_is_mmio =		CAT(low,_is_mmio)			\

#घोषणा IO(UP,low)							\
	IO_LITE(UP,low),						\
	.pci_ops =		&CAT(low,_pci_ops),			\
	.mv_pci_tbi =		CAT(low,_pci_tbi)

#घोषणा DO_APECS_IO	IO(APECS,apecs)
#घोषणा DO_CIA_IO	IO(CIA,cia)
#घोषणा DO_IRONGATE_IO	IO(IRONGATE,irongate)
#घोषणा DO_LCA_IO	IO(LCA,lca)
#घोषणा DO_MARVEL_IO	IO(MARVEL,marvel)
#घोषणा DO_MCPCIA_IO	IO(MCPCIA,mcpcia)
#घोषणा DO_POLARIS_IO	IO(POLARIS,polaris)
#घोषणा DO_T2_IO	IO(T2,t2)
#घोषणा DO_TSUNAMI_IO	IO(TSUNAMI,tsunami)
#घोषणा DO_TITAN_IO	IO(TITAN,titan)
#घोषणा DO_WILDFIRE_IO	IO(WILDFIRE,wildfire)

#घोषणा DO_PYXIS_IO	IO_LITE(CIA,cia_bwx), \
			.pci_ops = &cia_pci_ops, \
			.mv_pci_tbi = cia_pci_tbi

/*
 * In a GENERIC kernel, we have lots of these vectors भग्नing about,
 * all but one of which we want to go away.  In a non-GENERIC kernel,
 * we want only one, ever.
 *
 * Accomplish this in the GENERIC kernel by putting all of the vectors
 * in the .init.data section where they'll go away.  We'll copy the
 * one we want to the real alpha_mv vector in setup_arch.
 *
 * Accomplish this in a non-GENERIC kernel by अगरdef'ing out all but
 * one of the vectors, which will not reside in .init.data.  We then
 * alias this one vector to alpha_mv, so no copy is needed.
 *
 * Upshot: set __initdata to nothing क्रम non-GENERIC kernels.
 */

#अगर_घोषित CONFIG_ALPHA_GENERIC
#घोषणा __iniपंचांगv __initdata
#घोषणा ALIAS_MV(x)
#अन्यथा
#घोषणा __iniपंचांगv __refdata

/* GCC actually has a syntax क्रम defining aliases, but is under some
   delusion that you shouldn't be able to declare it बाह्य somewhere
   अन्यथा beक्रमehand.  Fine.  We'll करो it ourselves.  */
#अगर 0
#घोषणा ALIAS_MV(प्रणाली) \
  काष्ठा alpha_machine_vector alpha_mv __attribute__((alias(#प्रणाली "_mv"))); \
  EXPORT_SYMBOL(alpha_mv);
#अन्यथा
#घोषणा ALIAS_MV(प्रणाली) \
  यंत्र(".global alpha_mv\nalpha_mv = " #प्रणाली "_mv"); \
  EXPORT_SYMBOL(alpha_mv);
#पूर्ण_अगर
#पूर्ण_अगर /* GENERIC */
