<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/ni_routing/ni_route_values.h
 *  Route inक्रमmation क्रम NI boards.
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2016 Spencer E. Olson <olsonse@umich.edu>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 */

#अगर_अघोषित _COMEDI_DRIVERS_NI_ROUTINT_NI_ROUTE_VALUES_H
#घोषणा _COMEDI_DRIVERS_NI_ROUTINT_NI_ROUTE_VALUES_H

#समावेश "../../comedi.h"
#समावेश <linux/types.h>

/*
 * This file includes the tables that are a list of all the values of various
 * संकेतs routes available on NI hardware.  In many हालs, one करोes not
 * explicitly make these routes, rather one might indicate that something is
 * used as the source of one particular trigger or another (using
 * *_src=TRIG_EXT).
 *
 * This file is meant to be included by comedi/drivers/ni_routes.c
 */

#घोषणा B(x)	((x) - NI_NAMES_BASE)

/** Marks a रेजिस्टर value as valid, implemented, and tested. */
#घोषणा V(x)	(((x) & 0x7f) | 0x80)

#अगर_अघोषित NI_ROUTE_VALUE_EXTERNAL_CONVERSION
	/** Marks a रेजिस्टर value as implemented but needing testing. */
	#घोषणा I(x)	V(x)
	/** Marks a रेजिस्टर value as not implemented. */
	#घोषणा U(x)	0x0

	प्रकार u8 रेजिस्टर_type;
#अन्यथा
	/** Marks a रेजिस्टर value as implemented but needing testing. */
	#घोषणा I(x)	(((x) & 0x7f) | 0x100)
	/** Marks a रेजिस्टर value as not implemented. */
	#घोषणा U(x)	(((x) & 0x7f) | 0x200)

	/** Tests whether a रेजिस्टर is marked as valid/implemented/tested */
	#घोषणा MARKED_V(x)	(((x) & 0x80) != 0)
	/** Tests whether a रेजिस्टर is implemented but not tested */
	#घोषणा MARKED_I(x)	(((x) & 0x100) != 0)
	/** Tests whether a रेजिस्टर is not implemented */
	#घोषणा MARKED_U(x)	(((x) & 0x200) != 0)

	/* need more space to store extra marks */
	प्रकार u16 रेजिस्टर_type;
#पूर्ण_अगर

/* Mask out the marking bit(s). */
#घोषणा UNMARK(x)	((x) & 0x7f)

/*
 * Gi_SRC(x,1) implements Gi_Src_SubSelect = 1
 *
 * This appears to only really be a valid MUX क्रम m-series devices.
 */
#घोषणा Gi_SRC(val, subsel)	((val) | ((subsel) << 6))

/**
 * काष्ठा family_route_values - Register values क्रम all routes क्रम a particular
 *				family.
 * @family: lower-हाल string representation of a specअगरic series or family of
 *	    devices from National Instruments where each member of this family
 *	    shares the same रेजिस्टर values क्रम the various संकेत MUXes.  It
 *	    should be noted that not all devices of any family have access to
 *	    all routes defined.
 * @रेजिस्टर_values: Table of all रेजिस्टर values क्रम various संकेत MUXes on
 *	    National Instruments devices.  The first index of this table is the
 *	    संकेत destination (i.e. identअगरication of the संकेत MUX).  The
 *	    second index of this table is the संकेत source (i.e. input of the
 *	    संकेत MUX).
 */
काष्ठा family_route_values अणु
	स्थिर अक्षर *family;
	स्थिर रेजिस्टर_type रेजिस्टर_values[NI_NUM_NAMES][NI_NUM_NAMES];

पूर्ण;

बाह्य स्थिर काष्ठा family_route_values *स्थिर ni_all_route_values[];

#पूर्ण_अगर /* _COMEDI_DRIVERS_NI_ROUTINT_NI_ROUTE_VALUES_H */
