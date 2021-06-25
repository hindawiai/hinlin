<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Framework क्रम ISA radio drivers.
 * This takes care of all the V4L2 scaffolding, allowing the ISA drivers
 * to concentrate on the actual hardware operation.
 *
 * Copyright (C) 2012 Hans Verkuil <hans.verkuil@cisco.com>
 */

#अगर_अघोषित _RADIO_ISA_H_
#घोषणा _RADIO_ISA_H_

#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

काष्ठा radio_isa_driver;
काष्ठा radio_isa_ops;

/* Core काष्ठाure क्रम radio ISA cards */
काष्ठा radio_isa_card अणु
	स्थिर काष्ठा radio_isa_driver *drv;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा video_device vdev;
	काष्ठा mutex lock;
	स्थिर काष्ठा radio_isa_ops *ops;
	काष्ठा अणु	/* mute/volume cluster */
		काष्ठा v4l2_ctrl *mute;
		काष्ठा v4l2_ctrl *volume;
	पूर्ण;
	/* I/O port */
	पूर्णांक io;

	/* Card is in stereo audio mode */
	bool stereo;
	/* Current frequency */
	u32 freq;
पूर्ण;

काष्ठा radio_isa_ops अणु
	/* Allocate and initialize a radio_isa_card काष्ठा */
	काष्ठा radio_isa_card *(*alloc)(व्योम);
	/* Probe whether a card is present at the given port */
	bool (*probe)(काष्ठा radio_isa_card *isa, पूर्णांक io);
	/* Special card initialization can be करोne here, this is called after
	 * the standard controls are रेजिस्टरed, but beक्रमe they are setup,
	 * thus allowing drivers to add their own controls here. */
	पूर्णांक (*init)(काष्ठा radio_isa_card *isa);
	/* Set mute and volume. */
	पूर्णांक (*s_mute_volume)(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक volume);
	/* Set frequency */
	पूर्णांक (*s_frequency)(काष्ठा radio_isa_card *isa, u32 freq);
	/* Set stereo/mono audio mode */
	पूर्णांक (*s_stereo)(काष्ठा radio_isa_card *isa, bool stereo);
	/* Get rxsubchans value क्रम VIDIOC_G_TUNER */
	u32 (*g_rxsubchans)(काष्ठा radio_isa_card *isa);
	/* Get the संकेत strength क्रम VIDIOC_G_TUNER */
	u32 (*g_संकेत)(काष्ठा radio_isa_card *isa);
पूर्ण;

/* Top level काष्ठाure needed to instantiate the cards */
काष्ठा radio_isa_driver अणु
	काष्ठा isa_driver driver;
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_driver pnp_driver;
#पूर्ण_अगर
	स्थिर काष्ठा radio_isa_ops *ops;
	/* The module_param_array with the specअगरied I/O ports */
	पूर्णांक *io_params;
	/* The module_param_array with the radio_nr values */
	पूर्णांक *radio_nr_params;
	/* Whether we should probe क्रम possible cards */
	bool probe;
	/* The list of possible I/O ports */
	स्थिर पूर्णांक *io_ports;
	/* The size of that list */
	पूर्णांक num_of_io_ports;
	/* The region size to request */
	अचिन्हित region_size;
	/* The name of the card */
	स्थिर अक्षर *card;
	/* Card can capture stereo audio */
	bool has_stereo;
	/* The maximum volume क्रम the volume control. If 0, then there
	   is no volume control possible. */
	पूर्णांक max_volume;
पूर्ण;

पूर्णांक radio_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev);
पूर्णांक radio_isa_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev);
व्योम radio_isa_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev);
#अगर_घोषित CONFIG_PNP
पूर्णांक radio_isa_pnp_probe(काष्ठा pnp_dev *dev,
			स्थिर काष्ठा pnp_device_id *dev_id);
व्योम radio_isa_pnp_हटाओ(काष्ठा pnp_dev *dev);
#पूर्ण_अगर

#पूर्ण_अगर
