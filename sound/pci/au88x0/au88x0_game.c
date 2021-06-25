<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Manuel Jander.
 *
 *  Based on the work of:
 *  Vojtech Pavlik
 *  Raymond Ingles
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@suse.cz>, or by paper mail:
 * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Reखुला
 *
 * Based 90% on Vojtech Pavlik pcigame driver.
 * Merged and modअगरied by Manuel Jander, क्रम the OpenVortex
 * driver. (email: mjander@embedded.cl).
 */

#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश "au88x0.h"
#समावेश <linux/gameport.h>
#समावेश <linux/export.h>

#अगर IS_REACHABLE(CONFIG_GAMEPORT)

#घोषणा VORTEX_GAME_DWAIT	20	/* 20 ms */

अटल अचिन्हित अक्षर vortex_game_पढ़ो(काष्ठा gameport *gameport)
अणु
	vortex_t *vortex = gameport_get_port_data(gameport);
	वापस hwपढ़ो(vortex->mmio, VORTEX_GAME_LEGACY);
पूर्ण

अटल व्योम vortex_game_trigger(काष्ठा gameport *gameport)
अणु
	vortex_t *vortex = gameport_get_port_data(gameport);
	hwग_लिखो(vortex->mmio, VORTEX_GAME_LEGACY, 0xff);
पूर्ण

अटल पूर्णांक
vortex_game_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	vortex_t *vortex = gameport_get_port_data(gameport);
	पूर्णांक i;

	*buttons = (~hwपढ़ो(vortex->mmio, VORTEX_GAME_LEGACY) >> 4) & 0xf;

	क्रम (i = 0; i < 4; i++) अणु
		axes[i] =
		    hwपढ़ो(vortex->mmio, VORTEX_GAME_AXIS + (i * AXIS_SIZE));
		अगर (axes[i] == AXIS_RANGE)
			axes[i] = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vortex_game_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	vortex_t *vortex = gameport_get_port_data(gameport);

	चयन (mode) अणु
	हाल GAMEPORT_MODE_COOKED:
		hwग_लिखो(vortex->mmio, VORTEX_CTRL2,
			hwपढ़ो(vortex->mmio,
			       VORTEX_CTRL2) | CTRL2_GAME_ADCMODE);
		msleep(VORTEX_GAME_DWAIT);
		वापस 0;
	हाल GAMEPORT_MODE_RAW:
		hwग_लिखो(vortex->mmio, VORTEX_CTRL2,
			hwपढ़ो(vortex->mmio,
			       VORTEX_CTRL2) & ~CTRL2_GAME_ADCMODE);
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_gameport_रेजिस्टर(vortex_t *vortex)
अणु
	काष्ठा gameport *gp;

	vortex->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(vortex->card->dev,
			"cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "AU88x0 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(vortex->pci_dev));
	gameport_set_dev_parent(gp, &vortex->pci_dev->dev);

	gp->पढ़ो = vortex_game_पढ़ो;
	gp->trigger = vortex_game_trigger;
	gp->cooked_पढ़ो = vortex_game_cooked_पढ़ो;
	gp->खोलो = vortex_game_खोलो;

	gameport_set_port_data(gp, vortex);
	gp->fuzz = 64;

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल व्योम vortex_gameport_unरेजिस्टर(vortex_t * vortex)
अणु
	अगर (vortex->gameport) अणु
		gameport_unरेजिस्टर_port(vortex->gameport);
		vortex->gameport = शून्य;
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक vortex_gameport_रेजिस्टर(vortex_t * vortex) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम vortex_gameport_unरेजिस्टर(vortex_t * vortex) अणु पूर्ण
#पूर्ण_अगर
