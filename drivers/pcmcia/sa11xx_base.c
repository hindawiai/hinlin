<शैली गुरु>
/*======================================================================

    Device driver क्रम the PCMCIA control functionality of StrongARM
    SA-1100 microprocessors.

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is John G. Dorsey
    <john+@cs.cmu.edu>.  Portions created by John G. Dorsey are
    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>

#समावेश "soc_common.h"
#समावेश "sa11xx_base.h"


/*
 * sa1100_pcmcia_शेष_mecr_timing
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Calculate MECR घड़ी रुको states क्रम given CPU घड़ी
 * speed and command रुको state. This function can be over-
 * written by a board specअगरic version.
 *
 * The शेष is to simply calculate the BS values as specअगरied in
 * the INTEL SA1100 development manual
 * "Expansion Memory (PCMCIA) Configuration Register (MECR)"
 * that's section 10.2.5 in _my_ version of the manual ;)
 */
अटल अचिन्हित पूर्णांक
sa1100_pcmcia_शेष_mecr_timing(काष्ठा soc_pcmcia_socket *skt,
				  अचिन्हित पूर्णांक cpu_speed,
				  अचिन्हित पूर्णांक cmd_समय)
अणु
	वापस sa1100_pcmcia_mecr_bs(cmd_समय, cpu_speed);
पूर्ण

/* sa1100_pcmcia_set_mecr()
 * ^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * set MECR value क्रम socket <sock> based on this sockets
 * io, mem and attribute space access speed.
 * Call board specअगरic BS value calculation to allow boards
 * to tweak the BS values.
 */
अटल पूर्णांक
sa1100_pcmcia_set_mecr(काष्ठा soc_pcmcia_socket *skt, अचिन्हित पूर्णांक cpu_घड़ी)
अणु
	काष्ठा soc_pcmcia_timing timing;
	u32 mecr, old_mecr;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bs_io, bs_mem, bs_attr;

	soc_common_pcmcia_get_timing(skt, &timing);

	bs_io = skt->ops->get_timing(skt, cpu_घड़ी, timing.io);
	bs_mem = skt->ops->get_timing(skt, cpu_घड़ी, timing.mem);
	bs_attr = skt->ops->get_timing(skt, cpu_घड़ी, timing.attr);

	local_irq_save(flags);

	old_mecr = mecr = MECR;
	MECR_FAST_SET(mecr, skt->nr, 0);
	MECR_BSIO_SET(mecr, skt->nr, bs_io);
	MECR_BSA_SET(mecr, skt->nr, bs_attr);
	MECR_BSM_SET(mecr, skt->nr, bs_mem);
	अगर (old_mecr != mecr)
		MECR = mecr;

	local_irq_restore(flags);

	debug(skt, 2, "FAST %X  BSM %X  BSA %X  BSIO %X\n",
	      MECR_FAST_GET(mecr, skt->nr),
	      MECR_BSM_GET(mecr, skt->nr), MECR_BSA_GET(mecr, skt->nr),
	      MECR_BSIO_GET(mecr, skt->nr));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक
sa1100_pcmcia_frequency_change(काष्ठा soc_pcmcia_socket *skt,
			       अचिन्हित दीर्घ val,
			       काष्ठा cpufreq_freqs *freqs)
अणु
	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
		अगर (freqs->new > freqs->old)
			sa1100_pcmcia_set_mecr(skt, freqs->new);
		अवरोध;

	हाल CPUFREQ_POSTCHANGE:
		अगर (freqs->new < freqs->old)
			sa1100_pcmcia_set_mecr(skt, freqs->new);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक
sa1100_pcmcia_set_timing(काष्ठा soc_pcmcia_socket *skt)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(skt->clk);

	वापस sa1100_pcmcia_set_mecr(skt, clk / 1000);
पूर्ण

अटल पूर्णांक
sa1100_pcmcia_show_timing(काष्ठा soc_pcmcia_socket *skt, अक्षर *buf)
अणु
	काष्ठा soc_pcmcia_timing timing;
	अचिन्हित पूर्णांक घड़ी = clk_get_rate(skt->clk) / 1000;
	अचिन्हित दीर्घ mecr = MECR;
	अक्षर *p = buf;

	soc_common_pcmcia_get_timing(skt, &timing);

	p+=प्र_लिखो(p, "I/O      : %uns (%uns)\n", timing.io,
		   sa1100_pcmcia_cmd_समय(घड़ी, MECR_BSIO_GET(mecr, skt->nr)));

	p+=प्र_लिखो(p, "attribute: %uns (%uns)\n", timing.attr,
		   sa1100_pcmcia_cmd_समय(घड़ी, MECR_BSA_GET(mecr, skt->nr)));

	p+=प्र_लिखो(p, "common   : %uns (%uns)\n", timing.mem,
		   sa1100_pcmcia_cmd_समय(घड़ी, MECR_BSM_GET(mecr, skt->nr)));

	वापस p - buf;
पूर्ण

अटल स्थिर अक्षर *skt_names[] = अणु
	"PCMCIA socket 0",
	"PCMCIA socket 1",
पूर्ण;

#घोषणा SKT_DEV_INFO_SIZE(n) \
	(माप(काष्ठा skt_dev_info) + (n)*माप(काष्ठा soc_pcmcia_socket))

पूर्णांक sa11xx_drv_pcmcia_add_one(काष्ठा soc_pcmcia_socket *skt)
अणु
	skt->res_skt.start = _PCMCIA(skt->nr);
	skt->res_skt.end = _PCMCIA(skt->nr) + PCMCIASp - 1;
	skt->res_skt.name = skt_names[skt->nr];
	skt->res_skt.flags = IORESOURCE_MEM;

	skt->res_io.start = _PCMCIAIO(skt->nr);
	skt->res_io.end = _PCMCIAIO(skt->nr) + PCMCIAIOSp - 1;
	skt->res_io.name = "io";
	skt->res_io.flags = IORESOURCE_MEM | IORESOURCE_BUSY;

	skt->res_mem.start = _PCMCIAMem(skt->nr);
	skt->res_mem.end = _PCMCIAMem(skt->nr) + PCMCIAMemSp - 1;
	skt->res_mem.name = "memory";
	skt->res_mem.flags = IORESOURCE_MEM;

	skt->res_attr.start = _PCMCIAAttr(skt->nr);
	skt->res_attr.end = _PCMCIAAttr(skt->nr) + PCMCIAAttrSp - 1;
	skt->res_attr.name = "attribute";
	skt->res_attr.flags = IORESOURCE_MEM;

	वापस soc_pcmcia_add_one(skt);
पूर्ण
EXPORT_SYMBOL(sa11xx_drv_pcmcia_add_one);

व्योम sa11xx_drv_pcmcia_ops(काष्ठा pcmcia_low_level *ops)
अणु
	/*
	 * set शेष MECR calculation अगर the board specअगरic
	 * code did not specअगरy one...
	 */
	अगर (!ops->get_timing)
		ops->get_timing = sa1100_pcmcia_शेष_mecr_timing;

	/* Provide our SA11x0 specअगरic timing routines. */
	ops->set_timing  = sa1100_pcmcia_set_timing;
	ops->show_timing = sa1100_pcmcia_show_timing;
#अगर_घोषित CONFIG_CPU_FREQ
	ops->frequency_change = sa1100_pcmcia_frequency_change;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(sa11xx_drv_pcmcia_ops);

पूर्णांक sa11xx_drv_pcmcia_probe(काष्ठा device *dev, काष्ठा pcmcia_low_level *ops,
			    पूर्णांक first, पूर्णांक nr)
अणु
	काष्ठा skt_dev_info *sinfo;
	काष्ठा soc_pcmcia_socket *skt;
	पूर्णांक i, ret = 0;
	काष्ठा clk *clk;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	sa11xx_drv_pcmcia_ops(ops);

	sinfo = devm_kzalloc(dev, SKT_DEV_INFO_SIZE(nr), GFP_KERNEL);
	अगर (!sinfo)
		वापस -ENOMEM;

	sinfo->nskt = nr;

	/* Initialize processor specअगरic parameters */
	क्रम (i = 0; i < nr; i++) अणु
		skt = &sinfo->skt[i];

		skt->nr = first + i;
		skt->clk = clk;
		soc_pcmcia_init_one(skt, ops, dev);

		ret = sa11xx_drv_pcmcia_add_one(skt);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		जबतक (--i >= 0)
			soc_pcmcia_हटाओ_one(&sinfo->skt[i]);
	पूर्ण अन्यथा अणु
		dev_set_drvdata(dev, sinfo);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sa11xx_drv_pcmcia_probe);

MODULE_AUTHOR("John Dorsey <john+@cs.cmu.edu>");
MODULE_DESCRIPTION("Linux PCMCIA Card Services: SA-11xx core socket driver");
MODULE_LICENSE("Dual MPL/GPL");
