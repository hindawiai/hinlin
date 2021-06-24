<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/ni_routes.c
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

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/sort.h>

#समावेश "../comedi.h"

#समावेश "ni_routes.h"
#समावेश "ni_routing/ni_route_values.h"
#समावेश "ni_routing/ni_device_routes.h"

/*
 * This is defined in ni_routing/ni_route_values.h:
 * #घोषणा B(x)	((x) - NI_NAMES_BASE)
 */

/*
 * These are defined in ni_routing/ni_route_values.h to identअगरy clearly
 * elements of the table that were set.  In other words, entries that are zero
 * are invalid.  To get the value to use क्रम the रेजिस्टर, one must mask out the
 * high bit.
 *
 * #घोषणा V(x)	((x) | 0x80)
 *
 * #घोषणा UNMARK(x)	((x) & (~(0x80)))
 *
 */

/* Helper क्रम accessing data. */
#घोषणा RVi(table, src, dest)	((table)[(dest) * NI_NUM_NAMES + (src)])

/*
 * Find the route values क्रम a device family.
 */
अटल स्थिर u8 *ni_find_route_values(स्थिर अक्षर *device_family)
अणु
	स्थिर u8 *rv = शून्य;
	पूर्णांक i;

	क्रम (i = 0; ni_all_route_values[i]; ++i) अणु
		अगर (स_भेद(ni_all_route_values[i]->family, device_family,
			   strnlen(device_family, 30)) == 0) अणु
			rv = &ni_all_route_values[i]->रेजिस्टर_values[0][0];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Find the valid routes क्रम a board.
 */
अटल स्थिर काष्ठा ni_device_routes *
ni_find_valid_routes(स्थिर अक्षर *board_name)
अणु
	स्थिर काष्ठा ni_device_routes *dr = शून्य;
	पूर्णांक i;

	क्रम (i = 0; ni_device_routes_list[i]; ++i) अणु
		अगर (स_भेद(ni_device_routes_list[i]->device, board_name,
			   strnlen(board_name, 30)) == 0) अणु
			dr = ni_device_routes_list[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस dr;
पूर्ण

/*
 * Find the proper route_values and ni_device_routes tables क्रम this particular
 * device.  Possibly try an alternate board name अगर device routes not found
 * क्रम the actual board name.
 *
 * Return: -ENODATA अगर either was not found; 0 अगर both were found.
 */
अटल पूर्णांक ni_find_device_routes(स्थिर अक्षर *device_family,
				 स्थिर अक्षर *board_name,
				 स्थिर अक्षर *alt_board_name,
				 काष्ठा ni_route_tables *tables)
अणु
	स्थिर काष्ठा ni_device_routes *dr;
	स्थिर u8 *rv;

	/* First, find the रेजिस्टर_values table क्रम this device family */
	rv = ni_find_route_values(device_family);

	/* Second, find the set of routes valid क्रम this device. */
	dr = ni_find_valid_routes(board_name);
	अगर (!dr && alt_board_name)
		dr = ni_find_valid_routes(alt_board_name);

	tables->route_values = rv;
	tables->valid_routes = dr;

	अगर (!rv || !dr)
		वापस -ENODATA;

	वापस 0;
पूर्ण

/**
 * ni_assign_device_routes() - Assign the proper lookup table क्रम NI संकेत
 *			       routing to the specअगरied NI device.
 * @device_family: Device family name (determines route values).
 * @board_name: Board name (determines set of routes).
 * @alt_board_name: Optional alternate board name to try on failure.
 * @tables: Poपूर्णांकer to asचिन्हित routing inक्रमmation.
 *
 * Finds the route values क्रम the device family and the set of valid routes
 * क्रम the board.  If valid routes could not be found क्रम the actual board
 * name and an alternate board name has been specअगरied, try that one.
 *
 * On failure, the asचिन्हित routing inक्रमmation may be partially filled
 * (क्रम example, with the route values but not the set of valid routes).
 *
 * Return: -ENODATA अगर assignment was not successful; 0 अगर successful.
 */
पूर्णांक ni_assign_device_routes(स्थिर अक्षर *device_family,
			    स्थिर अक्षर *board_name,
			    स्थिर अक्षर *alt_board_name,
			    काष्ठा ni_route_tables *tables)
अणु
	स_रखो(tables, 0, माप(काष्ठा ni_route_tables));
	वापस ni_find_device_routes(device_family, board_name, alt_board_name,
				     tables);
पूर्ण
EXPORT_SYMBOL_GPL(ni_assign_device_routes);

/**
 * ni_count_valid_routes() - Count the number of valid routes.
 * @tables: Routing tables क्रम which to count all valid routes.
 */
अचिन्हित पूर्णांक ni_count_valid_routes(स्थिर काष्ठा ni_route_tables *tables)
अणु
	पूर्णांक total = 0;
	पूर्णांक i;

	क्रम (i = 0; i < tables->valid_routes->n_route_sets; ++i) अणु
		स्थिर काष्ठा ni_route_set *R = &tables->valid_routes->routes[i];
		पूर्णांक j;

		क्रम (j = 0; j < R->n_src; ++j) अणु
			स्थिर पूर्णांक src  = R->src[j];
			स्थिर पूर्णांक dest = R->dest;
			स्थिर u8 *rv = tables->route_values;

			अगर (RVi(rv, B(src), B(dest)))
				/* direct routing is valid */
				++total;
			अन्यथा अगर (channel_is_rtsi(dest) &&
				 (RVi(rv, B(src), B(NI_RGOUT0)) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(0))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(1))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(2))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(3))))) अणु
				++total;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस total;
पूर्ण
EXPORT_SYMBOL_GPL(ni_count_valid_routes);

/**
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
				 अचिन्हित पूर्णांक *pair_data)
अणु
	अचिन्हित पूर्णांक n_valid = ni_count_valid_routes(tables);
	पूर्णांक i;

	अगर (n_pairs == 0 || n_valid == 0)
		वापस n_valid;

	अगर (!pair_data)
		वापस 0;

	n_valid = 0;

	क्रम (i = 0; i < tables->valid_routes->n_route_sets; ++i) अणु
		स्थिर काष्ठा ni_route_set *R = &tables->valid_routes->routes[i];
		पूर्णांक j;

		क्रम (j = 0; j < R->n_src; ++j) अणु
			स्थिर पूर्णांक src  = R->src[j];
			स्थिर पूर्णांक dest = R->dest;
			bool valid = false;
			स्थिर u8 *rv = tables->route_values;

			अगर (RVi(rv, B(src), B(dest)))
				/* direct routing is valid */
				valid = true;
			अन्यथा अगर (channel_is_rtsi(dest) &&
				 (RVi(rv, B(src), B(NI_RGOUT0)) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(0))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(1))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(2))) ||
				  RVi(rv, B(src), B(NI_RTSI_BRD(3))))) अणु
				/* indirect routing also valid */
				valid = true;
			पूर्ण

			अगर (valid) अणु
				pair_data[2 * n_valid] = src;
				pair_data[2 * n_valid + 1] = dest;
				++n_valid;
			पूर्ण

			अगर (n_valid >= n_pairs)
				वापस n_valid;
		पूर्ण
	पूर्ण
	वापस n_valid;
पूर्ण
EXPORT_SYMBOL_GPL(ni_get_valid_routes);

/**
 * List of NI global संकेत names that, as destinations, are only routeable
 * indirectly through the *_arg elements of the comedi_cmd काष्ठाure.
 */
अटल स्थिर पूर्णांक NI_CMD_DESTS[] = अणु
	NI_AI_SampleClock,
	NI_AI_StartTrigger,
	NI_AI_ConvertClock,
	NI_AO_SampleClock,
	NI_AO_StartTrigger,
	NI_DI_SampleClock,
	NI_DO_SampleClock,
पूर्ण;

/**
 * ni_is_cmd_dest() - Determine whether the given destination is only
 *		      configurable via a comedi_cmd काष्ठा.
 * @dest: Destination to test.
 */
bool ni_is_cmd_dest(पूर्णांक dest)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(NI_CMD_DESTS); ++i)
		अगर (NI_CMD_DESTS[i] == dest)
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(ni_is_cmd_dest);

/* **** BEGIN Routes sort routines **** */
अटल पूर्णांक _ni_sort_destcmp(स्थिर व्योम *va, स्थिर व्योम *vb)
अणु
	स्थिर काष्ठा ni_route_set *a = va;
	स्थिर काष्ठा ni_route_set *b = vb;

	अगर (a->dest < b->dest)
		वापस -1;
	अन्यथा अगर (a->dest > b->dest)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक _ni_sort_srccmp(स्थिर व्योम *vsrc0, स्थिर व्योम *vsrc1)
अणु
	स्थिर पूर्णांक *src0 = vsrc0;
	स्थिर पूर्णांक *src1 = vsrc1;

	अगर (*src0 < *src1)
		वापस -1;
	अन्यथा अगर (*src0 > *src1)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ni_sort_device_routes() - Sort the list of valid device संकेत routes in
 *			     preparation क्रम use.
 * @valid_routes:	poपूर्णांकer to ni_device_routes काष्ठा to sort.
 */
व्योम ni_sort_device_routes(काष्ठा ni_device_routes *valid_routes)
अणु
	अचिन्हित पूर्णांक n;

	/* 1. Count and set the number of ni_route_set objects. */
	valid_routes->n_route_sets = 0;
	जबतक (valid_routes->routes[valid_routes->n_route_sets].dest != 0)
		++valid_routes->n_route_sets;

	/* 2. sort all ni_route_set objects by destination. */
	sort(valid_routes->routes, valid_routes->n_route_sets,
	     माप(काष्ठा ni_route_set), _ni_sort_destcmp, शून्य);

	/* 3. Loop through each route_set क्रम sorting. */
	क्रम (n = 0; n < valid_routes->n_route_sets; ++n) अणु
		काष्ठा ni_route_set *rs = &valid_routes->routes[n];

		/* 3a. Count and set the number of sources. */
		rs->n_src = 0;
		जबतक (rs->src[rs->n_src])
			++rs->n_src;

		/* 3a. Sort sources. */
		sort(valid_routes->routes[n].src, valid_routes->routes[n].n_src,
		     माप(पूर्णांक), _ni_sort_srccmp, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ni_sort_device_routes);

/* sort all valid device संकेत routes in prep क्रम use */
अटल व्योम ni_sort_all_device_routes(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; ni_device_routes_list[i]; ++i)
		ni_sort_device_routes(ni_device_routes_list[i]);
पूर्ण

/* **** BEGIN Routes search routines **** */
अटल पूर्णांक _ni_द्वा_खोज_destcmp(स्थिर व्योम *vkey, स्थिर व्योम *velt)
अणु
	स्थिर पूर्णांक *key = vkey;
	स्थिर काष्ठा ni_route_set *elt = velt;

	अगर (*key < elt->dest)
		वापस -1;
	अन्यथा अगर (*key > elt->dest)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक _ni_द्वा_खोज_srccmp(स्थिर व्योम *vkey, स्थिर व्योम *velt)
अणु
	स्थिर पूर्णांक *key = vkey;
	स्थिर पूर्णांक *elt = velt;

	अगर (*key < *elt)
		वापस -1;
	अन्यथा अगर (*key > *elt)
		वापस 1;
	वापस 0;
पूर्ण

/**
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
		  स्थिर काष्ठा ni_device_routes *valid_routes)
अणु
	वापस द्वा_खोज(&destination, valid_routes->routes,
		       valid_routes->n_route_sets, माप(काष्ठा ni_route_set),
		       _ni_द्वा_खोज_destcmp);
पूर्ण
EXPORT_SYMBOL_GPL(ni_find_route_set);

/**
 * ni_route_set_has_source() - Determines whether the given source is in
 *			       included given route_set.
 *
 * Return: true अगर found; false otherwise.
 */
bool ni_route_set_has_source(स्थिर काष्ठा ni_route_set *routes,
			     स्थिर पूर्णांक source)
अणु
	अगर (!द्वा_खोज(&source, routes->src, routes->n_src, माप(पूर्णांक),
		     _ni_द्वा_खोज_srccmp))
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ni_route_set_has_source);

/**
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
			    स्थिर काष्ठा ni_route_tables *tables)
अणु
	s8 regval;

	/*
	 * Be sure to use the B() macro to subtract off the NI_NAMES_BASE beक्रमe
	 * indexing पूर्णांकo the route_values array.
	 */
	src = B(src);
	dest = B(dest);
	अगर (src < 0 || src >= NI_NUM_NAMES || dest < 0 || dest >= NI_NUM_NAMES)
		वापस -EINVAL;
	regval = RVi(tables->route_values, src, dest);
	अगर (!regval)
		वापस -EINVAL;
	/* mask out the valid-value marking bit */
	वापस UNMARK(regval);
पूर्ण
EXPORT_SYMBOL_GPL(ni_lookup_route_रेजिस्टर);

/**
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
			स्थिर काष्ठा ni_route_tables *tables)
अणु
	स्थिर काष्ठा ni_route_set *routes =
		ni_find_route_set(dest, tables->valid_routes);
	स्थिर u8 *rv;
	s8 regval;

	/* first check to see अगर source is listed with bunch of destinations. */
	अगर (!routes)
		वापस -1;
	/* 2nd, check to see अगर destination is in list of source's tarमाला_लो. */
	अगर (!ni_route_set_has_source(routes, src))
		वापस -1;
	/*
	 * finally, check to see अगर we know how to route...
	 * Be sure to use the B() macro to subtract off the NI_NAMES_BASE beक्रमe
	 * indexing पूर्णांकo the route_values array.
	 */
	rv = tables->route_values;
	regval = RVi(rv, B(src), B(dest));

	/*
	 * अगर we did not validate the route, we'll see अगर we can route through
	 * one of the muxes
	 */
	अगर (!regval && channel_is_rtsi(dest)) अणु
		regval = RVi(rv, B(src), B(NI_RGOUT0));
		अगर (!regval && (RVi(rv, B(src), B(NI_RTSI_BRD(0))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(1))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(2))) ||
				RVi(rv, B(src), B(NI_RTSI_BRD(3)))))
			regval = BIT(6);
	पूर्ण

	अगर (!regval)
		वापस -1;
	/* mask out the valid-value marking bit */
	वापस UNMARK(regval);
पूर्ण
EXPORT_SYMBOL_GPL(ni_route_to_रेजिस्टर);

/**
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
पूर्णांक ni_find_route_source(स्थिर u8 src_sel_reg_value, पूर्णांक dest,
			 स्थिर काष्ठा ni_route_tables *tables)
अणु
	पूर्णांक src;

	अगर (!tables->route_values)
		वापस -EINVAL;

	dest = B(dest); /* subtract NI names offset */
	/* ensure we are not going to under/over run the route value table */
	अगर (dest < 0 || dest >= NI_NUM_NAMES)
		वापस -EINVAL;
	क्रम (src = 0; src < NI_NUM_NAMES; ++src)
		अगर (RVi(tables->route_values, src, dest) ==
		    V(src_sel_reg_value))
			वापस src + NI_NAMES_BASE;
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(ni_find_route_source);

/* **** END Routes search routines **** */

/* **** BEGIN simple module entry/निकास functions **** */
अटल पूर्णांक __init ni_routes_module_init(व्योम)
अणु
	ni_sort_all_device_routes();
	वापस 0;
पूर्ण

अटल व्योम __निकास ni_routes_module_निकास(व्योम)
अणु
पूर्ण

module_init(ni_routes_module_init);
module_निकास(ni_routes_module_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi helper for routing signals-->terminals for NI");
MODULE_LICENSE("GPL");
/* **** END simple module entry/निकास functions **** */
