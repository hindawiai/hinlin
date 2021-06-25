<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*======================================================================

  Device driver क्रम the PCMCIA control functionality of PXA2xx
  microprocessors.


    (c) Ian Molton (spyro@f2s.com) 2003
    (c) Stefan Eletzhofer (stefan.eletzhofer@inquant.de) 2003,4

    derived from sa11xx_base.c

     Portions created by John G. Dorsey are
     Copyright (C) 1999 John G. Dorsey.

  ======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <mach/hardware.h>
#समावेश <mach/smemc.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>

#समावेश "soc_common.h"
#समावेश "pxa2xx_base.h"

/*
 * Personal Computer Memory Card International Association (PCMCIA) sockets
 */

#घोषणा PCMCIAPrtSp	0x04000000	/* PCMCIA Partition Space [byte]   */
#घोषणा PCMCIASp	(4*PCMCIAPrtSp)	/* PCMCIA Space [byte]             */
#घोषणा PCMCIAIOSp	PCMCIAPrtSp	/* PCMCIA I/O Space [byte]         */
#घोषणा PCMCIAAttrSp	PCMCIAPrtSp	/* PCMCIA Attribute Space [byte]   */
#घोषणा PCMCIAMemSp	PCMCIAPrtSp	/* PCMCIA Memory Space [byte]      */

#घोषणा PCMCIA0Sp	PCMCIASp	/* PCMCIA 0 Space [byte]           */
#घोषणा PCMCIA0IOSp	PCMCIAIOSp	/* PCMCIA 0 I/O Space [byte]       */
#घोषणा PCMCIA0AttrSp	PCMCIAAttrSp	/* PCMCIA 0 Attribute Space [byte] */
#घोषणा PCMCIA0MemSp	PCMCIAMemSp	/* PCMCIA 0 Memory Space [byte]    */

#घोषणा PCMCIA1Sp	PCMCIASp	/* PCMCIA 1 Space [byte]           */
#घोषणा PCMCIA1IOSp	PCMCIAIOSp	/* PCMCIA 1 I/O Space [byte]       */
#घोषणा PCMCIA1AttrSp	PCMCIAAttrSp	/* PCMCIA 1 Attribute Space [byte] */
#घोषणा PCMCIA1MemSp	PCMCIAMemSp	/* PCMCIA 1 Memory Space [byte]    */

#घोषणा _PCMCIA(Nb)			/* PCMCIA [0..1]                   */ \
			(0x20000000 + (Nb) * PCMCIASp)
#घोषणा _PCMCIAIO(Nb)	_PCMCIA(Nb)	/* PCMCIA I/O [0..1]               */
#घोषणा _PCMCIAAttr(Nb)			/* PCMCIA Attribute [0..1]         */ \
			(_PCMCIA(Nb) + 2 * PCMCIAPrtSp)
#घोषणा _PCMCIAMem(Nb)			/* PCMCIA Memory [0..1]            */ \
			(_PCMCIA(Nb) + 3 * PCMCIAPrtSp)

#घोषणा _PCMCIA0	_PCMCIA(0)	/* PCMCIA 0                        */
#घोषणा _PCMCIA0IO	_PCMCIAIO(0)	/* PCMCIA 0 I/O                    */
#घोषणा _PCMCIA0Attr	_PCMCIAAttr(0)	/* PCMCIA 0 Attribute              */
#घोषणा _PCMCIA0Mem	_PCMCIAMem(0)	/* PCMCIA 0 Memory                 */

#घोषणा _PCMCIA1	_PCMCIA(1)	/* PCMCIA 1                        */
#घोषणा _PCMCIA1IO	_PCMCIAIO(1)	/* PCMCIA 1 I/O                    */
#घोषणा _PCMCIA1Attr	_PCMCIAAttr(1)	/* PCMCIA 1 Attribute              */
#घोषणा _PCMCIA1Mem	_PCMCIAMem(1)	/* PCMCIA 1 Memory                 */


#घोषणा MCXX_SETUP_MASK     (0x7f)
#घोषणा MCXX_ASST_MASK      (0x1f)
#घोषणा MCXX_HOLD_MASK      (0x3f)
#घोषणा MCXX_SETUP_SHIFT    (0)
#घोषणा MCXX_ASST_SHIFT     (7)
#घोषणा MCXX_HOLD_SHIFT     (14)

अटल अंतरभूत u_पूर्णांक pxa2xx_mcxx_hold(u_पूर्णांक pcmcia_cycle_ns,
				     u_पूर्णांक mem_clk_10khz)
अणु
	u_पूर्णांक code = pcmcia_cycle_ns * mem_clk_10khz;
	वापस (code / 300000) + ((code % 300000) ? 1 : 0) - 1;
पूर्ण

अटल अंतरभूत u_पूर्णांक pxa2xx_mcxx_asst(u_पूर्णांक pcmcia_cycle_ns,
				     u_पूर्णांक mem_clk_10khz)
अणु
	u_पूर्णांक code = pcmcia_cycle_ns * mem_clk_10khz;
	वापस (code / 300000) + ((code % 300000) ? 1 : 0) + 1;
पूर्ण

अटल अंतरभूत u_पूर्णांक pxa2xx_mcxx_setup(u_पूर्णांक pcmcia_cycle_ns,
				      u_पूर्णांक mem_clk_10khz)
अणु
	u_पूर्णांक code = pcmcia_cycle_ns * mem_clk_10khz;
	वापस (code / 100000) + ((code % 100000) ? 1 : 0) - 1;
पूर्ण

/* This function वापसs the (approximate) command निश्चितion period, in
 * nanoseconds, क्रम a given CPU घड़ी frequency and MCXX_ASST value:
 */
अटल अंतरभूत u_पूर्णांक pxa2xx_pcmcia_cmd_समय(u_पूर्णांक mem_clk_10khz,
					   u_पूर्णांक pcmcia_mcxx_asst)
अणु
	वापस (300000 * (pcmcia_mcxx_asst + 1) / mem_clk_10khz);
पूर्ण

अटल पूर्णांक pxa2xx_pcmcia_set_mcmem( पूर्णांक sock, पूर्णांक speed, पूर्णांक घड़ी )
अणु
	uपूर्णांक32_t val;

	val = ((pxa2xx_mcxx_setup(speed, घड़ी)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, घड़ी)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_hold(speed, घड़ी)
		& MCXX_HOLD_MASK) << MCXX_HOLD_SHIFT);

	__raw_ग_लिखोl(val, MCMEM(sock));

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pcmcia_set_mcio( पूर्णांक sock, पूर्णांक speed, पूर्णांक घड़ी )
अणु
	uपूर्णांक32_t val;

	val = ((pxa2xx_mcxx_setup(speed, घड़ी)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, घड़ी)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_hold(speed, घड़ी)
		& MCXX_HOLD_MASK) << MCXX_HOLD_SHIFT);

	__raw_ग_लिखोl(val, MCIO(sock));

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pcmcia_set_mcatt( पूर्णांक sock, पूर्णांक speed, पूर्णांक घड़ी )
अणु
	uपूर्णांक32_t val;

	val = ((pxa2xx_mcxx_setup(speed, घड़ी)
		& MCXX_SETUP_MASK) << MCXX_SETUP_SHIFT)
		| ((pxa2xx_mcxx_asst(speed, घड़ी)
		& MCXX_ASST_MASK) << MCXX_ASST_SHIFT)
		| ((pxa2xx_mcxx_hold(speed, घड़ी)
		& MCXX_HOLD_MASK) << MCXX_HOLD_SHIFT);

	__raw_ग_लिखोl(val, MCATT(sock));

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pcmcia_set_mcxx(काष्ठा soc_pcmcia_socket *skt, अचिन्हित पूर्णांक clk)
अणु
	काष्ठा soc_pcmcia_timing timing;
	पूर्णांक sock = skt->nr;

	soc_common_pcmcia_get_timing(skt, &timing);

	pxa2xx_pcmcia_set_mcmem(sock, timing.mem, clk);
	pxa2xx_pcmcia_set_mcatt(sock, timing.attr, clk);
	pxa2xx_pcmcia_set_mcio(sock, timing.io, clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pcmcia_set_timing(काष्ठा soc_pcmcia_socket *skt)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(skt->clk);
	वापस pxa2xx_pcmcia_set_mcxx(skt, clk / 10000);
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ

अटल पूर्णांक
pxa2xx_pcmcia_frequency_change(काष्ठा soc_pcmcia_socket *skt,
			       अचिन्हित दीर्घ val,
			       काष्ठा cpufreq_freqs *freqs)
अणु
	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
		अगर (freqs->new > freqs->old) अणु
			debug(skt, 2, "new frequency %u.%uMHz > %u.%uMHz, "
			       "pre-updating\n",
			       freqs->new / 1000, (freqs->new / 100) % 10,
			       freqs->old / 1000, (freqs->old / 100) % 10);
			pxa2xx_pcmcia_set_timing(skt);
		पूर्ण
		अवरोध;

	हाल CPUFREQ_POSTCHANGE:
		अगर (freqs->new < freqs->old) अणु
			debug(skt, 2, "new frequency %u.%uMHz < %u.%uMHz, "
			       "post-updating\n",
			       freqs->new / 1000, (freqs->new / 100) % 10,
			       freqs->old / 1000, (freqs->old / 100) % 10);
			pxa2xx_pcmcia_set_timing(skt);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम pxa2xx_configure_sockets(काष्ठा device *dev, काष्ठा pcmcia_low_level *ops)
अणु
	/*
	 * We have at least one socket, so set MECR:CIT
	 * (Card Is There)
	 */
	uपूर्णांक32_t mecr = MECR_CIT;

	/* Set MECR:NOS (Number Of Sockets) */
	अगर ((ops->first + ops->nr) > 1 ||
	    machine_is_viper() || machine_is_arcom_zeus())
		mecr |= MECR_NOS;

	__raw_ग_लिखोl(mecr, MECR);
पूर्ण
EXPORT_SYMBOL(pxa2xx_configure_sockets);

अटल स्थिर अक्षर *skt_names[] = अणु
	"PCMCIA socket 0",
	"PCMCIA socket 1",
पूर्ण;

#घोषणा SKT_DEV_INFO_SIZE(n) \
	(माप(काष्ठा skt_dev_info) + (n)*माप(काष्ठा soc_pcmcia_socket))

पूर्णांक pxa2xx_drv_pcmcia_add_one(काष्ठा soc_pcmcia_socket *skt)
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
EXPORT_SYMBOL(pxa2xx_drv_pcmcia_add_one);

व्योम pxa2xx_drv_pcmcia_ops(काष्ठा pcmcia_low_level *ops)
अणु
	/* Provide our PXA2xx specअगरic timing routines. */
	ops->set_timing  = pxa2xx_pcmcia_set_timing;
#अगर_घोषित CONFIG_CPU_FREQ
	ops->frequency_change = pxa2xx_pcmcia_frequency_change;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pxa2xx_drv_pcmcia_ops);

अटल पूर्णांक pxa2xx_drv_pcmcia_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा pcmcia_low_level *ops;
	काष्ठा skt_dev_info *sinfo;
	काष्ठा soc_pcmcia_socket *skt;
	काष्ठा clk *clk;

	ops = (काष्ठा pcmcia_low_level *)dev->dev.platक्रमm_data;
	अगर (!ops) अणु
		ret = -ENODEV;
		जाओ err0;
	पूर्ण

	अगर (cpu_is_pxa320() && ops->nr > 1) अणु
		dev_err(&dev->dev, "pxa320 supports only one pcmcia slot");
		ret = -EINVAL;
		जाओ err0;
	पूर्ण

	clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस -ENODEV;

	pxa2xx_drv_pcmcia_ops(ops);

	sinfo = devm_kzalloc(&dev->dev, SKT_DEV_INFO_SIZE(ops->nr),
			     GFP_KERNEL);
	अगर (!sinfo)
		वापस -ENOMEM;

	sinfo->nskt = ops->nr;

	/* Initialize processor specअगरic parameters */
	क्रम (i = 0; i < ops->nr; i++) अणु
		skt = &sinfo->skt[i];

		skt->nr = ops->first + i;
		skt->clk = clk;
		soc_pcmcia_init_one(skt, ops, &dev->dev);

		ret = pxa2xx_drv_pcmcia_add_one(skt);
		अगर (ret)
			जाओ err1;
	पूर्ण

	pxa2xx_configure_sockets(&dev->dev, ops);
	dev_set_drvdata(&dev->dev, sinfo);

	वापस 0;

err1:
	जबतक (--i >= 0)
		soc_pcmcia_हटाओ_one(&sinfo->skt[i]);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक pxa2xx_drv_pcmcia_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा skt_dev_info *sinfo = platक्रमm_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_हटाओ_one(&sinfo->skt[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_drv_pcmcia_resume(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_low_level *ops = (काष्ठा pcmcia_low_level *)dev->platक्रमm_data;

	pxa2xx_configure_sockets(dev, ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pxa2xx_drv_pcmcia_pm_ops = अणु
	.resume		= pxa2xx_drv_pcmcia_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver pxa2xx_pcmcia_driver = अणु
	.probe		= pxa2xx_drv_pcmcia_probe,
	.हटाओ		= pxa2xx_drv_pcmcia_हटाओ,
	.driver		= अणु
		.name	= "pxa2xx-pcmcia",
		.pm	= &pxa2xx_drv_pcmcia_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pxa2xx_pcmcia_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pxa2xx_pcmcia_driver);
पूर्ण

अटल व्योम __निकास pxa2xx_pcmcia_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pxa2xx_pcmcia_driver);
पूर्ण

fs_initcall(pxa2xx_pcmcia_init);
module_निकास(pxa2xx_pcmcia_निकास);

MODULE_AUTHOR("Stefan Eletzhofer <stefan.eletzhofer@inquant.de> and Ian Molton <spyro@f2s.com>");
MODULE_DESCRIPTION("Linux PCMCIA Card Services: PXA2xx core socket driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-pcmcia");
