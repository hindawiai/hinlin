<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/ni_routes.h
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

#अगर_अघोषित _COMEDI_DRIVERS_NI_ROUTES_H
#घोषणा _COMEDI_DRIVERS_NI_ROUTES_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#अगर_अघोषित NI_ROUTE_VALUE_EXTERNAL_CONVERSION
#समावेश <linux/bitops.h>
#पूर्ण_अगर

#समावेश "../comedi.h"

/**
 * काष्ठा ni_route_set - Set of destinations with a common source.
 * @dest: Destination of all sources in this route set.
 * @n_src: Number of sources क्रम this route set.
 * @src: List of sources that all map to the same destination.
 */
काष्ठा ni_route_set अणु
	पूर्णांक dest;
	पूर्णांक n_src;
	पूर्णांक *src;
पूर्ण;

/**
 * काष्ठा ni_device_routes - List of all src->dest sets क्रम a particular device.
 * @device: Name of board/device (e.g. pxi-6733).
 * @n_route_sets: Number of route sets that are valid क्रम this device.
 * @routes: List of route sets that are valid क्रम this device.
 */
काष्ठा ni_device_routes अणु
	स्थिर अक्षर *device;
	पूर्णांक n_route_sets;
	काष्ठा ni_route_set *routes;
पूर्ण;

/**
 * काष्ठा ni_route_tables - Register values and valid routes क्रम a device.
 * @valid_routes: Poपूर्णांकer to a all valid route sets क्रम a single device.
 * @route_values: Poपूर्णांकer to रेजिस्टर values क्रम all routes क्रम the family to
 *		  which the device beदीर्घs.
 *
 * Link to the valid src->dest routes and the रेजिस्टर values used to assign
 * such routes क्रम that particular device.
 */
काष्ठा ni_route_tables अणु
	स्थिर काष्ठा ni_device_routes *valid_routes;
	स्थिर u8 *route_values;
पूर्ण;

/*
 * ni_assign_device_routes() - Assign the proper lookup table क्रम NI संकेत
 *			       routing to the specअगरied NI device.
 *
 * Return: -ENODATA अगर assignment was not successful; 0 अगर successful.
 */
पूर्णांक ni_assign_device_routes(स्थिर अक्षर *device_family,
			    स्थिर अक्षर *board_name,
			    स्थिर अक्षर *alt_board_name,
			    काष्ठा ni_route_tables *tables);

/*
 * ni_find_route_set() - Finds the proper route set with the specअगरied
 *			 destination.
 * @destination: Destination of which to search क्रम the route set.
 * @valid_routes: Poपूर्णांकer to device routes within which to search.
 *
 * Return: शून्य अगर no route_set is found with the specअगरied @destination;
 *	otherwise, a poपूर्णांकer to the route_set अगर found.
 */
स्थिर काष्ठा ni_route_set *
ni_find_route_set(स्थिर पूर्णांक destination,
		  स्थिर काष्ठा ni_device_routes *valid_routes);

/*
 * ni_route_set_has_source() - Determines whether the given source is in
 *			       included given route_set.
 *
 * Return: true अगर found; false otherwise.
 */
bool ni_route_set_has_source(स्थिर काष्ठा ni_route_set *routes, स्थिर पूर्णांक src);

/*
 * ni_route_to_रेजिस्टर() - Validates and converts the specअगरied संकेत route
 *			    (src-->dest) to the value used at the appropriate
 *			    रेजिस्टर.
 * @src:	global-identअगरier क्रम route source
 * @dest:	global-identअगरier क्रम route destination
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 *
 * Generally speaking, most routes require the first six bits and a few require
 * 7 bits.  Special handling is given क्रम the वापस value when the route is to
 * be handled by the RTSI sub-device.  In this हाल, the वापसed रेजिस्टर may
 * not be sufficient to define the entire route path, but rather may only
 * indicate the पूर्णांकermediate route.  For example, अगर the route must go through
 * the RGOUT0 pin, the (src->RGOUT0) रेजिस्टर value will be वापसed.
 * Similarly, अगर the route must go through the NI_RTSI_BRD lines, the BIT(6)
 * will be set:
 *
 * अगर route करोes not need RTSI_BRD lines:
 *   bits 0:7 : रेजिस्टर value
 *              क्रम a route that must go through RGOUT0 pin, this will be equal
 *              to the (src->RGOUT0) रेजिस्टर value.
 * अन्यथा: * route is (src->RTSI_BRD(x), RTSI_BRD(x)->TRIGGER_LINE(i)) *
 *   bits 0:5 : zero
 *   bits 6   : set to 1
 *   bits 7:7 : zero
 *
 * Return: रेजिस्टर value to be used क्रम source at destination with special
 *	हालs given above; Otherwise, -1 अगर the specअगरied route is not valid क्रम
 *	this particular device.
 */
s8 ni_route_to_रेजिस्टर(स्थिर पूर्णांक src, स्थिर पूर्णांक dest,
			स्थिर काष्ठा ni_route_tables *tables);

अटल अंतरभूत bool ni_rtsi_route_requires_mux(s8 value)
अणु
	वापस value & BIT(6);
पूर्ण

/*
 * ni_lookup_route_रेजिस्टर() - Look up a रेजिस्टर value क्रम a particular route
 *				without checking whether the route is valid क्रम
 *				the particular device.
 * @src:	global-identअगरier क्रम route source
 * @dest:	global-identअगरier क्रम route destination
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 *
 * Return: -EINVAL अगर the specअगरied route is not valid क्रम this device family.
 */
s8 ni_lookup_route_रेजिस्टर(पूर्णांक src, पूर्णांक dest,
			    स्थिर काष्ठा ni_route_tables *tables);

/**
 * route_is_valid() - Determines whether the specअगरied संकेत route (src-->dest)
 *		      is valid क्रम the given NI comedi_device.
 * @src:	global-identअगरier क्रम route source
 * @dest:	global-identअगरier क्रम route destination
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 *
 * Return: True अगर the route is valid, otherwise false.
 */
अटल अंतरभूत bool route_is_valid(स्थिर पूर्णांक src, स्थिर पूर्णांक dest,
				  स्थिर काष्ठा ni_route_tables *tables)
अणु
	वापस ni_route_to_रेजिस्टर(src, dest, tables) >= 0;
पूर्ण

/*
 * ni_is_cmd_dest() - Determine whether the given destination is only
 *		      configurable via a comedi_cmd काष्ठा.
 * @dest: Destination to test.
 */
bool ni_is_cmd_dest(पूर्णांक dest);

अटल अंतरभूत bool channel_is_pfi(पूर्णांक channel)
अणु
	वापस NI_PFI(0) <= channel && channel <= NI_PFI(-1);
पूर्ण

अटल अंतरभूत bool channel_is_rtsi(पूर्णांक channel)
अणु
	वापस TRIGGER_LINE(0) <= channel && channel <= TRIGGER_LINE(-1);
पूर्ण

अटल अंतरभूत bool channel_is_ctr(पूर्णांक channel)
अणु
	वापस channel >= NI_COUNTER_NAMES_BASE &&
	       channel <= NI_COUNTER_NAMES_MAX;
पूर्ण

/*
 * ni_count_valid_routes() - Count the number of valid routes.
 * @tables: Routing tables क्रम which to count all valid routes.
 */
अचिन्हित पूर्णांक ni_count_valid_routes(स्थिर काष्ठा ni_route_tables *tables);

/*
 * ni_get_valid_routes() - Implements INSN_DEVICE_CONFIG_GET_ROUTES.
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 * @n_pairs:	Number of pairs क्रम which memory is allocated by the user.  If
 *		the user specअगरies '0', only the number of available pairs is
 *		वापसed.
 * @pair_data:	Poपूर्णांकer to memory allocated to वापस pairs back to user.  Each
 *		even, odd indexed member of this array will hold source,
 *		destination of a route pair respectively.
 *
 * Return: the number of valid routes अगर n_pairs == 0; otherwise, the number of
 *	valid routes copied.
 */
अचिन्हित पूर्णांक ni_get_valid_routes(स्थिर काष्ठा ni_route_tables *tables,
				 अचिन्हित पूर्णांक n_pairs,
				 अचिन्हित पूर्णांक *pair_data);

/*
 * ni_sort_device_routes() - Sort the list of valid device संकेत routes in
 *			     preparation क्रम use.
 * @valid_routes:	poपूर्णांकer to ni_device_routes काष्ठा to sort.
 */
व्योम ni_sort_device_routes(काष्ठा ni_device_routes *valid_routes);

/*
 * ni_find_route_source() - Finds the संकेत source corresponding to a संकेत
 *			    route (src-->dest) of the specअगरied routing रेजिस्टर
 *			    value and the specअगरied route destination on the
 *			    specअगरied device.
 *
 * Note that this function करोes _not_ validate the source based on device
 * routes.
 *
 * Return: The NI संकेत value (e.g. NI_PFI(0) or PXI_Clk10) अगर found.
 *	If the source was not found (i.e. the रेजिस्टर value is not
 *	valid क्रम any routes to the destination), -EINVAL is वापसed.
 */
पूर्णांक ni_find_route_source(स्थिर u8 src_sel_reg_value, स्थिर पूर्णांक dest,
			 स्थिर काष्ठा ni_route_tables *tables);

/**
 * route_रेजिस्टर_is_valid() - Determines whether the रेजिस्टर value क्रम the
 *			       specअगरied route destination on the specअगरied
 *			       device is valid.
 */
अटल अंतरभूत bool route_रेजिस्टर_is_valid(स्थिर u8 src_sel_reg_value,
					   स्थिर पूर्णांक dest,
					   स्थिर काष्ठा ni_route_tables *tables)
अणु
	वापस ni_find_route_source(src_sel_reg_value, dest, tables) >= 0;
पूर्ण

/**
 * ni_get_reg_value_roffs() - Determines the proper रेजिस्टर value क्रम a
 *			      particular valid NI संकेत/terminal route.
 * @src:	Either a direct रेजिस्टर value or one of NI_* संकेत names.
 * @dest:	global-identअगरier क्रम route destination
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 * @direct_reg_offset:
 *		Compatibility compensation argument.  This argument allows us to
 *		arbitrarily apply an offset to src अगर src is a direct रेजिस्टर
 *		value reference.  This is necessary to be compatible with
 *		definitions of रेजिस्टर values as previously exported directly
 *		to user space.
 *
 * Return: the रेजिस्टर value (>0) to be used at the destination अगर the src is
 *	valid क्रम the given destination; -1 otherwise.
 */
अटल अंतरभूत s8 ni_get_reg_value_roffs(पूर्णांक src, स्थिर पूर्णांक dest,
					स्थिर काष्ठा ni_route_tables *tables,
					स्थिर पूर्णांक direct_reg_offset)
अणु
	अगर (src < NI_NAMES_BASE) अणु
		src += direct_reg_offset;
		/*
		 * In this हाल, the src is expected to actually be a रेजिस्टर
		 * value.
		 */
		अगर (route_रेजिस्टर_is_valid(src, dest, tables))
			वापस src;
		वापस -1;
	पूर्ण

	/*
	 * Otherwise, the src is expected to be one of the असलtracted NI
	 * संकेत/terminal names.
	 */
	वापस ni_route_to_रेजिस्टर(src, dest, tables);
पूर्ण

अटल अंतरभूत पूर्णांक ni_get_reg_value(स्थिर पूर्णांक src, स्थिर पूर्णांक dest,
				   स्थिर काष्ठा ni_route_tables *tables)
अणु
	वापस ni_get_reg_value_roffs(src, dest, tables, 0);
पूर्ण

/**
 * ni_check_trigger_arg_roffs() - Checks the trigger argument (*_arg) of an NI
 *				  device to ensure that the *_arg value
 *				  corresponds to _either_ a valid रेजिस्टर value
 *				  to define a trigger source, _or_ a valid NI
 *				  संकेत/terminal name that has a valid route to
 *				  the destination on the particular device.
 * @src:	Either a direct रेजिस्टर value or one of NI_* संकेत names.
 * @dest:	global-identअगरier क्रम route destination
 * @tables:	poपूर्णांकer to relevant set of routing tables.
 * @direct_reg_offset:
 *		Compatibility compensation argument.  This argument allows us to
 *		arbitrarily apply an offset to src अगर src is a direct रेजिस्टर
 *		value reference.  This is necessary to be compatible with
 *		definitions of रेजिस्टर values as previously exported directly
 *		to user space.
 *
 * Return: 0 अगर the src (either रेजिस्टर value or NI संकेत/terminal name) is
 *	valid क्रम the destination; -EINVAL otherwise.
 */
अटल अंतरभूत
पूर्णांक ni_check_trigger_arg_roffs(पूर्णांक src, स्थिर पूर्णांक dest,
			       स्थिर काष्ठा ni_route_tables *tables,
			       स्थिर पूर्णांक direct_reg_offset)
अणु
	अगर (ni_get_reg_value_roffs(src, dest, tables, direct_reg_offset) < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ni_check_trigger_arg(स्थिर पूर्णांक src, स्थिर पूर्णांक dest,
				       स्थिर काष्ठा ni_route_tables *tables)
अणु
	वापस ni_check_trigger_arg_roffs(src, dest, tables, 0);
पूर्ण

#पूर्ण_अगर /* _COMEDI_DRIVERS_NI_ROUTES_H */
