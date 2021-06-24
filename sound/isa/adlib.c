<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AdLib FM card driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/isa.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/opl3.h>

#घोषणा CRD_NAME "AdLib FM"
#घोषणा DEV_NAME "adlib"

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Rene Herman");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CRD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CRD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CRD_NAME " soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " CRD_NAME " driver.");

अटल पूर्णांक snd_adlib_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	अगर (!enable[n])
		वापस 0;

	अगर (port[n] == SNDRV_AUTO_PORT) अणु
		dev_err(dev, "please specify port\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम snd_adlib_मुक्त(काष्ठा snd_card *card)
अणु
	release_and_मुक्त_resource(card->निजी_data);
पूर्ण

अटल पूर्णांक snd_adlib_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक error;

	error = snd_card_new(dev, index[n], id[n], THIS_MODULE, 0, &card);
	अगर (error < 0) अणु
		dev_err(dev, "could not create card\n");
		वापस error;
	पूर्ण

	card->निजी_data = request_region(port[n], 4, CRD_NAME);
	अगर (!card->निजी_data) अणु
		dev_err(dev, "could not grab ports\n");
		error = -EBUSY;
		जाओ out;
	पूर्ण
	card->निजी_मुक्त = snd_adlib_मुक्त;

	म_नकल(card->driver, DEV_NAME);
	म_नकल(card->लघुname, CRD_NAME);
	प्र_लिखो(card->दीर्घname, CRD_NAME " at %#lx", port[n]);

	error = snd_opl3_create(card, port[n], port[n] + 2, OPL3_HW_AUTO, 1, &opl3);
	अगर (error < 0) अणु
		dev_err(dev, "could not create OPL\n");
		जाओ out;
	पूर्ण

	error = snd_opl3_hwdep_new(opl3, 0, 0, शून्य);
	अगर (error < 0) अणु
		dev_err(dev, "could not create FM\n");
		जाओ out;
	पूर्ण

	error = snd_card_रेजिस्टर(card);
	अगर (error < 0) अणु
		dev_err(dev, "could not register card\n");
		जाओ out;
	पूर्ण

	dev_set_drvdata(dev, card);
	वापस 0;

out:	snd_card_मुक्त(card);
	वापस error;
पूर्ण

अटल व्योम snd_adlib_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा isa_driver snd_adlib_driver = अणु
	.match		= snd_adlib_match,
	.probe		= snd_adlib_probe,
	.हटाओ		= snd_adlib_हटाओ,

	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

module_isa_driver(snd_adlib_driver, SNDRV_CARDS);
