<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित DIM_H
#घोषणा DIM_H

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

/*
 * Number of events between DIM iterations.
 * Causes a moderation of the algorithm run.
 */
#घोषणा DIM_NEVENTS 64

/*
 * Is a dअगरference between values justअगरies taking an action.
 * We consider 10% dअगरference as signअगरicant.
 */
#घोषणा IS_SIGNIFICANT_DIFF(val, ref) \
	(((100UL * असल((val) - (ref))) / (ref)) > 10)

/*
 * Calculate the gap between two values.
 * Take wrap-around and variable size पूर्णांकo consideration.
 */
#घोषणा BIT_GAP(bits, end, start) ((((end) - (start)) + BIT_ULL(bits)) \
		& (BIT_ULL(bits) - 1))

/**
 * काष्ठा dim_cq_moder - Structure क्रम CQ moderation values.
 * Used क्रम communications between DIM and its consumer.
 *
 * @usec: CQ समयr suggestion (by DIM)
 * @pkts: CQ packet counter suggestion (by DIM)
 * @comps: Completion counter
 * @cq_period_mode: CQ period count mode (from CQE/EQE)
 */
काष्ठा dim_cq_moder अणु
	u16 usec;
	u16 pkts;
	u16 comps;
	u8 cq_period_mode;
पूर्ण;

/**
 * काष्ठा dim_sample - Structure क्रम DIM sample data.
 * Used क्रम communications between DIM and its consumer.
 *
 * @समय: Sample बारtamp
 * @pkt_ctr: Number of packets
 * @byte_ctr: Number of bytes
 * @event_ctr: Number of events
 * @comp_ctr: Current completion counter
 */
काष्ठा dim_sample अणु
	kसमय_प्रकार समय;
	u32 pkt_ctr;
	u32 byte_ctr;
	u16 event_ctr;
	u32 comp_ctr;
पूर्ण;

/**
 * काष्ठा dim_stats - Structure क्रम DIM stats.
 * Used क्रम holding current measured rates.
 *
 * @ppms: Packets per msec
 * @bpms: Bytes per msec
 * @epms: Events per msec
 * @cpms: Completions per msec
 * @cpe_ratio: Ratio of completions to events
 */
काष्ठा dim_stats अणु
	पूर्णांक ppms; /* packets per msec */
	पूर्णांक bpms; /* bytes per msec */
	पूर्णांक epms; /* events per msec */
	पूर्णांक cpms; /* completions per msec */
	पूर्णांक cpe_ratio; /* ratio of completions to events */
पूर्ण;

/**
 * काष्ठा dim - Main काष्ठाure क्रम dynamic पूर्णांकerrupt moderation (DIM).
 * Used क्रम holding all inक्रमmation about a specअगरic DIM instance.
 *
 * @state: Algorithm state (see below)
 * @prev_stats: Measured rates from previous iteration (क्रम comparison)
 * @start_sample: Sampled data at start of current iteration
 * @measuring_sample: A &dim_sample that is used to update the current events
 * @work: Work to perक्रमm on action required
 * @priv: A poपूर्णांकer to the काष्ठा that poपूर्णांकs to dim
 * @profile_ix: Current moderation profile
 * @mode: CQ period count mode
 * @tune_state: Algorithm tuning state (see below)
 * @steps_right: Number of steps taken towards higher moderation
 * @steps_left: Number of steps taken towards lower moderation
 * @tired: Parking depth counter
 */
काष्ठा dim अणु
	u8 state;
	काष्ठा dim_stats prev_stats;
	काष्ठा dim_sample start_sample;
	काष्ठा dim_sample measuring_sample;
	काष्ठा work_काष्ठा work;
	व्योम *priv;
	u8 profile_ix;
	u8 mode;
	u8 tune_state;
	u8 steps_right;
	u8 steps_left;
	u8 tired;
पूर्ण;

/**
 * क्रमागत dim_cq_period_mode - Modes क्रम CQ period count
 *
 * @DIM_CQ_PERIOD_MODE_START_FROM_EQE: Start counting from EQE
 * @DIM_CQ_PERIOD_MODE_START_FROM_CQE: Start counting from CQE (implies समयr reset)
 * @DIM_CQ_PERIOD_NUM_MODES: Number of modes
 */
क्रमागत dim_cq_period_mode अणु
	DIM_CQ_PERIOD_MODE_START_FROM_EQE = 0x0,
	DIM_CQ_PERIOD_MODE_START_FROM_CQE = 0x1,
	DIM_CQ_PERIOD_NUM_MODES
पूर्ण;

/**
 * क्रमागत dim_state - DIM algorithm states
 *
 * These will determine अगर the algorithm is in a valid state to start an iteration.
 *
 * @DIM_START_MEASURE: This is the first iteration (also after applying a new profile)
 * @DIM_MEASURE_IN_PROGRESS: Algorithm is alपढ़ोy in progress - check अगर
 * need to perक्रमm an action
 * @DIM_APPLY_NEW_PROखाता: DIM consumer is currently applying a profile - no need to measure
 */
क्रमागत dim_state अणु
	DIM_START_MEASURE,
	DIM_MEASURE_IN_PROGRESS,
	DIM_APPLY_NEW_PROखाता,
पूर्ण;

/**
 * क्रमागत dim_tune_state - DIM algorithm tune states
 *
 * These will determine which action the algorithm should perक्रमm.
 *
 * @DIM_PARKING_ON_TOP: Algorithm found a local top poपूर्णांक - निकास on signअगरicant dअगरference
 * @DIM_PARKING_TIRED: Algorithm found a deep top poपूर्णांक - करोn't निकास अगर tired > 0
 * @DIM_GOING_RIGHT: Algorithm is currently trying higher moderation levels
 * @DIM_GOING_LEFT: Algorithm is currently trying lower moderation levels
 */
क्रमागत dim_tune_state अणु
	DIM_PARKING_ON_TOP,
	DIM_PARKING_TIRED,
	DIM_GOING_RIGHT,
	DIM_GOING_LEFT,
पूर्ण;

/**
 * क्रमागत dim_stats_state - DIM algorithm statistics states
 *
 * These will determine the verdict of current iteration.
 *
 * @DIM_STATS_WORSE: Current iteration shows worse perक्रमmance than beक्रमe
 * @DIM_STATS_SAME:  Current iteration shows same perक्रमmance than beक्रमe
 * @DIM_STATS_BETTER: Current iteration shows better perक्रमmance than beक्रमe
 */
क्रमागत dim_stats_state अणु
	DIM_STATS_WORSE,
	DIM_STATS_SAME,
	DIM_STATS_BETTER,
पूर्ण;

/**
 * क्रमागत dim_step_result - DIM algorithm step results
 *
 * These describe the result of a step.
 *
 * @DIM_STEPPED: Perक्रमmed a regular step
 * @DIM_TOO_TIRED: Same kind of step was करोne multiple बार - should go to
 * tired parking
 * @DIM_ON_EDGE: Stepped to the most left/right profile
 */
क्रमागत dim_step_result अणु
	DIM_STEPPED,
	DIM_TOO_TIRED,
	DIM_ON_EDGE,
पूर्ण;

/**
 *	dim_on_top - check अगर current state is a good place to stop (top location)
 *	@dim: DIM context
 *
 * Check अगर current profile is a good place to park at.
 * This will result in reducing the DIM checks frequency as we assume we
 * shouldn't probably change profiles, unless traffic pattern wasn't changed.
 */
bool dim_on_top(काष्ठा dim *dim);

/**
 *	dim_turn - change profile altering direction
 *	@dim: DIM context
 *
 * Go left अगर we were going right and vice-versa.
 * Do nothing अगर currently parking.
 */
व्योम dim_turn(काष्ठा dim *dim);

/**
 *	dim_park_on_top - enter a parking state on a top location
 *	@dim: DIM context
 *
 * Enter parking state.
 * Clear all movement history.
 */
व्योम dim_park_on_top(काष्ठा dim *dim);

/**
 *	dim_park_tired - enter a tired parking state
 *	@dim: DIM context
 *
 * Enter parking state.
 * Clear all movement history and cause DIM checks frequency to reduce.
 */
व्योम dim_park_tired(काष्ठा dim *dim);

/**
 *	dim_calc_stats - calculate the dअगरference between two samples
 *	@start: start sample
 *	@end: end sample
 *	@curr_stats: delta between samples
 *
 * Calculate the delta between two samples (in data rates).
 * Takes पूर्णांकo consideration counter wrap-around.
 */
व्योम dim_calc_stats(काष्ठा dim_sample *start, काष्ठा dim_sample *end,
		    काष्ठा dim_stats *curr_stats);

/**
 *	dim_update_sample - set a sample's fields with given values
 *	@event_ctr: number of events to set
 *	@packets: number of packets to set
 *	@bytes: number of bytes to set
 *	@s: DIM sample
 */
अटल अंतरभूत व्योम
dim_update_sample(u16 event_ctr, u64 packets, u64 bytes, काष्ठा dim_sample *s)
अणु
	s->समय	     = kसमय_get();
	s->pkt_ctr   = packets;
	s->byte_ctr  = bytes;
	s->event_ctr = event_ctr;
पूर्ण

/**
 *	dim_update_sample_with_comps - set a sample's fields with given
 *	values including the completion parameter
 *	@event_ctr: number of events to set
 *	@packets: number of packets to set
 *	@bytes: number of bytes to set
 *	@comps: number of completions to set
 *	@s: DIM sample
 */
अटल अंतरभूत व्योम
dim_update_sample_with_comps(u16 event_ctr, u64 packets, u64 bytes, u64 comps,
			     काष्ठा dim_sample *s)
अणु
	dim_update_sample(event_ctr, packets, bytes, s);
	s->comp_ctr = comps;
पूर्ण

/* Net DIM */

/**
 *	net_dim_get_rx_moderation - provide a CQ moderation object क्रम the given RX profile
 *	@cq_period_mode: CQ period mode
 *	@ix: Profile index
 */
काष्ठा dim_cq_moder net_dim_get_rx_moderation(u8 cq_period_mode, पूर्णांक ix);

/**
 *	net_dim_get_def_rx_moderation - provide the शेष RX moderation
 *	@cq_period_mode: CQ period mode
 */
काष्ठा dim_cq_moder net_dim_get_def_rx_moderation(u8 cq_period_mode);

/**
 *	net_dim_get_tx_moderation - provide a CQ moderation object क्रम the given TX profile
 *	@cq_period_mode: CQ period mode
 *	@ix: Profile index
 */
काष्ठा dim_cq_moder net_dim_get_tx_moderation(u8 cq_period_mode, पूर्णांक ix);

/**
 *	net_dim_get_def_tx_moderation - provide the शेष TX moderation
 *	@cq_period_mode: CQ period mode
 */
काष्ठा dim_cq_moder net_dim_get_def_tx_moderation(u8 cq_period_mode);

/**
 *	net_dim - मुख्य DIM algorithm entry poपूर्णांक
 *	@dim: DIM instance inक्रमmation
 *	@end_sample: Current data measurement
 *
 * Called by the consumer.
 * This is the मुख्य logic of the algorithm, where data is processed in order
 * to decide on next required action.
 */
व्योम net_dim(काष्ठा dim *dim, काष्ठा dim_sample end_sample);

/* RDMA DIM */

/*
 * RDMA DIM profile:
 * profile size must be of RDMA_DIM_PARAMS_NUM_PROखाताS.
 */
#घोषणा RDMA_DIM_PARAMS_NUM_PROखाताS 9
#घोषणा RDMA_DIM_START_PROखाता 0

/**
 * rdma_dim - Runs the adaptive moderation.
 * @dim: The moderation काष्ठा.
 * @completions: The number of completions collected in this round.
 *
 * Each call to rdma_dim takes the latest amount of completions that
 * have been collected and counts them as a new event.
 * Once enough events have been collected the algorithm decides a new
 * moderation level.
 */
व्योम rdma_dim(काष्ठा dim *dim, u64 completions);

#पूर्ण_अगर /* DIM_H */
