<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A घातer allocator to manage temperature
 *
 * Copyright (C) 2014 ARM Ltd.
 *
 */

#घोषणा pr_fmt(fmt) "Power allocator: " fmt

#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/thermal_घातer_allocator.h>

#समावेश "thermal_core.h"

#घोषणा INVALID_TRIP -1

#घोषणा FRAC_BITS 10
#घोषणा पूर्णांक_to_frac(x) ((x) << FRAC_BITS)
#घोषणा frac_to_पूर्णांक(x) ((x) >> FRAC_BITS)

/**
 * mul_frac() - multiply two fixed-poपूर्णांक numbers
 * @x:	first multiplicand
 * @y:	second multiplicand
 *
 * Return: the result of multiplying two fixed-poपूर्णांक numbers.  The
 * result is also a fixed-poपूर्णांक number.
 */
अटल अंतरभूत s64 mul_frac(s64 x, s64 y)
अणु
	वापस (x * y) >> FRAC_BITS;
पूर्ण

/**
 * भाग_frac() - भागide two fixed-poपूर्णांक numbers
 * @x:	the भागidend
 * @y:	the भागisor
 *
 * Return: the result of भागiding two fixed-poपूर्णांक numbers.  The
 * result is also a fixed-poपूर्णांक number.
 */
अटल अंतरभूत s64 भाग_frac(s64 x, s64 y)
अणु
	वापस भाग_s64(x << FRAC_BITS, y);
पूर्ण

/**
 * काष्ठा घातer_allocator_params - parameters क्रम the घातer allocator governor
 * @allocated_tzp:	whether we have allocated tzp क्रम this thermal zone and
 *			it needs to be मुक्तd on unbind
 * @err_पूर्णांकegral:	accumulated error in the PID controller.
 * @prev_err:	error in the previous iteration of the PID controller.
 *		Used to calculate the derivative term.
 * @trip_चयन_on:	first passive trip poपूर्णांक of the thermal zone.  The
 *			governor चयनes on when this trip poपूर्णांक is crossed.
 *			If the thermal zone only has one passive trip poपूर्णांक,
 *			@trip_चयन_on should be INVALID_TRIP.
 * @trip_max_desired_temperature:	last passive trip poपूर्णांक of the thermal
 *					zone.  The temperature we are
 *					controlling क्रम.
 * @sustainable_घातer:	Sustainable घातer (heat) that this thermal zone can
 *			dissipate
 */
काष्ठा घातer_allocator_params अणु
	bool allocated_tzp;
	s64 err_पूर्णांकegral;
	s32 prev_err;
	पूर्णांक trip_चयन_on;
	पूर्णांक trip_max_desired_temperature;
	u32 sustainable_घातer;
पूर्ण;

/**
 * estimate_sustainable_घातer() - Estimate the sustainable घातer of a thermal zone
 * @tz: thermal zone we are operating in
 *
 * For thermal zones that करोn't provide a sustainable_घातer in their
 * thermal_zone_params, estimate one.  Calculate it using the minimum
 * घातer of all the cooling devices as that gives a valid value that
 * can give some degree of functionality.  For optimal perक्रमmance of
 * this governor, provide a sustainable_घातer in the thermal zone's
 * thermal_zone_params.
 */
अटल u32 estimate_sustainable_घातer(काष्ठा thermal_zone_device *tz)
अणु
	u32 sustainable_घातer = 0;
	काष्ठा thermal_instance *instance;
	काष्ठा घातer_allocator_params *params = tz->governor_data;

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		काष्ठा thermal_cooling_device *cdev = instance->cdev;
		u32 min_घातer;

		अगर (instance->trip != params->trip_max_desired_temperature)
			जारी;

		अगर (!cdev_is_घातer_actor(cdev))
			जारी;

		अगर (cdev->ops->state2घातer(cdev, instance->upper, &min_घातer))
			जारी;

		sustainable_घातer += min_घातer;
	पूर्ण

	वापस sustainable_घातer;
पूर्ण

/**
 * estimate_pid_स्थिरants() - Estimate the स्थिरants क्रम the PID controller
 * @tz:		thermal zone क्रम which to estimate the स्थिरants
 * @sustainable_घातer:	sustainable घातer क्रम the thermal zone
 * @trip_चयन_on:	trip poपूर्णांक number क्रम the चयन on temperature
 * @control_temp:	target temperature क्रम the घातer allocator governor
 *
 * This function is used to update the estimation of the PID
 * controller स्थिरants in काष्ठा thermal_zone_parameters.
 */
अटल व्योम estimate_pid_स्थिरants(काष्ठा thermal_zone_device *tz,
				   u32 sustainable_घातer, पूर्णांक trip_चयन_on,
				   पूर्णांक control_temp)
अणु
	पूर्णांक ret;
	पूर्णांक चयन_on_temp;
	u32 temperature_threshold;
	s32 k_i;

	ret = tz->ops->get_trip_temp(tz, trip_चयन_on, &चयन_on_temp);
	अगर (ret)
		चयन_on_temp = 0;

	temperature_threshold = control_temp - चयन_on_temp;
	/*
	 * estimate_pid_स्थिरants() tries to find appropriate शेष
	 * values क्रम thermal zones that करोn't provide them. If a
	 * प्रणाली पूर्णांकegrator has configured a thermal zone with two
	 * passive trip poपूर्णांकs at the same temperature, that person
	 * hasn't put any efक्रमt to set up the thermal zone properly
	 * so just give up.
	 */
	अगर (!temperature_threshold)
		वापस;

	tz->tzp->k_po = पूर्णांक_to_frac(sustainable_घातer) /
		temperature_threshold;

	tz->tzp->k_pu = पूर्णांक_to_frac(2 * sustainable_घातer) /
		temperature_threshold;

	k_i = tz->tzp->k_pu / 10;
	tz->tzp->k_i = k_i > 0 ? k_i : 1;

	/*
	 * The शेष क्रम k_d and पूर्णांकegral_cutoff is 0, so we can
	 * leave them as they are.
	 */
पूर्ण

/**
 * get_sustainable_घातer() - Get the right sustainable घातer
 * @tz:		thermal zone क्रम which to estimate the स्थिरants
 * @params:	parameters क्रम the घातer allocator governor
 * @control_temp:	target temperature क्रम the घातer allocator governor
 *
 * This function is used क्रम getting the proper sustainable घातer value based
 * on variables which might be updated by the user sysfs पूर्णांकerface. If that
 * happen the new value is going to be estimated and updated. It is also used
 * after thermal zone binding, where the initial values where set to 0.
 */
अटल u32 get_sustainable_घातer(काष्ठा thermal_zone_device *tz,
				 काष्ठा घातer_allocator_params *params,
				 पूर्णांक control_temp)
अणु
	u32 sustainable_घातer;

	अगर (!tz->tzp->sustainable_घातer)
		sustainable_घातer = estimate_sustainable_घातer(tz);
	अन्यथा
		sustainable_घातer = tz->tzp->sustainable_घातer;

	/* Check अगर it's init value 0 or there was update via sysfs */
	अगर (sustainable_घातer != params->sustainable_घातer) अणु
		estimate_pid_स्थिरants(tz, sustainable_घातer,
				       params->trip_चयन_on, control_temp);

		/* Do the estimation only once and make available in sysfs */
		tz->tzp->sustainable_घातer = sustainable_घातer;
		params->sustainable_घातer = sustainable_घातer;
	पूर्ण

	वापस sustainable_घातer;
पूर्ण

/**
 * pid_controller() - PID controller
 * @tz:	thermal zone we are operating in
 * @control_temp:	the target temperature in millicelsius
 * @max_allocatable_घातer:	maximum allocatable घातer क्रम this thermal zone
 *
 * This PID controller increases the available घातer budget so that the
 * temperature of the thermal zone माला_लो as बंद as possible to
 * @control_temp and limits the घातer अगर it exceeds it.  k_po is the
 * proportional term when we are overshooting, k_pu is the
 * proportional term when we are undershooting.  पूर्णांकegral_cutoff is a
 * threshold below which we stop accumulating the error.  The
 * accumulated error is only valid अगर the requested घातer will make
 * the प्रणाली warmer.  If the प्रणाली is mostly idle, there's no poपूर्णांक
 * in accumulating positive error.
 *
 * Return: The घातer budget क्रम the next period.
 */
अटल u32 pid_controller(काष्ठा thermal_zone_device *tz,
			  पूर्णांक control_temp,
			  u32 max_allocatable_घातer)
अणु
	s64 p, i, d, घातer_range;
	s32 err, max_घातer_frac;
	u32 sustainable_घातer;
	काष्ठा घातer_allocator_params *params = tz->governor_data;

	max_घातer_frac = पूर्णांक_to_frac(max_allocatable_घातer);

	sustainable_घातer = get_sustainable_घातer(tz, params, control_temp);

	err = control_temp - tz->temperature;
	err = पूर्णांक_to_frac(err);

	/* Calculate the proportional term */
	p = mul_frac(err < 0 ? tz->tzp->k_po : tz->tzp->k_pu, err);

	/*
	 * Calculate the पूर्णांकegral term
	 *
	 * अगर the error is less than cut off allow पूर्णांकegration (but
	 * the पूर्णांकegral is limited to max घातer)
	 */
	i = mul_frac(tz->tzp->k_i, params->err_पूर्णांकegral);

	अगर (err < पूर्णांक_to_frac(tz->tzp->पूर्णांकegral_cutoff)) अणु
		s64 i_next = i + mul_frac(tz->tzp->k_i, err);

		अगर (असल(i_next) < max_घातer_frac) अणु
			i = i_next;
			params->err_पूर्णांकegral += err;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the derivative term
	 *
	 * We करो err - prev_err, so with a positive k_d, a decreasing
	 * error (i.e. driving बंदr to the line) results in less
	 * घातer being applied, slowing करोwn the controller)
	 */
	d = mul_frac(tz->tzp->k_d, err - params->prev_err);
	d = भाग_frac(d, jअगरfies_to_msecs(tz->passive_delay_jअगरfies));
	params->prev_err = err;

	घातer_range = p + i + d;

	/* feed-क्रमward the known sustainable dissipatable घातer */
	घातer_range = sustainable_घातer + frac_to_पूर्णांक(घातer_range);

	घातer_range = clamp(घातer_range, (s64)0, (s64)max_allocatable_घातer);

	trace_thermal_घातer_allocator_pid(tz, frac_to_पूर्णांक(err),
					  frac_to_पूर्णांक(params->err_पूर्णांकegral),
					  frac_to_पूर्णांक(p), frac_to_पूर्णांक(i),
					  frac_to_पूर्णांक(d), घातer_range);

	वापस घातer_range;
पूर्ण

/**
 * घातer_actor_set_घातer() - limit the maximum घातer a cooling device consumes
 * @cdev:	poपूर्णांकer to &thermal_cooling_device
 * @instance:	thermal instance to update
 * @घातer:	the घातer in milliwatts
 *
 * Set the cooling device to consume at most @घातer milliwatts. The limit is
 * expected to be a cap at the maximum घातer consumption.
 *
 * Return: 0 on success, -EINVAL अगर the cooling device करोes not
 * implement the घातer actor API or -E* क्रम other failures.
 */
अटल पूर्णांक
घातer_actor_set_घातer(काष्ठा thermal_cooling_device *cdev,
		      काष्ठा thermal_instance *instance, u32 घातer)
अणु
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = cdev->ops->घातer2state(cdev, घातer, &state);
	अगर (ret)
		वापस ret;

	instance->target = clamp_val(state, instance->lower, instance->upper);
	mutex_lock(&cdev->lock);
	__thermal_cdev_update(cdev);
	mutex_unlock(&cdev->lock);

	वापस 0;
पूर्ण

/**
 * भागvy_up_घातer() - भागvy the allocated घातer between the actors
 * @req_घातer:	each actor's requested घातer
 * @max_घातer:	each actor's maximum available घातer
 * @num_actors:	size of the @req_घातer, @max_घातer and @granted_घातer's array
 * @total_req_घातer: sum of @req_घातer
 * @घातer_range:	total allocated घातer
 * @granted_घातer:	output array: each actor's granted घातer
 * @extra_actor_घातer:	an appropriately sized array to be used in the
 *			function as temporary storage of the extra घातer given
 *			to the actors
 *
 * This function भागides the total allocated घातer (@घातer_range)
 * fairly between the actors.  It first tries to give each actor a
 * share of the @घातer_range according to how much घातer it requested
 * compared to the rest of the actors.  For example, अगर only one actor
 * requests घातer, then it receives all the @घातer_range.  If
 * three actors each requests 1mW, each receives a third of the
 * @घातer_range.
 *
 * If any actor received more than their maximum घातer, then that
 * surplus is re-भागvied among the actors based on how far they are
 * from their respective maximums.
 *
 * Granted घातer क्रम each actor is written to @granted_घातer, which
 * should've been allocated by the calling function.
 */
अटल व्योम भागvy_up_घातer(u32 *req_घातer, u32 *max_घातer, पूर्णांक num_actors,
			   u32 total_req_घातer, u32 घातer_range,
			   u32 *granted_घातer, u32 *extra_actor_घातer)
अणु
	u32 extra_घातer, capped_extra_घातer;
	पूर्णांक i;

	/*
	 * Prevent भागision by 0 अगर none of the actors request घातer.
	 */
	अगर (!total_req_घातer)
		total_req_घातer = 1;

	capped_extra_घातer = 0;
	extra_घातer = 0;
	क्रम (i = 0; i < num_actors; i++) अणु
		u64 req_range = (u64)req_घातer[i] * घातer_range;

		granted_घातer[i] = DIV_ROUND_CLOSEST_ULL(req_range,
							 total_req_घातer);

		अगर (granted_घातer[i] > max_घातer[i]) अणु
			extra_घातer += granted_घातer[i] - max_घातer[i];
			granted_घातer[i] = max_घातer[i];
		पूर्ण

		extra_actor_घातer[i] = max_घातer[i] - granted_घातer[i];
		capped_extra_घातer += extra_actor_घातer[i];
	पूर्ण

	अगर (!extra_घातer)
		वापस;

	/*
	 * Re-भागvy the reclaimed extra among actors based on
	 * how far they are from the max
	 */
	extra_घातer = min(extra_घातer, capped_extra_घातer);
	अगर (capped_extra_घातer > 0)
		क्रम (i = 0; i < num_actors; i++) अणु
			u64 extra_range = (u64)extra_actor_घातer[i] * extra_घातer;
			granted_घातer[i] += DIV_ROUND_CLOSEST_ULL(extra_range,
							 capped_extra_घातer);
		पूर्ण
पूर्ण

अटल पूर्णांक allocate_घातer(काष्ठा thermal_zone_device *tz,
			  पूर्णांक control_temp)
अणु
	काष्ठा thermal_instance *instance;
	काष्ठा घातer_allocator_params *params = tz->governor_data;
	u32 *req_घातer, *max_घातer, *granted_घातer, *extra_actor_घातer;
	u32 *weighted_req_घातer;
	u32 total_req_घातer, max_allocatable_घातer, total_weighted_req_घातer;
	u32 total_granted_घातer, घातer_range;
	पूर्णांक i, num_actors, total_weight, ret = 0;
	पूर्णांक trip_max_desired_temperature = params->trip_max_desired_temperature;

	mutex_lock(&tz->lock);

	num_actors = 0;
	total_weight = 0;
	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर ((instance->trip == trip_max_desired_temperature) &&
		    cdev_is_घातer_actor(instance->cdev)) अणु
			num_actors++;
			total_weight += instance->weight;
		पूर्ण
	पूर्ण

	अगर (!num_actors) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	/*
	 * We need to allocate five arrays of the same size:
	 * req_घातer, max_घातer, granted_घातer, extra_actor_घातer and
	 * weighted_req_घातer.  They are going to be needed until this
	 * function वापसs.  Allocate them all in one go to simplअगरy
	 * the allocation and deallocation logic.
	 */
	BUILD_BUG_ON(माप(*req_घातer) != माप(*max_घातer));
	BUILD_BUG_ON(माप(*req_घातer) != माप(*granted_घातer));
	BUILD_BUG_ON(माप(*req_घातer) != माप(*extra_actor_घातer));
	BUILD_BUG_ON(माप(*req_घातer) != माप(*weighted_req_घातer));
	req_घातer = kसुस्मृति(num_actors * 5, माप(*req_घातer), GFP_KERNEL);
	अगर (!req_घातer) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	max_घातer = &req_घातer[num_actors];
	granted_घातer = &req_घातer[2 * num_actors];
	extra_actor_घातer = &req_घातer[3 * num_actors];
	weighted_req_घातer = &req_घातer[4 * num_actors];

	i = 0;
	total_weighted_req_घातer = 0;
	total_req_घातer = 0;
	max_allocatable_घातer = 0;

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		पूर्णांक weight;
		काष्ठा thermal_cooling_device *cdev = instance->cdev;

		अगर (instance->trip != trip_max_desired_temperature)
			जारी;

		अगर (!cdev_is_घातer_actor(cdev))
			जारी;

		अगर (cdev->ops->get_requested_घातer(cdev, &req_घातer[i]))
			जारी;

		अगर (!total_weight)
			weight = 1 << FRAC_BITS;
		अन्यथा
			weight = instance->weight;

		weighted_req_घातer[i] = frac_to_पूर्णांक(weight * req_घातer[i]);

		अगर (cdev->ops->state2घातer(cdev, instance->lower,
					   &max_घातer[i]))
			जारी;

		total_req_घातer += req_घातer[i];
		max_allocatable_घातer += max_घातer[i];
		total_weighted_req_घातer += weighted_req_घातer[i];

		i++;
	पूर्ण

	घातer_range = pid_controller(tz, control_temp, max_allocatable_घातer);

	भागvy_up_घातer(weighted_req_घातer, max_घातer, num_actors,
		       total_weighted_req_घातer, घातer_range, granted_घातer,
		       extra_actor_घातer);

	total_granted_घातer = 0;
	i = 0;
	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर (instance->trip != trip_max_desired_temperature)
			जारी;

		अगर (!cdev_is_घातer_actor(instance->cdev))
			जारी;

		घातer_actor_set_घातer(instance->cdev, instance,
				      granted_घातer[i]);
		total_granted_घातer += granted_घातer[i];

		i++;
	पूर्ण

	trace_thermal_घातer_allocator(tz, req_घातer, total_req_घातer,
				      granted_घातer, total_granted_घातer,
				      num_actors, घातer_range,
				      max_allocatable_घातer, tz->temperature,
				      control_temp - tz->temperature);

	kमुक्त(req_घातer);
unlock:
	mutex_unlock(&tz->lock);

	वापस ret;
पूर्ण

/**
 * get_governor_trips() - get the number of the two trip poपूर्णांकs that are key क्रम this governor
 * @tz:	thermal zone to operate on
 * @params:	poपूर्णांकer to निजी data क्रम this governor
 *
 * The घातer allocator governor works optimally with two trips poपूर्णांकs:
 * a "switch on" trip poपूर्णांक and a "maximum desired temperature".  These
 * are defined as the first and last passive trip poपूर्णांकs.
 *
 * If there is only one trip poपूर्णांक, then that's considered to be the
 * "maximum desired temperature" trip poपूर्णांक and the governor is always
 * on.  If there are no passive or active trip poपूर्णांकs, then the
 * governor won't करो anything.  In fact, its throttle function
 * won't be called at all.
 */
अटल व्योम get_governor_trips(काष्ठा thermal_zone_device *tz,
			       काष्ठा घातer_allocator_params *params)
अणु
	पूर्णांक i, last_active, last_passive;
	bool found_first_passive;

	found_first_passive = false;
	last_active = INVALID_TRIP;
	last_passive = INVALID_TRIP;

	क्रम (i = 0; i < tz->trips; i++) अणु
		क्रमागत thermal_trip_type type;
		पूर्णांक ret;

		ret = tz->ops->get_trip_type(tz, i, &type);
		अगर (ret) अणु
			dev_warn(&tz->device,
				 "Failed to get trip point %d type: %d\n", i,
				 ret);
			जारी;
		पूर्ण

		अगर (type == THERMAL_TRIP_PASSIVE) अणु
			अगर (!found_first_passive) अणु
				params->trip_चयन_on = i;
				found_first_passive = true;
			पूर्ण अन्यथा  अणु
				last_passive = i;
			पूर्ण
		पूर्ण अन्यथा अगर (type == THERMAL_TRIP_ACTIVE) अणु
			last_active = i;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (last_passive != INVALID_TRIP) अणु
		params->trip_max_desired_temperature = last_passive;
	पूर्ण अन्यथा अगर (found_first_passive) अणु
		params->trip_max_desired_temperature = params->trip_चयन_on;
		params->trip_चयन_on = INVALID_TRIP;
	पूर्ण अन्यथा अणु
		params->trip_चयन_on = INVALID_TRIP;
		params->trip_max_desired_temperature = last_active;
	पूर्ण
पूर्ण

अटल व्योम reset_pid_controller(काष्ठा घातer_allocator_params *params)
अणु
	params->err_पूर्णांकegral = 0;
	params->prev_err = 0;
पूर्ण

अटल व्योम allow_maximum_घातer(काष्ठा thermal_zone_device *tz, bool update)
अणु
	काष्ठा thermal_instance *instance;
	काष्ठा घातer_allocator_params *params = tz->governor_data;
	u32 req_घातer;

	mutex_lock(&tz->lock);
	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		काष्ठा thermal_cooling_device *cdev = instance->cdev;

		अगर ((instance->trip != params->trip_max_desired_temperature) ||
		    (!cdev_is_घातer_actor(instance->cdev)))
			जारी;

		instance->target = 0;
		mutex_lock(&instance->cdev->lock);
		/*
		 * Call क्रम updating the cooling devices local stats and aव्योम
		 * periods of करोzen of seconds when those have not been
		 * मुख्यtained.
		 */
		cdev->ops->get_requested_घातer(cdev, &req_घातer);

		अगर (update)
			__thermal_cdev_update(instance->cdev);

		mutex_unlock(&instance->cdev->lock);
	पूर्ण
	mutex_unlock(&tz->lock);
पूर्ण

/**
 * check_घातer_actors() - Check all cooling devices and warn when they are
 *			not घातer actors
 * @tz:		thermal zone to operate on
 *
 * Check all cooling devices in the @tz and warn every समय they are missing
 * घातer actor API. The warning should help to investigate the issue, which
 * could be e.g. lack of Energy Model क्रम a given device.
 *
 * Return: 0 on success, -EINVAL अगर any cooling device करोes not implement
 * the घातer actor API.
 */
अटल पूर्णांक check_घातer_actors(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_instance *instance;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर (!cdev_is_घातer_actor(instance->cdev)) अणु
			dev_warn(&tz->device, "power_allocator: %s is not a power actor\n",
				 instance->cdev->type);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * घातer_allocator_bind() - bind the घातer_allocator governor to a thermal zone
 * @tz:	thermal zone to bind it to
 *
 * Initialize the PID controller parameters and bind it to the thermal
 * zone.
 *
 * Return: 0 on success, or -ENOMEM अगर we ran out of memory, or -EINVAL
 * when there are unsupported cooling devices in the @tz.
 */
अटल पूर्णांक घातer_allocator_bind(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक ret;
	काष्ठा घातer_allocator_params *params;
	पूर्णांक control_temp;

	ret = check_घातer_actors(tz);
	अगर (ret)
		वापस ret;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	अगर (!tz->tzp) अणु
		tz->tzp = kzalloc(माप(*tz->tzp), GFP_KERNEL);
		अगर (!tz->tzp) अणु
			ret = -ENOMEM;
			जाओ मुक्त_params;
		पूर्ण

		params->allocated_tzp = true;
	पूर्ण

	अगर (!tz->tzp->sustainable_घातer)
		dev_warn(&tz->device, "power_allocator: sustainable_power will be estimated\n");

	get_governor_trips(tz, params);

	अगर (tz->trips > 0) अणु
		ret = tz->ops->get_trip_temp(tz,
					params->trip_max_desired_temperature,
					&control_temp);
		अगर (!ret)
			estimate_pid_स्थिरants(tz, tz->tzp->sustainable_घातer,
					       params->trip_चयन_on,
					       control_temp);
	पूर्ण

	reset_pid_controller(params);

	tz->governor_data = params;

	वापस 0;

मुक्त_params:
	kमुक्त(params);

	वापस ret;
पूर्ण

अटल व्योम घातer_allocator_unbind(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा घातer_allocator_params *params = tz->governor_data;

	dev_dbg(&tz->device, "Unbinding from thermal zone %d\n", tz->id);

	अगर (params->allocated_tzp) अणु
		kमुक्त(tz->tzp);
		tz->tzp = शून्य;
	पूर्ण

	kमुक्त(tz->governor_data);
	tz->governor_data = शून्य;
पूर्ण

अटल पूर्णांक घातer_allocator_throttle(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	पूर्णांक ret;
	पूर्णांक चयन_on_temp, control_temp;
	काष्ठा घातer_allocator_params *params = tz->governor_data;
	bool update;

	/*
	 * We get called क्रम every trip poपूर्णांक but we only need to करो
	 * our calculations once
	 */
	अगर (trip != params->trip_max_desired_temperature)
		वापस 0;

	ret = tz->ops->get_trip_temp(tz, params->trip_चयन_on,
				     &चयन_on_temp);
	अगर (!ret && (tz->temperature < चयन_on_temp)) अणु
		update = (tz->last_temperature >= चयन_on_temp);
		tz->passive = 0;
		reset_pid_controller(params);
		allow_maximum_घातer(tz, update);
		वापस 0;
	पूर्ण

	tz->passive = 1;

	ret = tz->ops->get_trip_temp(tz, params->trip_max_desired_temperature,
				&control_temp);
	अगर (ret) अणु
		dev_warn(&tz->device,
			 "Failed to get the maximum desired temperature: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	वापस allocate_घातer(tz, control_temp);
पूर्ण

अटल काष्ठा thermal_governor thermal_gov_घातer_allocator = अणु
	.name		= "power_allocator",
	.bind_to_tz	= घातer_allocator_bind,
	.unbind_from_tz	= घातer_allocator_unbind,
	.throttle	= घातer_allocator_throttle,
पूर्ण;
THERMAL_GOVERNOR_DECLARE(thermal_gov_घातer_allocator);
