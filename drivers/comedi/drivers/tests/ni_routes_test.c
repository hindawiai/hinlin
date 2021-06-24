<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/tests/ni_routes_test.c
 *  Unit tests क्रम NI routes (ni_routes.c module).
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

#समावेश "../ni_stc.h"
#समावेश "../ni_routes.h"
#समावेश "unittest.h"

#घोषणा RVI(table, src, dest)	((table)[(dest) * NI_NUM_NAMES + (src)])
#घोषणा O(x)	((x) + NI_NAMES_BASE)
#घोषणा B(x)	((x) - NI_NAMES_BASE)
#घोषणा V(x)	((x) | 0x80)

/* *** BEGIN fake board data *** */
अटल स्थिर अक्षर *pci_6070e = "pci-6070e";
अटल स्थिर अक्षर *pci_6220 = "pci-6220";
अटल स्थिर अक्षर *pci_fake = "pci-fake";

अटल स्थिर अक्षर *ni_eseries = "ni_eseries";
अटल स्थिर अक्षर *ni_mseries = "ni_mseries";

अटल काष्ठा ni_board_काष्ठा board = अणु
	.name = शून्य,
पूर्ण;

अटल काष्ठा ni_निजी निजी = अणु
	.is_m_series = 0,
पूर्ण;

अटल स्थिर पूर्णांक bad_dest = O(8), dest0 = O(0), desti = O(5);
अटल स्थिर पूर्णांक ith_dest_index = 2;
अटल स्थिर पूर्णांक no_val_dest = O(7), no_val_index = 4;

/* These have to be defs to be used in init code below */
#घोषणा rgout0_src0	(O(100))
#घोषणा rgout0_src1	(O(101))
#घोषणा brd0_src0	(O(110))
#घोषणा brd0_src1	(O(111))
#घोषणा brd1_src0	(O(120))
#घोषणा brd1_src1	(O(121))
#घोषणा brd2_src0	(O(130))
#घोषणा brd2_src1	(O(131))
#घोषणा brd3_src0	(O(140))
#घोषणा brd3_src1	(O(141))

/* I1 and I2 should not call O(...).  Mostly here to shut checkpatch.pl up */
#घोषणा I1(x1)	\
	((पूर्णांक[])अणु \
		(x1), 0 \
	 पूर्ण)
#घोषणा I2(x1, x2)	\
	((पूर्णांक[])अणु \
		(x1), (x2), 0 \
	 पूर्ण)
#घोषणा I3(x1, x2, x3)	\
	((पूर्णांक[])अणु \
		(x1), (x2), (x3), 0 \
	 पूर्ण)

/* O9 is build to call O(...) क्रम each arg */
#घोषणा O9(x1, x2, x3, x4, x5, x6, x7, x8, x9)	\
	((पूर्णांक[])अणु \
		O(x1), O(x2), O(x3), O(x4), O(x5), O(x6), O(x7), O(x8), O(x9), \
		0 \
	 पूर्ण)

अटल काष्ठा ni_device_routes DR = अणु
	.device = "testdev",
	.routes = (काष्ठा ni_route_set[])अणु
		अणु.dest = O(0), .src = O9(/**/1, 2, 3, 4, 5, 6, 7, 8, 9)पूर्ण,
		अणु.dest = O(1), .src = O9(0, /**/2, 3, 4, 5, 6, 7, 8, 9)पूर्ण,
		/* ith route_set */
		अणु.dest = O(5), .src = O9(0, 1, 2, 3, 4,/**/ 6, 7, 8, 9)पूर्ण,
		अणु.dest = O(6), .src = O9(0, 1, 2, 3, 4, 5,/**/ 7, 8, 9)पूर्ण,
		/* next one will not have valid reg values */
		अणु.dest = O(7), .src = O9(0, 1, 2, 3, 4, 5, 6,/**/ 8, 9)पूर्ण,
		अणु.dest = O(9), .src = O9(0, 1, 2, 3, 4, 5, 6, 7, 8/**/)पूर्ण,

		/* indirect routes करोne through muxes */
		अणु.dest = TRIGGER_LINE(0), .src = I1(rgout0_src0)पूर्ण,
		अणु.dest = TRIGGER_LINE(1), .src = I3(rgout0_src0,
						    brd3_src0,
						    brd3_src1)पूर्ण,
		अणु.dest = TRIGGER_LINE(2), .src = I3(rgout0_src1,
						    brd2_src0,
						    brd2_src1)पूर्ण,
		अणु.dest = TRIGGER_LINE(3), .src = I3(rgout0_src1,
						    brd1_src0,
						    brd1_src1)पूर्ण,
		अणु.dest = TRIGGER_LINE(4), .src = I2(brd0_src0,
						    brd0_src1)पूर्ण,
		अणु.dest = 0पूर्ण,
	पूर्ण,
पूर्ण;

#अघोषित I1
#अघोषित I2
#अघोषित O9

#घोषणा RV9(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
	[x1] = V(x1), [x2] = V(x2), [x3] = V(x3), [x4] = V(x4), \
	[x5] = V(x5), [x6] = V(x6), [x7] = V(x7), [x8] = V(x8), \
	[x9] = V(x9),

/* This table is indexed as RV[destination][source] */
अटल स्थिर u8 RV[NI_NUM_NAMES][NI_NUM_NAMES] = अणु
	[0] = अणुRV9(/**/1, 2, 3, 4, 5, 6, 7, 8, 9)पूर्ण,
	[1] = अणुRV9(0,/**/ 2, 3, 4, 5, 6, 7, 8, 9)पूर्ण,
	[2] = अणुRV9(0,  1,/**/3, 4, 5, 6, 7, 8, 9)पूर्ण,
	[3] = अणुRV9(0,  1, 2,/**/4, 5, 6, 7, 8, 9)पूर्ण,
	[4] = अणुRV9(0,  1, 2, 3,/**/5, 6, 7, 8, 9)पूर्ण,
	[5] = अणुRV9(0,  1, 2, 3, 4,/**/6, 7, 8, 9)पूर्ण,
	[6] = अणुRV9(0,  1, 2, 3, 4, 5,/**/7, 8, 9)पूर्ण,
	/* [7] is पूर्णांकentionaly left असलent to test invalid routes */
	[8] = अणुRV9(0,  1, 2, 3, 4, 5, 6, 7,/**/9)पूर्ण,
	[9] = अणुRV9(0,  1, 2, 3, 4, 5, 6, 7, 8/**/)पूर्ण,
	/* some tests क्रम needing extra muxes */
	[B(NI_RGOUT0)]	= अणु[B(rgout0_src0)]   = V(0),
			   [B(rgout0_src1)]   = V(1)पूर्ण,
	[B(NI_RTSI_BRD(0))] = अणु[B(brd0_src0)] = V(0),
			       [B(brd0_src1)] = V(1)पूर्ण,
	[B(NI_RTSI_BRD(1))] = अणु[B(brd1_src0)] = V(0),
			       [B(brd1_src1)] = V(1)पूर्ण,
	[B(NI_RTSI_BRD(2))] = अणु[B(brd2_src0)] = V(0),
			       [B(brd2_src1)] = V(1)पूर्ण,
	[B(NI_RTSI_BRD(3))] = अणु[B(brd3_src0)] = V(0),
			       [B(brd3_src1)] = V(1)पूर्ण,
पूर्ण;

#अघोषित RV9

/* *** END fake board data *** */

/* *** BEGIN board data initializers *** */
अटल व्योम init_निजी(व्योम)
अणु
	स_रखो(&निजी, 0, माप(काष्ठा ni_निजी));
पूर्ण

अटल व्योम init_pci_6070e(व्योम)
अणु
	board.name = pci_6070e;
	init_निजी();
	निजी.is_m_series = 0;
पूर्ण

अटल व्योम init_pci_6220(व्योम)
अणु
	board.name = pci_6220;
	init_निजी();
	निजी.is_m_series = 1;
पूर्ण

अटल व्योम init_pci_fake(व्योम)
अणु
	board.name = pci_fake;
	init_निजी();
	निजी.routing_tables.route_values = &RV[0][0];
	निजी.routing_tables.valid_routes = &DR;
पूर्ण

/* *** END board data initializers *** */

/* Tests that route_sets are in order of the संकेत destination. */
अटल bool route_set_dests_in_order(स्थिर काष्ठा ni_device_routes *devroutes)
अणु
	पूर्णांक i;
	पूर्णांक last = NI_NAMES_BASE - 1;

	क्रम (i = 0; i < devroutes->n_route_sets; ++i) अणु
		अगर (last >= devroutes->routes[i].dest)
			वापस false;
		last = devroutes->routes[i].dest;
	पूर्ण
	वापस true;
पूर्ण

/* Tests that all route_set->src are in order of the संकेत source. */
अटल bool route_set_sources_in_order(स्थिर काष्ठा ni_device_routes *devroutes)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < devroutes->n_route_sets; ++i) अणु
		पूर्णांक j;
		पूर्णांक last = NI_NAMES_BASE - 1;

		क्रम (j = 0; j < devroutes->routes[i].n_src; ++j) अणु
			अगर (last >= devroutes->routes[i].src[j])
				वापस false;
			last = devroutes->routes[i].src[j];
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम test_ni_assign_device_routes(व्योम)
अणु
	स्थिर काष्ठा ni_device_routes *devroutes;
	स्थिर u8 *table, *oldtable;

	init_pci_6070e();
	ni_assign_device_routes(ni_eseries, pci_6070e, शून्य,
				&निजी.routing_tables);
	devroutes = निजी.routing_tables.valid_routes;
	table = निजी.routing_tables.route_values;

	unittest(म_भेदन(devroutes->device, pci_6070e, 10) == 0,
		 "find device pci-6070e\n");
	unittest(devroutes->n_route_sets == 37,
		 "number of pci-6070e route_sets == 37\n");
	unittest(devroutes->routes->dest == NI_PFI(0),
		 "first pci-6070e route_set is for NI_PFI(0)\n");
	unittest(devroutes->routes->n_src == 1,
		 "first pci-6070e route_set length == 1\n");
	unittest(devroutes->routes->src[0] == NI_AI_StartTrigger,
		 "first pci-6070e route_set src. == NI_AI_StartTrigger\n");
	unittest(devroutes->routes[10].dest == TRIGGER_LINE(0),
		 "10th pci-6070e route_set is for TRIGGER_LINE(0)\n");
	unittest(devroutes->routes[10].n_src == 10,
		 "10th pci-6070e route_set length == 10\n");
	unittest(devroutes->routes[10].src[0] == NI_CtrSource(0),
		 "10th pci-6070e route_set src. == NI_CtrSource(0)\n");
	unittest(route_set_dests_in_order(devroutes),
		 "all pci-6070e route_sets in order of signal destination\n");
	unittest(route_set_sources_in_order(devroutes),
		 "all pci-6070e route_set->src's in order of signal source\n");

	unittest(RVI(table, B(PXI_Star), B(NI_AI_SampleClock)) == V(17) &&
		 RVI(table, B(NI_10MHzRefClock), B(TRIGGER_LINE(0))) == 0 &&
		 RVI(table, B(NI_AI_ConvertClock), B(NI_PFI(0))) == 0 &&
		 RVI(table, B(NI_AI_ConvertClock), B(NI_PFI(2))) == V(NI_PFI_OUTPUT_AI_CONVERT),
		 "pci-6070e finds e-series route_values table\n");

	oldtable = table;
	init_pci_6220();
	ni_assign_device_routes(ni_mseries, pci_6220, शून्य,
				&निजी.routing_tables);
	devroutes = निजी.routing_tables.valid_routes;
	table = निजी.routing_tables.route_values;

	unittest(म_भेदन(devroutes->device, pci_6220, 10) == 0,
		 "find device pci-6220\n");
	unittest(oldtable != table, "pci-6220 find other route_values table\n");

	unittest(RVI(table, B(PXI_Star), B(NI_AI_SampleClock)) == V(20) &&
		 RVI(table, B(NI_10MHzRefClock), B(TRIGGER_LINE(0))) == V(12) &&
		 RVI(table, B(NI_AI_ConvertClock), B(NI_PFI(0))) == V(3) &&
		 RVI(table, B(NI_AI_ConvertClock), B(NI_PFI(2))) == V(3),
		 "pci-6220 finds m-series route_values table\n");
पूर्ण

अटल व्योम test_ni_sort_device_routes(व्योम)
अणु
	/* We begin by sorting the device routes क्रम use in later tests */
	ni_sort_device_routes(&DR);
	/* now we test that sorting. */
	unittest(route_set_dests_in_order(&DR),
		 "all route_sets of fake data in order of sig. destination\n");
	unittest(route_set_sources_in_order(&DR),
		 "all route_set->src's of fake data in order of sig. source\n");
पूर्ण

अटल व्योम test_ni_find_route_set(व्योम)
अणु
	unittest(!ni_find_route_set(bad_dest, &DR),
		 "check for nonexistent route_set\n");
	unittest(ni_find_route_set(dest0, &DR) == &DR.routes[0],
		 "find first route_set\n");
	unittest(ni_find_route_set(desti, &DR) == &DR.routes[ith_dest_index],
		 "find ith route_set\n");
	unittest(ni_find_route_set(no_val_dest, &DR) ==
		 &DR.routes[no_val_index],
		 "find no_val route_set in spite of missing values\n");
	unittest(ni_find_route_set(DR.routes[DR.n_route_sets - 1].dest, &DR) ==
		 &DR.routes[DR.n_route_sets - 1],
		 "find last route_set\n");
पूर्ण

अटल व्योम test_ni_route_set_has_source(व्योम)
अणु
	unittest(!ni_route_set_has_source(&DR.routes[0], O(0)),
		 "check for bad source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(1)),
		 "find first source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(5)),
		 "find fifth source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(9)),
		 "find last source\n");
पूर्ण

अटल व्योम test_ni_route_to_रेजिस्टर(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_route_to_रेजिस्टर(O(0), O(0), T) < 0,
		 "check for bad route 0-->0\n");
	unittest(ni_route_to_रेजिस्टर(O(1), O(0), T) == 1,
		 "validate first destination\n");
	unittest(ni_route_to_रेजिस्टर(O(6), O(5), T) == 6,
		 "validate middle destination\n");
	unittest(ni_route_to_रेजिस्टर(O(8), O(9), T) == 8,
		 "validate last destination\n");

	/* choice of trigger line in the following is somewhat अक्रमom */
	unittest(ni_route_to_रेजिस्टर(rgout0_src0, TRIGGER_LINE(0), T) == 0,
		 "validate indirect route through rgout0 to TRIGGER_LINE(0)\n");
	unittest(ni_route_to_रेजिस्टर(rgout0_src0, TRIGGER_LINE(1), T) == 0,
		 "validate indirect route through rgout0 to TRIGGER_LINE(1)\n");
	unittest(ni_route_to_रेजिस्टर(rgout0_src1, TRIGGER_LINE(2), T) == 1,
		 "validate indirect route through rgout0 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_रेजिस्टर(rgout0_src1, TRIGGER_LINE(3), T) == 1,
		 "validate indirect route through rgout0 to TRIGGER_LINE(3)\n");

	unittest(ni_route_to_रेजिस्टर(brd0_src0, TRIGGER_LINE(4), T) ==
		 BIT(6),
		 "validate indirect route through brd0 to TRIGGER_LINE(4)\n");
	unittest(ni_route_to_रेजिस्टर(brd0_src1, TRIGGER_LINE(4), T) ==
		 BIT(6),
		 "validate indirect route through brd0 to TRIGGER_LINE(4)\n");
	unittest(ni_route_to_रेजिस्टर(brd1_src0, TRIGGER_LINE(3), T) ==
		 BIT(6),
		 "validate indirect route through brd1 to TRIGGER_LINE(3)\n");
	unittest(ni_route_to_रेजिस्टर(brd1_src1, TRIGGER_LINE(3), T) ==
		 BIT(6),
		 "validate indirect route through brd1 to TRIGGER_LINE(3)\n");
	unittest(ni_route_to_रेजिस्टर(brd2_src0, TRIGGER_LINE(2), T) ==
		 BIT(6),
		 "validate indirect route through brd2 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_रेजिस्टर(brd2_src1, TRIGGER_LINE(2), T) ==
		 BIT(6),
		 "validate indirect route through brd2 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_रेजिस्टर(brd3_src0, TRIGGER_LINE(1), T) ==
		 BIT(6),
		 "validate indirect route through brd3 to TRIGGER_LINE(1)\n");
	unittest(ni_route_to_रेजिस्टर(brd3_src1, TRIGGER_LINE(1), T) ==
		 BIT(6),
		 "validate indirect route through brd3 to TRIGGER_LINE(1)\n");
पूर्ण

अटल व्योम test_ni_lookup_route_रेजिस्टर(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_lookup_route_रेजिस्टर(O(0), O(0), T) == -EINVAL,
		 "check for bad route 0-->0\n");
	unittest(ni_lookup_route_रेजिस्टर(O(1), O(0), T) == 1,
		 "validate first destination\n");
	unittest(ni_lookup_route_रेजिस्टर(O(6), O(5), T) == 6,
		 "validate middle destination\n");
	unittest(ni_lookup_route_रेजिस्टर(O(8), O(9), T) == 8,
		 "validate last destination\n");
	unittest(ni_lookup_route_रेजिस्टर(O(10), O(9), T) == -EINVAL,
		 "lookup invalid destination\n");

	unittest(ni_lookup_route_रेजिस्टर(rgout0_src0, TRIGGER_LINE(0), T) ==
		 -EINVAL,
		 "rgout0_src0: no direct lookup of indirect route\n");
	unittest(ni_lookup_route_रेजिस्टर(rgout0_src0, NI_RGOUT0, T) == 0,
		 "rgout0_src0: lookup indirect route register\n");
	unittest(ni_lookup_route_रेजिस्टर(rgout0_src1, TRIGGER_LINE(2), T) ==
		 -EINVAL,
		 "rgout0_src1: no direct lookup of indirect route\n");
	unittest(ni_lookup_route_रेजिस्टर(rgout0_src1, NI_RGOUT0, T) == 1,
		 "rgout0_src1: lookup indirect route register\n");

	unittest(ni_lookup_route_रेजिस्टर(brd0_src0, TRIGGER_LINE(4), T) ==
		 -EINVAL,
		 "brd0_src0: no direct lookup of indirect route\n");
	unittest(ni_lookup_route_रेजिस्टर(brd0_src0, NI_RTSI_BRD(0), T) == 0,
		 "brd0_src0: lookup indirect route register\n");
	unittest(ni_lookup_route_रेजिस्टर(brd0_src1, TRIGGER_LINE(4), T) ==
		 -EINVAL,
		 "brd0_src1: no direct lookup of indirect route\n");
	unittest(ni_lookup_route_रेजिस्टर(brd0_src1, NI_RTSI_BRD(0), T) == 1,
		 "brd0_src1: lookup indirect route register\n");
पूर्ण

अटल व्योम test_route_is_valid(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(!route_is_valid(O(0), O(0), T),
		 "check for bad route 0-->0\n");
	unittest(route_is_valid(O(0), O(1), T),
		 "validate first destination\n");
	unittest(route_is_valid(O(5), O(6), T),
		 "validate middle destination\n");
	unittest(route_is_valid(O(8), O(9), T),
		 "validate last destination\n");
पूर्ण

अटल व्योम test_ni_is_cmd_dest(व्योम)
अणु
	init_pci_fake();
	unittest(ni_is_cmd_dest(NI_AI_SampleClock),
		 "check that AI/SampleClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_StartTrigger),
		 "check that AI/StartTrigger is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_ConvertClock),
		 "check that AI/ConvertClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AO_SampleClock),
		 "check that AO/SampleClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_DO_SampleClock),
		 "check that DO/SampleClock is cmd destination\n");
	unittest(!ni_is_cmd_dest(NI_AO_SampleClockTimebase),
		 "check that AO/SampleClockTimebase _not_ cmd destination\n");
पूर्ण

अटल व्योम test_channel_is_pfi(व्योम)
अणु
	init_pci_fake();
	unittest(channel_is_pfi(NI_PFI(0)), "check First pfi channel\n");
	unittest(channel_is_pfi(NI_PFI(10)), "check 10th pfi channel\n");
	unittest(channel_is_pfi(NI_PFI(-1)), "check last pfi channel\n");
	unittest(!channel_is_pfi(NI_PFI(-1) + 1),
		 "check first non pfi channel\n");
पूर्ण

अटल व्योम test_channel_is_rtsi(व्योम)
अणु
	init_pci_fake();
	unittest(channel_is_rtsi(TRIGGER_LINE(0)),
		 "check First rtsi channel\n");
	unittest(channel_is_rtsi(TRIGGER_LINE(3)),
		 "check 3rd rtsi channel\n");
	unittest(channel_is_rtsi(TRIGGER_LINE(-1)),
		 "check last rtsi channel\n");
	unittest(!channel_is_rtsi(TRIGGER_LINE(-1) + 1),
		 "check first non rtsi channel\n");
पूर्ण

अटल व्योम test_ni_count_valid_routes(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_count_valid_routes(T) == 57, "count all valid routes\n");
पूर्ण

अटल व्योम test_ni_get_valid_routes(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;
	अचिन्हित पूर्णांक pair_data[2];

	init_pci_fake();
	unittest(ni_get_valid_routes(T, 0, शून्य) == 57,
		 "count all valid routes through ni_get_valid_routes\n");

	unittest(ni_get_valid_routes(T, 1, pair_data) == 1,
		 "copied first valid route from ni_get_valid_routes\n");
	unittest(pair_data[0] == O(1),
		 "source of first valid pair from ni_get_valid_routes\n");
	unittest(pair_data[1] == O(0),
		 "destination of first valid pair from ni_get_valid_routes\n");
पूर्ण

अटल व्योम test_ni_find_route_source(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_find_route_source(4, O(4), T) == -EINVAL,
		 "check for bad source 4-->4\n");
	unittest(ni_find_route_source(0, O(1), T) == O(0),
		 "find first source\n");
	unittest(ni_find_route_source(4, O(6), T) == O(4),
		 "find middle source\n");
	unittest(ni_find_route_source(9, O(8), T) == O(9),
		 "find last source");
	unittest(ni_find_route_source(8, O(9), T) == O(8),
		 "find invalid source (without checking device routes)\n");
पूर्ण

अटल व्योम test_route_रेजिस्टर_is_valid(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(!route_रेजिस्टर_is_valid(4, O(4), T),
		 "check for bad source 4-->4\n");
	unittest(route_रेजिस्टर_is_valid(0, O(1), T),
		 "find first source\n");
	unittest(route_रेजिस्टर_is_valid(4, O(6), T),
		 "find middle source\n");
	unittest(route_रेजिस्टर_is_valid(9, O(8), T),
		 "find last source");
पूर्ण

अटल व्योम test_ni_check_trigger_arg(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_check_trigger_arg(0, O(0), T) == -EINVAL,
		 "check bad direct trigger arg for first reg->dest\n");
	unittest(ni_check_trigger_arg(0, O(1), T) == 0,
		 "check direct trigger arg for first reg->dest\n");
	unittest(ni_check_trigger_arg(4, O(6), T) == 0,
		 "check direct trigger arg for middle reg->dest\n");
	unittest(ni_check_trigger_arg(9, O(8), T) == 0,
		 "check direct trigger arg for last reg->dest\n");

	unittest(ni_check_trigger_arg_roffs(-1, O(0), T, 1) == -EINVAL,
		 "check bad direct trigger arg for first reg->dest w/offs\n");
	unittest(ni_check_trigger_arg_roffs(0, O(1), T, 0) == 0,
		 "check direct trigger arg for first reg->dest w/offs\n");
	unittest(ni_check_trigger_arg_roffs(3, O(6), T, 1) == 0,
		 "check direct trigger arg for middle reg->dest w/offs\n");
	unittest(ni_check_trigger_arg_roffs(7, O(8), T, 2) == 0,
		 "check direct trigger arg for last reg->dest w/offs\n");

	unittest(ni_check_trigger_arg(O(0), O(0), T) == -EINVAL,
		 "check bad trigger arg for first src->dest\n");
	unittest(ni_check_trigger_arg(O(0), O(1), T) == 0,
		 "check trigger arg for first src->dest\n");
	unittest(ni_check_trigger_arg(O(5), O(6), T) == 0,
		 "check trigger arg for middle src->dest\n");
	unittest(ni_check_trigger_arg(O(8), O(9), T) == 0,
		 "check trigger arg for last src->dest\n");
पूर्ण

अटल व्योम test_ni_get_reg_value(व्योम)
अणु
	स्थिर काष्ठा ni_route_tables *T = &निजी.routing_tables;

	init_pci_fake();
	unittest(ni_get_reg_value(0, O(0), T) == -1,
		 "check bad direct trigger arg for first reg->dest\n");
	unittest(ni_get_reg_value(0, O(1), T) == 0,
		 "check direct trigger arg for first reg->dest\n");
	unittest(ni_get_reg_value(4, O(6), T) == 4,
		 "check direct trigger arg for middle reg->dest\n");
	unittest(ni_get_reg_value(9, O(8), T) == 9,
		 "check direct trigger arg for last reg->dest\n");

	unittest(ni_get_reg_value_roffs(-1, O(0), T, 1) == -1,
		 "check bad direct trigger arg for first reg->dest w/offs\n");
	unittest(ni_get_reg_value_roffs(0, O(1), T, 0) == 0,
		 "check direct trigger arg for first reg->dest w/offs\n");
	unittest(ni_get_reg_value_roffs(3, O(6), T, 1) == 4,
		 "check direct trigger arg for middle reg->dest w/offs\n");
	unittest(ni_get_reg_value_roffs(7, O(8), T, 2) == 9,
		 "check direct trigger arg for last reg->dest w/offs\n");

	unittest(ni_get_reg_value(O(0), O(0), T) == -1,
		 "check bad trigger arg for first src->dest\n");
	unittest(ni_get_reg_value(O(0), O(1), T) == 0,
		 "check trigger arg for first src->dest\n");
	unittest(ni_get_reg_value(O(5), O(6), T) == 5,
		 "check trigger arg for middle src->dest\n");
	unittest(ni_get_reg_value(O(8), O(9), T) == 8,
		 "check trigger arg for last src->dest\n");
पूर्ण

/* **** BEGIN simple module entry/निकास functions **** */
अटल पूर्णांक __init ni_routes_unittest(व्योम)
अणु
	अटल स्थिर unittest_fptr unit_tests[] = अणु
		test_ni_assign_device_routes,
		test_ni_sort_device_routes,
		test_ni_find_route_set,
		test_ni_route_set_has_source,
		test_ni_route_to_रेजिस्टर,
		test_ni_lookup_route_रेजिस्टर,
		test_route_is_valid,
		test_ni_is_cmd_dest,
		test_channel_is_pfi,
		test_channel_is_rtsi,
		test_ni_count_valid_routes,
		test_ni_get_valid_routes,
		test_ni_find_route_source,
		test_route_रेजिस्टर_is_valid,
		test_ni_check_trigger_arg,
		test_ni_get_reg_value,
		शून्य,
	पूर्ण;

	exec_unittests("ni_routes", unit_tests);
	वापस 0;
पूर्ण

अटल व्योम __निकास ni_routes_unittest_निकास(व्योम) अणु पूर्ण

module_init(ni_routes_unittest);
module_निकास(ni_routes_unittest_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi unit-tests for ni_routes module");
MODULE_LICENSE("GPL");
/* **** END simple module entry/निकास functions **** */
