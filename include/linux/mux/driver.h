<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mux/driver.h - definitions क्रम the multiplexer driver पूर्णांकerface
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#अगर_अघोषित _LINUX_MUX_DRIVER_H
#घोषणा _LINUX_MUX_DRIVER_H

#समावेश <dt-bindings/mux/mux.h>
#समावेश <linux/device.h>
#समावेश <linux/semaphore.h>

काष्ठा mux_chip;
काष्ठा mux_control;

/**
 * काष्ठा mux_control_ops -	Mux controller operations क्रम a mux chip.
 * @set:			Set the state of the given mux controller.
 */
काष्ठा mux_control_ops अणु
	पूर्णांक (*set)(काष्ठा mux_control *mux, पूर्णांक state);
पूर्ण;

/**
 * काष्ठा mux_control -	Represents a mux controller.
 * @lock:		Protects the mux controller state.
 * @chip:		The mux chip that is handling this mux controller.
 * @cached_state:	The current mux controller state, or -1 अगर none.
 * @states:		The number of mux controller states.
 * @idle_state:		The mux controller state to use when inactive, or one
 *			of MUX_IDLE_AS_IS and MUX_IDLE_DISCONNECT.
 *
 * Mux drivers may only change @states and @idle_state, and may only करो so
 * between allocation and registration of the mux controller. Specअगरically,
 * @cached_state is पूर्णांकernal to the mux core and should never be written by
 * mux drivers.
 */
काष्ठा mux_control अणु
	काष्ठा semaphore lock; /* protects the state of the mux */

	काष्ठा mux_chip *chip;
	पूर्णांक cached_state;

	अचिन्हित पूर्णांक states;
	पूर्णांक idle_state;
पूर्ण;

/**
 * काष्ठा mux_chip -	Represents a chip holding mux controllers.
 * @controllers:	Number of mux controllers handled by the chip.
 * @mux:		Array of mux controllers that are handled.
 * @dev:		Device काष्ठाure.
 * @id:			Used to identअगरy the device पूर्णांकernally.
 * @ops:		Mux controller operations.
 */
काष्ठा mux_chip अणु
	अचिन्हित पूर्णांक controllers;
	काष्ठा mux_control *mux;
	काष्ठा device dev;
	पूर्णांक id;

	स्थिर काष्ठा mux_control_ops *ops;
पूर्ण;

#घोषणा to_mux_chip(x) container_of((x), काष्ठा mux_chip, dev)

/**
 * mux_chip_priv() - Get the extra memory reserved by mux_chip_alloc().
 * @mux_chip: The mux-chip to get the निजी memory from.
 *
 * Return: Poपूर्णांकer to the निजी memory reserved by the allocator.
 */
अटल अंतरभूत व्योम *mux_chip_priv(काष्ठा mux_chip *mux_chip)
अणु
	वापस &mux_chip->mux[mux_chip->controllers];
पूर्ण

काष्ठा mux_chip *mux_chip_alloc(काष्ठा device *dev,
				अचिन्हित पूर्णांक controllers, माप_प्रकार माप_priv);
पूर्णांक mux_chip_रेजिस्टर(काष्ठा mux_chip *mux_chip);
व्योम mux_chip_unरेजिस्टर(काष्ठा mux_chip *mux_chip);
व्योम mux_chip_मुक्त(काष्ठा mux_chip *mux_chip);

काष्ठा mux_chip *devm_mux_chip_alloc(काष्ठा device *dev,
				     अचिन्हित पूर्णांक controllers,
				     माप_प्रकार माप_priv);
पूर्णांक devm_mux_chip_रेजिस्टर(काष्ठा device *dev, काष्ठा mux_chip *mux_chip);

/**
 * mux_control_get_index() - Get the index of the given mux controller
 * @mux: The mux-control to get the index क्रम.
 *
 * Return: The index of the mux controller within the mux chip the mux
 * controller is a part of.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mux_control_get_index(काष्ठा mux_control *mux)
अणु
	वापस mux - mux->chip->mux;
पूर्ण

#पूर्ण_अगर /* _LINUX_MUX_DRIVER_H */
