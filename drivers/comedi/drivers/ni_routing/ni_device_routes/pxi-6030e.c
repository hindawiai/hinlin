<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/ni_routing/ni_device_routes/pxi-6030e.c
 *  List of valid routes क्रम specअगरic NI boards.
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

/*
 * The contents of this file are generated using the tools in
 * comedi/drivers/ni_routing/tools
 *
 * Please use those tools to help मुख्यtain the contents of this file.
 */

#समावेश "../ni_device_routes.h"
#समावेश "all.h"

काष्ठा ni_device_routes ni_pxi_6030e_device_routes = अणु
	.device = "pxi-6030e",
	.routes = (काष्ठा ni_route_set[])अणु
		अणु
			.dest = NI_PFI(0),
			.src = (पूर्णांक[])अणु
				NI_AI_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(1),
			.src = (पूर्णांक[])अणु
				NI_AI_ReferenceTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(2),
			.src = (पूर्णांक[])अणु
				NI_AI_ConvertClock,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(3),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(1),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(4),
			.src = (पूर्णांक[])अणु
				NI_CtrGate(1),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(5),
			.src = (पूर्णांक[])अणु
				NI_AO_SampleClock,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(6),
			.src = (पूर्णांक[])अणु
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(7),
			.src = (पूर्णांक[])अणु
				NI_AI_SampleClock,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(8),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_PFI(9),
			.src = (पूर्णांक[])अणु
				NI_CtrGate(0),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(0),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(1),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(2),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(3),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(4),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(5),
			.src = (पूर्णांक[])अणु
				NI_CtrSource(0),
				NI_CtrGate(0),
				NI_CtrInternalOutput(0),
				NI_CtrOut(0),
				NI_AI_SampleClock,
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AI_ConvertClock,
				NI_AO_SampleClock,
				NI_AO_StartTrigger,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = TRIGGER_LINE(7),
			.src = (पूर्णांक[])अणु
				NI_20MHzTimebase,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrSource(0),
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				TRIGGER_LINE(7),
				NI_MasterTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrSource(1),
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				TRIGGER_LINE(7),
				NI_MasterTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrGate(0),
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(1),
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrGate(1),
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(0),
				NI_AI_StartTrigger,
				NI_AI_ReferenceTrigger,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrOut(0),
			.src = (पूर्णांक[])अणु
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(0),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_CtrOut(1),
			.src = (पूर्णांक[])अणु
				NI_CtrInternalOutput(1),
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_SampleClock,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(0),
				NI_AI_SampleClockTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_SampleClockTimebase,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				TRIGGER_LINE(7),
				NI_MasterTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_StartTrigger,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(0),
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_ReferenceTrigger,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_ConvertClock,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(0),
				NI_AI_ConvertClockTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_ConvertClockTimebase,
			.src = (पूर्णांक[])अणु
				TRIGGER_LINE(7),
				NI_AI_SampleClockTimebase,
				NI_MasterTimebase,
				NI_20MHzTimebase,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_PauseTrigger,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AI_HoldComplete,
			.src = (पूर्णांक[])अणु
				NI_AI_HoldCompleteEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AO_SampleClock,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_CtrInternalOutput(1),
				NI_AO_SampleClockTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AO_SampleClockTimebase,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				TRIGGER_LINE(7),
				NI_MasterTimebase,
				NI_20MHzTimebase,
				NI_100kHzTimebase,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AO_StartTrigger,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_AI_StartTrigger,
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_AO_PauseTrigger,
			.src = (पूर्णांक[])अणु
				NI_PFI(0),
				NI_PFI(1),
				NI_PFI(2),
				NI_PFI(3),
				NI_PFI(4),
				NI_PFI(5),
				NI_PFI(6),
				NI_PFI(7),
				NI_PFI(8),
				NI_PFI(9),
				TRIGGER_LINE(0),
				TRIGGER_LINE(1),
				TRIGGER_LINE(2),
				TRIGGER_LINE(3),
				TRIGGER_LINE(4),
				TRIGGER_LINE(5),
				NI_AnalogComparisonEvent,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु
			.dest = NI_MasterTimebase,
			.src = (पूर्णांक[])अणु
				TRIGGER_LINE(7),
				NI_20MHzTimebase,
				0, /* Termination */
			पूर्ण
		पूर्ण,
		अणु /* Termination of list */
			.dest = 0,
		पूर्ण,
	पूर्ण,
पूर्ण;
