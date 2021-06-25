<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Standard pin control state definitions
 */

#अगर_अघोषित __LINUX_PINCTRL_PINCTRL_STATE_H
#घोषणा __LINUX_PINCTRL_PINCTRL_STATE_H

/**
 * @PINCTRL_STATE_DEFAULT: the state the pinctrl handle shall be put
 *	पूर्णांकo as शेष, usually this means the pins are up and पढ़ोy to
 *	be used by the device driver. This state is commonly used by
 *	hogs to configure muxing and pins at boot, and also as a state
 *	to go पूर्णांकo when वापसing from sleep and idle in
 *	.pm_runसमय_resume() or ordinary .resume() क्रम example.
 * @PINCTRL_STATE_INIT: normally the pinctrl will be set to "default"
 *	beक्रमe the driver's probe() function is called.  There are some
 *	drivers where that is not appropriate becausing करोing so would
 *	glitch the pins.  In those हालs you can add an "init" pinctrl
 *	which is the state of the pins beक्रमe drive probe.  After probe
 *	अगर the pins are still in "init" state they'll be moved to
 *	"default".
 * @PINCTRL_STATE_IDLE: the state the pinctrl handle shall be put पूर्णांकo
 *	when the pins are idle. This is a state where the प्रणाली is relaxed
 *	but not fully sleeping - some घातer may be on but घड़ीs gated क्रम
 *	example. Could typically be set from a pm_runसमय_suspend() or
 *	pm_runसमय_idle() operation.
 * @PINCTRL_STATE_SLEEP: the state the pinctrl handle shall be put पूर्णांकo
 *	when the pins are sleeping. This is a state where the प्रणाली is in
 *	its lowest sleep state. Could typically be set from an
 *	ordinary .suspend() function.
 */
#घोषणा PINCTRL_STATE_DEFAULT "default"
#घोषणा PINCTRL_STATE_INIT "init"
#घोषणा PINCTRL_STATE_IDLE "idle"
#घोषणा PINCTRL_STATE_SLEEP "sleep"

#पूर्ण_अगर /* __LINUX_PINCTRL_PINCTRL_STATE_H */
