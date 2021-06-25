<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश "sja1105.h"

#घोषणा SJA1105_TAS_CLKSRC_DISABLED	0
#घोषणा SJA1105_TAS_CLKSRC_STANDALONE	1
#घोषणा SJA1105_TAS_CLKSRC_AS6802	2
#घोषणा SJA1105_TAS_CLKSRC_PTP		3
#घोषणा SJA1105_GATE_MASK		GENMASK_ULL(SJA1105_NUM_TC - 1, 0)

#घोषणा work_to_sja1105_tas(d) \
	container_of((d), काष्ठा sja1105_tas_data, tas_work)
#घोषणा tas_to_sja1105(d) \
	container_of((d), काष्ठा sja1105_निजी, tas_data)

अटल पूर्णांक sja1105_tas_set_runसमय_params(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	काष्ठा sja1105_gating_config *gating_cfg = &tas_data->gating_cfg;
	काष्ठा dsa_चयन *ds = priv->ds;
	s64 earliest_base_समय = S64_MAX;
	s64 latest_base_समय = 0;
	s64 its_cycle_समय = 0;
	s64 max_cycle_समय = 0;
	पूर्णांक port;

	tas_data->enabled = false;

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		स्थिर काष्ठा tc_taprio_qopt_offload *offload;

		offload = tas_data->offload[port];
		अगर (!offload)
			जारी;

		tas_data->enabled = true;

		अगर (max_cycle_समय < offload->cycle_समय)
			max_cycle_समय = offload->cycle_समय;
		अगर (latest_base_समय < offload->base_समय)
			latest_base_समय = offload->base_समय;
		अगर (earliest_base_समय > offload->base_समय) अणु
			earliest_base_समय = offload->base_समय;
			its_cycle_समय = offload->cycle_समय;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&gating_cfg->entries)) अणु
		tas_data->enabled = true;

		अगर (max_cycle_समय < gating_cfg->cycle_समय)
			max_cycle_समय = gating_cfg->cycle_समय;
		अगर (latest_base_समय < gating_cfg->base_समय)
			latest_base_समय = gating_cfg->base_समय;
		अगर (earliest_base_समय > gating_cfg->base_समय) अणु
			earliest_base_समय = gating_cfg->base_समय;
			its_cycle_समय = gating_cfg->cycle_समय;
		पूर्ण
	पूर्ण

	अगर (!tas_data->enabled)
		वापस 0;

	/* Roll the earliest base समय over until it is in a comparable
	 * समय base with the latest, then compare their deltas.
	 * We want to enक्रमce that all ports' base बार are within
	 * SJA1105_TAS_MAX_DELTA 200ns cycles of one another.
	 */
	earliest_base_समय = future_base_समय(earliest_base_समय,
					      its_cycle_समय,
					      latest_base_समय);
	जबतक (earliest_base_समय > latest_base_समय)
		earliest_base_समय -= its_cycle_समय;
	अगर (latest_base_समय - earliest_base_समय >
	    sja1105_delta_to_ns(SJA1105_TAS_MAX_DELTA)) अणु
		dev_err(ds->dev,
			"Base times too far apart: min %llu max %llu\n",
			earliest_base_समय, latest_base_समय);
		वापस -दुस्फल;
	पूर्ण

	tas_data->earliest_base_समय = earliest_base_समय;
	tas_data->max_cycle_समय = max_cycle_समय;

	dev_dbg(ds->dev, "earliest base time %lld ns\n", earliest_base_समय);
	dev_dbg(ds->dev, "latest base time %lld ns\n", latest_base_समय);
	dev_dbg(ds->dev, "longest cycle time %lld ns\n", max_cycle_समय);

	वापस 0;
पूर्ण

/* Lo and behold: the egress scheduler from hell.
 *
 * At the hardware level, the Time-Aware Shaper holds a global linear arrray of
 * all schedule entries क्रम all ports. These are the Gate Control List (GCL)
 * entries, let's call them "timeslots" क्रम लघु. This linear array of
 * बारlots is held in BLK_IDX_SCHEDULE.
 *
 * Then there are a maximum of 8 "execution threads" inside the चयन, which
 * iterate cyclically through the "schedule". Each "cycle" has an entry poपूर्णांक
 * and an निकास poपूर्णांक, both being बारlot indices in the schedule table. The
 * hardware calls each cycle a "subschedule".
 *
 * Subschedule (cycle) i starts when
 *   ptpclkval >= ptpschपंचांग + BLK_IDX_SCHEDULE_ENTRY_POINTS[i].delta.
 *
 * The hardware scheduler iterates BLK_IDX_SCHEDULE with a k ranging from
 *   k = BLK_IDX_SCHEDULE_ENTRY_POINTS[i].address to
 *   k = BLK_IDX_SCHEDULE_PARAMS.subscheind[i]
 *
 * For each schedule entry (बारlot) k, the engine executes the gate control
 * list entry क्रम the duration of BLK_IDX_SCHEDULE[k].delta.
 *
 *         +---------+
 *         |         | BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS
 *         +---------+
 *              |
 *              +-----------------+
 *                                | .actsubsch
 *  BLK_IDX_SCHEDULE_ENTRY_POINTS v
 *                 +-------+-------+
 *                 |cycle 0|cycle 1|
 *                 +-------+-------+
 *                   |  |      |  |
 *  +----------------+  |      |  +-------------------------------------+
 *  |   .subschindx     |      |             .subschindx                |
 *  |                   |      +---------------+                        |
 *  |          .address |        .address      |                        |
 *  |                   |                      |                        |
 *  |                   |                      |                        |
 *  |  BLK_IDX_SCHEDULE v                      v                        |
 *  |              +-------+-------+-------+-------+-------+------+     |
 *  |              |entry 0|entry 1|entry 2|entry 3|entry 4|entry5|     |
 *  |              +-------+-------+-------+-------+-------+------+     |
 *  |                                  ^                    ^  ^  ^     |
 *  |                                  |                    |  |  |     |
 *  |        +-------------------------+                    |  |  |     |
 *  |        |              +-------------------------------+  |  |     |
 *  |        |              |              +-------------------+  |     |
 *  |        |              |              |                      |     |
 *  | +---------------------------------------------------------------+ |
 *  | |subscheind[0]<=subscheind[1]<=subscheind[2]<=...<=subscheind[7]| |
 *  | +---------------------------------------------------------------+ |
 *  |        ^              ^                BLK_IDX_SCHEDULE_PARAMS    |
 *  |        |              |                                           |
 *  +--------+              +-------------------------------------------+
 *
 *  In the above picture there are two subschedules (cycles):
 *
 *  - cycle 0: iterates the schedule table from 0 to 2 (and back)
 *  - cycle 1: iterates the schedule table from 3 to 5 (and back)
 *
 *  All other possible execution thपढ़ोs must be marked as unused by making
 *  their "subschedule end index" (subscheind) equal to the last valid
 *  subschedule's end index (in this हाल 5).
 */
पूर्णांक sja1105_init_scheduling(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_schedule_entry_poपूर्णांकs_entry *schedule_entry_poपूर्णांकs;
	काष्ठा sja1105_schedule_entry_poपूर्णांकs_params_entry
					*schedule_entry_poपूर्णांकs_params;
	काष्ठा sja1105_schedule_params_entry *schedule_params;
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	काष्ठा sja1105_gating_config *gating_cfg = &tas_data->gating_cfg;
	काष्ठा sja1105_schedule_entry *schedule;
	काष्ठा sja1105_table *table;
	पूर्णांक schedule_start_idx;
	s64 entry_poपूर्णांक_delta;
	पूर्णांक schedule_end_idx;
	पूर्णांक num_entries = 0;
	पूर्णांक num_cycles = 0;
	पूर्णांक cycle = 0;
	पूर्णांक i, k = 0;
	पूर्णांक port, rc;

	rc = sja1105_tas_set_runसमय_params(priv);
	अगर (rc < 0)
		वापस rc;

	/* Discard previous Schedule Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous Schedule Entry Poपूर्णांकs Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous Schedule Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_PARAMS];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Discard previous Schedule Entry Poपूर्णांकs Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS];
	अगर (table->entry_count) अणु
		kमुक्त(table->entries);
		table->entry_count = 0;
	पूर्ण

	/* Figure out the dimensioning of the problem */
	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		अगर (tas_data->offload[port]) अणु
			num_entries += tas_data->offload[port]->num_entries;
			num_cycles++;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&gating_cfg->entries)) अणु
		num_entries += gating_cfg->num_entries;
		num_cycles++;
	पूर्ण

	/* Nothing to करो */
	अगर (!num_cycles)
		वापस 0;

	/* Pre-allocate space in the अटल config tables */

	/* Schedule Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE];
	table->entries = kसुस्मृति(num_entries, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = num_entries;
	schedule = table->entries;

	/* Schedule Poपूर्णांकs Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS_PARAMS];
	table->entries = kसुस्मृति(SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		/* Previously allocated memory will be मुक्तd स्वतःmatically in
		 * sja1105_अटल_config_मुक्त. This is true क्रम all early
		 * वापसs below.
		 */
		वापस -ENOMEM;
	table->entry_count = SJA1105_MAX_SCHEDULE_ENTRY_POINTS_PARAMS_COUNT;
	schedule_entry_poपूर्णांकs_params = table->entries;

	/* Schedule Parameters Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_PARAMS];
	table->entries = kसुस्मृति(SJA1105_MAX_SCHEDULE_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = SJA1105_MAX_SCHEDULE_PARAMS_COUNT;
	schedule_params = table->entries;

	/* Schedule Entry Poपूर्णांकs Table */
	table = &priv->अटल_config.tables[BLK_IDX_SCHEDULE_ENTRY_POINTS];
	table->entries = kसुस्मृति(num_cycles, table->ops->unpacked_entry_size,
				 GFP_KERNEL);
	अगर (!table->entries)
		वापस -ENOMEM;
	table->entry_count = num_cycles;
	schedule_entry_poपूर्णांकs = table->entries;

	/* Finally start populating the अटल config tables */
	schedule_entry_poपूर्णांकs_params->clksrc = SJA1105_TAS_CLKSRC_PTP;
	schedule_entry_poपूर्णांकs_params->actsubsch = num_cycles - 1;

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		स्थिर काष्ठा tc_taprio_qopt_offload *offload;
		/* Relative base समय */
		s64 rbt;

		offload = tas_data->offload[port];
		अगर (!offload)
			जारी;

		schedule_start_idx = k;
		schedule_end_idx = k + offload->num_entries - 1;
		/* This is the base समय expressed as a number of TAS ticks
		 * relative to PTPSCHTM, which we'll (perhaps improperly) call
		 * the operational base समय.
		 */
		rbt = future_base_समय(offload->base_समय,
				       offload->cycle_समय,
				       tas_data->earliest_base_समय);
		rbt -= tas_data->earliest_base_समय;
		/* UM10944.pdf 4.2.2. Schedule Entry Poपूर्णांकs table says that
		 * delta cannot be zero, which is shitty. Advance all relative
		 * base बार by 1 TAS delta, so that even the earliest base
		 * समय becomes 1 in relative terms. Then start the operational
		 * base समय (PTPSCHTM) one TAS delta earlier than planned.
		 */
		entry_poपूर्णांक_delta = ns_to_sja1105_delta(rbt) + 1;

		schedule_entry_poपूर्णांकs[cycle].subschindx = cycle;
		schedule_entry_poपूर्णांकs[cycle].delta = entry_poपूर्णांक_delta;
		schedule_entry_poपूर्णांकs[cycle].address = schedule_start_idx;

		/* The subschedule end indices need to be
		 * monotonically increasing.
		 */
		क्रम (i = cycle; i < 8; i++)
			schedule_params->subscheind[i] = schedule_end_idx;

		क्रम (i = 0; i < offload->num_entries; i++, k++) अणु
			s64 delta_ns = offload->entries[i].पूर्णांकerval;

			schedule[k].delta = ns_to_sja1105_delta(delta_ns);
			schedule[k].destports = BIT(port);
			schedule[k].resmedia_en = true;
			schedule[k].resmedia = SJA1105_GATE_MASK &
					~offload->entries[i].gate_mask;
		पूर्ण
		cycle++;
	पूर्ण

	अगर (!list_empty(&gating_cfg->entries)) अणु
		काष्ठा sja1105_gate_entry *e;

		/* Relative base समय */
		s64 rbt;

		schedule_start_idx = k;
		schedule_end_idx = k + gating_cfg->num_entries - 1;
		rbt = future_base_समय(gating_cfg->base_समय,
				       gating_cfg->cycle_समय,
				       tas_data->earliest_base_समय);
		rbt -= tas_data->earliest_base_समय;
		entry_poपूर्णांक_delta = ns_to_sja1105_delta(rbt) + 1;

		schedule_entry_poपूर्णांकs[cycle].subschindx = cycle;
		schedule_entry_poपूर्णांकs[cycle].delta = entry_poपूर्णांक_delta;
		schedule_entry_poपूर्णांकs[cycle].address = schedule_start_idx;

		क्रम (i = cycle; i < 8; i++)
			schedule_params->subscheind[i] = schedule_end_idx;

		list_क्रम_each_entry(e, &gating_cfg->entries, list) अणु
			schedule[k].delta = ns_to_sja1105_delta(e->पूर्णांकerval);
			schedule[k].destports = e->rule->vl.destports;
			schedule[k].setvalid = true;
			schedule[k].txen = true;
			schedule[k].vlindex = e->rule->vl.sharindx;
			schedule[k].winstindex = e->rule->vl.sharindx;
			अगर (e->gate_state) /* Gate खोलो */
				schedule[k].winst = true;
			अन्यथा /* Gate बंदd */
				schedule[k].winend = true;
			k++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Be there 2 port subschedules, each executing an arbitrary number of gate
 * खोलो/बंद events cyclically.
 * None of those gate events must ever occur at the exact same समय, otherwise
 * the चयन is known to act in exotically strange ways.
 * However the hardware करोesn't bother perक्रमming these पूर्णांकegrity checks.
 * So here we are with the task of validating whether the new @admin offload
 * has any conflict with the alपढ़ोy established TAS configuration in
 * tas_data->offload.  We alपढ़ोy know the other ports are in harmony with one
 * another, otherwise we wouldn't have saved them.
 * Each gate event executes periodically, with a period of @cycle_समय and a
 * phase given by its cycle's @base_समय plus its offset within the cycle
 * (which in turn is given by the length of the events prior to it).
 * There are two aspects to possible collisions:
 * - Collisions within one cycle's (actually the longest cycle's) समय frame.
 *   For that, we need to compare the cartesian product of each possible
 *   occurrence of each event within one cycle समय.
 * - Collisions in the future. Events may not collide within one cycle समय,
 *   but अगर two port schedules करोn't have the same periodicity (aka the cycle
 *   बार aren't multiples of one another), they surely will some समय in the
 *   future (actually they will collide an infinite amount of बार).
 */
अटल bool
sja1105_tas_check_conflicts(काष्ठा sja1105_निजी *priv, पूर्णांक port,
			    स्थिर काष्ठा tc_taprio_qopt_offload *admin)
अणु
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	स्थिर काष्ठा tc_taprio_qopt_offload *offload;
	s64 max_cycle_समय, min_cycle_समय;
	s64 delta1, delta2;
	s64 rbt1, rbt2;
	s64 stop_समय;
	s64 t1, t2;
	पूर्णांक i, j;
	s32 rem;

	offload = tas_data->offload[port];
	अगर (!offload)
		वापस false;

	/* Check अगर the two cycle बार are multiples of one another.
	 * If they aren't, then they will surely collide.
	 */
	max_cycle_समय = max(offload->cycle_समय, admin->cycle_समय);
	min_cycle_समय = min(offload->cycle_समय, admin->cycle_समय);
	भाग_s64_rem(max_cycle_समय, min_cycle_समय, &rem);
	अगर (rem)
		वापस true;

	/* Calculate the "reduced" base समय of each of the two cycles
	 * (transposed back as बंद to 0 as possible) by भागiding to
	 * the cycle समय.
	 */
	भाग_s64_rem(offload->base_समय, offload->cycle_समय, &rem);
	rbt1 = rem;

	भाग_s64_rem(admin->base_समय, admin->cycle_समय, &rem);
	rbt2 = rem;

	stop_समय = max_cycle_समय + max(rbt1, rbt2);

	/* delta1 is the relative base समय of each GCL entry within
	 * the established ports' TAS config.
	 */
	क्रम (i = 0, delta1 = 0;
	     i < offload->num_entries;
	     delta1 += offload->entries[i].पूर्णांकerval, i++) अणु
		/* delta2 is the relative base समय of each GCL entry
		 * within the newly added TAS config.
		 */
		क्रम (j = 0, delta2 = 0;
		     j < admin->num_entries;
		     delta2 += admin->entries[j].पूर्णांकerval, j++) अणु
			/* t1 follows all possible occurrences of the
			 * established ports' GCL entry i within the
			 * first cycle समय.
			 */
			क्रम (t1 = rbt1 + delta1;
			     t1 <= stop_समय;
			     t1 += offload->cycle_समय) अणु
				/* t2 follows all possible occurrences
				 * of the newly added GCL entry j
				 * within the first cycle समय.
				 */
				क्रम (t2 = rbt2 + delta2;
				     t2 <= stop_समय;
				     t2 += admin->cycle_समय) अणु
					अगर (t1 == t2) अणु
						dev_warn(priv->ds->dev,
							 "GCL entry %d collides with entry %d of port %d\n",
							 j, i, port);
						वापस true;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* Check the tc-taprio configuration on @port क्रम conflicts with the tc-gate
 * global subschedule. If @port is -1, check it against all ports.
 * To reuse the sja1105_tas_check_conflicts logic without refactoring it,
 * convert the gating configuration to a dummy tc-taprio offload काष्ठाure.
 */
bool sja1105_gating_check_conflicts(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_gating_config *gating_cfg = &priv->tas_data.gating_cfg;
	माप_प्रकार num_entries = gating_cfg->num_entries;
	काष्ठा tc_taprio_qopt_offload *dummy;
	काष्ठा sja1105_gate_entry *e;
	bool conflict;
	पूर्णांक i = 0;

	अगर (list_empty(&gating_cfg->entries))
		वापस false;

	dummy = kzalloc(काष्ठा_size(dummy, entries, num_entries), GFP_KERNEL);
	अगर (!dummy) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to allocate memory");
		वापस true;
	पूर्ण

	dummy->num_entries = num_entries;
	dummy->base_समय = gating_cfg->base_समय;
	dummy->cycle_समय = gating_cfg->cycle_समय;

	list_क्रम_each_entry(e, &gating_cfg->entries, list)
		dummy->entries[i++].पूर्णांकerval = e->पूर्णांकerval;

	अगर (port != -1) अणु
		conflict = sja1105_tas_check_conflicts(priv, port, dummy);
	पूर्ण अन्यथा अणु
		क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
			conflict = sja1105_tas_check_conflicts(priv, port,
							       dummy);
			अगर (conflict)
				अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(dummy);

	वापस conflict;
पूर्ण

पूर्णांक sja1105_setup_tc_taprio(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    काष्ठा tc_taprio_qopt_offload *admin)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	पूर्णांक other_port, rc, i;

	/* Can't change an alपढ़ोy configured port (must delete qdisc first).
	 * Can't delete the qdisc from an unconfigured port.
	 */
	अगर (!!tas_data->offload[port] == admin->enable)
		वापस -EINVAL;

	अगर (!admin->enable) अणु
		taprio_offload_मुक्त(tas_data->offload[port]);
		tas_data->offload[port] = शून्य;

		rc = sja1105_init_scheduling(priv);
		अगर (rc < 0)
			वापस rc;

		वापस sja1105_अटल_config_reload(priv, SJA1105_SCHEDULING);
	पूर्ण

	/* The cycle समय extension is the amount of समय the last cycle from
	 * the old OPER needs to be extended in order to phase-align with the
	 * base समय of the ADMIN when that becomes the new OPER.
	 * But of course our चयन needs to be reset to चयन-over between
	 * the ADMIN and the OPER configs - so much क्रम a seamless transition.
	 * So करोn't add insult over injury and just say we don't support cycle
	 * समय extension.
	 */
	अगर (admin->cycle_समय_extension)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < admin->num_entries; i++) अणु
		s64 delta_ns = admin->entries[i].पूर्णांकerval;
		s64 delta_cycles = ns_to_sja1105_delta(delta_ns);
		bool too_दीर्घ, too_लघु;

		too_दीर्घ = (delta_cycles >= SJA1105_TAS_MAX_DELTA);
		too_लघु = (delta_cycles == 0);
		अगर (too_दीर्घ || too_लघु) अणु
			dev_err(priv->ds->dev,
				"Interval %llu too %s for GCL entry %d\n",
				delta_ns, too_दीर्घ ? "long" : "short", i);
			वापस -दुस्फल;
		पूर्ण
	पूर्ण

	क्रम (other_port = 0; other_port < SJA1105_NUM_PORTS; other_port++) अणु
		अगर (other_port == port)
			जारी;

		अगर (sja1105_tas_check_conflicts(priv, other_port, admin))
			वापस -दुस्फल;
	पूर्ण

	अगर (sja1105_gating_check_conflicts(priv, port, शून्य)) अणु
		dev_err(ds->dev, "Conflict with tc-gate schedule\n");
		वापस -दुस्फल;
	पूर्ण

	tas_data->offload[port] = taprio_offload_get(admin);

	rc = sja1105_init_scheduling(priv);
	अगर (rc < 0)
		वापस rc;

	वापस sja1105_अटल_config_reload(priv, SJA1105_SCHEDULING);
पूर्ण

अटल पूर्णांक sja1105_tas_check_running(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	काष्ठा dsa_चयन *ds = priv->ds;
	काष्ठा sja1105_ptp_cmd cmd = अणु0पूर्ण;
	पूर्णांक rc;

	rc = sja1105_ptp_commit(ds, &cmd, SPI_READ);
	अगर (rc < 0)
		वापस rc;

	अगर (cmd.ptpstrtsch == 1)
		/* Schedule successfully started */
		tas_data->state = SJA1105_TAS_STATE_RUNNING;
	अन्यथा अगर (cmd.ptpstopsch == 1)
		/* Schedule is stopped */
		tas_data->state = SJA1105_TAS_STATE_DISABLED;
	अन्यथा
		/* Schedule is probably not configured with PTP घड़ी source */
		rc = -EINVAL;

	वापस rc;
पूर्ण

/* Write to PTPCLKCORP */
अटल पूर्णांक sja1105_tas_adjust_drअगरt(काष्ठा sja1105_निजी *priv,
				    u64 correction)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u32 ptpclkcorp = ns_to_sja1105_ticks(correction);

	वापस sja1105_xfer_u32(priv, SPI_WRITE, regs->ptpclkcorp,
				&ptpclkcorp, शून्य);
पूर्ण

/* Write to PTPSCHTM */
अटल पूर्णांक sja1105_tas_set_base_समय(काष्ठा sja1105_निजी *priv,
				     u64 base_समय)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u64 ptpschपंचांग = ns_to_sja1105_ticks(base_समय);

	वापस sja1105_xfer_u64(priv, SPI_WRITE, regs->ptpschपंचांग,
				&ptpschपंचांग, शून्य);
पूर्ण

अटल पूर्णांक sja1105_tas_start(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	काष्ठा sja1105_ptp_cmd *cmd = &priv->ptp_data.cmd;
	काष्ठा dsa_चयन *ds = priv->ds;
	पूर्णांक rc;

	dev_dbg(ds->dev, "Starting the TAS\n");

	अगर (tas_data->state == SJA1105_TAS_STATE_ENABLED_NOT_RUNNING ||
	    tas_data->state == SJA1105_TAS_STATE_RUNNING) अणु
		dev_err(ds->dev, "TAS already started\n");
		वापस -EINVAL;
	पूर्ण

	cmd->ptpstrtsch = 1;
	cmd->ptpstopsch = 0;

	rc = sja1105_ptp_commit(ds, cmd, SPI_WRITE);
	अगर (rc < 0)
		वापस rc;

	tas_data->state = SJA1105_TAS_STATE_ENABLED_NOT_RUNNING;

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_tas_stop(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;
	काष्ठा sja1105_ptp_cmd *cmd = &priv->ptp_data.cmd;
	काष्ठा dsa_चयन *ds = priv->ds;
	पूर्णांक rc;

	dev_dbg(ds->dev, "Stopping the TAS\n");

	अगर (tas_data->state == SJA1105_TAS_STATE_DISABLED) अणु
		dev_err(ds->dev, "TAS already disabled\n");
		वापस -EINVAL;
	पूर्ण

	cmd->ptpstopsch = 1;
	cmd->ptpstrtsch = 0;

	rc = sja1105_ptp_commit(ds, cmd, SPI_WRITE);
	अगर (rc < 0)
		वापस rc;

	tas_data->state = SJA1105_TAS_STATE_DISABLED;

	वापस 0;
पूर्ण

/* The schedule engine and the PTP घड़ी are driven by the same oscillator, and
 * they run in parallel. But whilst the PTP घड़ी can keep an असलolute
 * समय-of-day, the schedule engine is only running in 'ticks' (25 ticks make
 * up a delta, which is 200ns), and wrapping around at the end of each cycle.
 * The schedule engine is started when the PTP घड़ी reaches the PTPSCHTM समय
 * (in PTP करोमुख्य).
 * Because the PTP घड़ी can be rate-corrected (accelerated or slowed करोwn) by
 * a software servo, and the schedule engine घड़ी runs in parallel to the PTP
 * घड़ी, there is logic पूर्णांकernal to the चयन that periodically keeps the
 * schedule engine from drअगरting away. The frequency with which this पूर्णांकernal
 * syntonization happens is the PTP घड़ी correction period (PTPCLKCORP). It is
 * a value also in the PTP घड़ी करोमुख्य, and is also rate-corrected.
 * To be precise, during a correction period, there is logic to determine by
 * how many scheduler घड़ी ticks has the PTP घड़ी drअगरted. At the end of each
 * correction period/beginning of new one, the length of a delta is shrunk or
 * expanded with an पूर्णांकeger number of ticks, compared with the typical 25.
 * So a delta lasts क्रम 200ns (or 25 ticks) only on average.
 * Someबार it is दीर्घer, someबार it is लघुer. The पूर्णांकernal syntonization
 * logic can adjust क्रम at most 5 ticks each 20 ticks.
 *
 * The first implication is that you should choose your schedule correction
 * period to be an पूर्णांकeger multiple of the schedule length. Preferably one.
 * In हाल there are schedules of multiple ports active, then the correction
 * period needs to be a multiple of them all. Given the restriction that the
 * cycle बार have to be multiples of one another anyway, this means the
 * correction period can simply be the largest cycle समय, hence the current
 * choice. This way, the updates are always synchronous to the transmission
 * cycle, and thereक्रमe predictable.
 *
 * The second implication is that at the beginning of a correction period, the
 * first few deltas will be modulated in समय, until the schedule engine is
 * properly phase-aligned with the PTP घड़ी. For this reason, you should place
 * your best-efक्रमt traffic at the beginning of a cycle, and your
 * समय-triggered traffic afterwards.
 *
 * The third implication is that once the schedule engine is started, it can
 * only adjust क्रम so much drअगरt within a correction period. In the servo you
 * can only change the PTPCLKRATE, but not step the घड़ी (PTPCLKADD). If you
 * want to करो the latter, you need to stop and restart the schedule engine,
 * which is what the state machine handles.
 */
अटल व्योम sja1105_tas_state_machine(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sja1105_tas_data *tas_data = work_to_sja1105_tas(work);
	काष्ठा sja1105_निजी *priv = tas_to_sja1105(tas_data);
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	काष्ठा बारpec64 base_समय_प्रकारs, now_ts;
	काष्ठा dsa_चयन *ds = priv->ds;
	काष्ठा बारpec64 dअगरf;
	s64 base_समय, now;
	पूर्णांक rc = 0;

	mutex_lock(&ptp_data->lock);

	चयन (tas_data->state) अणु
	हाल SJA1105_TAS_STATE_DISABLED:
		/* Can't करो anything at all अगर घड़ी is still being stepped */
		अगर (tas_data->last_op != SJA1105_PTP_ADJUSTFREQ)
			अवरोध;

		rc = sja1105_tas_adjust_drअगरt(priv, tas_data->max_cycle_समय);
		अगर (rc < 0)
			अवरोध;

		rc = __sja1105_ptp_समय_लोx(ds, &now, शून्य);
		अगर (rc < 0)
			अवरोध;

		/* Plan to start the earliest schedule first. The others
		 * will be started in hardware, by way of their respective
		 * entry poपूर्णांकs delta.
		 * Try our best to aव्योम fringe हालs (race condition between
		 * ptpschपंचांग and ptpstrtsch) by pushing the oper_base_समय at
		 * least one second in the future from now. This is not ideal,
		 * but this only needs to buy us समय until the
		 * sja1105_tas_start command below माला_लो executed.
		 */
		base_समय = future_base_समय(tas_data->earliest_base_समय,
					     tas_data->max_cycle_समय,
					     now + 1ull * NSEC_PER_SEC);
		base_समय -= sja1105_delta_to_ns(1);

		rc = sja1105_tas_set_base_समय(priv, base_समय);
		अगर (rc < 0)
			अवरोध;

		tas_data->oper_base_समय = base_समय;

		rc = sja1105_tas_start(priv);
		अगर (rc < 0)
			अवरोध;

		base_समय_प्रकारs = ns_to_बारpec64(base_समय);
		now_ts = ns_to_बारpec64(now);

		dev_dbg(ds->dev, "OPER base time %lld.%09ld (now %lld.%09ld)\n",
			base_समय_प्रकारs.tv_sec, base_समय_प्रकारs.tv_nsec,
			now_ts.tv_sec, now_ts.tv_nsec);

		अवरोध;

	हाल SJA1105_TAS_STATE_ENABLED_NOT_RUNNING:
		अगर (tas_data->last_op != SJA1105_PTP_ADJUSTFREQ) अणु
			/* Clock was stepped.. bad news क्रम TAS */
			sja1105_tas_stop(priv);
			अवरोध;
		पूर्ण

		/* Check अगर TAS has actually started, by comparing the
		 * scheduled start समय with the SJA1105 PTP घड़ी
		 */
		rc = __sja1105_ptp_समय_लोx(ds, &now, शून्य);
		अगर (rc < 0)
			अवरोध;

		अगर (now < tas_data->oper_base_समय) अणु
			/* TAS has not started yet */
			dअगरf = ns_to_बारpec64(tas_data->oper_base_समय - now);
			dev_dbg(ds->dev, "time to start: [%lld.%09ld]",
				dअगरf.tv_sec, dअगरf.tv_nsec);
			अवरोध;
		पूर्ण

		/* Time elapsed, what happened? */
		rc = sja1105_tas_check_running(priv);
		अगर (rc < 0)
			अवरोध;

		अगर (tas_data->state != SJA1105_TAS_STATE_RUNNING)
			/* TAS has started */
			dev_err(ds->dev,
				"TAS not started despite time elapsed\n");

		अवरोध;

	हाल SJA1105_TAS_STATE_RUNNING:
		/* Clock was stepped.. bad news क्रम TAS */
		अगर (tas_data->last_op != SJA1105_PTP_ADJUSTFREQ) अणु
			sja1105_tas_stop(priv);
			अवरोध;
		पूर्ण

		rc = sja1105_tas_check_running(priv);
		अगर (rc < 0)
			अवरोध;

		अगर (tas_data->state != SJA1105_TAS_STATE_RUNNING)
			dev_err(ds->dev, "TAS surprisingly stopped\n");

		अवरोध;

	शेष:
		अगर (net_ratelimit())
			dev_err(ds->dev, "TAS in an invalid state (incorrect use of API)!\n");
	पूर्ण

	अगर (rc && net_ratelimit())
		dev_err(ds->dev, "An operation returned %d\n", rc);

	mutex_unlock(&ptp_data->lock);
पूर्ण

व्योम sja1105_tas_घड़ीstep(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;

	अगर (!tas_data->enabled)
		वापस;

	tas_data->last_op = SJA1105_PTP_CLOCKSTEP;
	schedule_work(&tas_data->tas_work);
पूर्ण

व्योम sja1105_tas_adjfreq(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;

	अगर (!tas_data->enabled)
		वापस;

	/* No reason to schedule the workqueue, nothing changed */
	अगर (tas_data->state == SJA1105_TAS_STATE_RUNNING)
		वापस;

	tas_data->last_op = SJA1105_PTP_ADJUSTFREQ;
	schedule_work(&tas_data->tas_work);
पूर्ण

व्योम sja1105_tas_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_tas_data *tas_data = &priv->tas_data;

	INIT_WORK(&tas_data->tas_work, sja1105_tas_state_machine);
	tas_data->state = SJA1105_TAS_STATE_DISABLED;
	tas_data->last_op = SJA1105_PTP_NONE;

	INIT_LIST_HEAD(&tas_data->gating_cfg.entries);
पूर्ण

व्योम sja1105_tas_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा tc_taprio_qopt_offload *offload;
	पूर्णांक port;

	cancel_work_sync(&priv->tas_data.tas_work);

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		offload = priv->tas_data.offload[port];
		अगर (!offload)
			जारी;

		taprio_offload_मुक्त(offload);
	पूर्ण
पूर्ण
