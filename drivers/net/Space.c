<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Holds initial configuration inक्रमmation क्रम devices.
 *
 * Version:	@(#)Space.c	1.0.7	08/12/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald J. Becker, <becker@scyld.com>
 *
 * Changelog:
 *		Stephen Hemminger (09/2003)
 *		- get rid of pre-linked dev list, dynamic device allocation
 *		Paul Gorपंचांगaker (03/2002)
 *		- काष्ठा init cleanup, enable multiple ISA स्वतःprobes.
 *		Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - 09/1999
 *		- fix sbni: s/device/net_device/
 *		Paul Gorपंचांगaker (06/98):
 *		 - sort probes in a sane way, make sure all (safe) probes
 *		   get run once & failed स्वतःprobes करोn't स्वतःprobe again.
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netlink.h>
#समावेश <net/Space.h>

/* A unअगरied ethernet device probe.  This is the easiest way to have every
 * ethernet adaptor have the name "eth[0123...]".
 */

काष्ठा devprobe2 अणु
	काष्ठा net_device *(*probe)(पूर्णांक unit);
	पूर्णांक status;	/* non-zero अगर स्वतःprobe has failed */
पूर्ण;

अटल पूर्णांक __init probe_list2(पूर्णांक unit, काष्ठा devprobe2 *p, पूर्णांक स्वतःprobe)
अणु
	काष्ठा net_device *dev;

	क्रम (; p->probe; p++) अणु
		अगर (स्वतःprobe && p->status)
			जारी;
		dev = p->probe(unit);
		अगर (!IS_ERR(dev))
			वापस 0;
		अगर (स्वतःprobe)
			p->status = PTR_ERR(dev);
	पूर्ण
	वापस -ENODEV;
पूर्ण

/* ISA probes that touch addresses < 0x400 (including those that also
 * look क्रम EISA/PCI cards in addition to ISA cards).
 */
अटल काष्ठा devprobe2 isa_probes[] __initdata = अणु
#अगर_घोषित CONFIG_3C515
	अणुtc515_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ULTRA
	अणुultra_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_WD80x3
	अणुwd_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_NE2000) /* ISA (use ne2k-pci क्रम PCI cards) */
	अणुne_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LANCE		/* ISA/VLB (use pcnet32 क्रम PCI cards) */
	अणुlance_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMC9194
	अणुsmc_init, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CS89x0
#अगर_अघोषित CONFIG_CS89x0_PLATFORM
	अणुcs89x0_probe, 0पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर defined(CONFIG_MVME16x_NET) || defined(CONFIG_BVME6000_NET)	/* Intel */
	अणुi82596_probe, 0पूर्ण,					/* I82596 */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NI65
	अणुni65_probe, 0पूर्ण,
#पूर्ण_अगर
	अणुशून्य, 0पूर्ण,
पूर्ण;

अटल काष्ठा devprobe2 m68k_probes[] __initdata = अणु
#अगर_घोषित CONFIG_ATARILANCE	/* Lance-based Atari ethernet boards */
	अणुatarilance_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3LANCE         /* sun3 onboard Lance chip */
	अणुsun3lance_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SUN3_82586        /* sun3 onboard Intel 82586 chip */
	अणुsun3_82586_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_APNE		/* A1200 PCMCIA NE2000 */
	अणुapne_probe, 0पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MVME147_NET	/* MVME147 पूर्णांकernal Ethernet */
	अणुmvme147lance_probe, 0पूर्ण,
#पूर्ण_अगर
	अणुशून्य, 0पूर्ण,
पूर्ण;

/* Unअगरied ethernet device probe, segmented per architecture and
 * per bus पूर्णांकerface. This drives the legacy devices only क्रम now.
 */

अटल व्योम __init ethअगर_probe2(पूर्णांक unit)
अणु
	अचिन्हित दीर्घ base_addr = netdev_boot_base("eth", unit);

	अगर (base_addr == 1)
		वापस;

	(व्योम)(probe_list2(unit, m68k_probes, base_addr == 0) &&
		probe_list2(unit, isa_probes, base_addr == 0));
पूर्ण

/*  Statically configured drivers -- order matters here. */
अटल पूर्णांक __init net_olddevs_init(व्योम)
अणु
	पूर्णांक num;

#अगर_घोषित CONFIG_SBNI
	क्रम (num = 0; num < 8; ++num)
		sbni_probe(num);
#पूर्ण_अगर
	क्रम (num = 0; num < 8; ++num)
		ethअगर_probe2(num);

#अगर_घोषित CONFIG_COPS
	cops_probe(0);
	cops_probe(1);
	cops_probe(2);
#पूर्ण_अगर
#अगर_घोषित CONFIG_LTPC
	ltpc_probe();
#पूर्ण_अगर

	वापस 0;
पूर्ण

device_initcall(net_olddevs_init);
