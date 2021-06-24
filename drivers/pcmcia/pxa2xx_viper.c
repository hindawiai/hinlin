<शैली गुरु>
/*
 * Viper/Zeus PCMCIA support
 *   Copyright 2004 Arcom Control Systems
 *
 * Maपूर्णांकained by Marc Zyngier <maz@misterjones.org>
 *
 * Based on:
 *   iPAQ h2200 PCMCIA support
 *   Copyright 2004 Koen Kooi <koen@vestingbar.nl>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/irq.h>

#समावेश <linux/platक्रमm_data/pcmcia-pxa2xx_viper.h>

#समावेश "soc_common.h"
#समावेश "pxa2xx_base.h"

अटल काष्ठा platक्रमm_device *arcom_pcmcia_dev;

अटल अंतरभूत काष्ठा arcom_pcmcia_pdata *viper_get_pdata(व्योम)
अणु
	वापस arcom_pcmcia_dev->dev.platक्रमm_data;
पूर्ण

अटल पूर्णांक viper_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा arcom_pcmcia_pdata *pdata = viper_get_pdata();
	अचिन्हित दीर्घ flags;

	skt->stat[SOC_STAT_CD].gpio = pdata->cd_gpio;
	skt->stat[SOC_STAT_CD].name = "PCMCIA_CD";
	skt->stat[SOC_STAT_RDY].gpio = pdata->rdy_gpio;
	skt->stat[SOC_STAT_RDY].name = "CF ready";

	अगर (gpio_request(pdata->pwr_gpio, "CF power"))
		जाओ err_request_pwr;

	local_irq_save(flags);

	अगर (gpio_direction_output(pdata->pwr_gpio, 0)) अणु
		local_irq_restore(flags);
		जाओ err_dir;
	पूर्ण

	local_irq_restore(flags);

	वापस 0;

err_dir:
	gpio_मुक्त(pdata->pwr_gpio);
err_request_pwr:
	dev_err(&arcom_pcmcia_dev->dev, "Failed to setup PCMCIA GPIOs\n");
	वापस -1;
पूर्ण

/*
 * Release all resources.
 */
अटल व्योम viper_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा arcom_pcmcia_pdata *pdata = viper_get_pdata();

	gpio_मुक्त(pdata->pwr_gpio);
पूर्ण

अटल व्योम viper_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt,
				      काष्ठा pcmcia_state *state)
अणु
	state->vs_3v  = 1; /* Can only apply 3.3V */
	state->vs_Xv  = 0;
पूर्ण

अटल पूर्णांक viper_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
					 स्थिर socket_state_t *state)
अणु
	काष्ठा arcom_pcmcia_pdata *pdata = viper_get_pdata();

	/* Silently ignore Vpp, output enable, speaker enable. */
	pdata->reset(state->flags & SS_RESET);

	/* Apply socket voltage */
	चयन (state->Vcc) अणु
	हाल 0:
		gpio_set_value(pdata->pwr_gpio, 0);
		अवरोध;
	हाल 33:
		gpio_set_value(pdata->pwr_gpio, 1);
		अवरोध;
	शेष:
		dev_err(&arcom_pcmcia_dev->dev, "Unsupported Vcc:%d\n", state->Vcc);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pcmcia_low_level viper_pcmcia_ops = अणु
	.owner          	= THIS_MODULE,
	.hw_init        	= viper_pcmcia_hw_init,
	.hw_shutकरोwn		= viper_pcmcia_hw_shutकरोwn,
	.socket_state		= viper_pcmcia_socket_state,
	.configure_socket	= viper_pcmcia_configure_socket,
	.nr         		= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *viper_pcmcia_device;

अटल पूर्णांक viper_pcmcia_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	/* I can't imagine more than one device, but you never know... */
	अगर (arcom_pcmcia_dev)
		वापस -EEXIST;

	अगर (!pdev->dev.platक्रमm_data)
		वापस -EINVAL;

	viper_pcmcia_device = platक्रमm_device_alloc("pxa2xx-pcmcia", -1);
	अगर (!viper_pcmcia_device)
		वापस -ENOMEM;

	arcom_pcmcia_dev = pdev;

	viper_pcmcia_device->dev.parent = &pdev->dev;

	ret = platक्रमm_device_add_data(viper_pcmcia_device,
				       &viper_pcmcia_ops,
				       माप(viper_pcmcia_ops));

	अगर (!ret)
		ret = platक्रमm_device_add(viper_pcmcia_device);

	अगर (ret) अणु
		platक्रमm_device_put(viper_pcmcia_device);
		arcom_pcmcia_dev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक viper_pcmcia_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_unरेजिस्टर(viper_pcmcia_device);
	arcom_pcmcia_dev = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device_id viper_pcmcia_id_table[] = अणु
	अणु .name = "viper-pcmcia", पूर्ण,
	अणु .name = "zeus-pcmcia",  पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver viper_pcmcia_driver = अणु
	.probe		= viper_pcmcia_probe,
	.हटाओ		= viper_pcmcia_हटाओ,
	.driver		= अणु
		.name	= "arcom-pcmcia",
	पूर्ण,
	.id_table	= viper_pcmcia_id_table,
पूर्ण;

module_platक्रमm_driver(viper_pcmcia_driver);

MODULE_DEVICE_TABLE(platक्रमm, viper_pcmcia_id_table);
MODULE_LICENSE("GPL");
