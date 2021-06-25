<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *	baycom_par.c  -- baycom par96 and picpar radio modem driver.
 *
 *	Copyright (C) 1996-2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 *
 *  Supported modems
 *
 *  par96:  This is a modem क्रम 9600 baud FSK compatible to the G3RUH standard.
 *          The modem करोes all the filtering and regenerates the receiver घड़ी.
 *          Data is transferred from and to the PC via a shअगरt रेजिस्टर.
 *          The shअगरt रेजिस्टर is filled with 16 bits and an पूर्णांकerrupt is
 *          संकेतled. The PC then empties the shअगरt रेजिस्टर in a burst. This
 *          modem connects to the parallel port, hence the name. The modem
 *          leaves the implementation of the HDLC protocol and the scrambler
 *          polynomial to the PC. This modem is no दीर्घer available (at least
 *          from Baycom) and has been replaced by the PICPAR modem (see below).
 *          You may however still build one from the schematics published in
 *          cq-DL :-).
 *
 *  picpar: This is a redesign of the par96 modem by Henning Rech, DF9IC. The
 *          modem is protocol compatible to par96, but uses only three low
 *          घातer ICs and can thereक्रमe be fed from the parallel port and
 *          करोes not require an additional घातer supply. It features
 *          built in DCD circuitry. The driver should thereक्रमe be configured
 *          क्रम hardware DCD.
 *
 *  Command line options (insmod command line)
 *
 *  mode     driver mode string. Valid choices are par96 and picpar.
 *  iobase   base address of the port; common values are 0x378, 0x278, 0x3bc
 *
 *  History:
 *   0.1  26.06.1996  Adapted from baycom.c and made network driver पूर्णांकerface
 *        18.10.1996  Changed to new user space access routines (copy_अणुto,fromपूर्ण_user)
 *   0.3  26.04.1997  init code/data tagged
 *   0.4  08.07.1997  alternative ser12 decoding algorithm (uses delta CTS पूर्णांकs)
 *   0.5  11.11.1997  split पूर्णांकo separate files क्रम ser12/par96
 *   0.6  03.08.1999  adapt to Linus' new __setup/__initcall
 *                    हटाओd some pre-2.2 kernel compatibility cruft
 *   0.7  10.08.1999  Check अगर parport can करो SPP and is safe to access during पूर्णांकerrupt contexts
 *   0.8  12.02.2000  adapted to softnet driver पूर्णांकerface
 *                    हटाओd direct parport access, uses parport driver methods
 *   0.9  03.07.2000  fix पूर्णांकerface name handling
 */

/*****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlcdrv.h>
#समावेश <linux/baycom.h>
#समावेश <linux/parport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/uaccess.h>

/* --------------------------------------------------------------------- */

#घोषणा BAYCOM_DEBUG

/*
 * modem options; bit mask
 */
#घोषणा BAYCOM_OPTIONS_SOFTDCD  1

/* --------------------------------------------------------------------- */

अटल स्थिर अक्षर bc_drvname[] = "baycom_par";
अटल स्थिर अक्षर bc_drvinfo[] = KERN_INFO "baycom_par: (C) 1996-2000 Thomas Sailer, HB9JNX/AE4WA\n"
"baycom_par: version 0.9\n";

/* --------------------------------------------------------------------- */

#घोषणा NR_PORTS 4

अटल काष्ठा net_device *baycom_device[NR_PORTS];

/* --------------------------------------------------------------------- */

#घोषणा PAR96_BURSTBITS 16
#घोषणा PAR96_BURST     4
#घोषणा PAR96_PTT       2
#घोषणा PAR96_TXBIT     1
#घोषणा PAR96_ACK       0x40
#घोषणा PAR96_RXBIT     0x20
#घोषणा PAR96_DCD       0x10
#घोषणा PAR97_POWER     0xf8

/* ---------------------------------------------------------------------- */
/*
 * Inक्रमmation that need to be kept क्रम each board.
 */

काष्ठा baycom_state अणु
	काष्ठा hdlcdrv_state hdrv;

	काष्ठा pardevice *pdev;
	अचिन्हित पूर्णांक options;

	काष्ठा modem_state अणु
		लघु arb_भागider;
		अचिन्हित अक्षर flags;
		अचिन्हित पूर्णांक shreg;
		काष्ठा modem_state_par96 अणु
			पूर्णांक dcd_count;
			अचिन्हित पूर्णांक dcd_shreg;
			अचिन्हित दीर्घ descram;
			अचिन्हित दीर्घ scram;
		पूर्ण par96;
	पूर्ण modem;

#अगर_घोषित BAYCOM_DEBUG
	काष्ठा debug_vals अणु
		अचिन्हित दीर्घ last_jअगरfies;
		अचिन्हित cur_पूर्णांकcnt;
		अचिन्हित last_पूर्णांकcnt;
		पूर्णांक cur_pllcorr;
		पूर्णांक last_pllcorr;
	पूर्ण debug_vals;
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण;

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम baycom_पूर्णांक_freq(काष्ठा baycom_state *bc)
अणु
#अगर_घोषित BAYCOM_DEBUG
	अचिन्हित दीर्घ cur_jअगरfies = jअगरfies;
	/*
	 * measure the पूर्णांकerrupt frequency
	 */
	bc->debug_vals.cur_पूर्णांकcnt++;
	अगर (समय_after_eq(cur_jअगरfies, bc->debug_vals.last_jअगरfies + HZ)) अणु
		bc->debug_vals.last_jअगरfies = cur_jअगरfies;
		bc->debug_vals.last_पूर्णांकcnt = bc->debug_vals.cur_पूर्णांकcnt;
		bc->debug_vals.cur_पूर्णांकcnt = 0;
		bc->debug_vals.last_pllcorr = bc->debug_vals.cur_pllcorr;
		bc->debug_vals.cur_pllcorr = 0;
	पूर्ण
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * ===================== PAR96 specअगरic routines =========================
 */

#घोषणा PAR96_DESCRAM_TAP1 0x20000
#घोषणा PAR96_DESCRAM_TAP2 0x01000
#घोषणा PAR96_DESCRAM_TAP3 0x00001

#घोषणा PAR96_DESCRAM_TAPSH1 17
#घोषणा PAR96_DESCRAM_TAPSH2 12
#घोषणा PAR96_DESCRAM_TAPSH3 0

#घोषणा PAR96_SCRAM_TAP1 0x20000 /* X^17 */
#घोषणा PAR96_SCRAM_TAPN 0x00021 /* X^0+X^5 */

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम par96_tx(काष्ठा net_device *dev, काष्ठा baycom_state *bc)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक data = hdlcdrv_getbits(&bc->hdrv);
	काष्ठा parport *pp = bc->pdev->port;

	क्रम(i = 0; i < PAR96_BURSTBITS; i++, data >>= 1) अणु
		अचिन्हित अक्षर val = PAR97_POWER;
		bc->modem.par96.scram = ((bc->modem.par96.scram << 1) |
					 (bc->modem.par96.scram & 1));
		अगर (!(data & 1))
			bc->modem.par96.scram ^= 1;
		अगर (bc->modem.par96.scram & (PAR96_SCRAM_TAP1 << 1))
			bc->modem.par96.scram ^=
				(PAR96_SCRAM_TAPN << 1);
		अगर (bc->modem.par96.scram & (PAR96_SCRAM_TAP1 << 2))
			val |= PAR96_TXBIT;
		pp->ops->ग_लिखो_data(pp, val);
		pp->ops->ग_लिखो_data(pp, val | PAR96_BURST);
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम par96_rx(काष्ठा net_device *dev, काष्ठा baycom_state *bc)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक data, mask, mask2, descx;
	काष्ठा parport *pp = bc->pdev->port;

	/*
	 * करो receiver; dअगरferential decode and descramble on the fly
	 */
	क्रम(data = i = 0; i < PAR96_BURSTBITS; i++) अणु
		bc->modem.par96.descram = (bc->modem.par96.descram << 1);
		अगर (pp->ops->पढ़ो_status(pp) & PAR96_RXBIT)
			bc->modem.par96.descram |= 1;
		descx = bc->modem.par96.descram ^
			(bc->modem.par96.descram >> 1);
		/* now the dअगरf decoded data is inverted in descram */
		pp->ops->ग_लिखो_data(pp, PAR97_POWER | PAR96_PTT);
		descx ^= ((descx >> PAR96_DESCRAM_TAPSH1) ^
			  (descx >> PAR96_DESCRAM_TAPSH2));
		data >>= 1;
		अगर (!(descx & 1))
			data |= 0x8000;
		pp->ops->ग_लिखो_data(pp, PAR97_POWER | PAR96_PTT | PAR96_BURST);
	पूर्ण
	hdlcdrv_putbits(&bc->hdrv, data);
	/*
	 * करो DCD algorithm
	 */
	अगर (bc->options & BAYCOM_OPTIONS_SOFTDCD) अणु
		bc->modem.par96.dcd_shreg = (bc->modem.par96.dcd_shreg >> 16)
			| (data << 16);
		/* search क्रम flags and set the dcd counter appropriately */
		क्रम(mask = 0x1fe00, mask2 = 0xfc00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			अगर ((bc->modem.par96.dcd_shreg & mask) == mask2)
				bc->modem.par96.dcd_count = HDLCDRV_MAXFLEN+4;
		/* check क्रम पात/noise sequences */
		क्रम(mask = 0x1fe00, mask2 = 0x1fe00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			अगर (((bc->modem.par96.dcd_shreg & mask) == mask2) &&
			    (bc->modem.par96.dcd_count >= 0))
				bc->modem.par96.dcd_count -= HDLCDRV_MAXFLEN-10;
		/* decrement and set the dcd variable */
		अगर (bc->modem.par96.dcd_count >= 0)
			bc->modem.par96.dcd_count -= 2;
		hdlcdrv_setdcd(&bc->hdrv, bc->modem.par96.dcd_count > 0);
	पूर्ण अन्यथा अणु
		hdlcdrv_setdcd(&bc->hdrv, !!(pp->ops->पढ़ो_status(pp) & PAR96_DCD));
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम par96_पूर्णांकerrupt(व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा baycom_state *bc = netdev_priv(dev);

	baycom_पूर्णांक_freq(bc);
	/*
	 * check अगर transmitter active
	 */
	अगर (hdlcdrv_ptt(&bc->hdrv))
		par96_tx(dev, bc);
	अन्यथा अणु
		par96_rx(dev, bc);
		अगर (--bc->modem.arb_भागider <= 0) अणु
			bc->modem.arb_भागider = 6;
			local_irq_enable();
			hdlcdrv_arbitrate(dev, &bc->hdrv);
		पूर्ण
	पूर्ण
	local_irq_enable();
	hdlcdrv_transmitter(dev, &bc->hdrv);
	hdlcdrv_receiver(dev, &bc->hdrv);
        local_irq_disable();
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम par96_wakeup(व्योम *handle)
अणु
        काष्ठा net_device *dev = (काष्ठा net_device *)handle;
	काष्ठा baycom_state *bc = netdev_priv(dev);

	prपूर्णांकk(KERN_DEBUG "baycom_par: %s: why am I being woken up?\n", dev->name);
	अगर (!parport_claim(bc->pdev))
		prपूर्णांकk(KERN_DEBUG "baycom_par: %s: I'm broken.\n", dev->name);
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक par96_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा pardev_cb par_cb;
	काष्ठा parport *pp;
	पूर्णांक i;

	अगर (!dev || !bc)
		वापस -ENXIO;
	pp = parport_find_base(dev->base_addr);
	अगर (!pp) अणु
		prपूर्णांकk(KERN_ERR "baycom_par: parport at 0x%lx unknown\n", dev->base_addr);
		वापस -ENXIO;
	पूर्ण
	अगर (pp->irq < 0) अणु
		prपूर्णांकk(KERN_ERR "baycom_par: parport at 0x%lx has no irq\n", pp->base);
		parport_put_port(pp);
		वापस -ENXIO;
	पूर्ण
	अगर ((~pp->modes) & (PARPORT_MODE_PCSPP | PARPORT_MODE_SAFEININT)) अणु
		prपूर्णांकk(KERN_ERR "baycom_par: parport at 0x%lx cannot be used\n", pp->base);
		parport_put_port(pp);
		वापस -ENXIO;
	पूर्ण
	स_रखो(&bc->modem, 0, माप(bc->modem));
	bc->hdrv.par.bitrate = 9600;
	स_रखो(&par_cb, 0, माप(par_cb));
	par_cb.wakeup = par96_wakeup;
	par_cb.irq_func = par96_पूर्णांकerrupt;
	par_cb.निजी = (व्योम *)dev;
	par_cb.flags = PARPORT_DEV_EXCL;
	क्रम (i = 0; i < NR_PORTS; i++)
		अगर (baycom_device[i] == dev)
			अवरोध;

	अगर (i == NR_PORTS) अणु
		pr_err("%s: no device found\n", bc_drvname);
		parport_put_port(pp);
		वापस -ENODEV;
	पूर्ण
	bc->pdev = parport_रेजिस्टर_dev_model(pp, dev->name, &par_cb, i);
	parport_put_port(pp);
	अगर (!bc->pdev) अणु
		prपूर्णांकk(KERN_ERR "baycom_par: cannot register parport at 0x%lx\n", dev->base_addr);
		वापस -ENXIO;
	पूर्ण
	अगर (parport_claim(bc->pdev)) अणु
		prपूर्णांकk(KERN_ERR "baycom_par: parport at 0x%lx busy\n", pp->base);
		parport_unरेजिस्टर_device(bc->pdev);
		वापस -EBUSY;
	पूर्ण
	pp = bc->pdev->port;
	dev->irq = pp->irq;
	pp->ops->data_क्रमward(pp);
        bc->hdrv.par.bitrate = 9600;
	pp->ops->ग_लिखो_data(pp, PAR96_PTT | PAR97_POWER); /* चयन off PTT */
	pp->ops->enable_irq(pp);
	prपूर्णांकk(KERN_INFO "%s: par96 at iobase 0x%lx irq %u options 0x%x\n",
	       bc_drvname, dev->base_addr, dev->irq, bc->options);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक par96_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा parport *pp;

	अगर (!dev || !bc)
		वापस -EINVAL;
	pp = bc->pdev->port;
	/* disable पूर्णांकerrupt */
	pp->ops->disable_irq(pp);
	/* चयन off PTT */
	pp->ops->ग_लिखो_data(pp, PAR96_PTT | PAR97_POWER);
	parport_release(bc->pdev);
	parport_unरेजिस्टर_device(bc->pdev);
	prपूर्णांकk(KERN_INFO "%s: close par96 at iobase 0x%lx irq %u\n",
	       bc_drvname, dev->base_addr, dev->irq);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * ===================== hdlcdrv driver पूर्णांकerface =========================
 */

अटल पूर्णांक baycom_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
			काष्ठा hdlcdrv_ioctl *hi, पूर्णांक cmd);

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा hdlcdrv_ops par96_ops = अणु
	.drvname = bc_drvname,
	.drvinfo = bc_drvinfo,
	.खोलो    = par96_खोलो,
	.बंद   = par96_बंद,
	.ioctl   = baycom_ioctl
पूर्ण;

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_seपंचांगode(काष्ठा baycom_state *bc, स्थिर अक्षर *modestr)
अणु
	अगर (!म_भेदन(modestr, "picpar", 6))
		bc->options = 0;
	अन्यथा अगर (!म_भेदन(modestr, "par96", 5))
		bc->options = BAYCOM_OPTIONS_SOFTDCD;
	अन्यथा
		bc->options = !!म_अक्षर(modestr, '*');
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
			काष्ठा hdlcdrv_ioctl *hi, पूर्णांक cmd)
अणु
	काष्ठा baycom_state *bc;
	काष्ठा baycom_ioctl bi;

	अगर (!dev)
		वापस -EINVAL;

	bc = netdev_priv(dev);
	BUG_ON(bc->hdrv.magic != HDLCDRV_MAGIC);

	अगर (cmd != SIOCDEVPRIVATE)
		वापस -ENOIOCTLCMD;
	चयन (hi->cmd) अणु
	शेष:
		अवरोध;

	हाल HDLCDRVCTL_GETMODE:
		म_नकल(hi->data.modename, bc->options ? "par96" : "picpar");
		अगर (copy_to_user(अगरr->अगरr_data, hi, माप(काष्ठा hdlcdrv_ioctl)))
			वापस -EFAULT;
		वापस 0;

	हाल HDLCDRVCTL_SETMODE:
		अगर (netअगर_running(dev) || !capable(CAP_NET_ADMIN))
			वापस -EACCES;
		hi->data.modename[माप(hi->data.modename)-1] = '\0';
		वापस baycom_seपंचांगode(bc, hi->data.modename);

	हाल HDLCDRVCTL_MODELIST:
		म_नकल(hi->data.modename, "par96,picpar");
		अगर (copy_to_user(अगरr->अगरr_data, hi, माप(काष्ठा hdlcdrv_ioctl)))
			वापस -EFAULT;
		वापस 0;

	हाल HDLCDRVCTL_MODEMPARMASK:
		वापस HDLCDRV_PARMASK_IOBASE;

	पूर्ण

	अगर (copy_from_user(&bi, अगरr->अगरr_data, माप(bi)))
		वापस -EFAULT;
	चयन (bi.cmd) अणु
	शेष:
		वापस -ENOIOCTLCMD;

#अगर_घोषित BAYCOM_DEBUG
	हाल BAYCOMCTL_GETDEBUG:
		bi.data.dbg.debug1 = bc->hdrv.ptt_keyed;
		bi.data.dbg.debug2 = bc->debug_vals.last_पूर्णांकcnt;
		bi.data.dbg.debug3 = bc->debug_vals.last_pllcorr;
		अवरोध;
#पूर्ण_अगर /* BAYCOM_DEBUG */

	पूर्ण
	अगर (copy_to_user(अगरr->अगरr_data, &bi, माप(bi)))
		वापस -EFAULT;
	वापस 0;

पूर्ण

/* --------------------------------------------------------------------- */

/*
 * command line settable parameters
 */
अटल अक्षर *mode[NR_PORTS] = अणु "picpar", पूर्ण;
अटल पूर्णांक iobase[NR_PORTS] = अणु 0x378, पूर्ण;

module_param_array(mode, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(mode, "baycom operating mode; eg. par96 or picpar");
module_param_hw_array(iobase, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(iobase, "baycom io base address");

MODULE_AUTHOR("Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODULE_DESCRIPTION("Baycom par96 and picpar amateur radio modem driver");
MODULE_LICENSE("GPL");

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_par_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;
	पूर्णांक len = म_माप(drv->name);

	अगर (म_भेदन(par_dev->name, drv->name, len))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver baycom_par_driver = अणु
	.name = "bcp",
	.probe = baycom_par_probe,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init init_baycompar(व्योम)
अणु
	पूर्णांक i, found = 0, ret;
	अक्षर set_hw = 1;

	prपूर्णांकk(bc_drvinfo);

	ret = parport_रेजिस्टर_driver(&baycom_par_driver);
	अगर (ret)
		वापस ret;

	/*
	 * रेजिस्टर net devices
	 */
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev;
		काष्ठा baycom_state *bc;
		अक्षर अगरname[IFNAMSIZ];

		प्र_लिखो(अगरname, "bcp%d", i);

		अगर (!mode[i])
			set_hw = 0;
		अगर (!set_hw)
			iobase[i] = 0;

		dev = hdlcdrv_रेजिस्टर(&par96_ops,
				       माप(काष्ठा baycom_state),
				       अगरname, iobase[i], 0, 0);
		अगर (IS_ERR(dev)) 
			अवरोध;

		bc = netdev_priv(dev);
		अगर (set_hw && baycom_seपंचांगode(bc, mode[i]))
			set_hw = 0;
		found++;
		baycom_device[i] = dev;
	पूर्ण

	अगर (!found) अणु
		parport_unरेजिस्टर_driver(&baycom_par_driver);
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_baycompar(व्योम)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = baycom_device[i];

		अगर (dev)
			hdlcdrv_unरेजिस्टर(dev);
	पूर्ण
	parport_unरेजिस्टर_driver(&baycom_par_driver);
पूर्ण

module_init(init_baycompar);
module_निकास(cleanup_baycompar);

/* --------------------------------------------------------------------- */

#अगर_अघोषित MODULE

/*
 * क्रमmat: baycom_par=io,mode
 * mode: par96,picpar
 */

अटल पूर्णांक __init baycom_par_setup(अक्षर *str)
अणु
        अटल अचिन्हित nr_dev;
	पूर्णांक पूर्णांकs[2];

        अगर (nr_dev >= NR_PORTS)
                वापस 0;
        str = get_options(str, 2, पूर्णांकs);
        अगर (पूर्णांकs[0] < 1)
                वापस 0;
        mode[nr_dev] = str;
        iobase[nr_dev] = पूर्णांकs[1];
	nr_dev++;
	वापस 1;
पूर्ण

__setup("baycom_par=", baycom_par_setup);

#पूर्ण_अगर /* MODULE */
/* --------------------------------------------------------------------- */
